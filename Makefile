# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 17:24:53 by yel-mrab          #+#    #+#              #
#    Updated: 2022/05/16 16:00:21 by oufisaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = $(CPPFLAGS) -Wall -Wextra -Werror
NAME = minishell
SRC = main
DIRBUILD = objdir
INC  = -I ./includes
HEADERS = includes/minishell.h
#APPEND BUILD/ TO EVERY OBJECT
OBJ = $(addprefix $(DIRBUILD)/, $(SRC:=.o))
all : $(NAME)
$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $^ -o $(NAME)
$(DIRBUILD)/%.o : source/%.c $(HEADERS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :
	rm -rf $(DIRBUILD)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : re fclean clean all