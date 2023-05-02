/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:05:36 by mbaanni           #+#    #+#             */
/*   Updated: 2023/04/30 15:16:12 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	next_cout(char *av, int i)
{
	int		j;
	char	c;

	c = av[i];
	j = i + 1;
	while (av[j])
	{
		if (av[j] == c)
		{
			while (av[j + 1] && av[j + 1] != ' ')
				j++;
			break ;
		}
		j++;
	}
	if (av[j])
		i = j;
	return (i);
}

void	count_word_in_cout(char *av, int *i, int *j, int *word)
{
	if (av[*i] && (av[*i] == '"' || av[*i] == '\''))
	{
		*j = next_cout(av, *i);
		if (*i != *j)
		{
			if (*i - 1 >= 0 && av[*i - 1] != ' ' && av[*i - 1] != '\'' && av[*i
					- 1] != '"')
				(*word)++;
			*i = *j;
			if (av[*i + 1] && av[*i + 1] != ' ')
				(*word)++;
			(*i)++;
		}
		else
			(*i)++;
	}
}
