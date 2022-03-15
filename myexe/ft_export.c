/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:11:32 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/15 14:53:34 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_export(void)
{
	char	**copy_env;
	int		i;
	int		size;
	int		tmp;

	size = ft_size_arr(g_info.envp);
	copy_env = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (i < size)
	{
		copy_env[i] = g_info.envp[i];
		i++;
	}
	char_arr_sort(copy_env);
	i = 0;
	while (i < size)
	{
		tmp = ft_strchr(copy_env[i], '=') - copy_env[i];
		if (copy_env[i][0] != '_')
			printf("declare -x %.*s=\"%s\"\n",
				tmp, copy_env[i], copy_env[i] + tmp + 1);
		i++;
	}
	free(copy_env);
}

void	print_err_export(char *msg)
{
	g_info.status = 1;
	ft_putstr_fd("minishell: export: '", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("' not a valid identifier\n", 2);
	g_info.status = 1;
}

void	ft_export(char **args)
{
	int		i;
	char	*name;
	char	*end_name;

	i = 1;
	g_info.status = 0;
	while (args[i])
	{
		end_name = ft_strchr(args[i], '=');
		if (end_name == args[i] || !is_key(args[i][0])
			|| ft_isdigit(args[i][0]))
			print_err_export(args[i]);
		else if (end_name != NULL)
		{
			name = ft_calloc(sizeof(char), (end_name - args[i] + 2));
			ft_strlcpy(name, args[i], end_name - args[i] + 1);
			set_env(name, args[i] + (end_name - args[i] + 1));
			free(name);
		}
		i++;
	}
	if (i == 1)
		show_export();
}
