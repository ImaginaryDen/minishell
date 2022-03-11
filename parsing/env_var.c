/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 18:52:29 by mslyther          #+#    #+#             */
/*   Updated: 2022/03/11 19:11:18 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*check_for_status(char *line, int j, int *i)
{
	if (line[j] == '?')
		line = merge_str(line, ft_itoa(g_info.status), i, 1);
	else if (line[j])
		(*i)++;
	return (line);
}

char	*env_var(char *line, int *i)
{
	int		j;
	char	*key;
	int		len;
	char	*env_line;

	j = (*i) + 1;
	if (!is_key(line[j]))
		return (check_for_status(line, j, i));
	while (line[j] && ft_isalnum(line[j]))
		j++;
	len = j - (*i) - 1;
	key = ft_substr(line, (*i) + 1, len);
	env_line = get_env(key);
	if (!env_line)
	{
		if (!ft_isdigit(key[0]))
			line_shift(line, *i, len - 1);
		line_shift(line, *i, 2);
		(*i)--;
	}
	else
		line = merge_str(line, ft_strdup(ft_strchr(env_line, '=') + 1), i, len);
	free(key);
	return (line);
}
