#include "libft.h"

static void	ft_check_isspace(const char **str)
{
	while (**str && ((**str >= 9 && **str <= 13) || **str == 32))
		(*str)++;
}

static int	ft_check_sign_char(const char **str)
{
	if (**str && (**str == '+' || **str == '-'))
	{
		(*str)++;
		if (*(*str - 1) == '-')
			return (-1);
	}
	return (1);
}

static int	ft_convert_to_int(const char **str)
{
	long int	num;
	int			sign;

	num = 0;
	sign = ft_check_sign_char(str);
	while (**str && **str >= '0' && **str <= '9'
		&& num <= INT_MAX && num >= INT_MIN)
	{
		num *= 10;
		num += (**str - '0') * sign;
		(*str)++;
	}
	if (num > INT_MAX)
		return (-1);
	if (num < INT_MIN)
		return (0);
	else
		return (num);
}

int	ft_atoi(const char *str)
{
	ft_check_isspace(&str);
	return (ft_convert_to_int(&str));
}
