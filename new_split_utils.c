/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:05:36 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/03 19:00:18 by mbaanni          ###   ########.fr       */
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
			if (av[j] && av[j] != c && av[j] != ' ')
				j++;
			break ;
		}
		j++;
	}
	return (j);
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

void	fill_spaced_str(t_data *data, char **new, int i)
{
	int	j;

	j = 0;
	if (data->k)
		return ;
	new[data->k] = ft_calloc(sizeof(char) * (i + 1));
	while (j < i)
	{
		new[data->k][j] = data->av[j];
		j++;
	}
	new[data->k][j] = 0;
	data->k++;
}

void	fill_new_string(t_data *data, char **new, int *t, int *i)
{
	if (data->av[*i] && data->av[*i] == data->c)
		(*i)++;
	else
	{
		new[data->k][*t] = data->av[*i];
		(*t)++;
		(*i)++;
	}
}
