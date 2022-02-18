#include "minishell.h"

void show_export()
{
	char	**copy_env;
	int		i;
	int		size;
	int		tmp;

	size = ft_size_arr(g_envp);
	copy_env = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (i < size)
	{
		copy_env[i] = g_envp[i];
		i++;
	}
	env_sort(copy_env);
	i = 0;
	while(i < size)
	{
		tmp = ft_strchr(copy_env[i], '=') - copy_env[i];
		if (copy_env[i][0] != '_')
			printf("declare -x %.*s=\"%s\"\n", tmp, copy_env[i], copy_env[i] + tmp + 1);
		i++;
	}
	free(copy_env);
}

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
		if (end_name == args[i])
		{
			g_status = 1;
			ft_putstr_fd("sintax error '='\n", 2);
			i++;
			continue;
		}
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
	if (i == 1)
		show_export();
}