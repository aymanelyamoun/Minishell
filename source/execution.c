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
        pid = fork();
        if (pid == -1)
            perror("fork : ");
        if (pid == 0)
        {
            // printf("\n--infile-%d\n--outfile-%d---\n", cmds[i].infile, cmds[i].outfile);
            // write(2, "i got here\n", 12);
            dup2(cmds[i].infile, STDIN_FILENO);
            // fprintf(stderr, "%d\n", cmds[i].infile);
            dup2(cmds[i].outfile, STDOUT_FILENO);
            // fprintf(stderr, "%d\n", cmds[i].outfile);
            close_pipes(pipes, pipes_num);
            // close_cmd_files(cmds, pipes_num);
            // close(cmds[i].infile);
            // close(cmds[i].outfile);
            // write(2, gen->envp[0], ft_strlen(gen->envp[0]));
            // write(2, cmds[i].cmd_args[0], ft_strlen(cmds[i].cmd_args[0]));
            execve(cmds[i].cmd_path, cmds[i].cmd_args, gen.envp);
            perror("execve : ");
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