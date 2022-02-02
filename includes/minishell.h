#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include "get_next_line.h"
# include "libft.h"

typedef struct s_info
{
	int status;
}t_info;

int	parser(char *line, t_info *info);
int	executor(t_info *info);

#endif