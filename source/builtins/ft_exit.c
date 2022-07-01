/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oufisaou <oufisaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 04:27:38 by oufisaou          #+#    #+#             */
/*   Updated: 2022/07/01 04:27:39 by oufisaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	suite7(char *str)
{
	ft_putstr_fd("Minishell : exit : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("  numeric argument required\n", 2);
}

int	ft_exit(char **next)
{
	if (ft_strlen2(next) == 1)
	{
		ft_putstr_fd("exit\n", 2);
		g_gen.exit_status = ft_atoll(*next);
	}
	if (ft_strlen2(next) == 2)
	{
		if (check_valid(*(next + 1)) == 0)
		{
			suite7(next[1]);
			g_gen.exit_status = 255;
		}
		else if (check_valid(*(next + 1)) == 1)
			g_gen.exit_status = ft_atoll(next[1]);
	}
	if (ft_strlen2(next) > 2)
	{
		ft_putstr_fd("exit\n", 2);
		ft_putstr_fd("exit : too many arguments\n", 2);
		g_gen.exit_status = 255;
	}
	exit(g_gen.exit_status);
	free_split(next);
	return (0);
}

int	is_long(char *next)
{
	if (ft_atoll(next) > 2147483647 || ft_atoll(next) < -2147483648)
		return (1);
	return (0);
}

int	check_valid(char *next)
{
	int	index;

	index = 0;
	while (next[index])
	{
		if (ft_isdigit(next[index]) != 1 || is_long(next))
		{
			if ((next[index] == '+' || next[index] == '-') && index == 0)
			{
				index++;
				continue ;
			}
			return (0);
		}
		index++;
	}
	return (1);
}
