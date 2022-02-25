#include "minishell.h"

void	char_arr_sort(char ** env)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = NULL;
	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if(ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char **get_files(char *path)
{
	char			**all_name;
	int				size;
	DIR*			dir;
	struct dirent*	dir_dirent;

	dir = opendir(path);
	all_name = NULL;
	size = 0;
	if(dir == NULL)
	{
		perror("opendir");
		return (NULL);
	}
	dir_dirent = readdir(dir);
	while(dir_dirent)
	{
		if(dir_dirent->d_name[0] != '.')
		{
			all_name = ft_realloc(all_name, size * sizeof(char *), (size + 2) * sizeof(char *));
			all_name[size] = ft_strdup(dir_dirent->d_name);
			size++;
		}
		dir_dirent = readdir(dir);
	}
	return (all_name);
}

void	exit_if_null(void *ptr, const char *msg_err)
{
	if (ptr)
		return ;
	perror(msg_err);
	g_status = 1;
	ft_exit(NULL);
}

char **copy_envp(char **envp)
{
	int		size;
	char	**copy_envp;
	int		i;

	size = 0;
	while (envp[size])
		size++;
	copy_envp = malloc(sizeof(char *) * (size + 1));
	exit_if_null(copy_envp, "malloc");
	if (!copy_envp)
		return (NULL);
	i = 0;
	while (i < size)
	{
		copy_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	copy_envp[i] = NULL;
	return (copy_envp);
}
