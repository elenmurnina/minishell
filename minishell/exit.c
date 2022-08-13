/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:40:07 by hregina           #+#    #+#             */
/*   Updated: 2022/03/23 17:40:10 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close(int fd)
{
	close(fd);
}

void	close_fd(t_cmd_data *cmds, int *status, pid_t pid)
{
	int	i;

	i = 0;
	while (i < cmds->pipe_count)
	{
		ft_close(cmds->pipes[i]);
		i++;
	}
	waitpid(pid, status, 0);
	while (1)
	{
		if (wait(NULL) <= 0)
			break ;
	}
}

int	is_number(char *str)
{
	int	i;
	int	j;

	i = 0;
	if (str[i] == '-')
		i++;
	j = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
		j++;
	}
	if (j > 0)
		return (1);
	return (0);
}

int	has_overflow(char *str)
{
	long long	lln;
	long double	ldn;
	int			sign;

	lln = 0;
	ldn = 0;
	sign = 1;
	if (str[0] == '-')
	{
		sign = -1;
		str++;
	}
	while (*str)
	{
		lln = lln * 10 + sign * (*str - '0');
		ldn = ldn * 10 + sign * (*str - '0');
		if (ldn - (long double)lln > 32767
			|| ldn - (long double)lln < -32767)
			return (1);
		str++;
	}
	return (0);
}

int	ft_exit(char **command)
{
	int	k;

	k = 0;
	if (command[1] && ft_strcmp(command[1], "--") == 0)
		k++;
	ft_printf("exit\n");
	if (command[1 + k])
	{
		if (is_number(command[1 + k]) && !has_overflow(command[1 + k]))
		{
			if (command[2 + k])
			{
				ft_printf ("minishell: exit: too many arguments\n");
				return (1);
			}
			exit((int)(ft_atoi(command[1 + k]) % 256));
		}
		ft_printf ("minishell: exit: %s: numeric argument required\n",
			command[1 + k]);
		exit(255);
	}
	exit(0);
}
