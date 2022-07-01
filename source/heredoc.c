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
	char	*str;
	int		i;
	char	*final_quote;
	char	*tmp;

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
	free(line);
	return (final_quote);
}

void	handler1(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

int	expand_y_n(char **str)
{
	char c;

	c = (*str)[0];
	if ((*str)[0] != '\0' && ((*str)[0] == '\'' || (*str)[0] == '\"'))
	{
		*str = rm_quotes(*str, c);
		return (0);
	}
	return (1);
}

void	wait_heredoc(int *exit_status, int pid)
{
	int	status;

	waitpid(pid, &status, 0);
	signal(SIGINT, handler);
	*exit_status = WEXITSTATUS(status);
	gen.skip_all = *exit_status;
	gen.exit_status = gen.skip_all;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			*exit_status = 1;
	}
}

int	heredoc_p(char *limiter, int *pipe_fd)
{
	int		expand;
	char	*line;

	expand = expand_y_n(&limiter);
	signal(SIGINT, handler1);
	printf("::%s\n", limiter);
	line = readline("> ");
	while (line != NULL && ft_strcmp(line, limiter))
	{
		if (expand)
			line = expander_heredoc(line);
		write_to_fd(pipe_fd[1], line);
		free(line);
		line = readline("> ");
	}
	if (line != NULL)
		free(line);
	exit (0);
}

int heredoc(char *limiter, int *exit_status)
{
	char	*line;
	int		pipe_fd[2];
	int		pid;
	int		status;
	int		expand;

	if (pipe(pipe_fd) < 0)
	{
		perror("");
		return (-1);
	}
	sig_ign();
	pid = fork();
	if (pid == 0)
	{
		heredoc_p(limiter, pipe_fd);
	}
	if (limiter != NULL)
		free(limiter);
	wait_heredoc(exit_status, pid);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}