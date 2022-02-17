#include "minishell.h"

int	ft_isredirect(char ch1, char ch2)
{
	if (ch1 == '>' && ch2 == '>')
		return (3);
	else if (ch1 == '>')
		return (1);
	else if (ch1 == '<' && ch2 == '<')
		return (4);
	else if (ch1 == '<')
		return (2);
	return (0);
}

int	redirect(t_pipe_data *cmds, int *j, char *line)
{
	int	type;
	int start;
	char	*filename;
	int	fd;

	type = ft_isredirect(line[*j], line[*j + 1]);
	(*j)++;
	if (type == 3 || type == 4)
		(*j)++;
	while (ft_isspace_ispipe(line[*j]))		// тут только isspace, исправить
		(*j)++;
	start = *j;
	while (line[*j] && !ft_isspace_ispipe(line[*j]))		// тут только isspace, исправить
		(*j)++;
	filename = ft_substr(line, start, *j - start);
	if (type == 1)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (type == 3)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (type == 2)
		fd = open(filename, O_RDONLY, 0644);
	if (type == 4)
		fd = here_doc(filename);
	free(filename);
	if (fd == -1)
		return (1);
	if (type == 1 || type == 3)
		cmds->fd_in_out[1] = fd;
	else
		cmds->fd_in_out[0] = fd;
	(*j)--;
	return (0);
}