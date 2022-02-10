#include "minishell.h"

void	ft_echo(char **arg)
{
	int i;
	int	j;
	int is_n;

	i = 1;
	is_n = 0;
	while(arg[i])
	{
		j = 1;
		if (arg[i][0] == '-')
			while (arg[i][j] && arg[i][j] == 'n')
				j++;
		if (arg[i][j] != '\0')
			break;
		is_n = 1;
		i++;
	}
	while(arg[i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		i++;
		if(arg[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!is_n)
		ft_putstr_fd("\n", STDOUT_FILENO);
}