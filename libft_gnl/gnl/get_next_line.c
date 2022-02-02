#include "get_next_line.h"

char	*ft_clean(int error, char **line, char **cache)
{
	if ((*line && error < 0) || (*line && **line == 0 && error == 0))
	{
		free(*line);
		*line = NULL;
	}
	if (*cache && error == -1)
	{
		free(*cache);
		*cache = NULL;
	}
	return (*line);
}

void	*ft_realloc(void *old, int size)
{
	void	*new;
	int		i;

	new = malloc(size);
	if (!new)
		return (NULL);
	i = 0;
	while (old && i < size && ((char *)old)[i])
	{
		((char *)new)[i] = ((char *)old)[i];
		i++;
	}
	((char *)new)[i] = '\0';
	if (old)
		free(old);
	return (new);
}

char	*ft_read_line(int fd, char **line, char **cache)
{
	char	buf[BUFFER_SIZE + 1];
	char	*end;
	size_t	len;
	int		error;

	len = ft_strlen(*line) + 1;
	while (1)
	{
		error = read(fd, buf, BUFFER_SIZE);
		buf[error] = 0;
		if (error <= 0)
			return (ft_clean(error, line, cache));
		end = ft_strchr(buf, '\n');
		if (end)
			break ;
		len += error;
		*line = ft_realloc(*line, len);
		ft_strlcat(*line, buf, len);
	}
	len += end - buf + 1;
	*line = ft_realloc(*line, len);
	ft_strlcat(*line, buf, len);
	*cache = ft_substr(buf, end - buf + 1, BUFFER_SIZE);
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*end;
	char		*start;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (cache)
	{
		end = ft_strchr(cache, '\n');
		if (end)
		{
			line = ft_substr(cache, 0, end - cache + 1);
			start = ft_substr(cache, end - cache + 1, BUFFER_SIZE);
			free(cache);
			cache = start;
			return (line);
		}
		line = cache;
		cache = NULL;
	}
	else
		line = ft_realloc(line, 1);
	return (ft_read_line(fd, &line, &cache));
}
