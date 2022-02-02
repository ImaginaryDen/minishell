#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (s && *s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		s = ft_strchr(s, c);
	}
	return (count);
}

static int	ft_add_words(char const *s, char c, char **words)
{
	char	*start;
	char	*end;
	size_t	size;

	start = (char *) s;
	while (start && *start)
	{
		while (*start == c)
			start++;
		end = ft_strchr(start, c);
		if (*start)
		{
			if (!end)
				size = ft_strlen(start) + 1;
			else
				size = end - start + 1;
			*words = malloc(sizeof(char) * size);
			if (!*words)
				return (0);
			ft_strlcpy(*words, start, size);
			words++;
		}
		start = end;
	}
	return (1);
}

static void	ft_free_words(char **words)
{
	char	**word;

	word = words;
	while (*word)
	{
		free(*word);
		word++;
	}
	free(words);
}

char	**ft_split(char const *s, char c)
{
	size_t	size;
	char	**words;

	if (!s)
		return (NULL);
	size = ft_count_words(s, c);
	words = ft_calloc(size + 1, sizeof(char *));
	if (!words)
		return (NULL);
	if (!ft_add_words(s, c, words))
		ft_free_words(words);
	return (words);
}
