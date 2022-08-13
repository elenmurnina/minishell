/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*       hregina                                      +:+ +:+         +:+     */
/*   By: exerath                                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:49:25 by hregina           #+#    #+#             */
/*   Updated: 2022/03/18 19:51:00 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# define SUCCESS 1
# define ERROR 0

# define GREEN "\001\033[1;92m\002"
# define RESET "\001\033[0m\002"

typedef struct s_command
{
	char	*command;
	int		*type_redir;
	int		cnt_redir;
	char	**file;
}				t_command;

typedef struct s_cmd_data
{
	t_command	*all_cmds;
	char		**commands;
	char		**env;
	char		**export;
	int			is_redir;
	int			*is_pipe;
	int			counter;
	int			last_cmd;
	int			j;
	int			is_last_pipe;
	int			*pipes;
	int			pipe_count;
}				t_cmd_data;

typedef struct s_fds
{
	int	*next_pipe;
	int	*prev_pipe;
	int	prev_pipe_in;
	int	prev_pipe_out;
	int	next_pipe_in;
	int	next_pipe_out;
	int	redir_fds[2];
	int	prev_fds[2];
}				t_fds;

//main.c (signal_cntrl_c)
int		ctrl_c_mode(int mode, int *last_cmd);

//сhange_get_env.c
int		len_env_key(char *str);
int		len_env_all(char *str);
void	add_env(char *cmd, char ***env, char ***export);
char	*get_env(char *check_env, char **env, int *last_cmd);
int		create_my_env(char **env, char ***my_env, char ***my_export);

//parser.c
int		parsing(char **line, t_cmd_data *cmds);

//edit_env.c
char	*add_char_to_string(char **str, char c);
int		edit_env_cmd(t_cmd_data *cmd);

//precheck_command.c
int		check_quote_open(int quote, char *line, int len_line);
int		check_begin(char *line, char check, int *last_cmd);
int		check_empty_cmd(char *cmd, int *last_cmd);
int		precheck_special(char *l, int len_line, int *last_cmd, int space);

//check_redir_pipe.c
int		find_special(t_cmd_data *cmds, int len_line, int quote);
int		check_redir(t_cmd_data *cmds, int i, int j);

//splitter.c
int		cmd_splitter(char ***cmds, int *cmds_counter);
char	*get_filename(char *cmd, int pos, int quote, char *to_erase);
void	erase_redirection_start(char *cmd, int pos, char *to_erase);

//cmds.c
void	inc_shlvl(char ***env, char ***export);
int		run_command(t_cmd_data *cmds);
int		run_build_in(t_cmd_data *cmds, char ***env, char ***export);
int		check_build_in(char *command);

//process_run_cmds.c
int		prepare_redir(char *file, int *redir_in_fd, int *redir_out_fd,
			int redir_type);
int		process_cmds(t_cmd_data *cmds, int i, int j);

//process_fd.c
void	init_fd_redir(t_cmd_data *cmds, int i, t_fds *fd);
void	fd_pipe_redir(t_fds *fd, int tmp_fd);
void	process_fd_pipe(t_cmd_data *cmds, int i, t_fds *fd);
void	cmds_fd_no_pipe(t_cmd_data *cmds, t_fds *fd, int i);
void	replace_fd_pipe(t_fds *fd);

//build_in.c
int		ft_pwd(void);
int		ft_cd(char **path, char ***env, char ***export);
int		ft_echo(char **command, int flag_n, char *new_line);

//build_in_2.c
int		ft_env(char **env);
int		ft_unset(char **cmd, char ***env, char ***export);
int		is_env_valid(char *command, char *cmd, int *i, int *last_cmd);

//build_in_3.c
int		ft_export(char **cmd, char ***env, char ***export);

//exit.c
void	ft_close(int fd);
void	close_fd(t_cmd_data *cmds, int *status, pid_t pid);
int		ft_exit(char **command);

//findpath.c
int		ft_findpath(char **cmd, char **env, int *last_cmd, char *tmp);

//print_error.c
int		print_syntax_error(char *c, int cnt, int *last_cmd);
int		print_command_not_found(char *command, int *last_cmd);
int		print_no_such_file_dir(char *command, int *last_cmd);
int		print_not_valid_identifier(char *command, char *cmd, int *last_cmd);
int		error_file(char *file_name, int *last_cmd);

//array_actions.c
int		cnt_str_arr(char **str);
void	free_arr(char **arr);
int		add_elem_arr(char *el_add, char ***arr);
int		del_elem_arr(char *el_del, int el_len, char ***arr, int i);
int		add_elem_int(int el_add, int **arr, int *cnt);

//other_utils.c
int		is_empty_char(char c);
int		is_special_char(char c);
int		is_empty(char *str);
int		print_no_such_file_dir_cd(char *dir);

#endif
