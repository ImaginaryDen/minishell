#include "minishell.h"

int	skip_quotations(char *line, int *i)
{
	char	quote_type;
	if (*i != 0 && line[*i - 1] == '\\')
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

	return (0);
}

int	ft_isspace(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32)
		return (1);
	return (0);
}

int special_symbol(char ch1, char ch2)
{
	int ret;

	if (ft_isspace(ch1))
		return (1);
//		printf("%c %c\n", ch1, ch2);
	if (ch1 == '|' && ch2 == '|')
		return (2);
	if (ch1 == '|' && ch2 != '|')
		return (3);
	if (ch1 == '&' && ch2 == '&')
		return (4);
	ret = ft_isredirect(ch1, ch2);
	if (ret == 1 || ret == 2)
		return (5);
	if (ret == 3 || ret == 4)
		return (6);
	return (0);
}

void add_str(char *line, int *i, int *start, char ***line_split)
{
	int len;

	len = ft_size_arr(*line_split);
	*line_split = ft_realloc(*line_split, sizeof(char *) * len, sizeof(char *) * (len + 2));
	(*line_split)[len] = ft_substr(line, *start, *i - *start);
	*start = *i;
}

char	**preparser(char **line)
{
	int	i;
	char *tmp;
	const char	isspace[7] = {9, 10, 11, 12, 13, 32, 0};
	char	**line_split;
	int symb;
	int len;

	tmp = *line;
	*line = ft_strtrim(*line, isspace);
	free(tmp);
	i = 0;
	int start = 0;
	len = ft_strlen(*line);
	line_split = NULL;
	while (i <= len)
	{
		if ((*line)[i] == '\'' || (*line)[i] == '\"')
		{
			if (skip_quotations(*line, &i) == 1)
				return (NULL);
		}
		symb = 0;
		if (i != len)
			symb = special_symbol((*line)[i], (*line)[i + 1]);
		if (symb || (*line)[i] == '\0')
		{
			if (start != i)
			{
				add_str(*line, &i, &start, &line_split);
				if (i == len)
					i++;
				continue ;
			}
			if (symb != 1)
			{
				i++;
				if (symb % 2 == 0)
					i++;
				add_str(*line, &i, &start, &line_split);
				continue ;
			}
			start++;
		}
		i++;
		// if (((*line)[i] == ';') || ((*line)[i + 1] == '\0'))
		// {
		// 	if (((*line)[i] != ';') && ((*line)[i + 1] == '\0'))
		// 		i++;
		// 	commands_line = ft_realloc(commands_line, sizeof(char *) * j, sizeof(char *) * (j + 1));
		// 	commands_line[j - 1] = ft_substr(*line, start, i - start);
		// 	tmp = commands_line[j - 1];
		// 	commands_line[j - 1] = ft_strtrim(commands_line[j - 1], isspace);
		// 	free(tmp);
		// 	len = ft_strlen(commands_line[j - 1]);
		// 	if (commands_line[j - 1][0] == '\0' || commands_line[j - 1][0] == '|' || commands_line[j - 1][len - 1] == '|')
		// 	{
		// 		printf("%s\n", commands_line[j - 1]);
		// 		return (NULL);
		// 	}
		// 	start = i + 1;
		// 	if ((*line)[i] == '\0')
		// 		i--;
		// 	j++;
		// }
	}
	// int i = 0;
	// int j = 0;
	// len = ft_size_arr(line_split);
	// while (line_split[i])
	// {
	// 	symb = special_symbol(line_split[i][j], line_split[i][j + 1]);
	// 	if (symb ==)
	// }
	return (line_split);
}