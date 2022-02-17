#include "minishell.h"

void ft_exit(char **argv)
{
	if (argv == NULL)
		ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	ft_free_dable_arr(g_history);
	ft_free_dable_arr(g_envp);
	exit(g_status);
}