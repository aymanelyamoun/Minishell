#include "../includes/minishell.h"

void	fail_to_generat_pipes(int **pipes, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		free(pipes[j]);
		j++;
	}
	free(pipes);
	exit (3);
}

void	free_pipes(int **pipes, int pipes_num)
{
	int	i;

	i = 0;
	if (pipes != NULL)
	{
		while (i < pipes_num)
		{
			free(pipes[i]);
			i++;
		}
		free(pipes);
	}
}

void	close_pipes(int **pipes, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	**creat_pipes(int pipes_num)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = malloc(sizeof(int*) * pipes_num);
	while (i < pipes_num)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes == NULL)
			fail_to_generat_pipes(pipes, i);
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}

void	assign_pipes(int **pipes, t_cmd **cmds, int pipes_num)
{
	int	i;

	i = 0;
	while (i <= pipes_num)
	{
		if (i == 0)
		{
			if ((*cmds)->infile == -1)
				(*cmds)->infile = STDIN_FILENO;
			if ((*cmds)->outfile == -1)
				(*cmds)->outfile = pipes[i][1];
			// else
				// close(pipes[i][1]);

		}
		if (i == pipes_num)
		{
			if ((*cmds)->infile == -1)
				(*cmds)->infile = pipes[i - 1][0];
			// else
			// 	close(pipes[i - 1][0]);
			if ((*cmds)->outfile == -1)
				(*cmds)->outfile = STDOUT_FILENO;
		}
		if (i < pipes_num)
		{
			if ((*cmds)->infile == -1)
				(*cmds)->infile = pipes[i - 1][0];
			if ((*cmds)->outfile == -1)
				(*cmds)->outfile = pipes[i][1];
		}
	}
}