/*
** link_rooms.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Thu Apr 24 10:22:18 2014 chalie_a
** Last update Fri Apr 25 07:05:11 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include "lem-in.h"

int			create_link(t_node *elem, t_room *room)
{
  t_node		*newelem;

  if (!(newelem = malloc(sizeof(t_node))))
    return (FAILURE);
  newelem->node = room;
  newelem->prev = elem->prev;
  newelem->next = elem;
  elem->prev->next = newelem;
  elem->prev = newelem;
  ++(room->nb_nodes);
  return (SUCCESS);
}

int		existing_node(t_room *r1, t_room *r2)
{
  t_node	*tmp;

  tmp = r1->links;
  while ((tmp = tmp->next) != r1->links)
    if (tmp->node == r2)
      return (TRUE);
  return (FALSE);
}

int		link_node(t_room *r1, t_room *r2)
{
  if (r1 != r2 && existing_node(r1, r2) == FALSE)
    {
      if (create_link(r1->links, r2) == FAILURE)
	return (FAILURE);
      else if (create_link(r2->links, r1) == FAILURE)
	return (FAILURE);
    }
  return (SUCCESS);
}
