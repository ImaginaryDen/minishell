/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:51:06 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:51:07 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = src;
	const unsigned char	stop = c;
	size_t				i;

	d = dst;
	if (!n)
		return (NULL);
	i = 0;
	while (i < n - 1 && s[i] != stop)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = s[i];
	if (s[i] != stop)
		return (NULL);
	else
		return (d + i + 1);
}
