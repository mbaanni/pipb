/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 11:56:00 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/03 17:12:06 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strpcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && i < 6)
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

char	*find_bin(char **env, char *argu)
{
	int	i;

	i = 0;
	if (argu == 0)
		return (0);
	while (argu[i] && argu[i] == ' ')
		i++;
	if (argu[i] == 0)
		return (0);
	while (*env)
	{
		if (!ft_strpcmp(*env, "PATH=/"))
			return (*env + 5);
		env++;
	}
	return ((void *) -1);
}

char	*check_path(char *argu, char **env)
{
	char	*path_full;
	char	**split_path;
	char	*bin;
	int		i;

	i = 0;
	bin = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki";
	if (!access(argu, F_OK))
		return (argu);
	path_full = find_bin(env, argu);
	if (path_full == (void *)-1)
		path_full = bin;
	split_path = ft_split(path_full, ':');
	while (split_path && split_path[i] && bin != 0)
	{
		bin = ft_strjoin(split_path[i], "/");
		bin = ft_strjoin(bin, argu);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		i++;
	}
	if (split_path)
		free_2d(split_path);
	return (argu);
}
