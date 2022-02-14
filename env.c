#include "minishell.h"

char *get_env_name(char *name)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(name);
	while(g_envp[i])
	{
		if (g_envp[i][len] == '=' && !ft_strncmp(g_envp[i], name, len))
			return g_envp[i];
		i++;
	}
	return (NULL);
}