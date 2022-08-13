/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hregina <hregina@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:38:35 by hregina           #+#    #+#             */
/*   Updated: 2022/03/23 17:38:39 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inc_shlvl(char ***env, char ***export)
{
	int		shlvl_current;
	char	*shlvl_new;
	char	*get_shlvl;

	if (get_env("SHLVL", *env, 0))
	{
		shlvl_current = (int)ft_atoi(get_env("SHLVL", *env, 0)) + 1;
		get_shlvl = ft_itoa(shlvl_current);
		shlvl_new = ft_strjoin("SHLVL=", get_shlvl);
		add_env(shlvl_new, env, export);
		free(get_shlvl);
		free(shlvl_new);
	}
	else
		add_env("SHLVL=1", env, export);
	del_elem_arr("OLDPWD", 6, env, 0);
	del_elem_arr("OLDPWD", 6, export, 0);
	add_elem_arr("OLDPWD", export);
}

int	run_command(t_cmd_data *cmds)
{
	int		pid;
	int		status;

	if (!cmds->commands[0] || ft_findpath(cmds->commands,
			cmds->env, &cmds->last_cmd, NULL) == ERROR)
		return (ERROR);
	pid = fork();
	if (pid < 0)
		return (ERROR);
	if (pid == 0)
	{
		execve(cmds->commands[0], cmds->commands, cmds->env);
		exit(cmds->last_cmd);
	}
	ctrl_c_mode(1, &cmds->last_cmd);
	waitpid(pid, &status, 0);
	ctrl_c_mode(0, &cmds->last_cmd);
	if (WIFEXITED(status))
		cmds->last_cmd = WEXITSTATUS(status);
	return (SUCCESS);
}

int	run_build_in(t_cmd_data *cmds, char ***env, char ***export)
{
	if (ft_strcmp(*cmds->commands, "pwd") == 0)
		cmds->last_cmd = ft_pwd();
	if (ft_strcmp(*cmds->commands, "cd") == 0)
		cmds->last_cmd = ft_cd(cmds->commands, env, export);
	if (ft_strcmp(*cmds->commands, "echo") == 0)
		cmds->last_cmd = ft_echo(cmds->commands, 0, "\n");
	if (ft_strcmp(*cmds->commands, "env") == 0)
		cmds->last_cmd = ft_env(*env);
	if (ft_strcmp(*cmds->commands, "unset") == 0)
		cmds->last_cmd = ft_unset(cmds->commands, env, export);
	if (ft_strcmp(*cmds->commands, "export") == 0)
		cmds->last_cmd = ft_export(cmds->commands, env, export);
	if (ft_strcmp(*cmds->commands, "exit") == 0)
		cmds->last_cmd = ft_exit(cmds->commands);
	return (0);
}

int	check_build_in(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (SUCCESS);
	if (ft_strcmp(command, "cd") == 0)
		return (SUCCESS);
	if (ft_strcmp(command, "pwd") == 0)
		return (SUCCESS);
	if (ft_strcmp(command, "export") == 0)
		return (SUCCESS);
	if (ft_strcmp(command, "unset") == 0)
		return (SUCCESS);
	if (ft_strcmp(command, "env") == 0)
		return (SUCCESS);
	if (ft_strcmp(command, "exit") == 0)
		return (SUCCESS);
	return (0);
}
