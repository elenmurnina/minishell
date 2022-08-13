/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:21:43 by hregina           #+#    #+#             */
/*   Updated: 2022/04/29 19:21:47 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define UNUSED (void)

char	*format_percent(t_format fmt, va_list *args, int *len)
{
	*len = -1;
	UNUSED(fmt);
	UNUSED(args);
	return (ft_strdup("%"));
}

char	*format_d(t_format fmt, va_list *args, int *len)
{
	*len = -1;
	UNUSED(fmt);
	return (ft_itoa(va_arg(*args, int)));
}

char	*format_s(t_format fmt, va_list *args, int *len)
{
	char	*str;

	*len = -1;
	str = va_arg(*args, char *);
	UNUSED(fmt);
	if (str == NULL)
	{
		if (fmt.precision != -1 && fmt.precision < 6)
			*len = 0;
		return (ft_strdup("(null)"));
	}
	return (ft_strdup(str));
}

char	*format_c(t_format fmt, va_list *args, int *len)
{
	char	*s;

	*len = 1;
	UNUSED(fmt);
	s = ft_strdup(" ");
	s[0] = va_arg(*args, int);
	return (s);
}

char	*format_u(t_format fmt, va_list *args, int *len)
{
	*len = -1;
	UNUSED(fmt);
	return (ft_utoa(va_arg(*args, unsigned)));
}
