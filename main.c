#include "minishell.h"

void init_shell(char **envp)
{
	char *tmp;
	int tmp_num;

	g_envp = copy_envp(envp);
	g_status = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);
	tmp = get_env("SHLVL");
	if (!tmp)
		return;
	tmp = ft_strchr(tmp, '=') + 1;
	if (!tmp)
		return;
	tmp_num = ft_atoi(tmp) + 1;
	tmp = ft_itoa(tmp_num);
	set_env("SHLVL", tmp);
	free(tmp);
}

int main(int argc, char **argv, char **envp)
{
	t_info	info;
	char	*line;

	(void)argc;
	(void)argv;
	info.status = 1;
	init_shell(envp);
	while (info.status)
	{
		line = ft_readline();
		ft_add_history(line);
		if (line == NULL)
		{
			ft_exit(NULL);
			break;
		}
		parser(line, &info);
	}
}