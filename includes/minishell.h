#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include "get_next_line.h"
# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct s_info
{
	int status;
	char **env;
	char **comands;
}t_info;

typedef struct s_comands
{
	char **comands;
	int size;
	int *end;
}t_comands;

typedef struct s_pipe_data
{
	int		fd_in_out[3];
	int		fd_close[2];
	char	**cmd_ard;
	char	**env;
}	t_pipe_data;

# define READ_FD 0
# define WRITE_FD 1
# define ERR_FD 2

int		parser(char *line, t_info *info);
int		executor(t_comands *comands, t_info *info);
int		ft_run_cmds(t_pipe_data *cmds, int size);
void	ft_free_dable_arr(char **strs);
void	check_cmd(t_pipe_data *data);

#endif