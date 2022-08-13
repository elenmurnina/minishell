/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:46:59 by hregina           #+#    #+#             */
/*   Updated: 2022/03/18 19:47:01 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_fd_redir(t_cmd_data *cmds, int i, t_fds *fd)
{
	if (i > 0 && i - 1 < cmds->counter && cmds->all_cmds[i - 1].command
		&& ft_strncmp(cmds->all_cmds[i - 1].command, "yes", 3) != 0)
		cmds->j = -2;
	(*fd).redir_fds[0] = -1;
	(*fd).redir_fds[1] = -1;
}

void	fd_pipe_redir(t_fds *fd, int tmp_fd)
{
	if (fd->prev_pipe_in != STDIN_FILENO)
	{
		tmp_fd = dup(STDIN_FILENO);
		dup2(fd->prev_pipe_in, STDIN_FILENO);
		ft_close(fd->prev_pipe_in);
		ft_close(tmp_fd);
	}
	if (fd->next_pipe_out != STDOUT_FILENO)
	{
		tmp_fd = dup(STDOUT_FILENO);
		ft_close(fd->next_pipe_in);
		dup2(fd->next_pipe_out, STDOUT_FILENO);
		ft_close(fd->next_pipe_out);
		ft_close(tmp_fd);
	}
	if ((fd->redir_fds)[0] >= 0)
	{
		dup2((fd->redir_fds)[0], STDIN_FILENO);
		ft_close((fd->redir_fds)[0]);
	}
	if ((fd->redir_fds)[1] >= 0)
	{
		dup2((fd->redir_fds)[1], STDOUT_FILENO);
		ft_close((fd->redir_fds)[1]);
	}
}

void	process_fd_pipe(t_cmd_data *cmds, int i, t_fds *fd)
{
	if (cmds->is_pipe[i] == 0 && i > 0 && cmds->is_pipe[i - 1] == 1
		&& (i + 1 == cmds->counter
			|| (i + 1 < cmds->counter && cmds->is_pipe[i + 1] == 0)))
		cmds->is_last_pipe = 1;
	else
		cmds->is_last_pipe = 0;
	(*fd).next_pipe = NULL;
	if (cmds->is_pipe[i] == 1)
	{
		(*fd).next_pipe = malloc(sizeof(int) * 2);
		pipe((*fd).next_pipe);
		cmds->pipes[cmds->pipe_count++] = (*fd).next_pipe[0];
		cmds->pipes[cmds->pipe_count++] = (*fd).next_pipe[1];
	}
	(*fd).prev_pipe_in = STDIN_FILENO;
	if ((*fd).prev_pipe)
		(*fd).prev_pipe_in = (*fd).prev_pipe[0];
	(*fd).next_pipe_out = STDOUT_FILENO;
	if ((*fd).next_pipe)
	{
		(*fd).next_pipe_in = (*fd).next_pipe[0];
		(*fd).next_pipe_out = (*fd).next_pipe[1];
	}
}

void	replace_fd_pipe(t_fds *fd)
{
	if ((*fd).prev_pipe)
		ft_close((*fd).prev_pipe[0]);
	if ((*fd).next_pipe)
		ft_close((*fd).next_pipe[1]);
	free((*fd).prev_pipe);
	(*fd).prev_pipe = (*fd).next_pipe;
}

void	cmds_fd_no_pipe(t_cmd_data *cmds, t_fds *fd, int i)
{
	while (i < 2)
	{
		if ((*fd).redir_fds[i] >= 0)
		{
			(*fd).prev_fds[i] = dup(i);
			dup2((*fd).redir_fds[i], i);
			ft_close((*fd).redir_fds[i]);
		}
		i++;
	}
	if (cmds->commands[0] && check_build_in(cmds->commands[0]))
		run_build_in(cmds, &cmds->env, &cmds->export);
	else
		run_command(cmds);
	i = 0;
	while (i < 2)
	{
		if ((*fd).redir_fds[i] >= 0)
		{
			dup2((*fd).prev_fds[i], i);
			ft_close((*fd).prev_fds[i]);
		}
		i++;
	}
}
