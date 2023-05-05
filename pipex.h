/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:45:34 by mbaanni           #+#    #+#             */
/*   Updated: 2023/05/03 12:22:13 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include<unistd.h>
# include<stdlib.h>
# include"get_next_line.h"
# include<fcntl.h>
# include<sys/wait.h>
# include<stdio.h>

typedef struct t_pipes
{
	int		id;
	int		fl;
	int		id2;
	int		prev;
	int		fd[2];
	int		pp[2];
	char	**envp;
	char	**av;
}t_pipes;

typedef struct t_data
{
	char	*av;
	int		j;
	int		k;
	char	c;
}t_data;

char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t size);
char	*ft_strjoin(char *buf, char *str);
int		ft_strlen(char *str);
void	fork_error(int id, int *idadress);
char	*check_path(char *str, char **env);
void	skip_cout(char **arg);
int		next_cout(char *av, int i);
int		check_script(char *arg);
char	**new_split(char *av);
void	count_word_in_cout(char *av, int *i, int *j, int *word);
int		here_doc(char **av, int ac, int *fl);
int		check_script(char *arg);
void	fill_spaced_str(t_data *data, char **new, int i);
void	fill_new_string(t_data *data, char **new, int *t, int *i);
int		ft_strpcmp(char *s1, char *s2);
int		ft_error(char *bin, char **argu);
int		ft_strcmp(char *s1, char *s2, int j);
void	arg_number(int ac);
void	check_pipe_err(int nb, int *id);
void	free_2d(char **argu);
char	**new_split(char *av);
#endif
