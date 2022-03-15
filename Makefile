NAME		=	minishell

LIBFT		=	./libft_gnl/libft_gnl.a
PATH_HEADER =	./includes/
PATH_LIB 	=	./libft_gnl/
HEADER  	=	./includes/minishell.h 
PATH_IMAC	=	~/.brew/Cellar/readline/8.1.2/

OBJ_DIR		=	./objects
SRC			=	$(shell ls ./*c) $(shell ls myexe/*c) $(shell ls parsing/*c) $(shell ls executor/*c) $(shell ls utils/*c)
OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CFLAGS		=   -I$(PATH_HEADER) -I$(PATH_IMAC)include -Wall -Wextra -Werror
RM			=	rm -rf
CC			=	gcc

all:			run_libft $(NAME) 

$(NAME):		${OBJ} $(HEADER) $(LIBFT)
				$(CC) ${OBJ} $(LIBFT) -lreadline -L $(PATH_IMAC)lib -o $(NAME)

run_libft:	
				@make -C $(PATH_LIB)

$(OBJ_DIR)/%.o:	%.c $(HEADER)
				mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) ${OBG}
				@make -C $(PATH_LIB) clean

fclean:			clean
				$(RM) $(NAME) $(OBJ_DIR)
				@make -C $(PATH_LIB) fclean

re:				fclean all

.PHONY: clean fclean re all