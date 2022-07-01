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

static t_cmd *creat_cmds_utils(t_token **tokens, t_cmd **cmds)
{
    t_token *tmp;
    t_token *new_head;
    int     i;

    i = 0;
	tmp = *tokens;
	new_head = tmp;
	while (tmp != NULL)
	{
		if (tmp->next != NULL && tmp->next->type == PIPE)
		{
			rm_token(&(tmp->next));
			(*cmds)[i].tokens_cmd = new_head;
			(*cmds)[i].infile = -1;
			(*cmds)[i].outfile = -1;
			(*cmds)[i].exec = 0;
			(*cmds)[i].cmd_args = NULL;
			(*cmds)[i].cmd_path = NULL;
			new_head = tmp->next;
			new_head->prev = NULL;
			tmp->next = NULL;
			tmp = new_head;
			i++;
		}
        else
		    tmp = tmp->next;
	}
	new_head->prev = NULL;
    (*cmds)[i].tokens_cmd = new_head;
	(*cmds)[i].infile = -1;
	(*cmds)[i].outfile = -1;
	(*cmds)[i].cmd_args = NULL;
	(*cmds)[i].cmd_path = NULL;
	(*cmds)[i].exec = 0;
	return (*cmds);
}

t_cmd	*creat_cmds(t_token **tokens)
{
	int		pipes;
	t_cmd	*cmds;
	int		i;

	i = 0;
	pipes = count_pipes(*tokens);
	cmds = malloc(sizeof(t_cmd) * (pipes + 1));
	if (cmds == NULL)
		return (NULL);
	if (pipes == 0)
	{
		cmds[i].tokens_cmd = *tokens;
		cmds[i].infile = -1;
		cmds[i].outfile = -1;
		cmds[i].exec = 0;
		cmds[i].cmd_args = NULL;
		cmds[i].cmd_path = NULL;
		return (cmds);
	}
	return (creat_cmds_utils(tokens, &cmds));
}

// checking cmds 
static void	ft_strcat(char *s1, const char *s2)
{
	while (*s1)
		s1++;
	while (*s2)
	{
		*s1 = *s2;
		s1++;
		s2++;
	}
	*s1 = '\0';
}

char	*ft_strjoin_1(char const *s1, char const *s2)
{
	int		total_len;
	char	*allocat;

	if (!s1 || !s2)
		return (0);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	allocat = (char *)malloc(total_len);
	if (!allocat)
		return (0);
	*allocat = '\0';
	ft_strcat(allocat, s1);
	ft_strcat(allocat, s2);
	return (allocat);
}

static void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i] != NULL)
		{
			free(arr[i]);
			i++;
		}
		free(arr);
	}
}

static char	*join_cmd(char *path, char *cmd)
{
	char	*cmd_path;
	char	*to_free;

	to_free = ft_strjoin_1("/", cmd);
	if (to_free == NULL)
		return (NULL);
	cmd_path = ft_strjoin_1(path, to_free);
	if (cmd_path == NULL)
		return (NULL);
	free(to_free);
	return (cmd_path);
}

void	cmd_not_found(char *cmd)
{
	char	*built_in;

	built_in = str_to_lower(cmd);
	if ((ft_strcmp(built_in, "echo") && ft_strcmp(built_in, "cd") 
        && ft_strcmp(built_in, "env") && ft_strcmp(built_in, "exit") 
        && ft_strcmp(built_in, "export") && ft_strcmp(built_in, "pwd") 
        && ft_strcmp(built_in, "unset")))
		printf("minishell: %s: command not found\n", cmd);
	free(built_in);
}

int isDirectory(const char *path) {
   struct stat statbuf;
   if (stat(path, &statbuf) != 0)
       return 0;
   return S_ISDIR(statbuf.st_mode);
}

void	is_a_dir(char *dir)
{
	printf("minishell: %s is a directory\n", dir);
}

char	*get_cmd_path(char *path, char *cmd)
{
	int		i;
	char	**paths;
	char	*cmd_path;

	i = 0;
	if (ft_strcmp(cmd, "") == 0)
		return (NULL);
	paths = ft_split(path, ':');
	if (paths == NULL)
		return (NULL);
	while (paths[i] != NULL)
	{
		cmd_path = join_cmd(paths[i], cmd);
		if (cmd_path == NULL)
			return (NULL);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			free_arr(paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_arr(paths);
	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}

int	get_cmds_path(t_cmd **cmds, int pipes)
{
	int	i;
	int	status;
	char	*path;
	char	*built_in;

	status = 0;
	i = 0;

	path = find_value("PATH", gen.env);
	if (path == NULL)
		return 1;
	while (i <= pipes)
	{
		if (isDirectory((*cmds)[i].cmd_args[0]))
		{
			if ((*cmds)[i].exec == 0)
				is_a_dir((*cmds)[i].cmd_args[0]);
			(*cmds)[i].exec = 126;
		}
		else if ((*cmds)[i].cmd_args[0] != NULL)
			(*cmds)[i].cmd_path = get_cmd_path(path, (*cmds)[i].cmd_args[0]);
		else
			(*cmds)[i].cmd_path = NULL;
		if (((*cmds)[i].cmd_path == NULL) && !is_buit_in((*cmds)[i].cmd_args[0]) && (*cmds)[i].exec == 0)
		{
			if ((*cmds)[i].cmd_args[0] != NULL)
				cmd_not_found((*cmds)[i].cmd_args[0]);
			if ((*cmds)[i].cmd_args[0] != NULL)
				(*cmds)[i].exec = 127;
			else
				gen.exec = 1;
		}
		i++;
	}
	free(path);
	return (status);
}

// int	commands(char *line)
// {
//     if (!ft_strncmp("echo", line, 4))
// 		return (YES);
// 	if (!ft_strncmp("export ", line, 7))
// 		return (YES);
// 	if (!ft_strncmp("pwd", line, 3) && ft_strlen(line) == 3)
// 		return (YES);
// 	if (!ft_strncmp("unset ", line, 6))
//         return (YES);
// 	if (!ft_strncmp("env", line, 3))
// 		return (YES);
// 	if (!ft_strncmp("exit", line, 4) && ft_strlen(line) == 4)
// 		return (YES);
// 	if (!ft_strncmp("cd ", line, 3))
// 		return (YES);
// 	return (NO);
// }

// void	go_commands(t_list *env, char *line)
// {
// 	if (!ft_strncmp("pwd", line, 3) && ft_strlen(line) == 3)
// 		ft_pwd();
// 	// if (!ft_strncmp("cd ", line, 3))
// 	// 	ft_cd(env, &line);
// 	if (!ft_strncmp("env", line, 3))
// 		ft_env(env);
// 	return ;
// }