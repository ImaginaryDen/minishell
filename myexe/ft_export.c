#include "minishell.h"

void	ft_export(char **args)
{
	char *name;
	char *end_name;

	if (args[1] == NULL)
		return ;
	end_name = ft_strchr(args[1], '=');
	if (end_name == NULL)
		return ;
	name = ft_calloc(sizeof(char), (end_name - args[1] + 1));
	if (name == NULL)
	{
		ft_putstr_fd("error\n", 2);
		return ;
	}
	ft_strlcpy(name, args[1], end_name - args[1] + 1);
	set_env(name, args[1] + (end_name - args[1] + 1));
}