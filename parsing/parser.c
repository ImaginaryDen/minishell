/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanya <tanya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:19:05 by mslyther          #+#    #+#             */
/*   Updated: 2022/03/13 18:27:58 by tanya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_define_size(char **line)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (line[i] && ft_strncmp(line[i], "||", 2)
		&& ft_strncmp(line[i], "&&", 2))
	{
		if (!ft_strncmp(line[i], "|", 1))
			count++;
		i++;
	}
	return (count);
}

void	add_cmd(t_cmd_data *cmds, int size, char *str)
{
	int	len;

	len = ft_size_arr(cmds[size - 1].cmd_arg);
	cmds[size - 1].cmd_arg = ft_realloc(cmds[size - 1].cmd_arg,
			sizeof(char *) * len, sizeof(char *) * (len + 2));
	cmds[size - 1].cmd_arg[len] = str;
}

void	word_parser(t_parser_data *data)
{
	int	flag;
	int	j;

	j = 0;
	flag = 0;
	while (data->line_split && data->curr_word[j])
	{
		if ((data->curr_word[j] == '\'') || (data->curr_word[j] == '\"'))
			data->curr_word = quotation(data->curr_word, &j, &flag);
		else if (data->curr_word[j] == '$')
		{
			data->curr_word = env_var(data->curr_word, &j);
			if (parser_after_env(data, &j))
				break ;
		}
		if (data->curr_word[j] == '*'
			&& data->curr_word[j + 1] == '\0' && !flag)
			wildcards(data, j);
		j++;
	}
	if (!data->curr_word)
		return ;
	add_cmd(data->cmds, data->size,
		ft_substr(data->curr_word, 0, ft_strlen(data->curr_word)));
	free(data->curr_word);
}

int	command_parser(t_parser_data *data)
{
	while (data->curr_cmd[0] && ft_strncmp(data->curr_cmd[0], "||", 2)
		&& ft_strncmp(data->curr_cmd[0], "&&", 2))
	{
		if (!ft_strncmp(*data->curr_cmd, "|", 1))
		{
			data->size++;
			data->curr_cmd++;
			continue ;
		}
		if (ft_isredirect(data->curr_cmd[0][0], data->curr_cmd[0][1]))
		{
			if (redirect(&(data->cmds[data->size - 1]),
					data->curr_cmd[0], data->curr_cmd[1]))
				return (free_if_error(data->line_split, data->cmds) + 1);
			data->curr_cmd += 2;
			continue ;
		}
		data->curr_word = ft_strdup(data->curr_cmd[0]);
		word_parser(data);
		data->curr_cmd++;
	}
	return (0);
}

void	parser(char *line, t_info *info)
{
	int				oper;
	t_parser_data	data;

	oper = 0;
	data.line_split = preparser(&line);
	free(line);
	if (!data.line_split)
		return ;
	data.curr_cmd = data.line_split;
	while (*data.curr_cmd)
	{
		data.cmds = init_cmds_fds(ft_define_size(data.curr_cmd));
		data.size = 1;
		if (command_parser(&data))
			break ;
		cmds_fds(data.cmds, data.size);
		if (!oper || (!ft_strncmp(data.line_split[oper], "||", 2)
				&& g_info.status != 0) || (!ft_strncmp(data.line_split[oper],
					"&&", 2) && g_info.status == 0))
			executor(data.cmds);
		oper = data.curr_cmd - data.line_split;
		if (*data.curr_cmd)
			data.curr_cmd++;
	}
	ft_free_array(data.line_split);
}
