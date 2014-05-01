/*
** test.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Thu May  1 12:26:07 2014 chalie_a
** Last update Thu May  1 12:34:26 2014 chalie_a
*/

#include <stdio.h>

int		fontion(char *str);

void		sigsev(char *str)
{
  int		i;

  i = 1;
  fonction(i);
}

int		fonction(char *str)
{
  printf("str = %s\n", str);
}

int		main()
{
  char		*str = "salut";

  sigsev(str);
}
