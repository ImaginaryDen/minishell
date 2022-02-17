#include "minishell.h"

void ft_env(char **arg)
{
	int	i;

	i = 0;
	g_status = 0;
	while (g_envp && g_envp[i])
	{
		if (ft_strchr(g_envp[i], '='))
		{
			ft_putstr_fd(g_envp[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
}