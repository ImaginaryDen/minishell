#include "minishell.h"

void	ft_export(char **args)
{
	int		i;
	char	*name;
	char	*end_name;

	i = 1;
	g_status = 0;
	while (args[i])
	{
		end_name = ft_strchr(args[i], '=');
		if (end_name == NULL)
			return ;
		name = ft_calloc(sizeof(char), (end_name - args[i] + 1));
		if (name == NULL)
		{
			ft_putstr_fd("error\n", 2);
			return ;
		}
		ft_strlcpy(name, args[i], end_name - args[i] + 1);
		set_env(name, args[i] + (end_name - args[i] + 1));
		free(name);
		i++;
	}
}