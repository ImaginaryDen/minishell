#include "minishell.h"



int	executor(t_comands *comands, t_info *info)
{
	int size = 3;
	int end[size];
	t_pipe_data *comand;
	
	comand = malloc(sizeof(t_pipe_data) * size);
	pipe(end);
	pipe(end + 2);
	comand[0].fd_in_out[READ_FD] = -1;
	comand[0].fd_in_out[WRITE_FD] = end[WRITE_FD];
	comand[0].fd_in_out[ERR_FD] = -1;
	comand[0].fd_close[0] = end[READ_FD];
	comand[0].fd_close[1] = -1;
	comand[0].env = info->env;
	comand[0].cmd_ard = ft_split("/usr/bin/ls -la", ' ');

	comand[1].fd_in_out[READ_FD] = end[READ_FD];
	comand[1].fd_in_out[WRITE_FD] = end[WRITE_FD + 2];
	comand[1].fd_in_out[ERR_FD] = -1;
	comand[1].fd_close[0] = end[WRITE_FD];
	comand[1].fd_close[1] = end[READ_FD + 2];
	comand[1].env = info->env;
	comand[1].cmd_ard = ft_split("cat", ' ');

	comand[2].fd_in_out[READ_FD] = end[READ_FD + 2];
	comand[2].fd_in_out[WRITE_FD] = -1;
	comand[2].fd_in_out[ERR_FD] = -1;
	comand[2].fd_close[0] = end[WRITE_FD + 2];
	comand[2].fd_close[1] = -1;
	comand[2].env = info->env;
	comand[2].cmd_ard = ft_split("/usr/bin/head -3", ' ');

	ft_run_cmds(comand, size);
	for(int i = 0; i < size; i++)
		ft_free_dable_arr(comand[i].cmd_ard);
	free(comand);
	exit(0);
}
