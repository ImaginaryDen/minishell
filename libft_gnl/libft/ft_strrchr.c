#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t		size;
	const char	ch = c;

	size = ft_strlen((char *)s);
	s += size - 1;
	if (ch == '\0')
		return ((char *)s + 1);
	while (size)
	{
		if (*s == ch)
			return ((char *)s);
		s--;
		size--;
	}
	return (NULL);
}
