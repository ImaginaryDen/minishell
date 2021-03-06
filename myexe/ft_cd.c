/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjamis <tjamis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 16:02:28 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/15 14:52:28 by tjamis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_home_path(char *path)
{
	char		*tmp;

	tmp = get_env("HOME");
	if (ft_strncmp(path, "~/", 2) || !tmp)
		return (path);
	tmp = ft_strjoin(ft_strchr(tmp, '=') + 1, path + 1);
	return (tmp);
}

int	change(char *path)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			set_env("OLDPWD", pwd);
			free(pwd);
		}
		pwd = getcwd(NULL, 0);
		if (pwd)
		{
			set_env("PWD", pwd);
			free(pwd);
		}
		return (1);
	}
	return (0);
}

int	set_directory(char *path)
{
	struct stat	st;

	if (change(path))
		return (1);
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	g_info.status = 1;
	if (stat(path, &st) == -1)
		ft_putstr_fd(": No such file or directory", 2);
	else if (!(st.st_mode & S_IXUSR))
		ft_putstr_fd(": Permission denied", 2);
	else
		ft_putstr_fd(": Not a directory", 2);
	ft_putchar_fd('\n', 2);
	g_info.status = 0;
	return (1);
}

void	set_home(char *path_arg)
{
	char	*path;

	path = get_env("HOME");
	if (!path)
	{
		return_error("cd: ", "HOME not set\n", 1);
		return ;
	}
	set_directory(ft_strchr(path, '=') + 1);
	if (path_arg && !ft_strncmp(path_arg, "~/", 2))
		set_directory(path_arg + 2);
	g_info.status = 0;
}

void	ft_cd(char **args)
{
	char	*path;

	if (args[1] && args[2])
		return_error("cd: ", "too many arguments\n", 2);
	else if (args[1] && !ft_strncmp(args[1], "-", 2))
	{
		path = get_env("OLDPWD");
		if (!path)
			return_error("cd: ", "OLDPWD not set\n", 1);
		else
		{
			set_directory(ft_strchr(path, '=') + 1);
			printf("%s\n", ft_strchr(get_env("PWD"), '=') + 1);
		}
	}
	else if (!args[1] || !ft_strncmp(args[1], "~", 1)
		|| !ft_strncmp(args[1], "--", 3))
		set_home(args[1]);
	else
		set_directory(add_home_path(args[1]));
}
