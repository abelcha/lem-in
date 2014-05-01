
CC	=	clang -g3 -O3 #-Ofast

NAME	=	lem_in

SRC	=	src/clean_all.c			\
		src/main.c

ALGO	=	src/ALGO/grid_workflow.c	\
		src/ALGO/shared.c		\
		src/ALGO/ant_ia.c		\
		src/ALGO/rev_swarm_int.c	\
		src/ALGO/swarm_int.c

MGR	=	src/MIGRATION/migration_loop.c	\
		src/MIGRATION/recovery_mode.c	\
		src/MIGRATION/start_migration.c

PARSER	=	src/PARSER/link_rooms.c		\
		src/PARSER/add_elem.c		\

LIB	=	lib/my_strings.c		\
		lib/gnl.c			\
		lib/to_tab.c			\
		lib/strmatch.c			\
		lib/my_atoi.c			\
		lib/x_free.c			\
		lib/my_rand.c

OBJ	=	$(SRC:.c=.o) $(LIB:.c=.o) $(PARSER:.c=.o) $(MGR:.c=.o) $(ALGO:.c=.o)

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
