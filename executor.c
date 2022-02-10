#include "minishell.h"

int	executor(t_pipe_data *comand)
{
	int size;

	size = 0;
	while(comand[size].cmd_ard != NULL)
		size++;
	ft_run_cmds(comand, size);
	for(int i = 0; i < size; i++)
		ft_free_dable_arr(comand[i].cmd_ard);
	free(comand);
}
