#include "../includes/minishell.h"

void    close_cmd_files(t_cmd *cmds, int count)
{
	int i;

	i = 0;
	while (i <= count)
	{
		close(cmds[i].infile);
		close(cmds[i].outfile);
		i++;
	}
}

void    free_envp(void)
{
	int i;

	i = 0;
	if (gen.envp != NULL)
	{
		while (gen.envp[i] != NULL)
		{
			free(gen.envp[i]);
			i++;
		}
		free(gen.envp);
	}
}

char    *str_to_lower(char *str)
{
	char    *new_str;
	int     i;

	i = 0;
	if (str != NULL)
	{
		new_str = malloc(sizeof(char) * ft_strlen(str) + 1);
		while (str[i] != '\0')
		{
			new_str[i] = ft_tolower(str[i]);
			i++;
		}
		new_str[i] = '\0';
		return (new_str);
	}
	return (NULL);
}

void    execut(t_cmd *cmds, int **pipes, int pipes_num, int i)
{
	dup2(cmds[i].infile, STDIN_FILENO);
	dup2(cmds[i].outfile, STDOUT_FILENO);
	close_pipes(pipes, pipes_num);
	if (cmds[i].infile != STDIN_FILENO)
		close(cmds[i].infile);
	if (cmds[i].outfile != STDOUT_FILENO)
		close(cmds[i].outfile);
	if ((cmds[i].exec == 0) && is_buit_in(cmds[i].cmd_args[0]))
		go_commands(cmds[i].cmd_args);
	else if (cmds[i].exec == 0 && gen.exec == 0)
	{
		free_envp();
		gen.envp = convert_to_array(&gen.env);
		execve(cmds[i].cmd_path, cmds[i].cmd_args, gen.envp);
		perror("execve : ");
	}
	exit(cmds[i].exec);
}

void    free_cmds(t_cmd *cmds, int pipes_num)
{
	int	i;
	int	j;

	i = 0;
	if (cmds != NULL)
	{
		while (i <= pipes_num)
		{
			j = 0;
			if (cmds[i].cmd_args != NULL)
			{
				while (cmds[i].cmd_args[j] != NULL)
				{
					free(cmds[i].cmd_args[j]);
					j++;
				}
				free(cmds[i].cmd_args);
			}
			if (cmds[i].cmd_path != NULL)
			{
				free(cmds[i].cmd_path);
			}
			i++;
		}
		free(cmds);
	}
}

int is_buit_in(char *cmd)
{
	char *built_in;


	if (cmd == NULL)
		return (0);
	built_in = str_to_lower(cmd);
	if ((ft_strcmp(built_in, "echo") && ft_strcmp(built_in, "cd") 
		&& ft_strcmp(built_in, "env") && ft_strcmp(built_in, "exit") 
		&& ft_strcmp(built_in, "export") && ft_strcmp(built_in, "pwd") 
		&& ft_strcmp(built_in, "unset")))
		{
			free(built_in);
			return (0);
		}
	else
	{
		free(built_in);
		return (1);
	}
}

void	exec_built_in(t_cmd *cmds, int i)
{
	int	in;
	int	out;

	in = dup(STDIN_FILENO);
	out = dup(STDOUT_FILENO);
	dup2(cmds[i].infile, STDIN_FILENO);
	dup2(cmds[i].outfile, STDOUT_FILENO);
	go_commands(cmds[i].cmd_args);
	close(cmds[i].infile);
	close(cmds[i].outfile);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
}

void	sig_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_handler(void)
{
	signal(SIGQUIT, handler);
	signal(SIGINT, handler);
}
int		run_cmd(t_cmd *cmds, int **pipes, int pipes_num, int *i)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("fork : ");
	if (pid == 0)
	{
		sig_dfl();
		execut(cmds, pipes, pipes_num, *i);
	}
	(*i)++;
	return (pid);
}

void	wait_all(int pid, int i, int pipes_num)
{
	int	status;

	if (i == pipes_num + 1)
	{
		waitpid(pid, &status, 0);
	}
	while (waitpid(-1, 0, 0) != -1)
		;
	gen.exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			printf("Quit: 3\n");
		gen.exit_status = 128 + WTERMSIG(status);
	}
}

void    execution(t_cmd *cmds, int pipes_num)
{
	int i;
	int pid;
	int **pipes;
	char *built_in;

	i = 0;
	pipes = creat_pipes(pipes_num);
	assign_pipes(pipes, &cmds, pipes_num);
	sig_ign();
	if (cmds[i].exec == 0 && pipes_num == 0 && is_buit_in(cmds[i].cmd_args[0]))
		exec_built_in(cmds, i);
	else
	{
		while (i <= pipes_num)
			pid = run_cmd(cmds, pipes, pipes_num, &i);
		close_pipes(pipes, pipes_num);
		wait_all(pid, i, pipes_num);
	}
	free_pipes(pipes, pipes_num);
	sig_handler();
}
