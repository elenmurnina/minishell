/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:23:45 by hregina           #+#    #+#             */
/*   Updated: 2022/04/29 19:23:47 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

int	is_numeric_specifier(t_format fmt)
{
	return (fmt.specifier == 'd' || fmt.specifier == 'i'
		|| fmt.specifier == 'u' || fmt.specifier == 'x'
		|| fmt.specifier == 'X' || fmt.specifier == 'o');
}

char	*format_space(t_format fmt, char *s, int *len)
{
	char	*s_new;

	s_new = 0;
	if (fmt.width < *len || *len == -1)
	{
		s_new = ft_calloc(ft_strlen(s) + 2, sizeof(char));
		s_new[0] = ' ';
		ft_memcpy(s_new + 1, s, ft_strlen(s));
		(*len) = -1;
	}
	else
	{
		s_new = ft_calloc(fmt.width + 1, sizeof(char));
		s_new[0] = ' ';
		ft_memcpy(s_new + 1, s, ft_strlen(s) - 1);
	}
	free(s);
	return (s_new);
}

char	*print_format_specifier(t_format fmt, va_list *args, int *len)
{
	char	*s;

	if (fmt.specifier == '%')
		s = format_percent(fmt, args, len);
	if (fmt.specifier == 'd' || fmt.specifier == 'i')
		s = format_d(fmt, args, len);
	if (fmt.specifier == 'u')
		s = format_u(fmt, args, len);
	if (fmt.specifier == 'x' || fmt.specifier == 'X')
		s = format_x_x_up(fmt, args, len);
	if (fmt.specifier == 'o')
		s = format_o(fmt, args, len);
	if (fmt.specifier == 's')
		s = format_s(fmt, args, len);
	if (fmt.specifier == 'c')
		s = format_c(fmt, args, len);
	if (fmt.specifier == 'p')
		s = format_p(fmt, args, len);
	return (s);
}

void	print_format(t_format fmt, va_list *args, t_print_result *result,
		int ind)
{
	char	*s;
	int		len;

	s = print_format_specifier(fmt, args, &len);
	if (fmt.specifier != '%')
	{
		if (fmt.precision != -1)
			s = format_precision(fmt, s, &len);
		if (fmt.width != -1)
			s = format_width(fmt, s, &len);
	}
	if (fmt.flag_space)
		s = format_space(fmt, s, &len);
	if (len == -1)
	{
		result->char_count += (int)ft_strlen(s);
		ft_putstr_fd(s, 1);
	}
	else
	{
		result->char_count += len;
		while (ind < len)
			ft_putchar_fd(s[ind++], 1);
	}
	free(s);
}

int	ft_printf(const char *pattern, ...)
{
	va_list			args;
	int				i;
	t_format		fmt;
	t_print_result	result;

	va_start(args, pattern);
	i = 0;
	result.char_count = 0;
	while (pattern[i] != '\0')
	{
		if (pattern[i] != '%')
		{
			ft_putchar_fd(pattern[i], 1);
			result.char_count++;
			i++;
		}
		else
		{
			fmt = parse(pattern, &i, &args);
			print_format(fmt, &args, &result, 0);
		}
	}
	va_end(args);
	return (result.char_count);
}
