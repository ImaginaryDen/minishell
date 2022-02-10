#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include "get_next_line.h"
# include "libft.h"

typedef struct s_info
{
	int status;
	char	**env;
}t_info;

typedef struct s_pipe_data
{
	int fd_in_out[3];
	int fd_close[2];
	char **cmd_ard;
} t_pipe_data;

t_pipe_data *parser(char *line, t_info *info);
int	executor(t_info *info);
char	**split_isspace(char const *s);

#endif