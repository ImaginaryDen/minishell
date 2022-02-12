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

typedef struct s_pipe_data
{
	int		fd_in_out[3];
	int		fd_close[2];
	char	**cmd_arg;
}	t_pipe_data;

char **g_envp;

# define READ_FD 0
# define WRITE_FD 1
# define ERR_FD 2

t_pipe_data *parser(char *line, t_info *info);
int		executor(t_pipe_data *comand);
int		ft_run_cmds(t_pipe_data *cmds, int size);
void	ft_free_dable_arr(char **strs);
void	check_cmd(t_pipe_data *data);
void	ft_echo(char **arg);
void	ft_env(char **arg);
int		return_error(char *cmd, char *msg, int ret, int status);
int		exev_include(t_pipe_data *data);
int		check(char **args);
char	*get_env(char *str);
char	**split_isspace(char const *s);
int		ft_cmd(t_pipe_data *data);
int ft_one_cmd(t_pipe_data *data);

#endif