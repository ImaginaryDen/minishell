#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str = s;
	const unsigned char	stop = c;

	while (n)
	{
		if (*str == stop)
			return ((unsigned char *)str);
		str++;
		n--;
	}
	return (NULL);
}
