/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:11:26 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/15 14:40:22 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_with_arg(char **argv)
{
	int	size;
	int	ret;

	size = 0;
	while (argv[size])
		size++;
	if (size > 2 && ft_isdigit(argv[1][0]))
	{
		g_info.status = 1;
		ft_putstr_fd("minishel: exit: too many arguments\n", 2);
		return (1);
	}
	if (argv[1])
	{
		ret = ft_atoi(argv[1]);
		if (!ft_isdigit(argv[1][0]))
		{
			ft_putstr_fd("minishel: exit:  numeric argument required\n", 2);
			g_info.status = 255;
		}
		else
			g_info.status = ret;
	}
	return (0);
}

void	ft_exit(char **argv)
{
	if (argv == NULL)
		ft_putstr_fd("exit\n", 1);
	else if (exit_with_arg(argv))
		return ;
	rl_clear_history();
	ft_free_array(g_info.history);
	ft_free_array(g_info.envp);
	exit(g_info.status);
}
