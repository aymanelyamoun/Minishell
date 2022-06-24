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

void    execution(t_cmd *cmds, int pipes_num)
{
    int i;
    int pid;
    int **pipes;

    i = 0;
    pipes = creat_pipes(pipes_num);
    assign_pipes(pipes, &cmds, pipes_num);
    while (i <= pipes_num)
    {
		// printf("%p\n",  gen.envp);
        pid = fork();
        if (pid == -1)
            perror("fork : ");
        if (pid == 0)
        {
            dup2(cmds[i].infile, STDIN_FILENO);
            dup2(cmds[i].outfile, STDOUT_FILENO);
            close_pipes(pipes, pipes_num);
            // close_cmd_files(cmds, pipes_num);
            if (cmds[i].infile != STDIN_FILENO)
                close(cmds[i].infile);
            // write(cmds[i].outfile,"the out", 7);
            if (cmds[i].outfile != STDOUT_FILENO)
                close(cmds[i].outfile);
            // write(2, gen.envp[0], ft_strlen(gen.envp[0]));
            // write(2, cmds[i].cmd_args[0], ft_strlen(cmds[i].cmd_args[0]));
            if (cmds[i].exec)
            {
                execve(cmds[i].cmd_path, cmds[i].cmd_args, gen.envp); //i changed this to an arrow 
                perror("execve : ");
            }
            exit(0);
        }
        i++;
    }
    close_pipes(pipes, pipes_num);
    while (waitpid(-1, 0, 0) != -1);
    
    // i = 0;
    // while (i <= pipes_num)
    // {
    //     wait(NULL);
    //     printf("lol1\n");
    //     i++;
    // }
    // waitpid(-1, 0, 0);
    // while (waitpid(-1, 0, 0) != -1);
    // close_cmd_files(cmds, pipes_num);
    }