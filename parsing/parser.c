/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 19:19:05 by mslyther          #+#    #+#             */
/*   Updated: 2022/03/11 20:19:16 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	line_shift(char *line, int i, int shift)
{
	int	len;

	len = ft_strlen(line);
	while (i + shift - 1 < len)
	{
		line[i] = line[i + shift];
		i++;
	}
}

void	define_fds(t_cmd_data *cmds)
{
	int	end[2];

	pipe(end);
	if (cmds[0].fd_in_out[WRITE_FD] == STDOUT_FILENO)
		cmds[0].fd_in_out[WRITE_FD] = end[WRITE_FD];
	else
		close(end[WRITE_FD]);
	if (cmds[1].fd_in_out[READ_FD] == STDIN_FILENO)
		cmds[1].fd_in_out[READ_FD] = end[READ_FD];
	else
		close(end[READ_FD]);
	if (cmds[0].fd_close[0] == -1)
		cmds[0].fd_close[0] = cmds[1].fd_in_out[READ_FD];
	else
		cmds[0].fd_close[1] = cmds[1].fd_in_out[READ_FD];
	if (cmds[1].fd_close[0] == -1)
		cmds[1].fd_close[0] = cmds[0].fd_in_out[WRITE_FD];
	else
		cmds[1].fd_close[1] = cmds[0].fd_in_out[WRITE_FD];
}

void	cmds_fds(t_cmd_data *cmds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((size != 1) && (i != size - 1))
			define_fds(cmds + i);
		if (i == size - 1 && (size != 1))
			cmds[i].fd_close[0] = cmds[i - 1].fd_in_out[WRITE_FD];
		i++;
	}
}

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

int	ft_isspace_ispipe(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32 || ch == '|')
		return (1);
	return (0);
}

void	free_if_error(char **line_split, t_cmd_data *comand)
{
	int	i;

	perror("minishell");
	ft_free_array(line_split);
	i = 0;
	while (comand[i].cmd_arg != NULL)
	{
		ft_free_double_arr(comand[i].cmd_arg);
		i++;
	}
	free(comand);
}

void add_cmd(t_cmd_data *cmds, int size, char *str)
{
	int len;

	len = ft_size_arr(cmds[size - 1].cmd_arg);
	cmds[size - 1].cmd_arg = ft_realloc(cmds[size - 1].cmd_arg, sizeof(char *) * len, sizeof(char *) * (len + 2));
	cmds[size - 1].cmd_arg[len] = str;
				
}

void parse_env(t_parser_data *data, int *j)
{
	int save_j;

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

void	wildcards(t_parser_data *data, int j)
{
	int	len;
	int	i;

	char **files = get_files(".");
	len = ft_size_arr(data->cmds[data->size - 1].cmd_arg);
	data->cmds[data->size - 1].cmd_arg = 
	ft_realloc(data->cmds[data->size - 1].cmd_arg, sizeof(char *) * len,
	sizeof(char *) * (len + ft_size_arr(files) + 2));
	i = 0;
	while (files[i])
	{
		data->cmds[data->size - 1].cmd_arg[len + i] = files[i];
		i++;
	}
	free(files);
	line_shift(data->curr_word, j, 1);
}

void	word_parser(t_parser_data *data)
{
	int	flag;
	int j;

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
				return ;
		}
		if (data->curr_word[j] == '*' && data->curr_word[j + 1] == '\0' && !flag)
			wildcards(data, j);
		j++;
	}
}

void	command_parser(t_parser_data *data)
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
			if (redirect(&(data->cmds[data->size - 1]), data->curr_cmd[0], data->curr_cmd[1]))
			{
				free_if_error(data->line_split, data->cmds);
				return ;
			}
			data->curr_cmd += 2;
			continue ;
		}
		data->curr_word = ft_strdup(data->curr_cmd[0]);
		word_parser(data);
		if (data->curr_word)
		{
			add_cmd(data->cmds, data->size, ft_substr(data->curr_word, 0, ft_strlen(data->curr_word)));
			free(data->curr_word);
		}
		data->curr_cmd++;
	}
}

void	parser(char *line, t_info *info)
{
	int			i;
	int			j;
	int			start;
	int			len;
	int			save_j;
	int			operator = 0;
	int			flag;
	t_parser_data	data;

	data.cmds = NULL;
	data.line_split = preparser(&line);
	free(line);
	if (!data.line_split)
		return ;
	i = 0;
	data.curr_cmd = data.line_split;
	while (*data.curr_cmd)
	{
		data.cmds = init_cmds_fds(ft_define_size(data.curr_cmd));
		data.size = 1;
		command_parser(&data);
		cmds_fds(data.cmds, data.size);
		if (operator == 0 || (!ft_strncmp(data.line_split[operator], "||", 2) && g_info.status != 0) || (!ft_strncmp(data.line_split[operator], "&&", 2) && g_info.status == 0))
			executor(data.cmds);
		operator = data.curr_cmd - data.line_split;
		if (*data.curr_cmd)
			data.curr_cmd++;
	}
	ft_free_array(data.line_split);
}
