#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	size;

	if (!dst && !dstsize)
		return (ft_strlen(src));
	size = ft_strlen(dst);
	i = size;
	if (size >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (i < dstsize - 1 && src[i - size])
	{
		dst[i] = src[i - size];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src) + size);
}
