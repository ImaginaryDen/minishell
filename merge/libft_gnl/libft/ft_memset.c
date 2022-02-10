/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:51:18 by mslyther          #+#    #+#             */
/*   Updated: 2022/01/19 17:51:19 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t					i;
	unsigned char			*str;

	i = 0;
	str = b;
	while (i < len)
		str[i++] = c;
	return (b);
}
