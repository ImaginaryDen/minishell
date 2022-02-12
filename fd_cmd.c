#include "minishell.h"

int ft_one_cmd(t_pipe_data *data)
{
	int pid;
	int	save_in;
	int	save_out;
	int	save_err;

	save_in = dup(STDIN_FILENO);
	save_out = dup(STDOUT_FILENO);
	save_err = dup(STDERR_FILENO);

	dup2(data->fd_in_out[READ_FD], STDIN_FILENO);
	dup2(data->fd_in_out[WRITE_FD], STDOUT_FILENO);
	dup2(data->fd_in_out[ERR_FD], STDERR_FILENO);
	check_cmd(data);
	check(data->cmd_arg);
	if (exev_include(data))
		return (0);
	else
	{
		pid = fork();
		if (!pid)
			execve(data->cmd_arg[0], data->cmd_arg, g_envp);
		waitpid(pid, NULL, 0);
	}
	dup2(save_in, data->fd_in_out[READ_FD]);
	dup2(save_out, data->fd_in_out[WRITE_FD]);
	dup2(save_err, data->fd_in_out[ERR_FD]);
	if (data->fd_in_out[READ_FD] != STDIN_FILENO)
		close(data->fd_in_out[READ_FD]);
	if (data->fd_in_out[WRITE_FD] != STDOUT_FILENO)
		close(data->fd_in_out[WRITE_FD]);
	if (data->fd_in_out[ERR_FD] != STDERR_FILENO)
		close(data->fd_in_out[ERR_FD]);
}

int	ft_cmd(t_pipe_data *data)
{
	int		ret;
	int i;

	i = 0;
	while (i < 2)
	{
		if(data->fd_close[i] > 0)
			close(data->fd_close[i]);
		i++;
	}
	printf("in- %d\nout- %d\n",data->fd_in_out[READ_FD], data->fd_in_out[WRITE_FD]);
	dup2(data->fd_in_out[READ_FD], STDIN_FILENO);
	dup2(data->fd_in_out[WRITE_FD], STDOUT_FILENO);
	dup2(data->fd_in_out[ERR_FD], STDERR_FILENO);
	ret = 0;
	errno = 0;
	if (exev_include(data))
		exit(ret);	
	check_cmd(data);
	if (!check(data->cmd_arg) && data->cmd_arg != NULL)
		ret = execve(data->cmd_arg[0], data->cmd_arg, g_envp);
}

void	free_cmd(t_pipe_data *data)
{
	if (data->cmd_arg)
	{
		ft_free_dable_arr(data->cmd_arg);
		data->cmd_arg = NULL;
	}
}

pid_t	get_fork(t_pipe_data *cmd, pid_t *pid, int i)
{
	pid[i] = fork();
	if (pid[i] == -1)
	{
		perror("fork");
		return (-1);
	}
	return (0);
}

void	ft_wait_all_pid(pid_t *pid_cmd, int size)
{
	int	i;
	int	status;	

	i = 0;
	while (i < size)
	{
		if(pid_cmd[i])
			waitpid(pid_cmd[i], &status, 0);
		i++;
	}
}

int	ft_run_cmds(t_pipe_data *cmds, int size)
{
	int		i;
	pid_t	*pid_cmd;

	pid_cmd = malloc(sizeof(pid_t) * size);
	ft_bzero(pid_cmd, sizeof(pid_t) * size);
	if (!pid_cmd)
		return (0);
	i = 0;
	while (i < size)
	{
		printf("%d\n", i);
		if (get_fork(cmds + i, pid_cmd, i))
			break ;
		if (!pid_cmd[i])
		{
			ft_cmd(cmds + i);
			exit(0);
		}
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
