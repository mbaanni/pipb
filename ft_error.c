/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 16:35:14 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/02 22:33:09 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_error(char *bin, char **argu)
{
	int	len;

	len = ft_strlen(bin);
	write(2, "pipex: command not found: ", 26);
	if (len)
		write(2, bin, len);
	write(2, "\n", 1);
	if (argu)
		free_2d(argu);
	if (bin)
		free(bin);
	return (127);
}

void	arg_number(int ac)
{
	if (ac < 5)
	{
		write(1, "Invalid number of arg\n", 23);
		exit (1);
	}
}

void	fork_error(int id, int *idadrress)
{
	if (id == -1)
	{
		if (idadrress != 0)
			free(idadrress);
		perror("pipex");
		exit (1);
	}
}

void	free_2d(char **argu)
{
	int	i;

	i = 0;
	while (argu[i])
	{
		if (!argu[i])
			free(argu[i]);
		i++;
	}
	free(argu[i]);
	free(argu);
}

void	check_pipe_err(int nb, int *id)
{
	if (nb == -1)
	{
		if (id)
			free(id);
		perror("pipex");
		exit(1);
	}
}
