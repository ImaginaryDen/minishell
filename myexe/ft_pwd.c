#include "minishell.h"

void ft_pwd(char **arg)
{
	char *path;
	
	path = get_env("PWD");
	g_status = 0;
	if (!path)
	{
		g_status = 1;
		return;
	}
	path = ft_strchr(path, '=');
	if (!path)
		return;
	ft_putstr_fd(path + 1, 1);
	ft_putstr_fd("\n", 1);
}