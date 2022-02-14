#include "minishell.h"

char *get_env(char *name)
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

int			set_env(char *env, char *new_env)
{
	char	*tmp;
	int		i;
	int		len;

	if (!env || !new_env)
		return (0);
	len = ft_strlen(env);
	i = 0;
	while (g_envp[i] && ft_strncmp(env, g_envp[i], len))
		i++;
	if (g_envp[i])
	{
		len = ft_strlen(env) + ft_strlen(new_env) + 2;
		g_envp[i] = ft_realloc(g_envp[i], len);
		ft_strchr(g_envp[i], '=')[1] = 0;
		ft_strlcat(g_envp[i], new_env, len);
		return (0);
	}
	g_envp = ft_realloc(g_envp, sizeof(char *) * (i + 2));
	g_envp[i + 1] = NULL;
	tmp = ft_strjoin(env, "=");
	g_envp[i] = ft_strjoin(tmp, new_env);
	free(tmp);
	return(0);
}
