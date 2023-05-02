/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:52:34 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/02 22:33:52 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(char *s1, char *s2, int j)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) - j != ft_strlen(s2))
		return (0);
	while (s1[i] && s1[i] != '\n' && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int	set_file(char *str)
{
	int	fd[2];

	if (pipe(fd))
		return (-1);
	write(fd[1], str, ft_strlen(str));
	free(str);
	close(fd[1]);
	return (fd[0]);
}

int	here_doc(char **av, int ac, int *fl)
{
	char	*buf;
	char	*str;

	str = 0;
	if (ft_strcmp(av[1], "here_doc", 0))
		arg_number(ac - 1);
	else
		return (-2);
	while (1)
	{
		write(1, "heredoc> ", 10);
		buf = get_next_line(0);
		if (buf)
		{
			if (ft_strcmp(buf, av[2], 1))
			{
				free(buf);
				break ;
			}
			str = ft_strjoin(str, buf);
			free(buf);
		}
	}
	*fl = 1;
	return (set_file(str));
}
