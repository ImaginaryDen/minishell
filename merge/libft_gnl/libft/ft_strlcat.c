/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:51:41 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:51:42 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	size;

	if (!dst && !dstsize)
		return (ft_strlen(src));
	size = ft_strlen(dst);
	i = size;
	if (size >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (i < dstsize - 1 && src[i - size])
	{
		dst[i] = src[i - size];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src) + size);
}
