#include "minishell.h"

void	ft_env(char **arg)
{
	int	i;

	i = 0;
	(void)arg;
	while (g_info.envp && g_info.envp[i])
	{
		if (ft_strchr(g_info.envp[i], '='))
		{
			ft_putstr_fd(g_info.envp[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
}