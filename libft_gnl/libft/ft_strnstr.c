#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (!*needle)
		return ((char *) haystack);
	while (i < len && needle[i] && haystack[i])
	{
		if (haystack[i] != needle[i])
		{
			haystack++;
			i = -1;
			len--;
		}
		i++;
	}
	if (!needle[i])
		return ((char *) haystack);
	return (NULL);
}
