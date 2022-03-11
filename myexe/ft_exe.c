/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:10:28 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/11 16:11:19 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_command(char *str)
{
	const char	*comands[] = {"echo", "env", "pwd", "cd", "exit", "export",
		"unset", "history", NULL};
	int			i;

	i = 0;
	while (comands[i])
	{
		if (!ft_strncmp(str, comands[i], ft_strlen(comands[i]) + 1))
			return (i);
		i++;
	}
	return (-1);
}

void	*init_commnds(void)
{
	void	(**command)(char **);

	command = malloc(sizeof(void *) * 8);
	command[0] = ft_echo;
	command[1] = ft_env;
	command[2] = ft_pwd;
	command[3] = ft_cd;
	command[4] = ft_exit;
	command[5] = ft_export;
	command[6] = ft_unset;
	command[7] = ft_history;
	return (command);
}

int	exev_include(t_pipe_data *data)
{
	void	(**command)(char **);
	int		i;

	command = init_commnds();
	i = get_command(data->cmd_arg[0]);
	if (i >= 0)
	{
		g_info.status = 0;
		command[i](data->cmd_arg);
		return (1);
	}
	free(command);
	return (0);
}
