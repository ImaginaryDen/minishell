/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tanya <tanya@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 15:46:40 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/13 18:31:27 by tanya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_full_path(char *path, char *cmd)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(path, "/");
	result = ft_strjoin(temp, cmd);
	free(temp);
	return (result);
}

char	**ft_get_paths(char **envp)
{
	int	i;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4))
		i++;
	return (ft_split(envp[i] + 5, ':'));
}

void	check_cmd(t_cmd_data *data)
{
	int		i;
	char	**paths;
	char	*path_cmd;

	if (!ft_strncmp(data->cmd_arg[0], "./", 2)
		|| data->cmd_arg[0][0] == '/' || get_env("PATH") == NULL)
		return ;
	paths = ft_get_paths(g_info.envp);
	i = 0;
	while (paths[i])
	{
		path_cmd = ft_full_path(paths[i], data->cmd_arg[0]);
		if (!access(path_cmd, X_OK))
		{
			free(data->cmd_arg[0]);
			data->cmd_arg[0] = path_cmd;
			break ;
		}
		free(path_cmd);
		path_cmd = NULL;
		i++;
	}
	ft_free_array(paths);
}

int	check(char **args)
{
	struct stat	f;
	int			flag;

	if (stat(args[0], &f) != -1)
	{
		if (f.st_mode & S_IFDIR)
			return (return_error(args[0], ": Is a directory\n", 126));
		if (f.st_mode & S_IXUSR && f.st_mode & S_IRUSR)
			return (0);
		return (return_error(args[0], ": Permission denied\n", 126));
	}
	else if (ft_strchr(args[0], '/') != NULL)
	{
		return (return_error(args[0], ": No such file or directory\n", 127));
	}
	return (return_error(args[0], ": command not found\n", 127));
}
