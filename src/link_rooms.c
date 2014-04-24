/*
** link_rooms.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Thu Apr 24 10:22:18 2014 chalie_a
** Last update Thu Apr 24 10:34:52 2014 chalie_a
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
  return (SUCCESS);
}


int		link_room(t_room *r1, t_room *r2)
{
  printf("%s is linked with %s\n", r1->name, r2->name);
  if (create_link(r1->links, r2) == FAILURE)
    return (FAILURE);
  if (create_link(r2->links, r1) == FAILURE)
    return (FAILURE);
  return (SUCCESS);
}
