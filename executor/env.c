#include "minishell.h"

char	*get_env(char *name)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(name);
	while(g_info.envp[i])
	{
		if (g_info.envp[i][len] == '=' && !ft_strncmp(g_info.envp[i], name, len))
			return g_info.envp[i];
		i++;
	}
	return (NULL);
}

int	set_env(char *env, char *new_env)
{
	char	*tmp;
	int		i;
	int		len;

	if (!env || !new_env)
		return (0);
	len = ft_strlen(env);
	i = 0;
	while (g_info.envp[i] && ft_strncmp(env, g_info.envp[i], len))
		i++;
	if (g_info.envp[i])
	{
		len = ft_strlen(env) + ft_strlen(new_env) + 2;
		g_info.envp[i] = ft_realloc(g_info.envp[i], ft_strlen(g_info.envp[i]), len);
		ft_strchr(g_info.envp[i], '=')[1] = 0;
		ft_strlcat(g_info.envp[i], new_env, len);
		return (0);
	}
	g_info.envp = ft_realloc(g_info.envp, sizeof(char *) * i, sizeof(char *) * (i + 2));
	tmp = ft_strjoin(env, "=");
	g_info.envp[i] = ft_strjoin(tmp, new_env);
	free(tmp);
	return(0);
}

int	unset_env(char *env)
{
	int		i;
	int		len;

	if (!env)
		return (0);
	len = ft_strlen(env);
	i = 0;
	while (g_info.envp[i] && ft_strncmp(env, g_info.envp[i], len))
		i++;
	if (!g_info.envp[i])
		return (1);
	free(g_info.envp[i]);
	while(g_info.envp[i])
	{
		g_info.envp[i] = g_info.envp[i + 1];
		i++;
	}
	g_info.envp = ft_realloc(g_info.envp, i * sizeof(char *), (i + 1) * sizeof(char *));
	return(0);
}
