NAME		=	minishell

LIBFT		=	./libft/libft.a
PATH_HEADER =	./includes/
PATH_LIB 	=	./libft/
HEADER  	=	./includes/minishell.h 

OBJ_DIR		=	./objects
SRC_GNL 	=	$(shell ls ./gnl/*.c)
SRC			=	$(SRC_GNL) main.c
OBJ			=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CFLAGS		=	-I$(PATH_HEADER) #-Wall -Wextra -Werror 
RM			=	rm -rf
CC			=	gcc

all:			run_libft $(NAME) 

$(NAME):		${OBJ} $(HEADER) $(LIBFT)
				$(CC) $(CFLAGS) ${OBJ} $(LIBFT) -o $(NAME)

bonus:		
				@make -C ./bonus

run_libft:	
				@make -C $(PATH_LIB)

$(OBJ_DIR)/%.o:	%.c $(HEADER)
				mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) ${OBG} ${OBG_BONUS}
				@make -C $(PATH_LIB) clean
				@make -C ./bonus clean

fclean:			clean
				$(RM) $(NAME) $(NAME_BONUS)
				@make -C $(PATH_LIB) fclean
				@make -C ./bonus fclean

re:				fclean all

.PHONY: clean fclean re all bonus