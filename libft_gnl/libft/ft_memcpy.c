#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	size_t				i;
	const unsigned char	*s = src;

	d = dst;
	i = 0;
	if (!d && !s)
		return (dst);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
