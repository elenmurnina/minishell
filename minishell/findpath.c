/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findpath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:38:35 by hregina           #+#    #+#             */
/*   Updated: 2022/03/23 17:38:39 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_ispath(char *path)
{
	return (open(path, O_RDONLY, 0) >= 0);
}

int	ft_isvalid(char ***path, char *cmd, char **tmp)
{
	char	**begin_path;

	begin_path = *path;
	while (**path)
	{
		*tmp = ft_strjoin(**path, cmd);
		if (!ft_ispath(*tmp))
			free(*tmp);
		else
		{
			free_arr(begin_path);
			free(cmd);
			return (SUCCESS);
		}
		(*path)++;
	}
	free_arr(begin_path);
	free(cmd);
	return (ERROR);
}

int	ft_findpath(char **cmd, char **env, int *last_cmd, char *tmp)
{
	char	**path;
	char	current_path[4096];

	getcwd(current_path, 4096);
	if (check_build_in(cmd[0]))
		return (SUCCESS);
	if (ft_strncmp(cmd[0], "/", 1) == 0)
	{
		if (!ft_ispath(cmd[0]))
			return (print_command_not_found(cmd[0], last_cmd));
		return (SUCCESS);
	}
	if (ft_strncmp(cmd[0], "./", 2) == 0 || ft_strncmp(cmd[0], "../", 3) == 0
		|| !get_env("PATH", env, 0))
		path = ft_split(current_path, ':');
	else if (get_env("PATH", env, 0))
		path = ft_split(get_env("PATH", env, 0), ':');
	else
		return (print_no_such_file_dir(cmd[0], last_cmd));
	tmp = ft_strjoin("/", cmd[0]);
	if (ft_isvalid(&path, tmp, &tmp) == ERROR)
		return (print_command_not_found(cmd[0], last_cmd));
	free(cmd[0]);
	cmd[0] = tmp;
	return (SUCCESS);
}
