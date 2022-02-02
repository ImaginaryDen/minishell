/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:39:34 by tjamis            #+#    #+#             */
/*   Updated: 2021/05/10 18:15:38 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		sign;

	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9' && res < INT_MAX && res > INT_MIN)
	{
		res *= 10;
		res += (str[i++] - '0') * sign;
	}
	if (res > (long)INT_MAX)
		return (-1);
	if (res < (long)INT_MIN)
		return (0);
	return (res);
}
