/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 12:58:02 by tjamis            #+#    #+#             */
/*   Updated: 2021/04/28 13:20:50 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	const unsigned char	*src_c = src;
	unsigned char		*dst_c;

	dst_c = dst;
	i = 0;
	if (dst > src)
	{
		i = 1;
		while (i <= len)
		{
			dst_c[len - i] = src_c[len - i];
			i++;
		}
	}
	else if (dst || src)
	{
		while (i < len)
		{
			dst_c[i] = src_c[i];
			i++;
		}
	}
	return (dst);
}
