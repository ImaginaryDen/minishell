/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:53:11 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/11 18:13:34 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	status_child(int pid)
{
	if (WIFEXITED(pid))
		g_info.status = WEXITSTATUS(pid);
	if (WIFSIGNALED(pid))
	{
		g_info.status = WTERMSIG(pid);
		if (g_info.status != 131)
			g_info.status += 128;
	}
}

void	free_cmd(t_pipe_data *data)
{
	if (data->cmd_arg)
	{
		ft_free_double_arr(data->cmd_arg);
		data->cmd_arg = NULL;
	}
}

void	set_redir(int *end)
{
	dup2(end[READ_FD], STDIN_FILENO);
	dup2(end[WRITE_FD], STDOUT_FILENO);
	dup2(end[ERR_FD], STDERR_FILENO);
}

pid_t	get_fork(t_pipe_data *cmd, pid_t *pid, int i)
{
	pid[i] = fork();
	g_info.pid = pid[i];
	if (pid[i] == -1)
	{
		perror("fork");
		return (-1);
	}
	return (0);
}