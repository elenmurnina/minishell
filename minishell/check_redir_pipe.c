/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redir_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:45:52 by hregina           #+#    #+#             */
/*   Updated: 2022/03/18 19:45:54 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	type_redir(char *l, t_cmd_data *cmds, int i)
{
	if (*(l + 1) == *l)
	{
		if (ft_strlen(l) < ft_strlen(cmds->commands[i]) && *(l - 1) == *l)
			return (print_syntax_error(l, 1, &cmds->last_cmd));
		return (-1);
	}
	if (ft_strlen(l) < ft_strlen(cmds->commands[i]) && *(l - 1) == *l)
	{
		if (*l == '<')
			return (3);
		else
			return (4);
	}
	if (*l == '<')
		return (1);
	else
		return (2);
	return (-1);
}

int	processing_redir_file(t_cmd_data *cmds, char **cmd, char **to_erase, int i)
{
	int		quote;
	char	*file_name;

	quote = 0;
	cmds->j = -1;
	while (cmd[i][++(cmds->j) + 1])
	{
		quote = check_quote_open(quote, (cmd[i] + cmds->j), ft_strlen(cmd[i]));
		if (quote == 0 && (cmd[i][cmds->j] == '<' || cmd[i][cmds->j] == '>'))
		{
			cmds->is_redir = type_redir(&cmd[i][cmds->j], cmds, i);
			if (cmds->is_redir == ERROR)
				return (ERROR);
			if (cmds->is_redir != -1)
			{
				file_name = get_filename(cmd[i], cmds->j + 1, quote, *to_erase);
				add_elem_arr(file_name, &cmds->all_cmds[i].file);
				free(file_name);
				erase_redirection_start(cmd[i], cmds->j, *to_erase);
			}
			add_elem_int(cmds->is_redir, &cmds->all_cmds[i].type_redir,
				&cmds->all_cmds[i].cnt_redir);
		}
	}
	return (SUCCESS);
}

int	check_redir(t_cmd_data *cmds, int i, int j)
{
	char	**cmd;
	char	*to_erase;

	i = 0;
	cmd = cmds->commands;
	while (cmd[i])
	{
		j = 0;
		to_erase = ft_strdup(cmd[i]);
		if (processing_redir_file(cmds, cmd, &to_erase, i) == ERROR)
			return (ERROR);
		cmds->all_cmds[i].command = ft_strdup("");
		while (to_erase[j])
		{
			if (to_erase[j] != 1)
				cmds->all_cmds[i].command
					= add_char_to_string(&cmds->all_cmds[i].command,
						to_erase[j]);
			j++;
		}
		free(to_erase);
		i++;
	}
	return (SUCCESS);
}

int	check_pipe(char *l, int quote, int len_line, t_cmd_data *cmds)
{
	int	len;

	len = ft_strlen(l);
	if (quote == 0 && *l == '|' && (len == len_line || *(l - 1) != '\\'))
	{
		if (*(l + 1) == '|')
		{
			if (*(l + 2) == '|')
				return (print_syntax_error(l, 2, &cmds->last_cmd));
			else
			{
				ft_printf("the command contains elements of the bonus part"
					" of the task, they are not ready yet :)\n");
				cmds->last_cmd = 258;
				return (ERROR);
			}
		}
	}
	return (SUCCESS);
}

int	find_special(t_cmd_data *cmds, int len_line, int quote)
{
	char	*i;
	int		cnt_cmd;

	i = cmds->commands[0];
	cnt_cmd = 0;
	if (i == NULL)
		return (SUCCESS);
	while (*i)
	{
		quote = check_quote_open(quote, i, len_line);
		if (*i == '|'
			&& check_pipe(i, quote, len_line, cmds) == ERROR)
			return (ERROR);
		if ((*i == ';' || *i == '|' || *i == '\n') && quote == 0)
		{
			add_elem_int(0, &cmds->is_pipe, &cnt_cmd);
			if (*i == '|')
				cmds->is_pipe[cnt_cmd - 1] = 1;
			*i = 1;
		}
		i++;
	}
	add_elem_int(0, &cmds->is_pipe, &cnt_cmd);
	return (SUCCESS);
}
