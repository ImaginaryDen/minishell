/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:04:23 by tjamis            #+#    #+#             */
/*   Updated: 2021/05/11 17:27:36 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_n;
	size_t	i;

	if (!needle[0])
		return ((char *)haystack);
	if (!len && needle[0])
		return (NULL);
	len_n = 0;
	while (len_n <= len && needle[len_n])
		len_n++;
	i = 0;
	while (i <= len - len_n && haystack[i])
	{
		if (!(ft_strncmp(haystack + i, needle, len_n)))
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
