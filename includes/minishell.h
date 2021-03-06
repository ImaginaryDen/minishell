/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:28:21 by tjamis            #+#    #+#             */
/*   Updated: 2022/03/15 14:03:26 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <sys/stat.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <signal.h>

typedef struct s_info
{
	char	**envp;
	char	**history;
	int		status;
	int		pid;
}t_info;

typedef struct s_cmd_data
{
	int		fd_in_out[3];
	int		fd_close[2];
	char	**cmd_arg;
}	t_cmd_data;

t_info	g_info;

typedef struct s_parser_data
{
	t_cmd_data	*cmds;
	char		**line_split;
	char		**curr_cmd;
	char		*curr_word;
	int			size;
}	t_parser_data;

# define READ_FD 0
# define WRITE_FD 1
# define ERR_FD 2

/*PARSER*/
void		parser(char *line);
char		**split_isspace(char const *s);
t_cmd_data	*init_cmds_fds(int size);
char		*quotation(char *line, int *i, int *flag);
int			redirect(t_cmd_data *cmds, char *redirect, char *filename);
void		line_shift(char *line, int i, int shift);
int			ft_isredirect(char ch1, char ch2);
char		**preparser(char **line);
char		*delete_isspace(char *line);
int			is_key(char ch);
char		**error_message(char ***line_split, int i);
char		**error_quotes(char ***line_split);
int			free_if_error(t_cmd_data *comand);
int			ft_isspace(char ch);
int			special_symbol(char *line);
void		add_str(char *line, int *i, int *start, char ***line_split);
void		define_fds(t_cmd_data *cmds);
void		cmds_fds(t_cmd_data *cmds, int size);
void		wildcards(t_parser_data *data, int j);
void		parse_env(t_parser_data *data, int *j);
int			parser_after_env(t_parser_data *data, int *j);
void		add_cmd(t_cmd_data *cmds, int size, char *str);
int			ft_define_size(char **line);
/*EXECUTOR*/
int			executor(t_cmd_data *comand);
int			ft_run_cmds(t_cmd_data *cmds, int size);
void		check_cmd(t_cmd_data *data);
int			exev_include(t_cmd_data *data);
int			check(char **args);
int			ft_cmd(t_cmd_data *data);
int			ft_one_cmd(t_cmd_data *data);
void		status_child(int pid);
void		sigint_handler(int sign_num);
int			here_doc(char *limit);
char		*ft_readline(void);
/*env function*/
int			set_env(char *env, char *new_env);
int			unset_env(char *env);
void		sigint_heredoc(int sign_num);
char		*get_env(char *str);
char		*env_var(char *line, int *i);
/*function for double*/
void		ft_free_array(char **array);
int			ft_size_arr(char **arr);
void		char_arr_sort(char **env);
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
char		**get_files(char *path);
void		exit_if_null(void *ptr, const char *msg_err);
int			ft_isspace_s(char ch);
void		status_child(int pid);
void		free_cmd(t_cmd_data *data);
void		set_redir(int *end);
pid_t		get_fork(pid_t *pid, int i);
/*rl library*/
void		rl_clear_history(void);
void		rl_replace_line(const char *text, int clear_undo);

# define CLOSE "\001\033[0m\002"
# define BLOD  "\001\033[1m\002"

#endif