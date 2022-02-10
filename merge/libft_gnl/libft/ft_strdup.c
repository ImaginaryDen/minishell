/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:51:37 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:51:38 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s_copy;
	size_t	size;

	size = ft_strlen(s1) + 1;
	s_copy = malloc(size);
	if (!s_copy)
		return (NULL);
	ft_strlcpy(s_copy, s1, size);
	return (s_copy);
}
