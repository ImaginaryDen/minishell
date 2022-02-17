#include "minishell.h"

// $0 - обрабатывать?
// $? - нужно обработать с возвращаемым значением от предыдущей команды (напрячь Дениса)
// в переменной окружения тоже надо разделять аргументы пробельными символами, а не оставлять как есть
// добавить обработку ${}

void	line_shift(char *line, int i, int shift)
{
	while (line[i + shift - 1])
	{
		line[i] = line[i + shift];
		i++;
	}
}

void	slash(char *line, int i)
{
	line_shift(line, i, 1);
}

void skip_isspace(char *line, int *i)
{
	while (line[*i] && ((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32))
		(*i)++;
}

int skip_isspace_reverse(char *line, int *i)
{
	while ((i != 0) && ((line[*i] >= 9 && line[*i] <= 13) || line[*i] == 32))
		(*i)--;
}

int	preparser(char *line)
{
	int	i;
	int count_qoutes;
	int count_double_qoutes;
	int len;

	i = 0;
	count_qoutes = 0;
	count_double_qoutes = 0;
	skip_isspace(line, &i);
	line += i;
	i = 0;
	len = ft_strlen(line);
	while ((len - 1 > 0) && ((line[len - 1] >= 9 && line[len - 1] <= 13) || line[len - 1] == 32))
		len--;
	if (len <= 0)
		return (-1);
	if (len == 1 && line[len - 1] == '\\')
		return (-1);
	if (line[len - 1] == '\\' && line[len - 2] != '\\')
		return (-1);
	if (line[0] == ';' || line[0] == '|')
		return (-1);
	while (i < len)
	{
		if (i != 0)
		{
			if (line[i] == ';' && (line[i - 1] == ';' || line[i - 1] == '|'))
				return (-1);
			
		}
		if (line[i] == '\'')
			count_qoutes++;
		if (line[i] == '\"')
			count_double_qoutes++;
		i++;
	}
	if (count_qoutes % 2 == 1 || count_double_qoutes % 2 == 1)
		return (-1);
	return (0);
}

void	define_fds(t_pipe_data *cmds)
{
	int	end[2];

	pipe(end);
	cmds[0].fd_in_out[WRITE_FD] = end[WRITE_FD];
	cmds[1].fd_in_out[READ_FD] = end[READ_FD];
	if (cmds[0].fd_close[0] == -1)
		cmds[0].fd_close[0] = cmds[1].fd_in_out[READ_FD];
	else
		cmds[0].fd_close[1] = cmds[1].fd_in_out[READ_FD];
	if (cmds[1].fd_close[0] == -1)
		cmds[1].fd_close[0] = cmds[0].fd_in_out[WRITE_FD];
	else
		cmds[1].fd_close[1] = cmds[0].fd_in_out[WRITE_FD];
}

void	cmds_fds(char *line, t_pipe_data *cmds, int size)
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

int ft_define_size(char *line)
{
	int	i;
	int count;

	i = 0;
	count = 1;
	while (line[i])
	{
		if (i != 0 && line[i] == '|' && line[i + 1])
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

int split_cmd(char *line, int *j, int *start, t_pipe_data *cmd)
{
	int	len;

	if (ft_isspace_ispipe(line[*j]) || line[*j + 1] == '\0')
	{
		if (!ft_isspace_ispipe(line[*j]) && line[*j + 1] == '\0')
			(*j)++;
		if ((*j) - *start > 0)
		{
			len = ft_size_arr(cmd->cmd_arg);
			cmd->cmd_arg = ft_realloc(cmd->cmd_arg, sizeof(char *) * len, sizeof(char *) * (len + 2));
			cmd->cmd_arg[len] = ft_substr(line, *start, *j - *start);
			*start = *j + 1;
			if (line[*j] == '\0')
				return (1) ;
		}
		else
			(*start)++;
	}
	return (0);
}

t_pipe_data *parser(char *line, t_info *info)
{
	int		i;
	int		j;
	char	*new_line;
	int		size;
	t_pipe_data *cmds;
	char	**commands_line;
	int		start;
	int		end;
	char	*substr;
	int save;

	if (preparser(line) == -1)
	{
		printf("ERROR\n");
		return (NULL);
	}
	commands_line = ft_split(line, ';');
	i = 0;
	while (commands_line[i])
	{
		size = ft_define_size(commands_line[i]);
		cmds = malloc(sizeof(t_pipe_data) * (size + 1));
		cmds[size].cmd_arg = NULL;
		init_cmds_fds(cmds, size);
		j = 0;
		start = j;
		size = 1;
		while (commands_line[i][j])
		{
			if ((commands_line[i][j] == '\'') || (commands_line[i][j] == '\"'))
				commands_line[i] = quotation(commands_line[i], &j, g_envp);
			else if (commands_line[i][j] == '\\')
				slash(commands_line[i], j);
			else if (commands_line[i][j] == '$')
			{
				save = j;
				commands_line[i] = env_var(commands_line[i], &j, g_envp);
				while (save <= j)
				{
					if (split_cmd(commands_line[i], &save, &start, &(cmds[size - 1])) == 1)
						continue ;
					save++;
				}
			}
			else if (ft_isredirect(commands_line[i][j], commands_line[i][j + 1]))
			{
				if (redirect(&(cmds[size - 1]), &j, commands_line[i]) == 1)
				{
					perror("Error: ");
					break ;
				}
			}
			else if (commands_line[i][j] == '|')
				size++;
			if (split_cmd(commands_line[i], &j, &start, &(cmds[size - 1])) == 1)
				continue ;
			j++;
		}
		cmds_fds(commands_line[i], cmds, size);
		executor(cmds);
		i++;
	}
	ft_free_array(commands_line);
	return (cmds);
}