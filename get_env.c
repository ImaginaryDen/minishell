#include "minishell.h"

char	*get_env(char *str)
{
	int i;

	i = 0;
	while (g_envp[i])
	{
		if(!ft_strncmp(g_envp[i], str, ft_strlen(str) + 1))
			return (g_envp[i]);
		i++;
	}
	return (NULL);
}

void set_env(char *str)
{
	
}