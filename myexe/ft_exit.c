/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:11:26 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/11 16:11:28 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **argv)
{
	if (argv == NULL)
		ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	ft_free_double_arr(g_info.history);
	ft_free_double_arr(g_info.envp);
	exit(g_info.status);
}
