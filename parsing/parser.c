#include "minishell.h"

// $0 - обрабатывать?
// $? - нужно обработать с возвращаемым значением от предыдущей команды (напрячь Дениса)
// 2> 1>
// добавить обработку ${}

// Проблемы:
// $321
// echo """""""""",         wtf     :""
// echo $?	
// echo ~
// 1) >fil$q'1' e$w"ho" s$i"r"ing f$r$u file1
// 2) pwd ; cat file1
// ~ брать не из env!
// echo \'\"\\ "\hello\$PWD"
// echo "\""
// echo "\'"
// >"helo l" echo hell\ f
// >>"helo l" echo hell\ f ; echo hell\ f
// echo -$t "-n" '-''n' '-n;'         -n hello
// export a=l d=s; $a$d
// echo ''\''"a|"\'q'a'\a'w'
// echo \"\|\;\"\| cat -e > \q\w\e\r\t\y ; cat qwerty
// pwd >a1>a2>a3; echo s1 >q1 s2>q2 s3; cat a2; cat a3; cat q1; cat q2; 
// echo hello '\' ';' "   '\' \" " \" "$PWD\\\"\~\;"\; >> t1 \' \ \ \\
// echo hello '\' ';' "   '\' \" " \" "$PWD\\\"\~\;"\; >> t1 \' \ \ \\; cat t1
// \ls\ ;
// export a1=a2 ; export a2=' a3' ; export a1=hello$a2=poka
// нельзя удалять пробелы с конца из-за /...

void	line_shift(char *line, int i, int shift)
{
	while (line[i + shift - 1])
	{
		line[i] = line[i + shift];
		i++;
	}
}

void	define_fds(t_pipe_data *cmds)
{
	int	end[2];

	pipe(end);
	if (cmds[0].fd_in_out[WRITE_FD] == STDOUT_FILENO)
		cmds[0].fd_in_out[WRITE_FD] = end[WRITE_FD];
	if (cmds[0].fd_in_out[READ_FD] == STDIN_FILENO)
		cmds[1].fd_in_out[READ_FD] = end[READ_FD];
	if (cmds[0].fd_close[0] == -1)
		cmds[0].fd_close[0] = cmds[1].fd_in_out[READ_FD];
	else
		cmds[0].fd_close[1] = cmds[1].fd_in_out[READ_FD];
	if (cmds[1].fd_close[0] == -1)
		cmds[1].fd_close[0] = cmds[0].fd_in_out[WRITE_FD];
	else
		cmds[1].fd_close[1] = cmds[0].fd_in_out[WRITE_FD];
}

void	cmds_fds(t_pipe_data *cmds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if ((size != 1) && (i != size - 1))
			define_fds(cmds + i);
		if (i == size - 1 && (size != 1))
			cmds[i].fd_close[0] = cmds[i - 1].fd_in_out[WRITE_FD];
		i++;
	}
}

int ft_define_size(char **line)
{
	int	i;
	int count;

	i = 0;
	count = 1;
	while (line[i] && ft_strncmp(line[i], "||", 2) && ft_strncmp(line[i], "&&", 2))
	{
		if (!ft_strncmp(line[i], "|", 1))
			count++;
		i++;
	}
	return (count);
}

int	ft_isspace_ispipe(char ch)
{
	if ((ch >= 9 && ch <= 13) || ch == 32 || ch == '|')
		return (1);
	return (0);
}

