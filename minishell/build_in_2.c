/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:48:10 by hregina           #+#    #+#             */
/*   Updated: 2022/03/18 19:48:13 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int	is_valid_export_unset(char *k)
{
	int	i;

	i = 0;
	if (((k[i] >= 'a' && k[i] <= 'z')
			|| (k[i] >= 'A' && k[i] <= 'Z')
			|| k[i] == '_'))
	{
		while (k[i] && i < len_env_all(k))
		{
			if (k[i] < '0' || (k[i] > '9' && k[i] < 'A')
				|| (k[i] > 'Z' && k[i] < 'a' && k[i] != '_')
				|| k[i] > 'z')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	is_env_valid(char *command, char *cmd, int *i, int *last_cmd)
{
	if (!is_valid_export_unset(cmd) || is_empty(cmd))
	{
		(*i)++;
		return (print_not_valid_identifier(command, cmd, last_cmd));
	}
	*last_cmd = 0;
	return (SUCCESS);
}

int	ft_unset(char **cmd, char ***env, char ***export)
{
	int		i;
	int		cnt_cmd;
	int		last_cmd;

	i = 1;
	cnt_cmd = cnt_str_arr(cmd);
	while (i < cnt_cmd)
	{
		if (!is_env_valid("unset", cmd[i], &i, &last_cmd))
			continue ;
		if (get_env(cmd[i], *env, 0))
		{
			if (del_elem_arr(cmd[i], ft_strlen(cmd[i]), env, 0) == ERROR)
				return (1);
			if (del_elem_arr(cmd[i], ft_strlen(cmd[i]), export, 0) == ERROR)
				return (1);
		}
		if (get_env(cmd[i], *export, 0))
		{
			if (del_elem_arr(cmd[i], ft_strlen(cmd[i]), export, 0) == ERROR)
				return (1);
		}
		i++;
	}
	return (last_cmd);
}
