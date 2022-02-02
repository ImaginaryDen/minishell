#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s_copy;
	size_t	size;

	size = ft_strlen(s1) + 1;
	s_copy = malloc(size);
	if (!s_copy)
		return (NULL);
	ft_strlcpy(s_copy, s1, size);
	return (s_copy);
}
