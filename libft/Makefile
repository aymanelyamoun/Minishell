NAME	=	libft.a
FLAGS	= -Wall -Wextra -Werror
CC	=	gcc

SOURCE	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
		  ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
		  ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c  ft_calloc.c ft_toupper.c ft_tolower.c

OBJ	=	$(SOURCE:.c=.o)

SO_BONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstdelone.c

BO_OBJ = $(SO_BONUS:.c=.o)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

$(NAME): $(OBJ)
	ar	-rcs $(NAME) $(OBJ)

bonus:	$(BO_OBJ)
	ar -rcs $(NAME) $(BO_OBJ)

clean:
	rm	-f	$(OBJ) $(BO_OBJ)

fclean:	clean
	rm -f	$(NAME)

re: fclean	all

.PHONY: all clean fclean re 
