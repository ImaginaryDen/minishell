#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_info	info;
	t_comands *comands;
	char	*line;

	info.status = 1;
	info.env = envp;
	comands = malloc(sizeof(t_comands) * 1);
	while (info.status)
	{
		//line = get_next_line(0);
		// if (line == NULL)
		// 	break;
		// parser(line, &info);
		// free(line);
		executor(comands, &info);
	}
}