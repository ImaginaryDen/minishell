NAME		=	minishell

LIBFT		=	./libft_gnl/libft_gnl.a
PATH_HEADER =	./includes/
PATH_LIB 	=	./libft_gnl/
HEADER  	=	./includes/minishell.h 

OBJ_DIR		=	./objects
SRC			=	$(shell ls ./*c) $(shell ls myexe/*c) $(shell ls parsing/*c)
OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o)) /usr/lib/x86_64-linux-gnu/libreadline.so.8

CFLAGS		=   -I$(PATH_HEADER) #-Wall -Wextra -Werror 
RM			=	rm -rf
CC			=	gcc

all:			run_libft $(NAME) 

$(NAME):		${OBJ} $(HEADER) $(LIBFT)
				$(CC) $(CFLAGS) ${OBJ} $(LIBFT) -o $(NAME)

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