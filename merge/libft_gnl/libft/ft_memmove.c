/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:51:16 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:51:17 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*d;
	const unsigned char		*s = src;

	d = dst;
	if (!d && !s)
		return (dst);
	if (s < d)
	{
		s += len - 1;
		d += len - 1;
		while (len)
		{
			*d-- = *s--;
			len--;
		}
	}
	else
	{
		while (len)
		{
			*d++ = *s++;
			len--;
		}
	}
	return (dst);
}
