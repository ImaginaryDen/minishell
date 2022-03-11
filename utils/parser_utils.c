/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:50:48 by mslyther          #+#    #+#             */
/*   Updated: 2022/03/11 18:51:20 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32)
		return (1);
	return (0);
}

int	special_symbol(char *line)
{
	int	ret;

	if (ft_isspace(*line))
		return (1);
	if (!ft_strncmp(line, "||", 2))
		return (2);
	if (!ft_strncmp(line, "|", 1))
		return (3);
	if (!ft_strncmp(line, "&&", 2))
		return (4);
	ret = ft_isredirect(*line, *(line + 1));
	if (ret == 1 || ret == 2)
		return (5);
	if (ret == 3 || ret == 4)
		return (6);
	return (0);
}

void	add_str(char *line, int *i, int *start, char ***line_split)
{
	int	len;

	len = ft_size_arr(*line_split);
	*line_split = ft_realloc(*line_split,
			sizeof(char *) * len, sizeof(char *) * (len + 2));
	(*line_split)[len] = ft_substr(line, *start, *i - *start);
	*start = *i;
}
