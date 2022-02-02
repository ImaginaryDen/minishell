/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:51:11 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:51:12 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1 = s1;
	const unsigned char	*str2 = s2;
	size_t				i;

	if (n == 0)
		return (n);
	i = 0;
	while (i < n && str1[i] == str2[i])
		i++;
	if (i == n)
		i--;
	return (str1[i] - str2[i]);
}
