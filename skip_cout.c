/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_cout.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 09:57:09 by mbaanni           #+#    #+#             */
/*   Updated: 2023/04/12 22:25:24 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	scan_cout(char *argu, int i)
{
	int	lent;

	lent = ft_strlen(argu);
	if (argu[i] == '\"' && argu[lent - i] == '\"')
		return (1);
	return (0);
}

char	*del_cout(char *arg, int start, int end)
{
	int		i;
	int		j;
	char	*new;

	i = -1;
	j = -1;
	new = ft_calloc(sizeof(char) * ft_strlen(arg) - 2);
	if (!new)
		return (0);
	while (arg[++i])
	{
		if (i != start && i != end)
			new[++j] = arg[i];
	}
	free(arg);
	new[++j] = 0;
	return (new);
}

void	skip_cout(char **arg)
{
	int	i;
	int	j;
	int	lent;

	i = -1;
	while (arg[++i])
	{
		j = -1;
		lent = ft_strlen(arg[i]) - 1;
		while (arg[i][++j])
		{
			if (scan_cout(arg[i], j))
				break ;
			if (arg[i][j] == '\'' && arg[i][lent - j] == '\'')
			{
				arg[i] = del_cout(arg[i], j, lent - j);
				lent -= 2;
				j = -1;
			}
		}
	}
}
