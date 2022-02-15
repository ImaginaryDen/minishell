#include "minishell.h"

void ft_unset(char **args)
{
	int	i;

	i = 1;
	g_status = 0;
	while (args[i])
	{
		unset_env(args[i]);
		i++;
	}
}