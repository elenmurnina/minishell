NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror
HEADER = libft.h

SRC = ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memccpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_max.c \
	ft_min.c \
	ft_strlen.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strnstr.c \
	ft_strncmp.c \
	ft_atoi.c \
	ft_itoa.c \
	ft_utoa.c \
	ft_otoa.c \
	ft_xtoa.c \
	ft_swap.c \
    ft_reverse.c \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_calloc.c \
	ft_realloc.c \
	ft_strcmp.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c

OBJS = $(patsubst %.c, %.o, $(SRC))

%.o:		%.c $(HEADER)
			$(CC) $(CFLAGS) -c $*.c

$(NAME):	$(OBJS) $(SRC) $(HEADER) Makefile
			ar rsc $(NAME) $(OBJS) 

all:		$(NAME)

clean:
			rm -f $(OBJS) $(BOBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
