/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:27:55 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/15 14:01:42 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(char **envp)
{
	char	*tmp;
	int		tmp_num;

	g_info.envp = copy_envp(envp);
	g_info.status = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	tmp = get_env("SHLVL");
	if (!tmp)
		return ;
	tmp = ft_strchr(tmp, '=') + 1;
	if (!tmp)
		return ;
	tmp_num = ft_atoi(tmp) + 1;
	tmp = ft_itoa(tmp_num);
	set_env("SHLVL", tmp);
	free(tmp);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	char	*line;

	(void)argc;
	(void)argv;
	info.status = 1;
	init_shell(envp);
	while (info.status)
	{
		line = ft_readline();
		ft_add_history(line);
		if (line == NULL)
		{
			ft_exit(NULL);
			break ;
		}
		parser(line);
	}
}
