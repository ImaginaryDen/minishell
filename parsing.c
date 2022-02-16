#include "minishell.h"

// $0 - обрабатывать?
// $? - нужно обработать с возвращаемым значением от предыдущей команды (напрячь Дениса)
// в переменной окружения тоже надо разделять аргументы пробельными символами, а не оставлять как есть
// добавить обработку ${}

char	*ft_realloc_str(char *old, int size)
{
	char	*new;
	int		i;

	new = malloc(size);
	if (!new)
		return (NULL);
	i = 0;
	while (old && i < size && old[i])
	{
		new[i] = old[i];
		i++;
	}
	new[i] = '\0';
	if (old)
		free(old);
	return (new);
}

void	line_shift(char *line, int i, int shift)
{
	while (line[i + shift - 1])
	{
		line[i] = line[i + shift];
		i++;
	}
}

int	is_key(char ch)
{
	if ((ch == '_') || ft_isalnum(ch))
		return (1);
	return (0);
}

char	*merge_str(char *line, char *env, int *i, int len)
{
	char	*tmp_start;
	char	*tmp_env;
	char	*tmp_start_env;
	char	*tmp_end;

	tmp_start = ft_substr(line, 0, *i);
	tmp_env = ft_strdup(env + len + 1);
	tmp_end = ft_strdup(line + (*i) + 1 + len);
	tmp_start_env = ft_strjoin(tmp_start, tmp_env);
	free(tmp_start);
	free(line);
	line = ft_strjoin(tmp_start_env, tmp_end);
	free(tmp_start_env);
	free(tmp_end);
	(*i) += ft_strlen(tmp_env) - 1;
	free(tmp_env);
	return (line);
}

char	*env_var(char *line, int *i, char **env)
{
	int	j;
	char	*key;
	int		len;
	int		found;

//	printf("%d\n", *i);
	j = (*i) + 1;
	if (!is_key(line[j]))
		return (line);
	while (line[j] && ft_isalnum(line[j]))
		j++;
	len = j - (*i) - 1;
	key = ft_substr(line, (*i) + 1, len);
//	printf("%d - %s\n", len, key);
	j = 0;
	found = 0;
	while (env[j])
	{
		if ((ft_strncmp(env[j], key, len) == 0) && (env[j][len] == '='))
		{
			found = 1;
			break ;
		}
		j++;
	}
//	printf("OK $\n");
	if (!found)
	{
		line_shift(line, *i, 1);
		if (ft_isdigit(key[0]))
			line_shift(line, *i, 1);
		else
			line_shift(line, *i, len);
		(*i)--;
	}
	else
		line = merge_str(line, env[j], i, len);
//	printf("%s\n%s\n%s\n", tmp_start, tmp_env, tmp_end);
//	printf("%d\n", *i);
	free(key);
	return (line);
}

void	slash(char *line, int i)
{
	line_shift(line, i, 1);
}

char	*quotation(char *line, int *i, char **env)
{
	char	q_type;

	q_type = line[*i];
	line_shift(line, *i, 1);
	while (line[*i])
	{
		if (line[*i] == q_type)
			break ;
		else if ((q_type == '\"') && (line[*i] == '\\') && (line[*i + 1] == '\"' || line[*i + 1] == '$' || line[*i + 1] == '\\'))
			slash(line, *i);
		else if ((q_type == '\"') && (line[*i] == '$'))
			line = env_var(line, i, env);
		(*i)++;
	}
	line_shift(line, *i, 1);
	(*i)--;
	return (line);
}

int	preparser(char *line)
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

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
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

void	cmds_split(char *line, t_pipe_data *cmds, int size)
{
	int	i;
	char	**cmds_unsplitted;

	i = 0;
//	cmds_unsplitted = ft_split(line, '|');
	while (i < size)
	{
		if ((size != 1) && (i != size - 1))
			define_fds(cmds + i);
		if (i == size - 1 && (size != 1))
			cmds[i].fd_close[0] = cmds[i - 1].fd_in_out[WRITE_FD];
//		cmds[i].cmd_arg = split_isspace(cmds_unsplitted[i]);
		i++;
	}
//	ft_free_array(cmds_unsplitted);
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

int	ft_size_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

int	ft_isspace_ispipe(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32 || ch == '|')
		return (1);
	return (0);
}

