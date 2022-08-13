/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:48:25 by hregina           #+#    #+#             */
/*   Updated: 2022/03/18 19:48:28 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	current_path[4096];

	getcwd(current_path, 4095);
	ft_printf("%s\n", current_path);
	return (0);
}

void	replace_env_pwd(char *env_key_val, char ***env, char ***export)
{
	char	path[4096];
	char	*tmp;

	if (get_env(env_key_val, *env, 0))
	{
		getcwd(path, 4095);
		del_elem_arr(env_key_val, ft_strlen(env_key_val), env, 0);
		del_elem_arr(env_key_val, ft_strlen(env_key_val), export, 0);
		tmp = ft_strjoin(env_key_val, "=");
		env_key_val = ft_strjoin(tmp, path);
		add_elem_arr(env_key_val, env);
		add_elem_arr(env_key_val, export);
		free(tmp);
		free(env_key_val);
	}
}

int	ft_cd(char **path, char ***env, char ***export)
{
	char	*dir;

	dir = path[1];
	if (!dir)
		dir = "HOME";
	else if (ft_strcmp(dir, "-") == 0)
		dir = "OLDPWD";
	if ((ft_strcmp(dir, "HOME") == 0 && !get_env(dir, *env, 0))
		|| (ft_strcmp(dir, "OLDPWD") == 0 && (!get_env("OLDPWD", *env, 0)
				|| ft_strcmp(get_env(dir, *env, 0), "OLDPWD") == 0)))
	{
		ft_printf("minishell: cd: %s not set\n", dir);
		return (1);
	}
	if (ft_strcmp(dir, "OLDPWD") == 0)
		ft_printf("%s\n", get_env(dir, *env, 0));
	if (ft_strcmp(dir, "HOME") == 0 || ft_strcmp(dir, "OLDPWD") == 0)
		dir = get_env(dir, *env, 0);
	if (!get_env("OLDPWD", *env, 0) && get_env("OLDPWD", *export, 0))
		add_elem_arr("OLDPWD", env);
	replace_env_pwd("OLDPWD", env, export);
	if ((chdir(dir)) == -1 && ft_strcmp(path[1], "-") != 0)
		return (print_no_such_file_dir_cd(dir));
	replace_env_pwd("PWD", env, export);
	return (0);
}

int	is_minus_n(char *check_cmd)
{
	int	i;

	i = 1;
	while (check_cmd[i] == 'n')
		i++;
	if (check_cmd[0] == '-' && check_cmd[i] == '\0')
		return (1);
	return (0);
}

int	ft_echo(char **command, int flag_n, char *new_line)
{
	int		i;

	i = 1;
	while (command[i])
	{
		if (is_minus_n(command[i]) && flag_n == 0)
		{
			new_line = "";
			i++;
			continue ;
		}
		else
			flag_n = -1;
		ft_printf("%s", command[i++]);
		if (command[i])
			ft_printf(" ");
	}
	ft_printf("%s", new_line);
	return (0);
}
