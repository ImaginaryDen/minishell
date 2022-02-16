#include "minishell.h"

void ft_exit(char **argv)
{
	if (argv == NULL)
		ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	exit(g_status);
}