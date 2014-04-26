/*
** main.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Wed Apr 16 22:50:26 2014 chalie_a
** Last update Sat Apr 26 22:09:30 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "lem-in.h"

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
  return (link_node(r1, r2));
}

char			**is_affectation(char *str)
{
  char			**stock;

  stock = to_tab(str, 0, '-');
  if (!stock || nb_param(stock, 0) != 2)
    return (NULL);
  return (stock);
}

void			link_rooms(t_room *elem, t_room *newelem)
{
  newelem->prev = elem->prev;
  newelem->next = elem;
  elem->prev->next = newelem;
  elem->prev = newelem;
}

void			get_start_and_end(t_pos *pos, int type, t_room *newelem)
{
 if (type == START)
    pos->start = newelem;
  if (type == END)
    pos->end = newelem; 
}
t_node			*init_links()
{
  t_node		*root;

  if (!(root = malloc(sizeof(t_node))))
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}
int			add_elem(t_room *elem, char *str, int type, t_pos *pos)
{
  t_room		*newelem;
  char			**stock;

  if ((stock = is_affectation(str)))
    return (add_affectation(stock, elem, newelem));
  if (!(newelem = malloc(sizeof(t_room))))
    return (FAILURE);
  newelem->nb_nodes = 0;
  newelem->curr_node = 0;
  newelem->visited = 0;
  newelem->coeff = 0;
  if (!(newelem->links = init_links()))
    return (FAILURE);
  get_start_and_end(pos, type, newelem);
  link_rooms(elem, newelem);
  return (add_declaration(newelem, str));
}
