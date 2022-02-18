#include "minishell.h"

static char	*add_home_path(char *path)
{
	char		*tmp;

	tmp = get_env("HOME");
	if (ft_strncmp(path, "~/", 2) || !tmp)
		return (path);
	tmp = ft_strjoin(ft_strchr(tmp, '=') + 1, path + 1);
	free(path);
	return (tmp);
}

static int	change(char *path)
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

int			set_directory(char *path)
{
	struct stat	st;

	if (change(path))
		return (1);
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	g_status = 1;
	if (stat(path, &st) == -1)
		ft_putstr_fd(": No such file or directory", 2);
	else if (!(st.st_mode & S_IXUSR))
		ft_putstr_fd(": Permission denied", 2);
	else
		ft_putstr_fd(": Not a directory", 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

void ft_cd(char **args)
{
	char	*path;

	path = NULL;
	g_status = 0;
	if (args[1] && args[2])
	{
		ft_putstr_fd("too many arguments\n", STDERR_FILENO);
	}
	if (args[1] && !ft_strncmp(args[1], "-", 2))
	{
		path = get_env("OLDPWD");
		if (!path)
			ft_putstr_fd("Error OLDPWD\n", STDERR_FILENO);
		else
		{
			set_directory(ft_strchr(path, '=') + 1);
			printf("%s\n", ft_strchr(get_env("PWD"), '=') + 1);
		}
		return ;
	}
	if (!args[1] || !ft_strncmp(args[1], "~", 1) || !ft_strncmp(args[1], "--", 3))
	{
		if (!(path = get_env("HOME")))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_status = 1;
			return ;
		}
		set_directory(ft_strchr(path, '=') + 1);
		return ;
	}
	args[1] = add_home_path(args[1]);
	set_directory(args[1]);
	return ;
}