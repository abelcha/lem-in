
CC	=	clang -g3 -O3 #-Ofast

NAME	=	lem_in

SRC	=	src/main.c			\
		src/link_rooms.c	\
		src/add_elem.c		\
		src/ugly_display.c	\
		src/bruteforce.c	\
		src/start_migration.c\
		src/clean_all.c		\
		src/rev_br.c

LIB	=	lib/my_strings.c	\
		lib/gnl.c			\
		lib/to_tab.c		\
		lib/strmatch.c		\
		lib/my_atoi.c		\
		lib/my_rand.c
OBJ	=	$(SRC:.c=.o) $(LIB:.c=.o)

CFLAGS	=	-I./includes/	#-W -Wall -Wextra -pedantic

RM	=	rm -fr

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

clean	:
		$(RM) $(OBJ)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
