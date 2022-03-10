#include "minishell.h"

int	is_key(char ch)
{
	if ((ch == '_') || ft_isalnum(ch))
		return (1);
	return (0);
}

char	*merge_str(char *line, char *env, int *i, int len)
{
	char	*tmp_start;
	char	*tmp_start_env;
	char	*tmp_end;

	tmp_start = ft_substr(line, 0, *i);
	tmp_end = ft_strdup(line + (*i) + 1 + len);
	tmp_start_env = ft_strjoin(tmp_start, env);
	free(tmp_start);
	free(line);
	line = ft_strjoin(tmp_start_env, tmp_end);
	free(tmp_start_env);
	free(tmp_end);
	(*i) += ft_strlen(env) - 1;
	free(env);
	return (line);
}

char	*env_var(char *line, int *i, char **env)
{
	int	j;
	char	*key;
	int		len;
	int		found;
	char	*env_line;

//	printf("%d\n", *i);
	j = (*i) + 1;
	if (!is_key(line[j]))
	{
		if (line[j] == '?')
			line = merge_str(line, ft_itoa(g_info.status), i, 1);
		else if (line[j])
			(*i)++;
		return (line);
	}
	while (line[j] && ft_isalnum(line[j]))
		j++;
	len = j - (*i) - 1;
	key = ft_substr(line, (*i) + 1, len);
//	printf("%d - %s\n", len, key);
	j = 0;
	found = 0;
	env_line = get_env(key);
//	printf("OK $\n");
	if (!env_line)
	{
		line_shift(line, *i, 1);
		if (ft_isdigit(key[0]))
			line_shift(line, *i, 1);
		else
			line_shift(line, *i, len);
		(*i)--;
	}
	else
		line = merge_str(line, ft_strdup(ft_strchr(env_line, '=') + 1), i, len);
//	printf("%s\n%s\n%s\n", tmp_start, tmp_env, tmp_end);
//	printf("%d\n", *i);
	free(key);
	return (line);
}