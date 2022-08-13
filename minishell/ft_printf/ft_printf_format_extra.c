/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_extra.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:22:25 by hregina           #+#    #+#             */
/*   Updated: 2022/04/29 19:22:27 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#define UNUSED (void)

static int	cnt_hex(size_t n)
{
	int	cnt;

	cnt = 1;
	while (n / 16 > 0)
	{
		n /= 16;
		cnt++;
	}
	return (cnt);
}

static char	hex(unsigned int d)
{
	if (d < 10)
		return ((char)('0' + d));
	return ((char)('a' + d - 10));
}

char	*format_p(t_format fmt, va_list *args, int *len)
{
	void	*p;
	size_t	n;
	int		length;
	char	*str;
	int		i;

	*len = -1;
	p = va_arg(*args, void *);
	n = (size_t)(p);
	length = cnt_hex(n);
	if (length + 2 < fmt.width && fmt.flag_zero)
		length = fmt.width - 2;
	i = length + 2;
	str = ft_calloc(length + 3, sizeof(char));
	while (i > 1)
	{
		str[--i] = hex(n % 16);
		n /= 16;
	}
	ft_memcpy(str, "0x", 2);
	return (str);
}

char	*format_x_x_up(t_format fmt, va_list *args, int *len)
{
	char	*s;
	int		i;

	*len = -1;
	s = ft_xtoa(va_arg(*args, unsigned));
	i = 0;
	if (fmt.specifier == 'x')
		return (s);
	while (s[i] != '\0')
	{
		s[i] = (char)ft_toupper(s[i]);
		i++;
	}
	return (s);
}

char	*format_o(t_format fmt, va_list *args, int *len)
{
	*len = -1;
	UNUSED(fmt);
	return (ft_otoa(va_arg(*args, unsigned)));
}
