/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanya <tanya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 17:03:09 by tanya             #+#    #+#             */
/*   Updated: 2022/03/13 17:05:25 by tanya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wildcards(t_parser_data *data, int j)
{
	int		len;
	int		i;
	char	**files;

	files = get_files(".");
	len = ft_size_arr(data->cmds[data->size - 1].cmd_arg);
	data->cmds[data->size - 1].cmd_arg
		= ft_realloc(data->cmds[data->size - 1].cmd_arg,
			sizeof(char *) * len, sizeof(char *)
			* (len + ft_size_arr(files) + 2));
	i = 0;
	while (files[i])
	{
		data->cmds[data->size - 1].cmd_arg[len + i] = files[i];
		i++;
	}
	free(files);
	line_shift(data->curr_word, j, 1);
}
