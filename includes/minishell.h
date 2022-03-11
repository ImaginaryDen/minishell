#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include "get_next_line.h"
# include "libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <signal.h>

typedef struct s_info
{
	char	**envp;
	char	**history;
	int		status;
	int		pid;
}t_info;

typedef struct s_pipe_data
{
	int		fd_in_out[3];
	int		fd_close[2];
	char	**cmd_arg;
}	t_pipe_data;

t_info g_info;

# define READ_FD 0
# define WRITE_FD 1
# define ERR_FD 2

/*PARSER*/
t_pipe_data	*parser(char *line, t_info *info);
char		**split_isspace(char const *s);
int			ft_isspace_ispipe(char ch);
void		init_cmds_fds(t_pipe_data *commands, int size);
char		*quotation(char *line, int *i, char **env);
int			redirect(t_pipe_data *cmds, int *j, char *line);
void		slash(char *line, int *i);
void		line_shift(char *line, int i, int shift);
int			ft_isredirect(char ch1, char ch2);
char		**preparser(char **line);
char		*delete_isspace(char *line);
int			is_key(char ch);
/*EXECUTOR*/
int			executor(t_pipe_data *comand);
int			ft_run_cmds(t_pipe_data *cmds, int size);
void		check_cmd(t_pipe_data *data);
int			exev_include(t_pipe_data *data);
int			check(char **args);
int			ft_cmd(t_pipe_data *data);
int			ft_one_cmd(t_pipe_data *data);
void		status_child(int pid);
void		sigint_handler(int sign_num);
int			here_doc(char *limit);
char		*ft_readline();
/*env function*/
int			set_env(char *env, char *new_env);
int			unset_env(char *env);
void		sigint_heredoc(int sign_num);
char		*get_env(char *str);
char		*env_var(char *line, int *i, char **env);
/*function for double*/
void		ft_free_double_arr(char **strs);
void		ft_free_array(char **array);
int			ft_size_arr(char **arr);
void		char_arr_sort(char **env);
int			ft_add_words(char const *s, char **words);
/*include function*/
void		ft_unset(char **args);
void		ft_echo(char **arg);
void		ft_pwd(char **arg);
void		ft_env(char **arg);
void		ft_cd(char **args);
void		ft_exit(char **argv);
void		ft_history(char **args);
void		ft_export(char **args);
void		ft_add_history(char *str);
/*utisl*/
char		**copy_envp(char **envp);
int			return_error(char *cmd, char *msg, int status);
void		line_shift(char *line, int i, int shift);
char		**get_files(char *path);
void		exit_if_null(void *ptr, const char *msg_err);
int			ft_isspace_s(char ch);
void		status_child(int pid);
void		free_cmd(t_pipe_data *data);
void		set_redir(int *end);
pid_t		get_fork(t_pipe_data *cmd, pid_t *pid, int i);

#define CLOSE "\001\033[0m\002"
#define BLOD  "\001\033[1m\002"
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"

#endif