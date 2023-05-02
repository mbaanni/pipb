# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/06 08:51:16 by mbaanni           #+#    #+#              #
#    Updated: 2023/04/28 20:38:47 by mbaanni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG= -Wall -Wextra -Werror
CC=cc
BSRC= pipexb.c ft_split.c f_calloc.c get_next_line.c get_next_line_utils.c ft_error.c\
check_path.c skip_cout.c check_script.c new_split.c here_doc.c new_split_utils.c
SRC= pipex.c ft_split.c f_calloc.c ft_strjoin.c ft_strlen.c new_split_utils.c\
check_path.c skip_cout.c check_script.c new_split.c ft_error.c
OBG= $(SRC:.c=.o)
BOBG= $(BSRC:.c=.o)
BNAME=pipexbonus
NAME=pipex

all : $(NAME)

bonus : $(BNAME)

$(NAME) : $(OBG)
	$(CC) $(FLAG) $(OBG) -o $(NAME)
$(OBG) : $(SRC)
	$(CC) $(FLAG)  -c $(SRC)
$(BNAME) : $(BOBG)
	$(CC) $(FLAG) $(BOBG) -o $(BNAME)
clean :
	rm -rf *.o
fclean : clean
	rm -rf $(NAME) $(BNAME)
re : fclean all
.PHONY: all clean fclean bonus re