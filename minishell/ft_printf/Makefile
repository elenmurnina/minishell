NAME = libftprintf.a

CC = gcc
HEADER = ft_printf.h

CFLAGS = -Wall -Wextra -Werror

SRC =	ft_printf.c \
	ft_printf_format.c \
	ft_printf_format_extra.c \
	ft_printf_format_width.c \
	ft_printf_format_precision.c \
	ft_printf_parse.c

OBJS = $(patsubst %.c, %.o, $(SRC))

%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) -c $*.c

$(NAME):	$(OBJS) $(SRC) $(HEADER) Makefile
			ar rsc $(NAME) $(OBJS)

all:		$(NAME)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
