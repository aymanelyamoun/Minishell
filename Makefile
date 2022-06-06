# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ael-yamo <ael-yamo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/24 17:24:53 by yel-mrab          #+#    #+#              #
#    Updated: 2022/06/03 21:19:53 by ael-yamo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
NAME = minishell
DIRBUILD = objdir
INC  = -I ./includes
HEADERS = includes/minishell.h
LIBFT = includes/libft/libft.a
SRC = main cmd_managment list_manupulation token builtins/ft_exit builtins/ft_env builtins/ft_echo syntax_analyzer error_free expantion signals enviroment builtins/ft_pwd
OBJ = $(addprefix $(DIRBUILD)/, $(SRC:=.o))
all : $(NAME)
$(NAME) : $(OBJ) $(LIBFT)
	@gcc $^ -o $(NAME) -lreadline $(LDFLAGS)  $(LIBFT) 
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
	@gcc  $(INC) $(CPPFLAGS) -c $< -o $@
clean :
	@rm -rf $(DIRBUILD)
	@make clean -C includes/libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C includes/libft
	@echo "\033[0;95m Everything is fcleaned in minishell!\033[m"

re : fclean all

.PHONY : re fclean clean all