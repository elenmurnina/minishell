/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_width.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:21:58 by hregina           #+#    #+#             */
/*   Updated: 2022/04/29 19:22:01 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*internal_format_width(t_format fmt, char *s, int *len)
{
	char	*s_new;
	char	filler;

	s_new = 0;
	if (is_numeric_specifier(fmt) && fmt.flag_zero && fmt.precision == -1)
		filler = '0';
	else
		filler = ' ';
	s_new = ft_calloc(fmt.width + 1, sizeof(char));
	if (fmt.flag_minus)
	{
		s_new = ft_memcpy(s_new, s, *len);
		ft_memset(s_new + *len, filler, fmt.width - *len);
	}
	else
	{
		s_new = ft_memset(s_new, filler, fmt.width - *len);
		ft_memcpy(s_new + fmt.width - *len, s, *len);
	}
	*len = fmt.width;
	if (is_numeric_specifier(fmt) && fmt.flag_zero
		&& fmt.precision == -1 && s[0] == '-')
		ft_swap(&s_new[0], ft_strchr(s_new, '-'));
	free(s);
	return (s_new);
}

char	*format_width(t_format fmt, char *s, int *len)
{
	if (*len == -1)
		*len = (int)ft_strlen(s);
	if (fmt.width <= *len)
		return (s);
	else
		return (internal_format_width(fmt, s, len));
}
