/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:52:12 by tjamis            #+#    #+#             */
/*   Updated: 2021/05/02 13:48:32 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	count;
	size_t	dest_len;

	if (!dest && !size)
		return (ft_strlen(src));
	dest_len = 0;
	while (dest_len < size && dest[dest_len])
		dest_len++;
	count = 0;
	if (dest_len == size)
		return (ft_strlen(src) + size);
	while (count + dest_len < size - 1 && src[count])
	{
		dest[dest_len + count] = src[count];
		count++;
	}
	dest[dest_len + count] = '\0';
	return (ft_strlen(src) + dest_len);
}
