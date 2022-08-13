/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_run_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:46:59 by hregina           #+#    #+#             */
/*   Updated: 2022/03/18 19:47:01 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_lines(char *end)
{
	int		fds[2];
	int		prev_out_fd;
	char	*s;

	pipe(fds);
	prev_out_fd = dup(STDERR_FILENO);
	dup2(fds[1], STDERR_FILENO);
	ft_close(fds[1]);
	s = readline("> ");
	while (s)
	{
		if (ft_strcmp(s, end) == 0)
		{
			free(s);
			break ;
		}
		write(STDERR_FILENO, s, ft_strlen(s));
		write(STDERR_FILENO, "\n", 1);
		free(s);
		s = readline("> ");
	}
	ft_close(STDERR_FILENO);
	dup2(prev_out_fd, STDERR_FILENO);
	ft_close(prev_out_fd);
	return (fds[0]);
}

void	init_flags_mask(int *flags, int *mask, int redir_type)
{
	*flags = 0;
	*mask = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (redir_type == 2)
		*flags = O_CREAT | O_RDWR | O_TRUNC;
	if (redir_type == 4)
		*flags = O_CREAT | O_RDWR | O_APPEND;
}

int	prepare_redir(char *file, int *redir_in_fd,
		int *redir_out_fd, int redir_type)
{
	int	flags;
	int	mask;

	init_flags_mask(&flags, &mask, redir_type);
	if (*redir_out_fd >= 0)
		ft_close(*redir_out_fd);
	if (redir_type == 2 || redir_type == 4)
	{
		*redir_out_fd = open(file, flags, mask);
		if (*redir_out_fd == -1)
			return (ERROR);
	}
	else if (redir_type == 1 || redir_type == 3)
	{
		if (redir_type == 1)
			*redir_in_fd = open(file, O_RDONLY);
		else
			*redir_in_fd = read_lines(file);
		if (*redir_in_fd == -1)
			return (ERROR);
	}
	else
		return (ERROR);
	return (SUCCESS);
}

int	run_cmd_pipe(t_cmd_data *cmds, t_fds fd, int status)
{
	pid_t	pid;

	if (ft_findpath(cmds->commands, cmds->env, &cmds->last_cmd, NULL) == ERROR)
		return (ERROR);
	pid = fork();
	if (pid < 0)
		return (ERROR);
	if (!pid)
	{
		fd_pipe_redir(&fd, 0);
		if (check_build_in(cmds->commands[0]))
			run_build_in(cmds, &cmds->env, &cmds->export);
		else
			execve(cmds->commands[0], cmds->commands, cmds->env);
		exit(cmds->last_cmd);
	}
	ctrl_c_mode(1, &cmds->last_cmd);
	if (cmds->is_last_pipe == 1)
		close_fd(cmds, &status, pid);
	ctrl_c_mode(0, &cmds->last_cmd);
	if (cmds->is_last_pipe == 1 && WIFEXITED(status))
		cmds->last_cmd = WEXITSTATUS(status);
	return (SUCCESS);
}

int	process_cmds(t_cmd_data *cmds, int i, int j)
{
	t_fds	fd;

	fd.prev_pipe = NULL;
	cmds->pipe_count = 0;
	while (++i < cmds->counter)
	{
		free_arr(cmds->commands);
		cmds->commands = ft_split(cmds->all_cmds[i].command, 2);
		init_fd_redir(cmds, i, &fd);
		j = -1;
		while (++j < cmds->all_cmds[i].cnt_redir)
			if (prepare_redir(cmds->all_cmds[i].file[j], &fd.redir_fds[0],
					&fd.redir_fds[1], cmds->all_cmds[i].type_redir[j]) == ERROR)
				return (error_file(cmds->all_cmds[i].file[j], &cmds->last_cmd));
		if (cmds->is_pipe[i] == 1 || (i > 0 && cmds->is_pipe[i - 1])
			|| !cmds->is_last_pipe)
		{
			process_fd_pipe(cmds, i, &fd);
			run_cmd_pipe(cmds, fd, 0);
			replace_fd_pipe(&fd);
		}
		else
			cmds_fd_no_pipe(cmds, &fd, 0);
	}
	return (SUCCESS);
}
