/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:48:25 by hregina           #+#    #+#             */
/*   Updated: 2022/03/18 19:48:28 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env_abc(int cnt_env, char ***export)
{
	int		i;
	int		j;
	char	*tmp;

	i = 1;
	while (i < cnt_env)
	{
		j = 0;
		while (j < cnt_env - i)
		{
			if (ft_strcmp((*export)[j], (*export)[j + 1]) > 0)
			{
				tmp = (*export)[j];
				(*export)[j] = (*export)[j + 1];
				(*export)[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_export_abc(char **export, int cnt_env)
{
	int		i;

	sort_env_abc(cnt_env, &export);
	i = 0;
	while (i < cnt_env)
	{
		if (ft_strchr(export[i], '='))
		{
			*(ft_strchr(export[i], '=')) = '\0';
			ft_printf("declare -x %s=", export[i]);
			*(ft_strchr(export[i], '\0')) = '=';
			ft_printf("\"%s\"\n", ft_strchr(export[i], '=') + 1);
		}
		else
			ft_printf("declare -x %s\n", export[i]);
		i++;
	}
}

int	ft_export(char **cmd, char ***env, char ***export)
{
	int		i;
	int		last_cmd;

	i = 1;
	last_cmd = 0;
	if (cnt_str_arr(cmd) > 1)
	{
		while (i < cnt_str_arr(cmd))
		{
			if (!is_env_valid("export", cmd[i], &i, &last_cmd))
				continue ;
			if (!ft_strchr(cmd[i], '='))
			{
				if (!get_env(cmd[i], *export, 0))
					add_elem_arr(cmd[i], export);
			}
			else
				add_env(cmd[i], env, export);
			i++;
		}
	}
	else
		print_export_abc(*export, cnt_str_arr(*export));
	return (last_cmd);
}
