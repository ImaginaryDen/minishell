/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_after_enc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanya <tanya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:07:17 by tanya             #+#    #+#             */
/*   Updated: 2022/03/13 17:07:32 by tanya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_env(t_parser_data *data, int *j)
{
	int	save_j;

	save_j = 0;
	while (save_j <= *j)
	{
		while (save_j <= *j && ft_isspace(data->curr_word[save_j]))
		{
			line_shift(data->curr_word, 0, 1);
			*j -= 1;
		}
		while (save_j <= *j && !ft_isspace(data->curr_word[save_j]))
			save_j++;
		if (save_j < *j)
		{
			add_cmd(data->cmds, data->size,
				ft_substr(data->curr_word, 0, save_j));
			line_shift(data->curr_word, 0, save_j + 1);
			*j -= save_j + 1;
			save_j = 0;
		}
	}
}

int	parser_after_env(t_parser_data *data, int *j)
{
	if (data->curr_word[0] == '\0')
	{
		free(data->curr_word);
		data->curr_word = NULL;
		return (1);
	}
	if (*j && data->curr_word[*j - 1] == '$' && data->curr_word[*j])
	{
		line_shift(data->curr_word, *j - 1, 1);
		(*j)--;
		return (0);
	}
	parse_env(data, j);
}
