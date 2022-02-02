/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realoc_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 17:26:45 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/09 17:26:47 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_realoc_str(char *old, int size)
{
	char	*new_ptr;
	int		i;

	new_ptr = malloc(size);
	i = 0;
	while (old && old[i] && i < size)
	{
		new_ptr[i] = old[i];
		i++;
	}
	new_ptr[i] = 0;
	if (old)
		free(old);
	return (new_ptr);
}
