#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	char	*new_s;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	size = ft_strlen(s1);
	while (size && ft_strchr(set, *(s1 + size)))
		size--;
	if (size)
		size++;
	new_s = malloc(size + 1);
	if (!new_s)
		return (NULL);
	ft_strlcpy(new_s, s1, size + 1);
	return (new_s);
}
