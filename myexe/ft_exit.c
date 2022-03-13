/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanya <tanya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:11:26 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/13 18:31:27 by tanya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **argv)
{
	if (argv == NULL)
		ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	ft_free_array(g_info.history);
	ft_free_array(g_info.envp);
	exit(g_info.status);
}
