/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 07:56:44 by mbaanni           #+#    #+#             */
/*   Updated: 2023/04/12 23:10:34 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *buf, char *str)
{
	char	*newline;
	int		i;
	int		j;

	i = 0;
	if (!buf)
		buf = ft_calloc(1);
	if (!buf)
		return (0);
	newline = malloc(sizeof(char) * (ft_strlen(buf) + ft_strlen(str) + 1));
	if (!newline)
		return (0);
	while (buf[i])
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
