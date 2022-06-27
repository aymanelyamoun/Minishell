#include "../includes/minishell.h"

int check_arg(char *next)
{    
    int index;

    index = 0;
    if(!next)
        return (0);
    if(ft_isdigit(next[0]) || next[0] == '=')
        return (1);
    while (next[index])
    {
        if(next[index] == '=')
            break ;
        if(!ft_isalnum(next[index]) && next[index] != '_')
            return(1);
        index++;
    }
    return (0);
}


int check_arg2(char *next)
{
    int	index;

	index = 0;
	if (!next)
		return (0);
	if (!next[index] || (!ft_isalpha(next[index]) && next[index] != '_')) // TODO :WHYYYYYY UNSET WITHOUT $ WORKS?
		return (1);
	index++;
	while (next[index])
	{
		if ((next[index] != '_' && !ft_isalnum(next[index])))
			return (1);
		index++;
	}
	return (0);
}

