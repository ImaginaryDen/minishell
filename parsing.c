#include "minishell.h"

// $0 - обрабатывать?
// $? - нужно обработать с возвращаемым значением от предыдущей команды (напрячь Дениса)

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

char	*line_shift(char *line, int i, int shift)
{
	while (line[i + shift - 1])
	{
		line[i] = line[i + shift];
		i++;
	}
	return (line);
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
		line = line_shift(line, *i, 1);
		if (ft_isdigit(key[0]))
			line = line_shift(line, *i, 1);
		else
			line = line_shift(line, *i, len);
		(*i)--;
	}
	else
		line = merge_str(line, env[j], i, len);
//	printf("%s\n%s\n%s\n", tmp_start, tmp_env, tmp_end);
//	printf("%d\n", *i);
	free(key);
	return (line);
}

char	*slash(char *line, int i)
{
	line = line_shift(line, i, 1);
	return (line);
}

char	*quotation(char *line, int *i, char **env)
{
	char	q_type;

	q_type = line[*i];
	line = line_shift(line, *i, 1);
	while (line[*i])
	{
		if (line[*i] == q_type)
			break ;
		else if ((q_type == '\"') && (line[*i] == '\\') && (line[*i + 1] == '\"' || line[*i + 1] == '$' || line[*i + 1] == '\\'))
			line = slash(line, *i);
		else if ((q_type == '\"') && (line[*i] == '$'))
			line = env_var(line, i, env);
		(*i)++;
	}
	line = line_shift(line, *i, 1);
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
		if (line[i] == ';' && line[i + 1])
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

void	cmds_split(char *line, t_pipe_data *cmds, int size)
{
	int	i;
	char	**cmds_unsplitted;

	i = 0;
	cmds_unsplitted = ft_split(line, ';');
	while (i < size)
	{
		cmds[i].cmd_arg = split_isspace(cmds_unsplitted[i]);
		i++;
	}
	ft_free_array(cmds_unsplitted);
}

t_pipe_data *parser(char *line, t_info *info)
{
	int		i;
	char	*new_line;
	int		size;
	t_pipe_data *cmds;

	i = 0;
	size = preparser(line);
	if (size == -1)
	{
		// print error;
		return (NULL);
	}
	cmds = malloc(sizeof(t_pipe_data) * (size + 1));
	cmds[size].cmd_arg = NULL;
//	printf("OK\n");
	while (line[i])
	{
		if ((line[i] == '\'') || (line[i] == '\"'))
			line = quotation(line, &i, g_envp);
		else if (line[i] == '\\')
			line = slash(line, i);
		else if (line[i] == '$')
			line = env_var(line, &i, g_envp);
		i++;
	}
	line = ft_realloc_str(line, ft_strlen(line));
	cmds_split(line, cmds, size);
	free(line);
	return (cmds);
}