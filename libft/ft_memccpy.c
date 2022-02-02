/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 19:41:06 by tjamis            #+#    #+#             */
/*   Updated: 2021/05/11 17:51:06 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *source, int ch, size_t count)
{
	size_t					i;
	unsigned char			*dest_c;
	const unsigned char		*source_c = source;

	if (!count)
		return (NULL);
	i = 0;
	dest_c = dest;
	while (i < count - 1 && source_c[i] != (unsigned char)ch)
	{
		dest_c[i] = source_c[i];
		i++;
	}
	dest_c[i] = source_c[i];
	if (source_c[i] != (unsigned char)ch)
		return (NULL);
	return (dest_c + i + 1);
}
