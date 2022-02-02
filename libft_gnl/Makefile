NAME = libft_gnl.a

# Headers
HEADERS_DIRECTORY = -I./includes/
HEADERS = $(shell ls ./includes/*.h)

# Sources
SRCS_LIBFT = $(shell ls ./libft/*.c)
SRCS_GNL = $(shell ls ./gnl/*.c)
SRCS = $(SRCS_LIBFT) $(SRCS_GNL)

# Objects
OBJS = $(SRCS:%.c=%.o)

# Compilation
CC = gcc
FLAGS = -Wall -Wextra -Werror

# Run lib
LIBC = ar rc
LIBR = ranlib

# Utils
RM = rm -rf

.PHONY: all clean fclean re

all: $(NAME)

%.o: %.c	
	$(CC) $(CFLAGS) $(HEADERS_DIRECTORY) -c $< -o $@

$(NAME): $(OBJS) $(HEADERS)
	$(LIBC) $(NAME) $(OBJS)
	$(LIBR) $(NAME)

clean:	
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
