#include "minishell.h"

char	*quotation(char *line, int *i, char **env)
{
	char	q_type;

	q_type = line[*i];
	line_shift(line, *i, 1);
	while (line[*i])
	{
		if (line[*i] == q_type)
			break ;
		else if ((q_type == '\"') && (line[*i] == '\\') && (line[*i + 1] == '\"' || line[*i + 1] == '$' || line[*i + 1] == '\\'))
			slash(line, *i);
		else if ((q_type == '\"') && (line[*i] == '$'))
			line = env_var(line, i, env);
		(*i)++;
	}
	line_shift(line, *i, 1);
	(*i)--;
	return (line);
}