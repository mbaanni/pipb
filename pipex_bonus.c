/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:48:46 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/02 22:34:20 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipe_redirection(t_pipes *pipes, int i, int fl, int ac)
{
	if (i == 0)
	{
		close(pipes->pp[0]);
		if (pipes->fd[0] < 0)
			return (1);
		dup2(pipes->fd[0], 0);
		dup2(pipes->pp[1], 1);
	}
	else
	{
		if (i < ac - 4 - fl)
		{
			close(pipes->pp[0]);
			dup2(pipes->prev, 0);
			dup2(pipes->pp[1], 1);
			return (0);
		}
		close(pipes->pp[1]);
		dup2(pipes->prev, 0);
		if (pipes->fd[1] < 0)
			return (1);
		dup2(pipes->fd[1], 1);
	}
	return (0);
}

void	execute_it(t_pipes *pipes, int *id, int fl, int i)
{
	char	**argu;
	char	*bin;

	argu = new_split(pipes->av[i + fl + 2]);
	bin = check_path(*argu, pipes->envp);
	if (access(bin, F_OK) != 0)
	{
		free(id);
		exit(ft_error(bin, argu));
	}
	if (execve(bin, argu, pipes->envp))
		perror("failed");
	free(id);
	if (bin)
		free(bin);
	if (argu)
		free_2d(argu);
	exit(1);
}

int	multiple_command_ex(t_pipes *pipes, int *id, int ac, int fl)
{
	int	i;

	i = -1;
	while (++i < ac - 3 - fl)
	{
		if (i < ac - 4 - fl)
			check_pipe_err(pipe(pipes->pp), id);
		id[i] = fork();
		fork_error(id[i], id);
		if (id[i] == 0)
		{
			if (pipe_redirection(pipes, i, fl, ac))
			{
				free(id);
				exit(1);
			}
			execute_it(pipes, id, fl, i);
		}
		else
		{
			if (i == 0)
				close(pipes->fd[0]);
			close(pipes->pp[1]);
			close(pipes->prev);
			pipes->prev = pipes->pp[0];
		}
	}
	return (i);
}

void	open_files(t_pipes *pipes, int ac)
{
	pipes->fd[0] = here_doc(pipes->av, ac, &pipes->fl);
	if (pipes->fd[0] == -2)
	{
		pipes->fd[0] = open(pipes->av[1], O_RDONLY);
		pipes->fd[1] = open(pipes->av[ac - 1], O_WRONLY | O_TRUNC | O_CREAT,
				0644);
	}
	else
		pipes->fd[1] = open(pipes->av[ac - 1], O_WRONLY | O_APPEND | O_CREAT,
				0644);
	if (pipes->fd[0] < 0 || pipes->fd[1] < 0)
	{
		write(2, "pipex: ", 7);
		if (pipes->fd[0] < 0)
			write(2, pipes->av[1], ft_strlen(pipes->av[1]));
		else
			write(2, pipes->av[ac - 1], ft_strlen(pipes->av[ac - 1]));
		write(2, ": ", 2);
		perror(0);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipes	pipes;
	int		*id;
	int		st;
	int		i;

	st = 0;
	pipes.fl = 0;
	pipes.envp = envp;
	pipes.av = av;
	pipes.prev = 0;
	arg_number(ac);
	open_files(&pipes, ac);
	id = malloc(sizeof(int) * ac);
	if (!id)
		return (1);
	i = multiple_command_ex(&pipes, id, ac, pipes.fl);
	pipes.fl = -1;
	while (++pipes.fl < i)
		waitpid(id[pipes.fl], &st, 0);
	free(id);
	return (st >> 8 & 255);
}