int	ft_isredirect(char ch1, char ch2)
{
	if (ch1 == '>' && ch2 == '>')
		return (3);
	else if (ch1 == '>')
		return (1);
	else if (ch1 == '<' && ch2 == '<')
		return (4);
	else if (ch1 == '<')
		return (2);
	return (0);
}

int	redirect(t_pipe_data *cmds, int *j, char *line)
{
	int	type;
	int start;
	char	*filename;
	int	fd;

	type = ft_isredirect(line[*j], line[*j + 1]);
	(*j)++;
	if (type == 3 || type == 4)
		(*j)++;
	while (ft_isspace_ispipe(line[*j]))		// тут только isspace, исправить
		(*j)++;
	start = *j;
	while (line[*j] && !ft_isspace_ispipe(line[*j]))		// тут только isspace, исправить
		(*j)++;
	filename = ft_substr(line, start, *j - start);
	if (type == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == 3)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (type == 2)
		fd = open(filename, O_RDONLY, 0644);
	if (type == 4)
		fd = 0;
	free(filename);
	if (fd == -1)
		return (1);
	if (type == 1 || type == 3)
		cmds->fd_in_out[1] = fd;
	else
		cmds->fd_in_out[0] = fd;
	return (0);
}

t_pipe_data *parser(char *line, t_info *info)
{
	int		i;
	int		j;
	char	*new_line;
	int		size;
	t_pipe_data *cmds;
	char	**commands;
	int		start;
	int		end;
	char	*substr;
	int		len;

	i = 0;
	if (preparser(line) == -1)
	{
		// print error;
		return (NULL);
	}
	commands = ft_split(line, ';');
//	size = ft_define_size(commands);
//	preparser(line);
//	printf("OK\n");
	j = 0;
	while (commands[i])
	{
		size = ft_define_size(commands[i]);
		cmds = malloc(sizeof(t_pipe_data) * (size + 1));
		cmds[size].cmd_arg = NULL;
		init_cmds_fds(cmds, size);
		start = j;
		size = 1;
		while (commands[i][j])
		{
			if (ft_isspace_ispipe(commands[i][j]) || ft_isredirect(commands[i][j], commands[i][j + 1]) || commands[i][j + 1] == '\0')
			{
				if ((j - start) > 0)
				{
					len = ft_size_arr(cmds[size - 1].cmd_arg);
					cmds[size - 1].cmd_arg = ft_realloc(cmds[size - 1].cmd_arg, sizeof(char *) * len, sizeof(char *) * (len + 2));
					cmds[size - 1].cmd_arg[len] = ft_substr(commands[i], start, j - start);
					start = j + 1;
				}
				else
					start++;
			//	printf("STR: %s\n", cmds[size - 1].cmd_arg[len]);
				if (ft_isredirect(commands[i][j], commands[i][j + 1]))
				{
					if (redirect(&(cmds[size - 1]), &j, commands[i]) == 1)
					{
						perror("Error: ");
						// надо как-то выйти...
					}
					start = j;
					continue ;
				}
			}
			if ((commands[i][j] == '\'') || (commands[i][j] == '\"'))
				commands[i] = quotation(commands[i], &j, g_envp);
			else if (commands[i][j] == '\\')
				slash(commands[i], j);
			else if (commands[i][j] == '$')
				commands[i] = env_var(commands[i], &j, g_envp);
			else if (commands[i][j] == '|')
				size++;
			j++;
		}
	//	cmds[size].cmd_arg = NULL;
	//	init_cmds_fds(cmds, size);
		cmds_split(commands[i], cmds, size);
		// int n = 0;
		// int z = 0;
		// while (cmds[n].cmd_arg)
		// {
		// 	while (cmds[n].cmd_arg[z])
		// 	{
		// 		printf("%s\n", cmds[n].cmd_arg[z]);
		// 		z++;
		// 	}
		// 	printf("***end***\n");
		// 	n++;
		// }
		executor(cmds);
		i++;
		j = 0;
		size = 1;
	}
	//line = ft_realloc_str(line, ft_strlen(line));
	free(line);
	return (cmds);
}