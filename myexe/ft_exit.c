#include "minishell.h"

void ft_exit(char **argv)
{
	if (argv == NULL)
		ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	ft_free_double_arr(g_info.history);
	ft_free_double_arr(g_info.envp);
	exit(g_info.status);
}