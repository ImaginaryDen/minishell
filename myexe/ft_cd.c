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
	{
		ft_putstr_fd(": No such file or directory", 2);
		g_status = 127;
	}
	else if (!(st.st_mode & S_IXUSR))
		ft_putstr_fd(": Permission denied", 2);
	else
		ft_putstr_fd(": Not a directory", 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

void ft_cd(char **args)
{
	char	*home;

	home = NULL;
	if (!args[1] || !ft_strncmp(args[1], "~", 1) || !ft_strncmp(args[1], "--", 3))
	{
		if (!(home = get_env("HOME")))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return ;
		}
		set_directory(ft_strchr(home, '=') + 1);
		return ;
	}
	args[1] = add_home_path(args[1]);
	set_directory(args[1]);
	return ;
}