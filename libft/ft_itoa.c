/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:07:15 by tjamis            #+#    #+#             */
/*   Updated: 2021/05/11 17:33:34 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int c)
{
	if (c < 0)
		return (-c);
	return (c);
}

static void	ft_pars(char *result, int n, int size)
{
	int	i;

	i = 1;
	while (n)
	{
		result[size - i] = ft_abs(n % 10) + '0';
		n /= 10;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		size;
	int		copy_n;

	size = 0;
	copy_n = n;
	while (copy_n)
	{
		size++;
		copy_n /= 10;
	}
	if (n <= 0)
		size++;
	result = malloc(size + 1);
	if (!result)
		return (NULL);
	result[0] = '0';
	result[size] = 0;
	if (n < 0)
		result[0] = '-';
	ft_pars(result, n, size);
	return (result);
}
