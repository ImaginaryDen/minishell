#include "libft.h"

static int	ft_count_power(int n)
{
	int	power;

	power = 0;
	while (n)
	{
		n /= 10;
		power++;
	}
	return (power - 1);
}

static int	ft_exp(int power)
{
	int	res;

	res = 1;
	while (power)
	{
		res *= 10;
		power--;
	}
	return (res);
}

void	ft_putnbr_fd(int n, int fd)
{
	int		res;
	char	digit;
	int		sign;

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	sign = 1;
	if (n < 0)
		sign = -1;
	res = ft_exp(ft_count_power(n));
	if (sign == -1)
		write(fd, "-", 1);
	while (res)
	{
		digit = '0' + (n / res) * sign;
		write(fd, &digit, 1);
		n %= res;
		res /= 10;
	}
}
