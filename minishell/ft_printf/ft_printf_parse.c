/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:22:37 by hregina           #+#    #+#             */
/*   Updated: 2022/04/29 19:22:39 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

void	parse_flags(const char *s, int *pos, t_format *fmt)
{
	fmt->flag_minus = 0;
	fmt->flag_space = 0;
	fmt->flag_zero = 0;
	while (s[*pos] == '0' || s[*pos] == '-' || s[*pos] == '+' || s[*pos] == ' ')
	{
		if (s[*pos] == '0')
			fmt->flag_zero = 1;
		if (s[*pos] == '-')
			fmt->flag_minus = 1;
		if (s[*pos] == '+')
			fmt->flag_minus = 1;
		if (s[*pos] == ' ')
			fmt->flag_space = 1;
		(*pos)++;
	}
	if (fmt->flag_zero && fmt->flag_minus)
		fmt->flag_zero = 0;
}

void	parse_width(const char *s, int *pos, t_format *fmt, va_list *args)
{
	if (ft_isdigit(s[*pos]))
	{
		fmt->width = 0;
		while (ft_isdigit(s[*pos]))
		{
			fmt->width = fmt->width * 10 + s[*pos] - '0';
			(*pos)++;
		}
	}
	else
	{
		fmt->width = -1;
		if (s[*pos] == '*')
		{
			fmt->width = va_arg(*args, int);
			if (fmt->width < 0)
			{
				fmt->flag_zero = 0;
				fmt->flag_minus = 1;
				fmt->width *= -1;
			}
			(*pos)++;
		}
	}
}

void	parse_precision(const char *s, int *pos, t_format *fmt, va_list *args)
{
	fmt->precision = -1;
	if (s[*pos] == '.')
	{
		fmt->precision = 0;
		(*pos)++;
		while (ft_isdigit(s[(*pos)]))
		{
			fmt->precision = fmt->precision * 10 + s[(*pos)] - '0';
			(*pos)++;
		}
		if (s[*pos] == '*')
		{
			fmt->precision = va_arg(*args, int);
			if (fmt->precision < 0)
				fmt->precision = -1;
			(*pos)++;
		}
	}
}

t_format	parse(const char *s, int *pos, va_list *args)
{
	t_format	fmt;

	(*pos)++;
	parse_flags(s, pos, &fmt);
	parse_width(s, pos, &fmt, args);
	parse_precision(s, pos, &fmt, args);
	fmt.specifier = s[*pos];
	(*pos)++;
	return (fmt);
}
