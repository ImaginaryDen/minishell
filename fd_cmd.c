#include "minishell.h"

int			return_error(char *cmd, char *msg, int ret, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	return (ret);
}

static int	check(char **args)
{
	struct stat	f;
	int			flag;

	if (stat(args[0], &f) != -1)
	{
		if (f.st_mode & S_IFDIR)
			return (return_error(args[0], ": Is a directory\n", 0, 126));
		if (f.st_mode & S_IXUSR && f.st_mode & S_IRUSR)
			return (0);
		return (return_error(args[0], ": Permission denied\n", 0, 126));
	}
	else if (!ft_strncmp(args[0], "./", 2) || args[0][0] == '/')
	{
		return (return_error(args[0], ": No such file or directory\n", 0, 127));
	}
	return (return_error(args[0], ": command not found\n", 0, 127));
}

void	ft_close_pipe(t_pipe_data *cmd)
{
	int i;

	i = 0;
	while (i < 2)
	{
		if(cmd->fd_close[i] > 0)
			close(cmd->fd_close[i]);
		i++;
	}
}

int	ft_cmd(t_pipe_data *data)
{
	int		ret;

	ft_close_pipe(data);
	check_cmd(data);
	if (data->fd_in_out[READ_FD] > 0)
		dup2(data->fd_in_out[READ_FD], STDIN_FILENO);
	if (data->fd_in_out[WRITE_FD] > 0)
		dup2(data->fd_in_out[WRITE_FD], STDOUT_FILENO);
	if (data->fd_in_out[ERR_FD] > 0)
		dup2(data->fd_in_out[ERR_FD], STDERR_FILENO);
	check(data->cmd_ard);
	ret = 0;
	errno = 0;
	if (data->cmd_ard != NULL)
		ret = execve(data->cmd_ard[0], data->cmd_ard, data->env);
	exit(ret);
}

void	free_cmd(t_pipe_data *data)
{
	if (data->cmd_ard)
	{
		ft_free_dable_arr(data->cmd_ard);
		data->cmd_ard = NULL;
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
	i = 0;
	while (i < size)
	{
		if(pid_cmd[i])
			kill(pid_cmd[i], SIGTERM);
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
		if (get_fork(cmds + i, pid_cmd, i))
			break ;
		if (!pid_cmd[i])
			ft_cmd(cmds + i);
		if (cmds[i].fd_in_out[WRITE_FD] > 0)
			close(cmds[i].fd_in_out[WRITE_FD]);
		if (cmds[i].fd_in_out[READ_FD] > 0)
			close(cmds[i].fd_in_out[READ_FD]);
		i++;
	}
	ft_wait_all_pid(pid_cmd, size);
	free(pid_cmd);
	return (0);
}
