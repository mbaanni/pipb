/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:48:46 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/02 20:08:22 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	command_1(t_pipes *pipes, char **av, char **envp)
{
	char	**argu;
	char	*bin;

	pipes->id = fork();
	fork_error(pipes->id, 0);
	if (pipes->id == 0)
	{
		close(pipes->pp[0]);
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
	close(pipes->pp[1]);
	return (pipes->pp[0]);
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
	pipes.fd[0] = open(av[1], O_RDONLY);
	pipes.fd[1] = open(av[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (pipes.fd[0] < 0 || pipes.fd[1] < 0 || pipe(pipes.pp) == -1)
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
