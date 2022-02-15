#include "minishell.h"

int get_command(char *str)
{
	const char *comands[] = {"echo", "env", "pwd", "cd", "exit", "export", "unset", NULL};
	int i;

	i = 0;
	while(comands[i])
	{
		if (!ft_strncmp(str, comands[i], ft_strlen(comands[i]) + 1))
			return (i);
		i++;
	}
	return (-1);
}

int exev_include(t_pipe_data *data)
{
	void (*command[])(char **) = {ft_echo, ft_env, ft_pwd, ft_cd, ft_exit, ft_export, ft_unset};
	int	i;

	i = get_command(data->cmd_arg[0]);
	if (i >= 0)
	{
		command[i](data->cmd_arg);
		return (1);
	}
	return (0);
}