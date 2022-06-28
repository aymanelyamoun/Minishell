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

void    free_envp()
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
	char    *built_in;

	built_in = str_to_lower(cmds[i].cmd_args[0]);
	dup2(cmds[i].infile, STDIN_FILENO);
	dup2(cmds[i].outfile, STDOUT_FILENO);
	close_pipes(pipes, pipes_num);
	if (cmds[i].infile != STDIN_FILENO)
		close(cmds[i].infile);
	if (cmds[i].outfile != STDOUT_FILENO)
		close(cmds[i].outfile);
	if ((cmds[i].exec == 0) && is_buit_in(cmds[i].cmd_args[0]))
		go_commands(cmds[i].cmd_args);
	else if (cmds[i].exec == 0)
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
	j = 0;
	if (cmds == NULL)
	{
		while (i <= pipes_num)
		{
			if (cmds->cmd_args != NULL)
			{
				while (cmds->cmd_args[j] != NULL)
				{
					free(cmds->cmd_args[j]);
					j++;
				}
				if (cmds->cmd_path != NULL)
					free(cmds->cmd_path);
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
		return (0);
	else
		return (1);
}

void    execution(t_cmd *cmds, int pipes_num)
{
	int i;
	int pid;
	int **pipes;
	char *built_in;
	int in;
	int out;
	int status;

	i = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pipes = creat_pipes(pipes_num);
	assign_pipes(pipes, &cmds, pipes_num);

	if (cmds[i].exec == 0 && pipes_num == 0 && is_buit_in(cmds[i].cmd_args[0]))
		{
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
	else
	{
		while (i <= pipes_num)
		{
			
			pid = fork();
			if (pid == -1)
				perror("fork : ");
			if (pid == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				execut(cmds, pipes, pipes_num, i);
			}
		
			i++;
		}
		close_pipes(pipes, pipes_num);
		free_cmds(cmds, pipes_num);
		free_pipes(pipes, pipes_num);
		if (i == pipes_num)
			waitpid(pid, &status, 0);
		while (waitpid(-1, 0, 0) != -1)
			;
		gen.exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			// printf("%d", WTERMSIG(status));
			if (WTERMSIG(status) == 3)
				printf("Quit: 3\n");
			gen.exit_status = 128 + WTERMSIG(status);
		}
	}
	signal(SIGQUIT, handler);
	signal(SIGINT, handler);
}
