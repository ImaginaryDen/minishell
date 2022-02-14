#include "minishell.h"

char **copy_envp(char **envp)
{
	int		size;
	char	**copy_envp;
	int		i;

	size = 0;
	while (envp[size])
		size++;
	copy_envp = malloc(sizeof(char *) * (size + 1));
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

int main(int argc, char **argv, char **envp)
{
	t_info	info;
	char	*line;

	info.status = 1;
	g_envp = copy_envp(envp);

	while (info.status)
	{
		ft_putstr_fd("$>", 1);
		line = get_next_line(1);
		if (line == NULL)
			break;
		parser(line, &info);
	}
}