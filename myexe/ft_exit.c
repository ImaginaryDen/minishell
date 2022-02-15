#include "minishell.h"

void ft_exit(char **argv)
{
	//ft_putstr_fd("exit\n", 1);
	exit(g_status);
}