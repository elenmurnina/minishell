/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:23:11 by hregina           #+#    #+#             */
/*   Updated: 2022/04/29 19:23:13 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/libft.h"

typedef struct s_format
{
	int		flag_minus;
	int		flag_space;
	int		flag_zero;
	int		width;
	int		precision;
	char	specifier;
}			t_format;

typedef struct s_print_result
{
	int			char_count;
}			t_print_result;

int			ft_printf(const char *pattern, ...);
char		*format_percent(t_format fmt, va_list *args, int *len);
char		*format_d(t_format fmt, va_list *args, int *len);
char		*format_s(t_format fmt, va_list *args, int *len);
char		*format_c(t_format fmt, va_list *args, int *len);
char		*format_u(t_format fmt, va_list *args, int *len);
char		*format_x_x_up(t_format fmt, va_list *args, int *len);
char		*format_o(t_format fmt, va_list *args, int *len);
char		*format_p(t_format fmt, va_list *args, int *len);
char		*internal_format_width(t_format fmt, char *s, int *len);
char		*format_width(t_format fmt, char *s, int *len);
char		*format_precision(t_format fmt, char *s, int *len);
int			is_numeric_specifier(t_format fmt);
void		parse_flags(const char *s, int *pos, t_format *fmt);
void		parse_width(const char *s, int *pos, t_format *fmt, va_list *args);
void		parse_precision(const char *s, int *pos, t_format *fmt,
				va_list *args);
t_format	parse(const char *s, int *pos, va_list *args);

#endif
