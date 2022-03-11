/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:48:06 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/11 19:33:24 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor(t_pipe_data *comand)
{
	int	size;
	int	i;

	size = 0;
	if (!comand)
		return (1);
	while (comand[size].cmd_arg != NULL)
		size++;
	if (size == 1)
		ft_one_cmd(comand);
	else if (size > 1)
		ft_run_cmds(comand, size);
	i = 0;
	while (i < size)
	{
		ft_free_double_arr(comand[i].cmd_arg);
		i++;
	}
	g_info.pid = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	free(comand);
	return (0);
}

t_pipe_data	*init_cmds_fds(int size)
{
	int			i;
	t_pipe_data	*commands;

	commands = malloc(sizeof(t_pipe_data) * (size + 1));
	commands[size].cmd_arg = NULL;
	i = 0;
	while (i < size)
	{
		commands[i].fd_in_out[READ_FD] = STDIN_FILENO;
		commands[i].fd_in_out[WRITE_FD] = STDOUT_FILENO;
		commands[i].fd_in_out[ERR_FD] = STDERR_FILENO;
		commands[i].fd_close[0] = -1;
		commands[i].fd_close[1] = -1;
		commands[i].cmd_arg = NULL;
		i++;
	}
	return (commands);
}
