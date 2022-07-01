#include "../includes/minishell.h"

int	count_pipes(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens != NULL)
	{
		if (tokens->type == PIPE)
			i++;
		tokens = tokens->next;
	}
	return (i);
}

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
	if (pipes == NULL)
		return (NULL);
	while (i < pipes_num)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
		{
			fail_to_generat_pipes(pipes, i);
			creat_pipes(pipes_num);
		}
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}

static void assign_f(t_cmd **cmds, int i, int pipes_num, int **pipes)
{
	if ((*cmds)[i].infile == -1)
		(*cmds)[i].infile = STDIN_FILENO;
	if ((*cmds)[i].outfile == -1)
	{
		if (pipes_num == 0)
		{
			(*cmds)[i].outfile = STDOUT_FILENO;
			return ;
		}
		else
			(*cmds)[i].outfile = pipes[i][1];
	}
}

void	assign_pipes(int **pipes, t_cmd **cmds, int pipes_num)
{
	int	i;

	i = 0;
	while (i <= pipes_num)
	{
		if (i == 0)
			assign_f(cmds, i, pipes_num, pipes);
		if (i == pipes_num)
		{
			if ((*cmds)[i].infile == -1)
				(*cmds)[i].infile = pipes[i - 1][0];
			if ((*cmds)[i].outfile == -1)
				(*cmds)[i].outfile = STDOUT_FILENO;
		}
		if (i < pipes_num)
		{
			if ((*cmds)[i].infile == -1)
				(*cmds)[i].infile = pipes[i - 1][0];
			if ((*cmds)[i].outfile == -1)
				(*cmds)[i].outfile = pipes[i][1];
		}
		i++;
	}
}
