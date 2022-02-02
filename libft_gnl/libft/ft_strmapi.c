/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:51:47 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:51:48 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_s;
	size_t	i;

	if (!s)
		return (NULL);
	new_s = ft_strdup(s);
	if (!new_s)
		return (NULL);
	i = 0;
	while (new_s[i])
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	return (new_s);
}
