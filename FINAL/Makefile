## 
## Makefile for lem_in in /home/chalie_a/rendu/lem-in
## 
## Made by chalie_a
## Login   <chalie_a@epitech.eu>
## 
## Started on  Sun Jan  5 08:34:59 2014 chalie_a
##

CC	=	gcc -Ofast

NAME	=	lem_in

G_NAME	=	visu_hex

SRC	=		src/main.c		\

GRAPH	=	src/GRAPH/main_graph.c		\
		src/GRAPH/graph.c		\
		src/GRAPH/keyboard.c		\
		src/GRAPH/display.c		\
		src/GRAPH/graph_parsing.c	\
		src/GRAPH/func.c		\
		src/GRAPH/parsing_funcs.c

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
		src/PARSER/read_data.c		\
		src/PARSER/clean_all.c
LIB	=	lib/gnl.c			\
		lib/to_tab.c			\
		lib/strmatch.c			\
		lib/my_atoi.c			\
		lib/x_free.c			\
		lib/my_rand.c

OBJ	=	$(SRC:.c=.o) $(LIB:.c=.o) $(PARSER:.c=.o) $(MGR:.c=.o) $(ALGO:.c=.o)

G_OBJ	=	$(GRAPH:.c=.o) $(LIB:.c=.o) $(PARSER:.c=.o)

CFLAGS	=	-I./includes/ #-W -Wall -Wextra -ansi

RM	=	rm -fr

all	:	 $(NAME) $(G_NAME)

$(NAME)	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

$(G_NAME):	$(G_OBJ)
		$(CC) -o $(G_NAME) $(G_OBJ) -lSDL -lGL -lGLU -lglut -lm

clean	:
		$(RM) $(OBJ) $(G_OBJ)

fclean	:	clean
		$(RM) $(NAME) $(G_NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
