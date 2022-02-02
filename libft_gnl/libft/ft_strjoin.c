#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_s = malloc(size);
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s1, size);
	ft_strlcat(new_s, s2, size);
	return (new_s);
}
