#include "minishell.h"

void ft_pwd(char **arg)
{
	char	*path;
	
	path = getcwd(NULL, 0);
	g_status = 0;
	if (!path)
	{
		g_status = 1;
		return;
	}
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	free(path);
}