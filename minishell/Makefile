NAME = minishell
HEADER = minishell.h
LIBREADLINEDIR = /usr/local/opt/readline/8.1.2

LIBFTPATH = ./libft
LIBFTNAME = $(LIBFTPATH)/libft.a
LIBFTSRC = $(shell find $(LIBFTPATH) -name '*.c')
LIBFTOBJS = $(patsubst %.c, %.o, $(LIBFTSRC))

PRINTFPATH = ./ft_printf
PRINTFNAME = $(PRINTFPATH)/libftprintf.a
PRINTFSRC = $(shell find $(PRINTFPATH) -name '*.c')
PRINTFOBJS = $(patsubst %.c, %.o, $(PRINTFSRC))

CC = gcc
CFLAGS = -Werror -Wall -Wextra -I$(LIBREADLINEDIR)/include
LFLAGS = -lreadline -L$(LIBREADLINEDIR)/lib

SRC =	main.c \
		change_get_env.c \
		parser.c \
		splitter.c \
		edit_env.c \
		precheck_command.c \
		check_redir_pipe.c \
		cmds.c \
		process_run_cmds.c \
		process_fd.c \
		build_in.c \
        build_in_2.c \
        build_in_3.c \
        exit.c \
		findpath.c \
		print_error.c \
		array_actions.c \
		other_utils.c

OBJS = $(patsubst %.c, %.o, $(SRC))

%.o:	%.c $(HEADER)
		$(CC) $(CFLAGS) -c $*.c

$(NAME): $(OBJS) $(LIBFTPATH) $(PRINTFPATH) $(HEADER) Makefile
		make -C $(LIBFTPATH)
		make -C $(PRINTFPATH)
		$(CC) $(CFLAGS) $(OBJS) $(LIBFTOBJS) $(PRINTFOBJS) -o $(NAME) $(LFLAGS)

all: 	$(NAME)

clean:
		rm -rf $(LIBFTPATH)/*.o
		rm -rf $(PRINTFPATH)/*.o
		rm -f $(OBJS)

fclean: clean
		rm -f $(LIBFTNAME) $(PRINTFNAME) $(NAME)

re: 	fclean $(NAME)

.PHONY: all clean fclean re
