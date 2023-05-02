/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 13:18:29 by mbaanni           #+#    #+#             */
/*   Updated: 2023/04/30 19:54:27 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_lent(char *s, char c, int *i)
{
	int	lent;

	lent = 0;
	while (s[*i] && s[*i] == c)
		*i = *i + 1;
	while (s[*i] && s[*i] != c)
	{
		*i = *i + 1;
		lent++;
	}
	return (lent);
}

static int	split_it(char **new, char *str, char c, int count)
{
	int	i;
	int	index;
	int	lent;
	int	j;

	index = 0;
	i = 0;
	while (i < count)
	{
		j = 0;
		lent = ft_lent(str, c, &index);
		new[i] = (char *)malloc(sizeof(char) * (lent + 1));
		if (!new[i])
			return (0);
		while (j < lent)
		{
			new[i][j] = str[index - lent + j];
			j++;
		}
		new[i][j] = 0;
		i++;
	}
	new[i] = 0;
	return (1);
}

static int	word_count(char *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] == c)
		i++;
	if (s[i] == '\0')
		return (0);
	while (s[i])
	{
		i++;
		if (s[i] == c)
		{
			while (s[i] && s[i] == c)
				i++;
			if (s[i])
				count++;
		}
	}
	return (count + 1);
}

char	**ft_split(char const *s, char c)
{
	char	**new_str;
	int		count;

	if (!s)
		return (0);
	count = word_count((char *)s, c);
	new_str = (char **)malloc(sizeof(char *) * (count + 1));
	if (!new_str)
		return (0);
	if (split_it(new_str, (char *)s, c, count))
		return (new_str);
	free(new_str);
	return (0);
}
