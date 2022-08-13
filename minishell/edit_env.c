/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:46:13 by hregina           #+#    #+#             */
/*   Updated: 2022/03/18 19:46:16 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_char_to_string(char **str, char c)
{
	char	*tmp;

	tmp = ft_calloc(ft_strlen(*str) + 2, sizeof(char));
	if (!tmp)
		return (ERROR);
	ft_memmove(tmp, *str, ft_strlen(*str));
	tmp[ft_strlen(*str)] = c;
	free(*str);
	return (tmp);
}

void	replace_env(char **new_cmd, t_cmd_data *cmd, int *i)
{
	char	*tmp;
	char	*check_env;
	char	*env_val;

	(*i) = len_env_key(++cmd->commands[0]);
	check_env = ft_substr(cmd->commands[0], 0, *i);
	env_val = get_env(check_env, cmd->env, &cmd->last_cmd);
	if (check_env && env_val)
	{
		tmp = *new_cmd;
		*new_cmd = ft_strjoin(*new_cmd, env_val);
		free(tmp);
	}
	if (ft_strcmp(check_env, "?") == 0 && env_val)
		free(env_val);
	free(check_env);
}

int	is_valid_env_value(char **cmd, int *i)
{
	if (*(*cmd + 1) >= '0' && *(*cmd + 1) <= '9')
	{
		(*i)++;
		(*cmd) += 2;
		return (0);
	}
	if (len_env_key(*cmd + 1) == 0
		||*(*cmd + 1) == '\0' || *(*cmd + 1) == '$'
		|| *(*cmd + 1) == ' ')
		return (0);
	return (1);
}

void	find_repl_env(char **new_cmd, t_cmd_data *cmd, int len_line)
{
	int		i;
	int		quote;

	quote = 0;
	while (*cmd->commands[0])
	{
		i = 0;
		quote = check_quote_open(quote, cmd->commands[0], len_line);
		if (quote != 1 && *cmd->commands[0] == '$'
			&& is_valid_env_value(&cmd->commands[0], &i))
			replace_env(new_cmd, cmd, &i);
		else
			*new_cmd = add_char_to_string(new_cmd, *cmd->commands[0]);
		if (*cmd->commands[0] != '\0')
			cmd->commands[0] += ft_max(1, i);
	}
}

int	edit_env_cmd(t_cmd_data *cmd)
{
	char	*new_cmd;
	char	*tmp;

	new_cmd = NULL;
	tmp = cmd->commands[0];
	find_repl_env(&new_cmd, cmd, ft_strlen(cmd->commands[0]));
	free(tmp);
	cmd->commands[0] = new_cmd;
	if (!cmd->commands[0])
		return (ERROR);
	return (SUCCESS);
}