t_pipe_data *parser(char *line, t_info *info)
{
	int		i;
	int		j;
	char	*new_line;
	int		size;
	t_pipe_data *cmds;
	char	**line_split;
	int		start;
	int		end;
	char	*substr;
	int len;
	int save;

	cmds = NULL;
	line_split = preparser(&line);
	if (!line_split)
	{
		printf("ERROR\n");
		return (NULL);
	}
	i = 0;
	 while (line_split[i])
	 {
	 	printf("%d - %s\n", i, line_split[i]);
	 	i++;
	 }
	 i = 0;
	// while (line_split[i])
	// {
	// 	size = ft_define_size(line_split + i);
	// 	cmds = malloc(sizeof(t_pipe_data) * (size + 1));
	// 	cmds[size].cmd_arg = NULL;
	// 	init_cmds_fds(cmds, size);
	// 	j = 0;
	// 	start = j;
	// 	size = 1;
	// 	while (line_split[i] && ft_strncmp(line_split[i], "||", 2) && ft_strncmp(line_split[i], "&&", 2))
	// 	{
	// 		if (!ft_strncmp(line_split[i], "|", 1))
	// 		{
	// 			size++;
	// 			i++;
	// 			continue ;
	// 		}
	// 		while (line_split[i][j])
	// 		{
				
	// 		}
			
	// 		else if ((line_split[i][j] == '\'') || (line_split[i][j] == '\"'))
	// 		{
	// 			line_split[i] = quotation(line_split[i], &j, g_info.envp);
	// 			continue ;
	// 		}
	// 		else if (line_split[i][j] == '$')
	// 		{
	// 			save = j;
	// 			line_split[i] = env_var(line_split[i], &j, g_info.envp);
	// 			while (save <= j)
	// 			{
	// 				if (split_cmd(line_split[i], &save, &start, &(cmds[size - 1])) == 1)
	// 					continue ;
	// 				save++;
	// 			}
	// 		}
	// 		else if (ft_isredirect(line_split[i][j], line_split[i][j + 1]))
	// 		{
	// 			if (redirect(&(cmds[size - 1]), &j, line_split[i]) == 1)
	// 			{
	// 				perror("Error: ");
	// 				break ;
	// 			}
	// 			start = j + 1;
	// 		}
	// 		else if (line_split[i][j] == '|')
	// 		{
	// 			if (split_cmd(line_split[i], &j, &start, &(cmds[size - 1])) == 1)
	// 				continue ;
	// 			j++;
	// 			size++;
	// 			continue ;
	// 		}
	// 		if (split_cmd(line_split[i], &j, &start, &(cmds[size - 1])) == 1)
	// 			continue ;
	// 		j++;
	// 	}
	// 	printf("%s\n", line_split[i]);
	// 	cmds_fds(line_split[i], cmds, size);
	// 	executor(cmds);
	// 	i++;
	// }

	while (line_split[i])
	{
		size = ft_define_size(line_split + i);
	 	cmds = malloc(sizeof(t_pipe_data) * (size + 1));
	 	cmds[size].cmd_arg = NULL;
	 	init_cmds_fds(cmds, size);
	 	size = 1;
		while (line_split[i] && ft_strncmp(line_split[i], "||", 2) && ft_strncmp(line_split[i], "&&", 2))
		{
			j = 0;
			if (!ft_strncmp(line_split[i], "|", 1))
			{
				size++;
				i++;
				continue ;
			}
			if (ft_isredirect(line_split[i][j], line_split[i][j + 1]))
			{
				if (redirect(&(cmds[size - 1]), line_split[i], line_split[i + 1]) == 1)
	 			{
	 				perror("Error: ");
	 				break ;
	 			}
				i += 2;
	 			continue ;
			}
			while (line_split[i][j])
			{
				if ((line_split[i][j] == '\'') || (line_split[i][j] == '\"'))
					line_split[i] = quotation(line_split[i], &j, g_info.envp);
				else if (line_split[i][j] == '$')
		 		{
		 			save = j;
		 			line_split[i] = env_var(line_split[i], &j, g_info.envp);
		 			// while (save <= j)						крч сделать обработку замененного значения
		 			// {
		 			// 	if (ft_isspace(line_split[i][j]))
					// 	{
							
					// 	}
		 			// 	j++;
		 			// }
		 		}
				j++;
			}
			len = ft_size_arr(cmds[size - 1].cmd_arg);
			cmds[size - 1].cmd_arg = ft_realloc(cmds[size - 1].cmd_arg, sizeof(char *) * len, sizeof(char *) * (len + 2));
			cmds[size - 1].cmd_arg[len] = line_split[i];
			i++;
		}
		cmds_fds(cmds, size);
	 	executor(cmds);
		i++;
	}

//	ft_free_array(line_split);
	return (cmds);
}