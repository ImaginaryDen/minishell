#include "minishell.h"
static void	process(int sign_num)
{
	if (!kill(g_pid, sign_num))
	{
		if (sign_num == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_status = 131;
		}
		else if (sign_num == SIGINT)
		{
			ft_putstr_fd("\n", 1);
			g_status = 130;
		}
	}
	else if (sign_num == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_status = 1;
	}
}

void		sigint_handler(int sign_num)
{	
	if ((sign_num == SIGINT || sign_num == SIGQUIT) && g_pid != 0)
		process(sign_num);
	else
	{
		if (sign_num == SIGINT)
		{
			g_status = 1;
			ft_putstr_fd("\n", 1);
			rl_on_new_line();
			rl_replace_line("", 1);
			rl_redisplay();
		}
		else if (sign_num == SIGQUIT)
			ft_putstr_fd("\b\b  \b\b", 1);
	}
}

void		sigint_heredoc(int sign_num)
{	
	if (sign_num == SIGINT)
	{
		g_status = 1;
		exit(2);
	}
	else if (sign_num == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
}