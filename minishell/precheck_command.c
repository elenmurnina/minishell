/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precheck_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:46:59 by hregina           #+#    #+#             */
/*   Updated: 2022/03/18 19:47:01 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote_open(int quote, char *line, int len_line)
{
	int	len;

	len = ft_strlen(line);
	if (*line == '\'' && (len == len_line
			|| *(line - 1) != '\\') && quote == 0)
		return (1);
	else if (*line == '\'' && (len == len_line
			|| *(line - 1) != '\\') && quote == 1)
		return (0);
	if (*line == '"' && (len == len_line
			|| *(line - 1) != '\\') && quote == 0)
		return (2);
	else if (*line == '"' && (len == len_line
			|| *(line - 1) != '\\') && quote == 2)
		return (0);
	return (quote);
}

int	check_begin(char *line, char check, int *last_cmd)
{
	if (*line && *line == check)
	{
		(*last_cmd) = 258;
		if (*(line + 1) == check)
			return (print_syntax_error(line, 2, last_cmd));
		else
			return (print_syntax_error(line, 1, last_cmd));
	}
	return (SUCCESS);
}

int	check_empty_cmd(char *cmd, int *last_cmd)
{
	int		len;

	len = ft_strlen(cmd);
	if (ft_strcmp(cmd + len - 1, ">") == 0 || ft_strcmp(cmd, ";") == 0)
		return (print_syntax_error(cmd, 1, last_cmd));
	if (ft_strcmp(cmd + len - 1, ">") == 0
		|| ft_strcmp(cmd + len - 1, "<") == 0
		|| (len >= 2 && ft_strcmp(cmd + len - 2, ">>") == 0)
		|| (len >= 2 && ft_strcmp(cmd + len - 2, "<<") == 0))
		return (print_syntax_error("n", 0, last_cmd));
	return (SUCCESS);
}

int	is_spec_sym(char c, int quote)
{
	if (quote == 0
		&& (c == ';' || c == '<' || c == '>' || c == '|'))
		return (1);
	return (0);
}

int	precheck_special(char *l, int len_line, int *last_cmd, int space)
{
	int		quote;
	int		spec;
	char	prev_sp;

	quote = 0;
	if (check_begin(l, ';', last_cmd) == ERROR
		|| check_begin(l, '|', last_cmd) == ERROR)
		return (ERROR);
	while (*l)
	{
		space = 0;
		quote = check_quote_open(quote, l, len_line);
		if (quote == 0 && *l && *l == ';' && *(l + 1) == ';')
			return (print_syntax_error(l, 2, last_cmd));
		spec = is_spec_sym(*l, quote);
		prev_sp = *l;
		l += spec;
		while (spec == 1 && *l == ' ' && l++)
			space++;
		if (((spec + is_spec_sym(*l, quote) == 2 && (space > 0
						|| *l != *(l - 1))) || *l == '\0') && prev_sp == *l)
			return (print_syntax_error(l, 1, last_cmd));
		l++;
	}
	return (SUCCESS);
}
