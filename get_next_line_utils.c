/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:56:23 by mbaanni           #+#    #+#             */
/*   Updated: 2023/04/30 19:57:33 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*f_calloc(int i, int size)
{
	char	*ptr;

	ptr = malloc(size * i);
	if (!ptr)
		return (0);
	*ptr = 0;
	return (ptr);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *buf, char *str)
{
	char	*newline;
	int		i;
	int		j;

	i = 0;
	if (!buf)
		buf = f_calloc(1, sizeof(char));
	if (!buf)
		return (0);
	newline = malloc(sizeof(char) * (ft_strlen(buf) + ft_strlen(str) + 1));
	if (!newline)
		return (0);
	while (buf != 0 && buf[i])
	{
		newline[i] = buf[i];
		i++;
	}
	j = 0;
	while (str[j])
		newline[i++] = str[j++];
	newline[i] = 0;
	free(buf);
	return (newline);
}

int	ft_strchr(char *buf)
{
	int	i;

	i = 0;
	if (buf == 0)
		return (1);
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}
