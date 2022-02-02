NAME	=	libft.a
P_HEADER	= ../includes/
HEADER	=	libft.h

SRCS	=	$(shell ls ./*c)
OBG		=	$(SRCS:%.c=%.o)

CFLAGS	= -Wall -Wextra -Werror 
RM		= rm -rf
CC		= gcc


all:		$(NAME)		

$(NAME):	${OBG}	$(P_HEADER)$(HEADER)
			ar rc ${NAME} ${OBG}
			ranlib ${NAME}

%.o: 		%.c	
			$(CC) $(CFLAGS) -I$(P_HEADER) -c $< -o $@

clean:
			$(RM) ${OBG} ${BONUS_OBJ}

fclean: 	clean
			$(RM) ${NAME}

re:			fclean all

.PHONY: all clean fclean re bonus