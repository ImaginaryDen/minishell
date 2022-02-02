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
