/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_get_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:45:21 by hregina           #+#    #+#             */
/*   Updated: 2022/03/18 19:45:24 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_env_key(char *str)
{
	int	i;

	i = 0;
	while ((*(str + i) >= 'a' && *(str + i) <= 'z')
		|| (*(str + i) >= 'A' && *(str + i) <= 'Z')
		|| (*(str + i) >= '0' && *(str + i) <= '9')
		|| *(str + i) == '_')
		i++;
	if (str[0] == '?' && i == 0)
		return (1);
	return (i);
}

int	len_env_all(char *str)
{
	int	i;

	i = 0;
	if (ft_strchr(str, '='))
	{
		while (*(str + i) != '='
			&& ((*(str + i) >= 'a' && *(str + i) <= 'z')
				|| (*(str + i) >= 'A' && *(str + i) <= 'Z')
				|| (*(str + i) >= '0' && *(str + i) <= '9')
				|| *(str + i) == '_'))
			i++;
		if (*(str + i) != '=')
			i++;
	}
	else
		i = ft_strlen(str);
	return (i);
}

void	add_env(char *cmd, char ***env, char ***export)
{
	char	*check_env;

	check_env = ft_substr(cmd, 0, len_env_all(cmd));
	if (!get_env(check_env, *env, 0))
	{
		add_elem_arr(cmd, env);
		if (get_env(check_env, *export, 0))
			del_elem_arr(check_env, ft_strlen(check_env), export, 0);
		add_elem_arr(cmd, export);
	}
	else
	{
		del_elem_arr(check_env, ft_strlen(check_env), env, 0);
		del_elem_arr(check_env, ft_strlen(check_env), export, 0);
		add_elem_arr(cmd, env);
		add_elem_arr(cmd, export);
	}
	free (check_env);
}

char	*get_env(char *check_env, char **env, int *last_cmd)
{
	int	cnt_env;
	int	len_env_key;
	int	i;

	len_env_key = ft_strlen(check_env);
	cnt_env = cnt_str_arr(env);
	i = 0;
	if (ft_strcmp(check_env, "?") == 0)
		return (ft_itoa(*last_cmd));
	while (i < cnt_env)
	{
		if (!ft_strchr(env[i], '=') && ft_strcmp(check_env, env[i]) == 0)
			return (env[i]);
		if (ft_strncmp(check_env, env[i], len_env_key) == 0
			&& env[i][len_env_key] == '=')
			return (env[i] + len_env_key + 1);
		i++;
	}
	return (NULL);
}

int	create_my_env(char **env, char ***my_env, char ***my_export)
{
	int		i;
	char	**envs;
	char	**exports;

	i = 0;
	envs = malloc(sizeof(char *) * (cnt_str_arr(env) + 1));
	if (!envs)
		return (ERROR);
	exports = malloc(sizeof(char *) * (cnt_str_arr(env) + 1));
	if (!exports)
		return (ERROR);
	while (env[i])
	{
		envs[i] = ft_strdup(env[i]);
		exports[i] = ft_strdup(env[i]);
		i++;
	}
	envs[i] = NULL;
	exports[i] = NULL;
	*my_env = envs;
	*my_export = exports;
	inc_shlvl(my_env, my_export);
	return (SUCCESS);
}
