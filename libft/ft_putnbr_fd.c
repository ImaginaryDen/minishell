/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:41:09 by tjamis            #+#    #+#             */
/*   Updated: 2021/05/10 17:26:46 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_pow(int num, int pow_n)
{
	int	result;

	result = 1;
	while (pow_n)
	{
		result *= num;
		pow_n--;
	}
	return (result);
}

static int	ft_abs(int c)
{
	if (c < 0)
		return (-c);
	return (c);
}

void	ft_putnbr_fd(int n, int fd)
{
	int	size;
	int	copy_n;

	size = 0;
	copy_n = n;
	while (copy_n)
	{
		size++;
		copy_n /= 10;
	}
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (!n)
		ft_putchar_fd('0', fd);
	while (size)
	{
		ft_putchar_fd(ft_abs(n / ft_pow(10, size - 1)) + '0', fd);
		n %= ft_pow(10, size - 1);
		size--;
	}
}
