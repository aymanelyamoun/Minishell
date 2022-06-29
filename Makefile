CC = gcc
NAME = minishell
DIRBUILD = objdir
INC  = -I ./includes
HEADERS = includes/minishell.h
LIBFT = includes/libft/libft.a
SRC = main cmd_managment builtins/go_build in_out_file_managment \
 heredoc signals list_manupulation token execution pipe_management\
  builtins/ft_exit builtins/ft_env builtins/ft_echo\
   syntax_analyzer more_func export_tool suite_syntax builtins/built_tools builtins/built_checks builtins/unset builtins/ft_export error_free expantion signals enviroment builtins/ft_pwd builtins/ft_cd
OBJ = $(addprefix $(DIRBUILD)/, $(SRC:=.o))
OBJ = $(addprefix $(DIRBUILD)/, $(SRC:=.o))
all : $(NAME)
$(NAME) : $(OBJ) $(LIBFT)
	@gcc $^ -o $(NAME) -lreadline -g $(LDFLAGS)  $(LIBFT) 

$(LIBFT) :
	@make -C includes/libft
	
$(DIRBUILD)/%.o : source/%.c $(HEADERS)
	@mkdir -p $(@D)
	@gcc $(INC) $(CPPFLAGS) -c $< -o $@
clean :
	@rm -rf $(DIRBUILD)
	@make clean -C includes/libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C includes/libft
	@echo "\033[0;95m Everything is fcleaned in minishell!\033[m"

re : fclean all

.PHONY : re fclean clean all

#TODO : SHOULD ADD THE 42 FLAGS TO GCC TO MAKE IT WORK , I REMOVED THEM BCAUSE THERE ARE SO MUCH UNUSED VARS IN YOUR PART
#TODO : ADOPT IT IN YOUR MAKEFILE