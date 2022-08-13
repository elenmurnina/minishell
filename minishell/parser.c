/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:46:41 by hregina           #+#    #+#             */
/*   Updated: 2022/03/18 19:46:43 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote_delete(char c, int quote)
{
	if ((quote == 0 && (c == '\'' || c == '\"'))
		|| (quote == 1 && c == '\'') || (quote == 2 && c == '\"'))
		return (1);
	return (0);
}

int	is_empty_quotes(char **cmds, char **new_cmds, int *i, int *quote)
{
	if ((ft_strncmp(cmds[0], "export", 6) == 0
			|| ft_strncmp(cmds[0], "unset", 6) == 0)
		&& ((((*quote) == 1 && cmds[0][(*i)] == '\''
				&& cmds[0][(*i) + 1] == '\'')
		|| ((*quote) == 2 && cmds[0][(*i)] == '\"'
		&& cmds[0][(*i) + 1] == '\"'))))
	{
		(*i) += 2;
		(*quote) = 0;
		**new_cmds = '\'';
		*(*new_cmds + 1) = 2;
		(*new_cmds) += 2;
		return (0);
	}
	return (1);
}

int	delete_quote(char **cmds, int len_line, int i, int quote)
{
	char	*new_cmds;
	char	*begin_new;

	new_cmds = ft_calloc(sizeof(char), ft_strlen(cmds[0]) + 1);
	if (!new_cmds)
		return (ERROR);
	begin_new = new_cmds;
	while (++i < len_line && cmds[0][i])
	{
		quote = check_quote_open(quote, cmds[0] + i, len_line);
		if (!is_empty_quotes(cmds, &new_cmds, &i, &quote))
			continue ;
		while (is_quote_delete(cmds[0][i], quote) == 1)
		{
			i++;
			quote = check_quote_open(quote, cmds[0] + i, len_line);
		}
		if (cmds[0][i] == ' ' && quote == 0)
			cmds[0][i] = 2;
		*new_cmds = cmds[0][i];
		new_cmds++;
	}
	free(*cmds);
	*cmds = begin_new;
	return (SUCCESS);
}

int	init_command(t_cmd_data *cmds, char *line, int i)
{
	cmds->commands = malloc(sizeof(char *) * 2);
	if (!cmds->commands)
		return (ERROR);
	cmds->commands[0] = ft_strdup(line);
	cmds->commands[1] = NULL;
	cmds->is_pipe = NULL;
	cmds->is_redir = 0;
	cmds->counter = 0;
	cmds->j = 0;
	cmds->is_last_pipe = 1;
	cmds->all_cmds = malloc(sizeof(t_command) * 300);
	if (!cmds->all_cmds)
		return (ERROR);
	while (i < 300)
	{
		cmds->all_cmds[i].file = malloc(sizeof(char *));
		if (!cmds->all_cmds[i].file)
			return (ERROR);
		cmds->all_cmds[i].file[0] = NULL;
		cmds->all_cmds[i].type_redir = NULL;
		cmds->all_cmds[i].cnt_redir = 0;
		cmds->all_cmds[i++].command = NULL;
	}
	cmds->pipes = malloc(sizeof(int) * 300);
	return (SUCCESS);
}

int	parsing(char **line, t_cmd_data *cmds)
{
	int	i;

	i = 0;
	if (init_command(cmds, *line, 0) == ERROR)
		return (ERROR);
	if (check_empty_cmd(cmds->commands[0], &cmds->last_cmd) == ERROR
		|| precheck_special(cmds->commands[0],
			ft_strlen(cmds->commands[0]), &cmds->last_cmd, 0) == ERROR
		|| find_special(cmds, ft_strlen(cmds->commands[0]), 0) == ERROR
		|| edit_env_cmd(cmds) == ERROR
		|| cmd_splitter(&cmds->commands, &cmds->counter) == ERROR
		|| check_redir(cmds, 0, 0) == ERROR)
		return (ERROR);
	while (i < cmds->counter)
	{
		if (delete_quote(&cmds->all_cmds[i].command,
				ft_strlen(cmds->all_cmds[i].command), -1, 0) == ERROR)
			return (ERROR);
		i++;
	}
	free(*line);
	return (SUCCESS);
}
