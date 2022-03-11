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

void	define_fds(t_pipe_data *cmds)
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

void	cmds_fds(t_pipe_data *cmds, int size)
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

void	free_if_error(char **line_split, t_pipe_data *comand)
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

void	parser(char *line, t_info *info)
{
	int			i;
	int			j;
	int			size;
	t_pipe_data	*cmds;
	char		**line_split;
	int			start;
	int			len;
	int			save_j;
	int			operator = 0;
	int			flag;

	cmds = NULL;
	line_split = preparser(&line);
	free(line);
	if (!line_split)
		return (NULL);
	i = 0;
	while (line_split[i])
	{
		cmds = init_cmds_fds(ft_define_size(line_split + i));
		size = 1;
		while (line_split[i] && ft_strncmp(line_split[i], "||", 2)
			&& ft_strncmp(line_split[i], "&&", 2))
		{
			j = 0;
			if (!ft_strncmp(line_split[i], "|", 1))
			{
				size++;
				i++;
				continue ;
			}
			if (ft_isredirect(line_split[i][j], line_split[i][j + 1]))
			{
				if (redirect(&(cmds[size - 1]),
						line_split[i], line_split[i + 1]))
				{
					free_if_error(line_shift, cmds);
					return ;
				}
				i += 2;
				continue ;
			}
			flag = 0;
			while (line_split && line_split[i][j])
			{
				if ((line_split[i][j] == '\'') || (line_split[i][j] == '\"'))
					line_split[i] = quotation(line_split[i], &j, &flag);
				else if (line_split[i][j] == '$')
				{
					start = 0;
					line_split[i] = env_var(line_split[i], &j);
					save_j = 0;
					if (line_split[i][0] == '\0')
					{
						free(line_split[i]);
						line_split[i] = NULL;
						break ;
					}
					if (j && line_split[i][j - 1] == '$' && line_split[i][j])
					{
						line_shift(line_split[i], j - 1, 1);
						j--;
						continue ;
					}
					while (save_j <= j)
					{
						if (ft_isspace_s(line_split[i][save_j]))
						{	
							if (start != save_j)
							{
								len = ft_size_arr(cmds[size - 1].cmd_arg);
								cmds[size - 1].cmd_arg = ft_realloc(cmds[size - 1].cmd_arg, sizeof(char *) * len, sizeof(char *) * (len + 2));
								cmds[size - 1].cmd_arg[len] = ft_substr(line_split[i], start, save_j - start);
								printf("ADDED %s\n", cmds[size - 1].cmd_arg[len]);
								line_shift(line_split[i], 0, save_j + 1);
								j -= save_j + 1;
								start = save_j = 0;
								continue ;
							}
							start++;
						}
						save_j++;
					}
					line_shift(line_split[i], 0, start);
				}
				if (line_split[i][j] == '*' && line_split[i][j + 1] == '\0' && !flag)
				{
					char **files = get_files(".");
					len = ft_size_arr(cmds[size - 1].cmd_arg);
					cmds[size - 1].cmd_arg = ft_realloc(cmds[size - 1].cmd_arg, sizeof(char *) * len, sizeof(char *) * (len + ft_size_arr(files) + 2));
					for(int i = 0; files[i]; i++)
						cmds[size - 1].cmd_arg[len + i] = files[i];
					free(files);
					line_shift(line_split[i], j, 1);
				}
				j++;
			}
			if (line_split[i])
			{
				printf("%s\n", line_split[i]);
				len = ft_size_arr(cmds[size - 1].cmd_arg);
				cmds[size - 1].cmd_arg = ft_realloc(cmds[size - 1].cmd_arg, sizeof(char *) * len, sizeof(char *) * (len + 2));
				cmds[size - 1].cmd_arg[len] = ft_substr(line_split[i], 0, ft_strlen(line_split[i]));
			}
			i++;
		}
		cmds_fds(cmds, size);
		if (operator == 0 || (!ft_strncmp(line_split[operator], "||", 2) && g_info.status != 0) || (!ft_strncmp(line_split[operator], "&&", 2) && g_info.status == 0))
			executor(cmds);
		operator = i;
		if (line_split[i])
			i++;
	}
	ft_free_array(line_split);
}
