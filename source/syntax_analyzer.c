#include "../includes/minishell.h"

static int	check_pairs1(char *s)
{
	int	q;

	q = 0;
	while (*s)
	{
		if (q == 0 && (*s == '\"' || *s == '\''))
		{
			if (*(s++) == '\'')
				q = 2;
			else
				q = 3;
		}
		while (*s && ((q == 3 && *s != '\"') || (q == 2 && *s != '\'')))
			s++;
		if ((q == 3 && *s == '\"') || (q == 2 && *s == '\''))
			q = 0;
		s++;
	}
	return (!q);
}

int	check_quotes(token_t *token)
{
	token_t	*tmp;
	char	*s;

	tmp = token;
	while (tmp)
	{
		s = tmp->data;
		if (!check_pairs1(s))
		{
			error_free(tmp->data, tmp);
			gen.exit_status = 258;
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_inside(token_t *tmp)
{
	if (tmp && tmp->type == PIPE)
	{
		error_free(tmp->data, tmp);
		return (0);
	}
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			tmp = tmp->next;
			if (tmp == NULL)
				return (0);
			while (tmp && tmp->type == SPAACE)
				tmp = tmp->next;
			if (tmp && tmp->type == PIPE)
			{
				error_free(tmp->data, tmp);
				gen.exit_status = 258;
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	check_newline(token_t *c)
{
	token_t	*tmp;

	tmp = NULL;
	tmp = c;
	while (tmp)
	{
		if ((tmp->type == LESS) || (tmp->type == GREAT) \
		|| (tmp->type == DGREAT) || (tmp->type == DLESS))
		{
			tmp = tmp->next;
			while (tmp && tmp->type == SPAACE)
				tmp = tmp->next;
			if ((tmp && is_other2(tmp)) || (tmp == NULL))
			{
				ft_putstr_fd("syntax error near unexpected", 2);
				ft_putstr_fd("  token : 'newline'\n", 2);
				gen.exit_status = 258;
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

int	handle_spaces(token_t *c)
{
	token_t	*tmp;

	tmp = NULL;
	tmp = c;
	while (tmp && tmp->type == SPAACE)
		tmp = tmp->next;
	if (tmp == NULL)
	{
		ft_putstr_fd("syntax error near unexpected", 2);
		ft_putstr_fd("  token : 'newline'\n", 2);
		gen.exit_status = 258;
		return (0);
	}
	else if (is_other(tmp))
	{
		error_free(tmp->data, tmp);
		gen.exit_status = 258;
		return (0);
	}
	return (1);
}
