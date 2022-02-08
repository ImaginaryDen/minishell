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


void check_cmd(t_pipe_data *data)
{
	int		i;
	char	**paths;
	char	*path_cmd;

	if (!ft_strncmp(data->cmd_ard[0], "./", 2) || data->cmd_ard[0][0] == '/')
		return ;
	paths = ft_get_paths(data->env);
	i = 0;
	while (paths[i])
	{
		path_cmd = ft_full_path(paths[i], data->cmd_ard[0]);
		if (!access(path_cmd, X_OK))
		{
			free(data->cmd_ard[0]);
			data->cmd_ard[0] = path_cmd;
			break ;
		}
		free(path_cmd);
		path_cmd = NULL;
		i++;
	}
	ft_free_dable_arr(paths);
}