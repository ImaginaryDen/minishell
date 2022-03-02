#include "minishell.h"

int	skip_quotations(char *line, int *i)
{
	char	quote_type;
	if (*i - 1 != 0 && line[*i - 1] == '\\')
	{
		(*i)++;
		return (0);
	}
	quote_type = line[*i];
	(*i)++;
	while (line[*i] && line[*i] != quote_type)
	{
		if (line[*i] == '\\' && line[*i + 1] == quote_type)
			(*i)++;
		(*i)++;
	}
	if (!line[*i])
		return (1);
	(*i)++;
	return (0);
}

char	**preparser(char **line)
{
	int	i;
	int len;
	char *tmp;
	const char	isspace[7] = {9, 10, 11, 12, 13, 32, 0};
	char	**commands_line;
	int j;

	i = 0;

	tmp = *line;
	*line = ft_strtrim(*line, isspace);
	free(tmp);
	len = ft_strlen(*line);
//	if (!len)
//		return (NULL);
	if (len > 1 && (*line)[len - 1] == '\\' && (*line)[len - 2] != '\\')
		return (NULL);
	if ((*line)[i] == ';' || (*line)[i] == '|')
		return (NULL);
	i++;
	while (i < len)
	{
		if ((*line)[i] == ';' && (*line)[i - 1] == ';')
			return (NULL);
		i++;
	}
	i = 0;
	j = 1;
	int start = 0;
	commands_line = ft_calloc(j, sizeof(char *));
	while ((*line)[i])
	{
		if ((*line)[i] == '\'' || (*line)[i] == '\"')
		{
			if (skip_quotations(*line, &i) == 1)
				return (NULL);
			continue ;
		}
		if (((*line)[i] == ';') || ((*line)[i + 1] == '\0'))
		{
			if (((*line)[i] != ';') && ((*line)[i + 1] == '\0'))
				i++;
			commands_line = ft_realloc(commands_line, sizeof(char *) * j, sizeof(char *) * (j + 1));
			commands_line[j - 1] = ft_substr(*line, start, i - start);
			tmp = commands_line[j - 1];
			commands_line[j - 1] = ft_strtrim(commands_line[j - 1], isspace);
			free(tmp);
			len = ft_strlen(commands_line[j - 1]);
			if (commands_line[j - 1][0] == '\0' || commands_line[j - 1][0] == '|' || commands_line[j - 1][len - 1] == '|')
				return (NULL);
			start = i + 1;
			if ((*line)[i] == '\0')
				i--;
			j++;
		}
		i++;
	}
	return (commands_line);
}