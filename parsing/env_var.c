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