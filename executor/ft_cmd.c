/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:49:38 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/11 18:09:34 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_cmd(t_pipe_data *data)
{
	int	status;

	check_cmd(data);
	g_info.pid = fork();
	if (!g_info.pid)
	{
		if (!check(data->cmd_arg))
			execve(data->cmd_arg[0], data->cmd_arg, g_info.envp);
		else
			exit(g_info.status);
	}
	if (ft_strnstr(data->cmd_arg[0], "minishell",
			ft_strlen(data->cmd_arg[0])))
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	waitpid(g_info.pid, &status, 0);
	g_info.pid = 0;
	status_child(status);
}

int	ft_one_cmd(t_pipe_data *data)
{
	int	save[3];
	int	status;

	save[READ_FD] = dup(STDIN_FILENO);
	save[WRITE_FD] = dup(STDOUT_FILENO);
	save[ERR_FD] = dup(STDERR_FILENO);
	set_redir(data->fd_in_out);
	if (!exev_include(data))
		fork_cmd(data);
	close(data->fd_in_out[READ_FD]);
	close(data->fd_in_out[WRITE_FD]);
	close(data->fd_in_out[ERR_FD]);
	set_redir(save);
	return (0);
}

int	ft_cmd(t_pipe_data *data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (data->fd_close[i] > 0)
			close(data->fd_close[i]);
		i++;
	}
	dup2(data->fd_in_out[READ_FD], STDIN_FILENO);
	dup2(data->fd_in_out[WRITE_FD], STDOUT_FILENO);
	dup2(data->fd_in_out[ERR_FD], STDERR_FILENO);
	errno = 0;
	if (!exev_include(data))
	{
		check_cmd(data);
		if (!check(data->cmd_arg) && data->cmd_arg != NULL)
			execve(data->cmd_arg[0], data->cmd_arg, g_info.envp);
	}
	exit(g_info.status);
}

void	ft_wait_all_pid(pid_t *pid_cmd, int size)
{
	int	i;
	int	status;	

	i = 0;
	while (i < size)
	{
		if (pid_cmd[i])
		{
			waitpid(pid_cmd[i], &status, 0);
			status_child(status);
		}
		i++;
	}
}

int	ft_run_cmds(t_pipe_data *cmds, int size)
{
	int		i;
	pid_t	*pid_cmd;

	pid_cmd = malloc(sizeof(pid_t) * size);
	exit_if_null(pid_cmd, "malloc");
	ft_bzero(pid_cmd, sizeof(pid_t) * size);
	if (!pid_cmd)
		return (0);
	i = 0;
	while (i < size)
	{
		if (get_fork(cmds + i, pid_cmd, i))
			break ;
		if (!pid_cmd[i])
			ft_cmd(cmds + i);
		if (cmds[i].fd_in_out[WRITE_FD] != STDOUT_FILENO)
			close(cmds[i].fd_in_out[WRITE_FD]);
		if (cmds[i].fd_in_out[READ_FD] != STDIN_FILENO)
			close(cmds[i].fd_in_out[READ_FD]);
		i++;
	}
	ft_wait_all_pid(pid_cmd, size);
	free(pid_cmd);
	return (0);
}
