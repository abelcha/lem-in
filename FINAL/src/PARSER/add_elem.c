/*
** main.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Wed Apr 16 22:50:26 2014 chalie_a
** Last update Sun May  4 17:36:07 2014 chalie_a
*/

#include <stdlib.h>
#include "lem_in.h"

static int			nb_param(char **stock, int i)
{
  return (stock[i] ? nb_param(stock, ++i) : i);
}

static int			add_declaration(t_room *room, char *str)
{
  char				**stock;

  stock = to_tab(str, 0, ' ');
   if (!stock || nb_param(stock, 0) != 3)
    return (FAILURE);
  room->name = stock[0];
  room->x = my_atoi(stock[1]);
  room->y = my_atoi(stock[2]);
  x_free(stock[1]);
  x_free(stock[2]);
  x_free(stock);
  return (SUCCESS);
}

static void			link_rooms(t_room *elem, t_room *newelem)
{
  newelem->prev = elem->prev;
  newelem->next = elem;
  elem->prev->next = newelem;
  elem->prev = newelem;
}

static t_node			*init_links()
{
  t_node			*root;

  if (!(root = calloc(1, sizeof(t_node))))
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}
int				add_elem(t_room *elem, char *str, t_pos *pos)
{
  t_room			*newelem;
  char				**stock;

  if ((stock = is_affectation(str)))
    return (add_affectation(stock, elem));
  ++(pos->nb_room);
  if (!(newelem = calloc(1, sizeof(t_room))))
    return (FAILURE);
  if (!(newelem->links = init_links()))
    return (FAILURE);
  link_rooms(elem, newelem);
  return (add_declaration(newelem, str));
}
