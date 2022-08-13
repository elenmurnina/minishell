/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 03:30:13 by hregina           #+#    #+#             */
/*   Updated: 2022/03/22 03:30:17 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_splitter(char ***cmds, int *cmds_counter)
{
	char	**new_cmd;

	new_cmd = ft_split(*cmds[0], 1);
	if (!new_cmd)
		return (ERROR);
	free_arr(*cmds);
	*cmds = new_cmd;
	*cmds_counter = cnt_str_arr(*cmds);
	return (SUCCESS);
}

char	*get_filename(char *cmd, int pos, int quote, char *to_erase)
{
	int		last_quote;
	int		cmd_len;
	char	c;
	char	*result;

	cmd_len = ft_strlen(cmd);
	while (pos < cmd_len && is_empty_char(cmd[pos]))
	{
		to_erase[pos] = 1;
		pos++;
	}
	result = ft_strdup("");
	while (pos < cmd_len)
	{
		c = cmd[pos];
		if (quote == 0 && (is_special_char(c) || is_empty_char(c)))
			break ;
		last_quote = quote;
		quote = check_quote_open(quote, cmd + pos, cmd_len);
		if (last_quote == quote)
			result = add_char_to_string(&result, c);
		to_erase[pos] = 1;
		pos++;
	}
	return (result);
}

void	erase_redirection_start(char *cmd, int pos, char *to_erase)
{
	int	left_space;
	int	all_digits;

	to_erase[pos--] = 1;
	if (pos >= 0 && cmd[pos] == cmd[pos + 1])
		to_erase[pos--] = 1;
	left_space = pos;
	while (left_space >= 0 && !is_empty_char(cmd[left_space]))
		left_space--;
	all_digits = 1;
	while (left_space < pos)
	{
		left_space++;
		if (!ft_isdigit(cmd[left_space]))
			all_digits = 0;
	}
	if (all_digits)
	{
		while (pos >= 0 && !is_empty_char(cmd[pos]))
			to_erase[pos--] = 1;
	}
}
