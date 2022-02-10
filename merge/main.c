#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_info	info;
	char	*line;

	info.status = 1;
	info.env = envp;
	
	while (info.status)
	{
		line = get_next_line(1);
		if (line == NULL)
			break;
		parser(line, &info);
//		executor(&info);
	}
}