##
## Makefile for epur in /home/dong_n/rendu/epur
## 
## Made by dong_n
## Login   <dong_n@epitech.net>
## 
## Started on  Mon Mar 17 18:59:53 2014 dong_n
## Last update Mon Mar 17 23:56:07 2014 
##

CC	=	clang -O3 -g3

NAME	=	lem-in

SRC	=	src/main.c


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
