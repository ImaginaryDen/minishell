/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 20:36:22 by tjamis            #+#    #+#             */
/*   Updated: 2021/05/10 18:11:48 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	end;

	if (!src)
		return (0);
	i = 1;
	end = 0;
	while (src[i - 1])
	{
		if (i < dstsize)
		{
			dst[i - 1] = src[i - 1];
			end = i;
		}
		i++;
	}
	if (dstsize)
		dst[end] = '\0';
	return (i - 1);
}
