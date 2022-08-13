/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*       hregina                                      +:+ +:+         +:+     */
/*   By: exerath                                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 19:51:13 by hregina & exerath #+#    #+#             */
/*   Updated: 2022/03/18 19:51:39 by hregina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_backslash(int signum)
{
	(void)signum;
}

int	ctrl_c_mode(int mode, int *last_cmd)
{
	static int	ctrl_c_mode = 0;

	if (mode == -1)
		return (ctrl_c_mode);
	ctrl_c_mode = mode;
	*last_cmd = 130;
	return (mode);
}

void	ctrl_c_handler(int signum)
{
	int	i;

	(void)signum;
	rl_on_new_line();
	ft_printf(" \n");
	rl_replace_line("", 0);
	if (ctrl_c_mode(-1, &i) == 0)
		rl_redisplay();
}

void	process_input(t_cmd_data *cmds, char *input, int i)
{
	add_history(input);
	if (parsing(&input, cmds) != ERROR && ft_strlen(cmds->commands[0]) != 0)
	{
		cmds->counter = cnt_str_arr(cmds->commands);
		process_cmds(cmds, -1, 0);
	}
	free_arr(cmds->commands);
	while (i < 300)
	{
		if (cmds->all_cmds[i].cnt_redir > 0)
		{
			free(cmds->all_cmds[i].type_redir);
			free_arr(cmds->all_cmds[i].file);
		}
		else
			free(cmds->all_cmds[i].file);
		if (cmds->all_cmds[i].command != NULL)
			free(cmds->all_cmds[i].command);
		i++;
	}
	free(cmds->pipes);
	free(cmds->is_pipe);
	free(cmds->all_cmds);
}

int	main(int argc, char **argv, char **env)
{
	t_cmd_data	cmds;
	char		*input;

	rl_catch_signals = 0;
	cmds.last_cmd = 0;
	if (create_my_env(env, &cmds.env, &cmds.export) == ERROR)
		return (ERROR);
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, ctrl_c_backslash);
	while (argc > 0 || argv != NULL)
	{
		input = readline(GREEN"minishell $ "RESET);
		if (!input)
			break ;
		if (is_empty(input))
		{
			free(input);
			continue ;
		}
		process_input(&cmds, input, 0);
	}
	free_arr(cmds.env);
	free_arr(cmds.export);
	ft_printf("exit\n");
}
