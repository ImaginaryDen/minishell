#include "minishell.h"

void	here_doc_gnl(int *end, char *limit)
{
	char		*str;
	const int	len = ft_strlen(limit);

	close(end[READ_FD]);

	signal(SIGINT, sigint_heredoc);
	signal(SIGQUIT, sigint_heredoc);
	ft_putchar_fd('>', 1);
	str = get_next_line(0);
	while (str)
	{
		if (!ft_strncmp(str, limit, len) && str[len] == '\n')
			break ;
		write(end[WRITE_FD], str, ft_strlen(str));
		free(str);
		ft_putchar_fd('>', 1);
		str = get_next_line(0);
	}
	if (str)
		free(str);
	close(end[WRITE_FD]);
	exit(0);
}

int	here_doc(char *limit)
{
	int end[2];
	pid_t pid;

	pipe(end);
	pid = fork();
	g_pid = pid;
	if (!pid)
		here_doc_gnl(end, limit);
	close(end[WRITE_FD]);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	wait(NULL);
	return (end[READ_FD]);
}
