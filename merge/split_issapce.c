#include "minishell.h"

int	ft_isspace(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32)
		return (1);
	return (0);
}

static size_t	ft_count_words(char const *s)
{
	size_t	count;

	count = 0;
	while (s && *s)
	{
		while (ft_isspace(*s))
			s++;
		if (*s)
			count++;
		while (*s && !ft_isspace(*s))
			s++;
	}
	return (count);
}

static int	ft_add_words(char const *s, char **words)
{
	char	*start;
	char	*end;
	size_t	size;

	start = (char *) s;
	while (start && *start)
	{
		while (ft_isspace(*start))
			start++;
		end = start;
		while (*end && !ft_isspace(*end))
			end++;
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

char	**split_isspace(char const *s)
{
	size_t	size;
	char	**words;

	if (!s)
		return (NULL);
	size = ft_count_words(s);
	words = ft_calloc(size + 1, sizeof(char *));
	if (!words)
		return (NULL);
	if (!ft_add_words(s, words))
		ft_free_words(words);
	return (words);
}