/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:47:15 by hregina           #+#    #+#             */
/*   Updated: 2022/03/18 19:47:18 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_syntax_error(char *c, int cnt, int *last_cmd)
{
	if (*c == '\0')
		c--;
	ft_printf("minishell: ");
	if (cnt == 2)
		ft_printf("syntax error near unexpected token `%c%c'\n", *c, *c);
	else if (cnt == 1)
		ft_printf("syntax error near unexpected token `%c'\n", *c);
	else
		ft_printf("syntax error near unexpected token `newline'\n");
	*last_cmd = 258;
	return (ERROR);
}

int	print_command_not_found(char *command, int *last_cmd)
{
	ft_printf ("minishell: %s: command not found\n", command);
	*last_cmd = 127;
	return (ERROR);
}

int	print_no_such_file_dir(char *command, int *last_cmd)
{
	ft_printf ("minishell: %s: No such file or directory\n", command);
	*last_cmd = 127;
	return (ERROR);
}

int	print_not_valid_identifier(char *command, char *cmd, int *last_cmd)
{
	ft_printf("minishell: %s: `%s': not a valid identifier\n", command, cmd);
	*last_cmd = 1;
	return (ERROR);
}

int	error_file(char *file_name, int *last_cmd)
{
	ft_printf("minishell: %s: %s\n", file_name, strerror(errno));
	*last_cmd = errno;
	return (ERROR);
}
