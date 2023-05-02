/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_script.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 23:11:34 by mbaanni           #+#    #+#             */
/*   Updated: 2023/04/12 23:12:58 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_script(char *arg)
{
	int	i;

	i = ft_strlen(arg);
	if (i < 3)
		return (0);
	i--;
	if (arg[i] == 'h' && arg[i - 1] == 's' && arg[i - 2] == '.')
		return (1);
	return (0);
}