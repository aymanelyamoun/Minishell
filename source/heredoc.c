#include "../includes/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

void	write_to_fd(int fd, char *str)
{
	int	status;

	status = write(fd, str, ft_strlen(str));
}

int heredoc(char *limiter)
{
    char	*line;
	int		fd;

	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC);
    line = readline("> ");
    while (line != NULL && ft_strcmp(line, limiter))
    {
        write_to_fd(fd, line);
		// free(line);
    	line = readline("> ");
    }
	if (line != NULL)
		free(line);
	if (limiter)
		free(limiter);
	puts("hoi");
	return (fd);
}