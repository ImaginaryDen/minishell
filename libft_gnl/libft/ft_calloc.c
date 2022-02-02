#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*arr;

	arr = malloc(count * size);
	if (!arr)
		return (NULL);
	return (ft_memset(arr, 0, count * size));
}
