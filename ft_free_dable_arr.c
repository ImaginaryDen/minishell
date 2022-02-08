/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_dable_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:27:44 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/09 17:27:45 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_dable_arr(char **strs)
{
	int	i;

	i = 0;
	while (strs && strs + i && strs[i])
	{
		free(strs[i]);
		i++;
	}
	if (strs)
		free(strs);
	strs = NULL;
}
