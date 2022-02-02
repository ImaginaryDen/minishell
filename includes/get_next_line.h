#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

char	*get_next_line(int fd);
char	*ft_clean(int ret, char **line, char **cache);
void	*ft_realloc(void *old, int size);
char	*ft_read_line(int fd, char **line, char **cache);

#endif
