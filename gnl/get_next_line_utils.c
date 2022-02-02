/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:08:59 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/09 19:08:59 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	const char	*s_c = s;

	while (*s_c)
		s_c++;
	return (s_c - s);
}

char	*ft_strchr(const char *s, int c)
{
	while (s && *s && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start || !len)
	{
		str = malloc(1);
		*str = 0;
		return (str);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

void	*ft_realloc(void *old, size_t new_size)
{
	char	*new_ch;
	size_t	i;

	new_ch = malloc(new_size);
	if (!new_ch)
		return (NULL);
	i = 0;
	while (old && ((char *)old)[i] && i < new_size)
	{
		new_ch[i] = ((char *)old)[i];
		i++;
	}
	new_ch[i] = 0;
	if (old)
		free(old);
	return (new_ch);
}

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
