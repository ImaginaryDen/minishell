/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:51:53 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:51:54 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		size;
	const char	ch = c;

	size = ft_strlen((char *)s);
	s += size - 1;
	if (ch == '\0')
		return ((char *)s + 1);
	while (size)
	{
		if (*s == ch)
			return ((char *)s);
		s--;
		size--;
	}
	return (NULL);
}
