/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_precision.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:22:51 by hregina           #+#    #+#             */
/*   Updated: 2022/04/29 19:22:54 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	format_precision_adjust_len(t_format fmt, char *s, int *len)
{
	if (*len == -1)
	{
		if (is_numeric_specifier(fmt))
		{
			if (s[0] == '-')
				*len = ft_max((int)ft_strlen(s), fmt.precision + 1);
			else
				*len = ft_max((int)ft_strlen(s), fmt.precision);
		}
		if (fmt.specifier == 'p')
			*len = ft_max((int)ft_strlen(s), fmt.precision + 2);
		if (fmt.specifier == 's')
			*len = ft_min((int)ft_strlen(s), fmt.precision);
	}
}

static char	*format_precision_adjust_numeric_s_new(t_format fmt, char *s,
		const int *len, char *s_new)
{
	if (*len < fmt.precision)
	{
		s_new = ft_memset(s_new, '0', fmt.precision - *len);
		ft_memcpy(s_new + fmt.precision - *len, s, ft_strlen(s));
	}
	else
	{
		s_new = ft_memset(s_new, '0', *len - ft_strlen(s));
		ft_memcpy(s_new + *len - ft_strlen(s), s, ft_strlen(s));
	}
	return (s_new);
}

static char	*format_precision_adjust_p_s_new(t_format fmt, char *s,
		const int *len, char *s_new)
{
	ft_memcpy(s_new, "0x", 2);
	if (*len < fmt.precision + 2)
	{
		s_new = ft_memset(s_new + 2, '0', fmt.precision + 2 - *len);
		ft_memcpy(s_new + 2 + fmt.precision + 2 - *len, s + 2,
			ft_strlen(s) - 2);
	}
	else
	{
		ft_memset(s_new + 2, '0', *len - ft_strlen(s));
		ft_memcpy(s_new + 2 + *len - ft_strlen(s), s + 2, ft_strlen(s) - 2);
	}
	return (s_new);
}

char	*format_precision(t_format fmt, char *s, int *len)
{
	char	*s_new;

	s_new = 0;
	format_precision_adjust_len(fmt, s, len);
	s_new = ft_calloc(*len + 1, sizeof(char));
	if (is_numeric_specifier(fmt))
		s_new = format_precision_adjust_numeric_s_new(fmt, s, len, s_new);
	else if (fmt.specifier == 'p')
		s_new = format_precision_adjust_p_s_new(fmt, s, len, s_new);
	else
		ft_memcpy(s_new, s, *len);
	if (is_numeric_specifier(fmt) && s[0] == '-')
		ft_swap(&s_new[0], ft_strchr(s_new, '-'));
	if (s[0] == '0' && ft_strlen(s) == 1 && fmt.precision == 0)
		*len = 0;
	free(s);
	return (s_new);
}
