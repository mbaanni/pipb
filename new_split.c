/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 22:25:17 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/03 19:04:02 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	count_word_in_cout_alloc(t_data *data, char **new, int *i, int *t)
{
	while (data->av[*i] && data->av[*i] == ' ')
		(*i)++;
	if (!data->av[*i])
		fill_spaced_str(data, new, *i);
	if (data->av[*i] && (data->av[*i] == '"' || data->av[*i] == '\''))
	{
		data->c = data->av[*i];
		data->j = next_cout(data->av, *i);
		*t = 0;
		if (*i != data->j)
		{
			(*i)++;
			new[data->k] = ft_calloc(sizeof(char) * (data->j - *i + 1));
			while (*i < data->j)
			{
				fill_new_string(data, new, t, i);
			}
			if (data->av[*i])
				(*i)++;
			new[data->k][*t] = 0;
			data->k++;
		}
	}
}

void	allocate_new_str_fill(t_data *data, char **new, int *t, int *i)
{
	data->j = 0;
	if (*t != *i)
	{
		new[data->k] = ft_calloc(sizeof(char) * (*t - *i + 1));
		while (*i < *t)
		{
			new[data->k][data->j] = data->av[*i];
			(*i)++;
			data->j++;
		}
		if (data->j)
		{
			new[data->k][data->j] = 0;
				data->k++;
		}
	}
}

void	fill_new(char *av, char **new)
{
	t_data	data;
	int		i;
	int		t;

	data.j = 0;
	i = 0;
	data.k = 0;
	data.av = av;
	while (av[i])
	{
		count_word_in_cout_alloc(&data, new, &i, &t);
		t = i;
		while (av[t] && av[t] != ' ')
		{
			if (av[t] == '"' || av[t] == '\'')
			{
				data.j = next_cout(av, t);
				if (t != data.j)
					break ;
			}
			t++;
		}
		allocate_new_str_fill(&data, new, &t, &i);
	}
}

int	word_count(char *av, int word)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[i] && av[i] == ' ')
			i++;
	if (!av[i])
		word++;
	while (av[i])
	{
		if (av[i] == ' ')
		{
			while (av[i] && av[i] == ' ')
				i++;
			word++;
		}
		count_word_in_cout(av, &i, &j, &word);
		if (av[i] && av[i] != ' ' && av[i] != '"' && av[i] != '\'')
			i++;
	}
	if ((i - 1 > 0 && av[i - 1] != ' ') || (i == 1 && !av[1] && av[0] != ' '))
		word++;
	return (word);
}

char	**new_split(char *av)
{
	int		word;
	char	**new;

	word = word_count(av, 0);
	if (!word)
		return (0);
	new = ft_calloc(sizeof(char *) * (word + 1));
	if (!new)
		return (0);
	fill_new(av, new);
	return (new);
}
