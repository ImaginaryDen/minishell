/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:02:36 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/15 14:51:48 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_flag(char **arg, int *i)
{
	int	j;
	int	is_n;

	is_n = 0;
	while (arg[*i])
	{
		j = 1;
		if (arg[*i][0] == '-')
			while (arg[*i][j] && arg[*i][j] == 'n')
				j++;
		if (arg[*i][j] != '\0' || j == 1)
			break ;
		is_n = 1;
		*i += 1;
	}
	return (is_n);
}

void	ft_echo(char **arg)
{
	int	i;
	int	is_n;

	i = 1;
	is_n = skip_flag(arg, &i);
	while (arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		i++;
		if (arg[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!is_n)
		ft_putstr_fd("\n", STDOUT_FILENO);
	g_info.status = 0;
}
