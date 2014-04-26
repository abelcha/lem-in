/*
** main.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Wed Apr 16 22:50:26 2014 chalie_a
** Last update Sat Apr 26 20:53:24 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "lem-in.h"

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
  if (str[0] == '#')
    return (str[1] == '#' ? get_sharp_value(&str[1]) : COMMENT);
  return (DATA);
}

t_room		*init_root()
{
  t_room	*root;

  if (!(root = malloc(sizeof(t_room))))
    return (NULL);
  root->links = NULL;
  root->prev = root;
  root->next = root;
  return (root);
}

int		read_data(t_room *root, t_pos *pos, int prev_type)
{

  int		type;
   char		*str;

   if (!(str = gnl(0)))
     return (SUCCESS);
   if ((type = get_line_type(str)) == FAILURE)
     return (FAILURE);
   if (type == DATA && add_elem(root, str, prev_type, pos) == FAILURE)
     return (FAILURE);
   return (read_data(root, pos, type));
}

int		main()
{  t_room	*root;
  t_pos		*pos;

  pos = malloc(sizeof(t_pos));
  pos->start = NULL;
  pos->end = NULL; 
  pos->nb = atoi(gnl(0));
  root = init_root();
  read_data(root, pos, DATA);
  //   display_room(root, pos);
   random_findpath(root, pos);
}
