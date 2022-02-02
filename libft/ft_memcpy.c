/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:29:18 by tjamis            #+#    #+#             */
/*   Updated: 2021/04/22 20:37:30 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *source, size_t count)
{
	size_t				i;
	unsigned char		*dest_c;
	const unsigned char	*source_c = source;

	dest_c = dest;
	if (!dest && !source)
		return (NULL);
	i = 0;
	while (i < count)
	{
		dest_c[i] = source_c[i];
		i++;
	}
	return (dest);
}
