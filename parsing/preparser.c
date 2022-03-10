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
			{
				printf("Syntax error: unclosed quote\n");
				ft_free_array(line_split);
				return (NULL);
			}
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
				if (i == len)
					i++;
				continue ;
			}
			start++;
		}
		i++;
	}
	i = 0;
	symb = special_symbol(line_split[0][0], line_split[0][1]);
	if (symb > 1 && symb < 5)
	{
		printf("minishell: syntax error near unexpected token \'%s\'\n", line_split[0]);
		ft_free_array(line_split);
		return (NULL);
	}
	len = ft_size_arr(line_split);
	symb = special_symbol(line_split[len - 1][0], line_split[len - 1][1]);
	if (symb > 1)
	{
		printf("minishell: syntax error near unexpected token \'%s\'\n", line_split[len - 1]);
		ft_free_array(line_split);
		return (NULL);
	}	
	while (line_split[i])
	{
		symb = special_symbol(line_split[i][0], line_split[i][1]);
		if (symb)
		{
			if (i - 1 > 0 && special_symbol(line_split[i - 1][0], line_split[i - 1][1]))
			{
				printf("minishell: syntax error near unexpected token \'%s\'\n", line_split[i]);
				ft_free_array(line_split);
				return (NULL);
			}
			if (line_split[i + 1] && special_symbol(line_split[i + 1][0], line_split[i + 1][1]) > 0 && special_symbol(line_split[i + 1][0], line_split[i + 1][1]) < 5)
			{
				printf("minishell: syntax error near unexpected token \'%s\'\n", line_split[i]);
				ft_free_array(line_split);
				return (NULL);
			}
		}
		i++;
	}
	return (line_split);
}