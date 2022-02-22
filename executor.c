#include "minishell.h"

int	executor(t_pipe_data *comand)
{
	int size;

	size = 0;
	if (!comand)
		return (1);
	while(comand[size].cmd_arg != NULL)
		size++;
	if(size == 1)
		ft_one_cmd(comand);
	else if (size > 1)
		ft_run_cmds(comand, size);
	for(int i = 0; i < size; i++)
		ft_free_dable_arr(comand[i].cmd_arg);
	g_pid = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	free(comand);
	return (0);
}

void init_cmds_fds(t_pipe_data *commands, int size)
{
	int i;

	i = 0;
	while(i < size)
	{
		commands[i].fd_in_out[READ_FD] = STDIN_FILENO;
		commands[i].fd_in_out[WRITE_FD] = STDOUT_FILENO;
		commands[i].fd_in_out[ERR_FD] = STDERR_FILENO;
		commands[i].fd_close[0] = -1;
		commands[i].fd_close[1] = -1;
		commands[i].cmd_arg = NULL;
		i++;
	}
}
