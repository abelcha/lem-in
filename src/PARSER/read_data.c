/*
** main.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Wed Apr 16 22:50:26 2014 chalie_a
** Last update Fri May  2 01:11:18 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "lem_in.h"

int			get_sharp_value(char *str)
{
  static char	*tab[2] = {"#start", "#end"};
  int			i;

  i = 2;
  while (--i >= 0 && !speed_cmp(tab[i], str));
  return (i);
}

int			get_line_type(char *str)
{
  return (str[1] == '#' ? get_sharp_value(&str[1]) : COMMENT);
}

void		get_start_and_end(t_pos *pos, int type, t_room *newelem)
{
  if (type == START)
    pos->start = newelem;
  if (type == END)
    pos->end = newelem; 
}

int		read_data(t_room *root, t_pos *pos, int prev_type)
{

  int		type;
  char		*str;

   if (!(str = gnl(0)))
     return (SUCCESS);
   printf("%s\n", str);
   type = (*str == '#' ? get_line_type(str) : DATA); 
   if (type == DATA && add_elem(root, str) == FAILURE)
     return (FAILURE);
   if (prev_type != DATA)
     get_start_and_end(pos, prev_type, root->prev);
   x_free(str);
   return (read_data(root, pos, type));
}
