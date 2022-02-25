#include "minishell.h"

void	ft_history(char **args)
{
	int i;

	(void)args;
	i = 0;
	while(g_history && g_history[i])
	{
		printf("%4d  %s\n", i, g_history[i]);
		i++;
	}
}

void ft_add_history(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == 0)
		return ;
	while (g_history && g_history[i])
		i++;
	g_history = ft_realloc(g_history, sizeof(char *) * i, sizeof(char *) * (i + 2));
	g_history[i] = ft_strdup(str);
	add_history(str);
}