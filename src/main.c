/*
** main.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Wed Apr 16 22:50:26 2014 chalie_a
** Last update Thu Apr 24 10:07:34 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "lem-in.h"

int			get_sharp_value(char *str)
{
  static const char	*tab[2] = {"#start", "#end"};
  int			i;

  i = 2;
  while (--i >= 0 && !speed_cmp(tab[i], str));
  return (i);
}

int			get_line_type(char *str)
{
  if (str[0] == '#')
    return (str[1] == '#' ? get_sharp_value(&str[1]) : COMMENT);
  return (42);
}

int			nb_param(char **stock, int i)
{
  return (stock[i] ? nb_param(stock, ++i) : i);
}


int			add_declaration(t_room *room, char *str)
{
  char			**stock;

  stock = to_tab(str, 0, ' ');
   if (!stock || nb_param(stock, 0) != 3)
    return (FAILURE);
  room->name = stock[0];
  room->x = atoi(stock[1]);
  room->y = atoi(stock[2]);
  printf("name = %s x = %d y = %d\n", room->name, room->x, room->y);
  return (SUCCESS);
}

int			link_room(t_room *tmp, t_room *new)
{
  printf("IT MATCH\n");
  return (SUCCESS);
}

t_room			*find_room(char *str, t_room *root)
{
  t_room		*tmp;

  tmp = root;
  while ((tmp = tmp->next) != root)
    {
      if (!speed_cmp(str, tmp->name))
	return (tmp);
    }
  printf("error : no such room %s\n", str);
  return (NULL);
}

int			add_affectation(char **stock, t_room *root, t_room *new)
{
  t_room		*r1;
  t_room		*r2;

  if (!stock || nb_param(stock, 0) != 2)
    return (FAILURE);
  if (!(r1 = find_room(stock[0], root)))
    return (FAILURE);
  if (!(r2 = find_room(stock[1], root)))
    return (FAILURE);
  printf("%s is linked with %s\n", r1->name, r2->name);
  return (SUCCESS);
}


char			**is_affectation(char *str)
{
  char			**stock;

  stock = to_tab(str, 0, '-');
  if (!stock || nb_param(stock, 0) != 2)
    return (NULL);
  return (stock);
}

int			add_elem(t_room *elem, char *str, int type, t_pos *pos)
{
  t_room		*newelem;
  char			**stock;

  if ((stock = is_affectation(str)))
    return (add_affectation(stock, elem, newelem));

  if (!(newelem = malloc(sizeof(t_room))))
    return (FAILURE);

  if (type == START)
    pos->start = newelem;
  if (type == END)
    pos->end = newelem;
  newelem->prev = elem->prev;
  newelem->next = elem;
  elem->prev->next = newelem;
  elem->prev = newelem;
  return (add_declaration(newelem, str));
}

t_room		*init_root()
{
  t_room	*root;

  if (!(root = malloc(sizeof(t_room))))
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}

int		main()
{
  int		type;
  int		prev_type;
  char		*str;
  t_room	*root;
  t_pos		*pos;

  prev_type = 42;
  pos = malloc(sizeof(t_pos));
  root = init_root(); 
  while ((str = gnl(0)))
    {
      if ((type = get_line_type(str)) == FAILURE)
	return (FAILURE);
      if (type == 42 && add_elem(root, str, prev_type, pos) == FAILURE)
	return (FAILURE);
      prev_type = type;
   }
}
