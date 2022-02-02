/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 19:09:01 by tjamis            #+#    #+#             */
/*   Updated: 2021/10/09 19:09:24 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdio.h>

char	*clear_all(int value, char **cache, char **line, char **buf)
{
	if (*buf)
		free(*buf);
	if (*cache && value <= -1)
	{
		free(*cache);
		*cache = NULL;
	}
	if ((*line && value == -1) || (*line && **line == 0 && value == 0))
	{
		free(*line);
		*line = NULL;
	}
	return (*line);
}

int	check_cache(char **cache, char **line, char **buf)
{
	char	*temp;

	if (!*cache)
	{
		*line = malloc(1);
		**line = 0;
		return (0);
	}
	temp = ft_strchr(*cache, '\n');
	if (temp)
	{
		*line = ft_substr(*cache, 0, temp - *cache + 1);
		temp = ft_substr(*cache, temp - *cache + 1, BUFFER_SIZE);
		if (!*line || !temp)
		{
			clear_all(-1, cache, line, buf);
			return (-1);
		}
		clear_all(-2, cache, line, buf);
		*cache = temp;
		return (1);
	}
	*line = *cache;
	*cache = NULL;
	return (0);
}

char	*save_cache(char **line, char **cache, char *temp, char **buf)
{
	size_t	size;

	size = ft_strlen(*line) + temp - *buf + 2;
	*line = ft_realloc(*line, size);
	if (!*line)
		return (clear_all(-1, cache, line, buf));
	ft_strlcat(*line, *buf, size);
	*cache = ft_substr(temp, 1, BUFFER_SIZE);
	free(*buf);
	return (*line);
}

char	*solve(int fd, char	**buf, char **line, char **cache)
{
	int		error;
	int		len;
	char	*temp;	

	while (1)
	{
		error = read(fd, *buf, BUFFER_SIZE);
		if (error <= 0)
			return (clear_all(error, cache, line, buf));
		(*buf)[error] = 0;
		temp = ft_strchr(*buf, '\n');
		if (temp)
			return (save_cache(line, cache, temp, buf));
		len = ft_strlen(*line) + error + 1;
		*line = ft_realloc(*line, len);
		if (!*line)
			return (clear_all(-1, cache, line, buf));
		ft_strlcat(*line, *buf, len);
	}
}

char	*get_next_line(int fd)
{
	static char	*cache;
	char		*line;
	char		*buf;

	line = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf || fd < 0 || BUFFER_SIZE <= 0)
		return (clear_all(-1, &cache, &line, &buf));
	if (check_cache(&cache, &line, &buf))
		return (line);
	return (solve(fd, &buf, &line, &cache));
}
