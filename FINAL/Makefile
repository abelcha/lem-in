## 
## Makefile for lem_in in /home/chalie_a/rendu/lem-in
## 
## Made by chalie_a
## Login   <chalie_a@epitech.eu>
## 
## Started on  Sun Jan  5 08:34:59 2014 chalie_a
## Last update Fri May  2 09:17:12 2014 chalie_a
##

CC	=	gcc -Ofast

NAME	=	lem_in

SRC	=	src/clean_all.c			\
		src/main.c

ALGO	=	src/ALGO/grid_workflow.c	\
		src/ALGO/shared.c		\
		src/ALGO/rev_swarm_int.c	\
		src/ALGO/swarm_int.c

MGR	=	src/MIGRATION/migration_loop.c	\
		src/MIGRATION/recovery_mode.c	\
		src/MIGRATION/start_migration.c	\
		src/MIGRATION/ant_ia.c

PARSER	=	src/PARSER/add_elem.c		\
		src/PARSER/affectation.c	\
		src/PARSER/link_rooms.c		\
		src/PARSER/read_data.c

LIB	=	lib/gnl.c			\
		lib/to_tab.c			\
		lib/strmatch.c			\
		lib/my_atoi.c			\
		lib/x_free.c			\
		lib/my_rand.c

OBJ	=	$(SRC:.c=.o) $(LIB:.c=.o) $(PARSER:.c=.o) $(MGR:.c=.o) $(ALGO:.c=.o)

CFLAGS	=	-I./includes/ -W -Wall -Wextra -ansi

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
