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

char	*expander_heredoc(char *line)
{
	char *str;
	int i;
	char *final_quote;
	char *tmp;

	str = line;
	i = 0;
	final_quote = ft_strdup("");
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			tmp = ft_substr(str, 0, i);
			final_quote = join(final_quote, tmp);
			str = str + i;
			final_quote = get_var(&str, final_quote, gen.env);
			i = -1;
		}
		i++;
	}
	tmp = ft_substr(str, 0, i);
	final_quote = join(final_quote, tmp);
	return (final_quote);
}
void    handler1(int sig)
{
    if(sig == SIGINT)
    {
		
   		exit(1);
    }
}
int heredoc(char *limiter, int *exit_status)
{
    char	*line;
	int		pipe_fd[2];
	int		pid;
	int		status;

	if (pipe(pipe_fd) < 0)
	{
		perror("");
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
    {
		signal(SIGINT, handler1);
		line = readline("> ");
		// ft_putchar_fd('1', 1);
		while (line != NULL && ft_strcmp(line, limiter))
		{
			line = expander_heredoc(line);
			write_to_fd(pipe_fd[1], line);
			free(line);
			line = readline("> ");
		}
		if (line != NULL)
			free(line);
		if (limiter != NULL)
			free(limiter);
		exit (0);
	}
	waitpid(pid, &status, 0);
	signal(SIGINT, handler);
	*exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			*exit_status = 1;
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}