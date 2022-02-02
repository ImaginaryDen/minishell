/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:38:54 by tjamis            #+#    #+#             */
/*   Updated: 2021/05/05 14:49:06 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	size;

	if (!s || !f)
		return (NULL);
	size = ft_strlen(s);
	result = malloc(size + 1);
	if (!result)
		return (NULL);
	result[size] = 0;
	while (size)
	{
		size--;
		result[size] = f(size, s[size]);
	}
	return (result);
}
