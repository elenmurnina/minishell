/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:38:35 by hregina           #+#    #+#             */
/*   Updated: 2022/03/23 17:38:39 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty_char(char c)
{
	return (c == '\n' || c == '\t' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ');
}

int	is_special_char(char c)
{
	return (c == ';' || c == '<' || c == '>' || c == '|');
}

int	is_empty(char *str)
{
	while (*str)
	{
		if (!is_empty_char(*str))
			return (0);
		str++;
	}
	return (1);
}

int	print_no_such_file_dir_cd(char *dir)
{
	ft_printf("minishell: cd: %s: No such file or directory\n", dir);
	return (1);
}
