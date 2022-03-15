/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:10:20 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/15 14:52:37 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **arg)
{
	int	i;

	i = 0;
	(void)arg;
	while (g_info.envp && g_info.envp[i])
	{
		if (ft_strchr(g_info.envp[i], '='))
		{
			ft_putstr_fd(g_info.envp[i], 1);
			ft_putchar_fd('\n', 1);
		}
		i++;
	}
	g_info.status = 0;
}
