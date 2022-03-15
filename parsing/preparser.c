/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:32:04 by mslyther          #+#    #+#             */
/*   Updated: 2022/03/15 14:02:01 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	**check_syntax_errors(char ***line_split)
{
	int	i;
	int	symb;
	int	len;

	i = 0;
	symb = special_symbol((*line_split)[0]);
	if (symb > 1 && symb < 5)
		return (error_message(line_split, 0));
	len = ft_size_arr(*line_split);
	symb = special_symbol((*line_split)[len - 1]);
	if (symb > 1)
		return (error_message(line_split, len - 1));
	while ((*line_split)[i])
	{
		if (special_symbol((*line_split)[i]))
		{
			if (i - 1 > 0 && special_symbol((*line_split)[i - 1]) > 0
				&& special_symbol((*line_split)[i - 1]) < 5)
				return (error_message(line_split, i));
			if ((*line_split)[i + 1] && special_symbol((*line_split)[i + 1]))
				return (error_message(line_split, i));
		}
		i++;
	}
	return (*line_split);
}

int	check_for_adding(char ***line_split, int *i, int *start, char *line)
{
	int			symb;
	const int	len = ft_strlen(line);

	symb = special_symbol(line + (*i));
	if ((*i != len && symb) || line[*i] == '\0')
	{
		if (*start == *i && symb != 1)
		{
			(*i)++;
			if (symb % 2 == 0)
				(*i)++;
		}
		if (*start != *i || symb != 1)
		{
			add_str(line, i, start, line_split);
			if (*i == len)
				(*i)++;
			return (1);
		}
		(*start)++;
	}
	return (0);
}

char	**split_line(char *line)
{
	int		i;
	int		len;
	int		start;
	char	**line_split;

	len = ft_strlen(line);
	start = 0;
	i = 0;
	line_split = NULL;
	while (i <= len)
	{
		if (line[i] == '\'' || line[i] == '\"')
			if (skip_quotations(line, &i) == 1)
				return (error_quotes(&line_split));
		if (check_for_adding(&line_split, &i, &start, line))
			continue ;
		i++;
	}
	return (line_split);
}

char	**preparser(char **line)
{
	char		*tmp;
	const char	isspace[7] = {9, 10, 11, 12, 13, 32, 0};
	char		**line_split;

	tmp = *line;
	*line = ft_strtrim(*line, isspace);
	free(tmp);
	if (**line == '\0')
		return (NULL);
	line_split = split_line(*line);
	if (line_split)
		return (check_syntax_errors(&line_split));
	return (line_split);
}
