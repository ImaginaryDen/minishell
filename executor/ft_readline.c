/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:55:45 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/15 13:27:23 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_str(char *str1, char *str2)
{
	char	*str_res;

	str_res = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (str_res);
}

char	*get_path(void)
{
	char	*tmp;
	char	*path;

	path = getcwd(NULL, 0);
	tmp = get_env("HOME");
	if (tmp)
	{
		tmp = ft_strchr(tmp, '=') + 1;
		if (!ft_strncmp(tmp, path, ft_strlen(path) + 1))
		{
			free(path);
			path = ft_strdup("~");
		}
		else if (tmp && ft_strnstr(path, tmp, ft_strlen(path)) == path)
		{
			line_shift(path, 2, ft_strlen(tmp) - 1);
			path[0] = '~';
			path[1] = '/';
		}
	}
	return (path);
}

char	*prompt(void)
{
	char	*str;
	char	*tmp;
	char	*path;

	tmp = get_env("USER");
	str = ft_strdup("\001\033[32;1m\002");
	if (tmp && ft_strchr(tmp, '='))
		str = ft_add_str(str, ft_strdup(ft_strchr(tmp, '=') + 1));
	str = ft_add_str(str, ft_strdup("@"CLOSE":"));
	str = ft_add_str(str, ft_strdup("\001\033[34;1m\002"));
	path = get_path();
	str = ft_add_str(str, path);
	str = ft_add_str(str, ft_strdup(CLOSE"$ "));
	return (str);
}

char	*ft_readline(void)
{
	char	*res;
	char	*prompt_str;

	prompt_str = prompt();
	res = readline(prompt_str);
	free(prompt_str);
	return (res);
}
