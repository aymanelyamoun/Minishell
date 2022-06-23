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
	write(fd, "\n", 1);
}

int heredoc(char *limiter)
{
    char	*line;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		exit(3);
    line = readline("> ");
    while (line != NULL && ft_strcmp(line, limiter))
    {
        write_to_fd(pipe_fd[1], line);
		free(line);
    	line = readline("> ");
    }
	if (line != NULL)
		free(line);
	if (limiter)
		free(limiter);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}