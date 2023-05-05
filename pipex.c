/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:48:46 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/03 19:23:34 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_and_check_error(char *name, int flag)
{
	int	fd;

	if (flag == 0)
	{
		fd = open(name, O_RDONLY);
	}
	else
		fd = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
	{
		write(2, "pipex: ", 7);
		write(2, name, ft_strlen(name));
		write(2, ": ", 2);
		perror(0);
	}
	return (fd);
}

int	command_1(t_pipes *pipes, char **av, char **envp)
{
	char	**argu;
	char	*bin;

	pipes->id = fork();
	fork_error(pipes->id, 0);
	if (pipes->id == 0)
	{
		close(pipes->pp[0]);
		if (pipes->fd[0] < 0)
			exit(1);
		dup2(pipes->fd[0], 0);
		dup2(pipes->pp[1], 1);
		argu = new_split(av[2]);
		bin = check_path(*argu, envp);
		if (access(bin, F_OK) != 0)
			exit(ft_error(bin, argu));
		if (execve(bin, argu, envp))
			perror("pipex");
		if (argu)
			free_2d(argu);
		if (bin)
			free(bin);
		exit(13);
	}
	return (close(pipes->pp[1]), pipes->pp[0]);
}

void	command_2(t_pipes *pipes, char **av, char **envp, int prev)
{
	char	**argu;
	char	*bin;

	pipes->id2 = fork();
	fork_error(pipes->id2, 0);
	if (pipes->id2 == 0)
	{
		dup2(prev, 0);
		dup2(pipes->fd[1], 1);
		if (pipes->fd[1] < 0)
			exit(1);
		argu = new_split(av[3]);
		bin = check_path(*argu, envp);
		if (access(bin, F_OK) != 0)
			exit(ft_error(bin, argu));
		if (execve(bin, argu, envp))
			perror("pipex");
		if (argu)
			free_2d(argu);
		if (bin)
			free(bin);
		exit(13);
	}
	close(prev);
	close(pipes->fd[1]);
}

int	main(int ac, char **av, char **envp)
{
	t_pipes	pipes;
	int		st;
	int		prev;

	st = 0;
	if (ac != 5)
	{
		write(1, "Invalid number of arg\n", 23);
		return (1);
	}
	pipes.fd[0] = open_and_check_error(av[1], 0);
	pipes.fd[1] = open_and_check_error(av[4], 1);
	if (pipe(pipes.pp) == -1)
	{
		perror("pipex");
		return (1);
	}
	prev = command_1(&pipes, av, envp);
	command_2(&pipes, av, envp, prev);
	waitpid(pipes.id, &st, 0);
	waitpid(pipes.id2, &st, 0);
	return (st >> 8 & 255);
}
