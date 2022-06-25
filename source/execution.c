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
    if (gen->envp != NULL)
    {
        while (gen->envp[i] != NULL)
        {
            free(gen->envp[i]);
            i++;
        }
        free(gen->envp);
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
   if (!(ft_strcmp(built_in, "echo") && ft_strcmp(built_in, "cd") 
            && ft_strcmp(built_in, "env") && ft_strcmp(built_in, "exit") 
            && ft_strcmp(built_in, "export") && ft_strcmp(built_in, "pwd") 
            && ft_strcmp(built_in, "unset")))
                go_commands(cmds[i].cmd_args);
    else if (cmds[i].exec)
    {
        free_envp();
        gen->envp = convert_to_array(&gen->env);
        execve(cmds[i].cmd_path, cmds[i].cmd_args, gen->envp);
        perror("execve : ");
    }
    exit(0);
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

void    execution(t_cmd *cmds, int pipes_num)
{
    int i;
    int pid;
    int **pipes;
    char *built_in;
    int in;
    int out;

    i = 0;
    // printf("---> %s\n", built_in);
    if (cmds->exec)
        built_in = str_to_lower(cmds[i].cmd_args[0]);
    else
        built_in = ft_strdup("");
    pipes = creat_pipes(pipes_num);
    assign_pipes(pipes, &cmds, pipes_num); 
    if (pipes_num == 0 && !(ft_strcmp(built_in, "echo") && ft_strcmp(built_in, "cd") 
        && ft_strcmp(built_in, "env") && ft_strcmp(built_in, "exit") 
        && ft_strcmp(built_in, "export") && ft_strcmp(built_in, "pwd") 
        && ft_strcmp(built_in, "unset")))
        {
            printf("got here1\n");
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
        printf("got here2\n");
        while (i <= pipes_num)
        {
            pid = fork();
            if (pid == -1)
                perror("fork : ");
            if (pid == 0)
            {
                execut(cmds, pipes, pipes_num, i);
            }
            i++;
        }
    }
    close_pipes(pipes, pipes_num);
    free_cmds(cmds, pipes_num);
	free_pipes(pipes, pipes_num);
    while (waitpid(-1, &(gen->exit_status), 0) != -1)
    ;
}