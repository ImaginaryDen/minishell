/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 17:22:40 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/11 17:22:57 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_history(char **args)
{
	int	i;

	(void)args;
	i = 0;
	while (g_info.history && g_info.history[i])
	{
		printf("%4d  %s\n", i, g_info.history[i]);
		i++;
	}
}

void	ft_add_history(char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == 0)
		return ;
	while (g_info.history && g_info.history[i])
		i++;
	g_info.history = ft_realloc(g_info.history,
			sizeof(char *) * i, sizeof(char *) * (i + 2));
	g_info.history[i] = ft_strdup(str);
	add_history(str);
}
