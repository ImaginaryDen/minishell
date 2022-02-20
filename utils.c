#include "minishell.h"

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

int	ft_size_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
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