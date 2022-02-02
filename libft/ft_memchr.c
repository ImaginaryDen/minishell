/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 20:00:34 by tjamis            #+#    #+#             */
/*   Updated: 2021/05/10 18:25:09 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *arr, int c, size_t n)
{
	size_t				i;
	const unsigned char	*c_arr = (const unsigned char *)arr;

	i = 0;
	while (n && i < n - 1 && c_arr[i] != (unsigned char)c)
		i++;
	if (!n || c_arr[i] != (unsigned char)c)
		return (NULL);
	return ((void *)arr + i);
}
