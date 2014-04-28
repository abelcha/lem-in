##
## Makefile for epur in /home/dong_n/rendu/epur
## 
## Made by dong_n
## Login   <dong_n@epitech.net>
## 
## Started on  Mon Mar 17 18:59:53 2014 dong_n
## Last update Thu Apr 24 22:38:14 2014 chalie_a
##

CC	=	clang -g3 -O3 #-Ofast

NAME	=	moulinette

SRC	=	src/main.c			\
		src/link_rooms.c	\
		src/add_elem.c		\
		src/ugly_display.c	\
		src/bruteforce.c	\
		src/start_migration.c\
		src/rev_br.c

LIB	=	lib/my_strings.c	\
		lib/gnl.c			\
		lib/to_tab.c		\
		lib/strmatch.c

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
