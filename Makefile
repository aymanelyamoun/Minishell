# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 17:24:53 by yel-mrab          #+#    #+#              #
#    Updated: 2022/06/01 22:24:08 by oufisaou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror 
NAME = minishell
DIRBUILD = objdir
INC  = -I ./includes
HEADERS = includes/minishell.h
LIBFT = includes/libft/libft.a
SRC = main list_manupulation token syntax_ana error_free signals
OBJ = $(addprefix $(DIRBUILD)/, $(SRC:=.o))
all : $(NAME)
$(NAME) : $(OBJ) $(LIBFT)
	@gcc $(CFLAGS) $^ -o $(NAME) -lreadline  $(LIBFT) 
	@echo "MINISHELL────▒▒▒▒▒▒▒▒"
	@echo "─────────▒▒▒──────▒▒▒"
	@echo "──BY────▒▒───▒▒▒▒──▒░▒"
	@echo "───────▒▒───▒▒──▒▒──▒░▒"
	@echo "Oufisaou▒▒░▒──────▒▒──▒░▒"
	@echo "──────▒▒░▒────▒▒──▒░▒"
	@echo "──&──────▒▒▒▒▒▒▒───▒▒"
	@echo "Ael-yamo───────────▒▒▒"
	@echo "─────▒▒▒▒────────▒▒"
	@echo "───▒▒▒░░▒▒▒─────▒▒──▓▓▓▓▓▓▓▓"
	@echo "──▒▒─────▒▒▒────▒▒▓▓▓▓▓░░░░░▓▓──▓▓▓▓"
	@echo "─▒───▒▒────▒▒─▓▓▒░░░░░░░░░█▓▒▓▓▓▓░░▓▓▓"
	@echo "▒▒──▒─▒▒───▓▒▒░░▒░░░░░████▓▓▒▒▓░░░░░░▓▓"
	@echo "░▒▒───▒──▓▓▓░▒░░░░░░█████▓▓▒▒▒▒▓▓▓▓▓░░▓▓"
	@echo "──▒▒▒▒──▓▓░░░░░░███████▓▓▓▒▒▒▒▒▓───▓▓░▓▓"
	@echo "──────▓▓░░░░░░███████▓▓▓▒▒▒▒▒▒▒▓───▓░░▓▓"
	@echo "─────▓▓░░░░░███████▓▓▓▒▒▒▒▒▒▒▒▒▓▓▓▓░░▓▓"
	@echo "────▓▓░░░░██████▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▓░░░░▓▓"
	@echo "────▓▓▓░████▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓"
	@echo "─────▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓"
	@echo "─────▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓"
	@echo "──────▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓"
	@echo "───────▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓"
	@echo "─────────▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓"
	@echo "───────────▓▓▓▓▓▓▒▒▒▒▒▓▓▓▓"
	@echo "───────────────▓▓▓▓▓▓▓▓"
	@echo "\033[0;95m The Compilation of minishell is done! Shall we begin? \033[m"

$(LIBFT) :
	@make -C includes/libft
	
$(DIRBUILD)/%.o : source/%.c $(HEADERS)
	@mkdir -p $(@D)
	@gcc  $(CFLAGS) $(INC) -I /goinfre/oufisaou/.brew/opt/readline/include -c $< -o $@
clean :
	@rm -rf $(DIRBUILD)
	@make clean -C includes/libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C includes/libft
	@echo "\033[0;95m Everything is fcleaned in minishell!\033[m"

re : fclean all

.PHONY : re fclean clean all