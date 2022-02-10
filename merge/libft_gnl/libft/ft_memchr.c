/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:51:08 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:51:09 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str = s;
	const unsigned char	stop = c;

	while (n)
	{
		if (*str == stop)
			return ((unsigned char *)str);
		str++;
		n--;
	}
	return (NULL);
}
