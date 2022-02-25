#include "minishell.h"

#define CLOSE "\001\033[0m\002"                 // Закрыть все свойства
#define BLOD  "\001\033[1m\002"                 // Подчеркнуть, жирным шрифтом, выделить
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"    // x: background, y: foreground

char *ft_add_str(char *str1, char *str2)
{
	char *str_res;

	str_res = ft_strjoin(str1, str2);
	free(str1);
	free(str2);
	return (str_res);
}

char	*prompt()
{
	char	*str;
	char	*tmp;
	char	*path;

	tmp = get_env("USER");
	str = ft_strdup(BEGIN(32, 1));
	if (tmp && ft_strchr(tmp, '='))
		str = ft_add_str(str, ft_strdup(ft_strchr(tmp, '=') + 1));
	str = ft_add_str(str, ft_strdup("@"CLOSE":"));
	str = ft_add_str(str, ft_strdup(BEGIN(34, 1)));
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
	str = ft_add_str(str, path);
	str = ft_add_str(str, ft_strdup(CLOSE"$ "));
	return (str);
}

char	*ft_readline()
{
	char	*res;
	char	*prompt_str;

	prompt_str = prompt();
	res = readline(prompt_str);
	free(prompt_str);
	return res;
}