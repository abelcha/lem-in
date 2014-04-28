/*
** start_migration.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sun Apr 27 07:27:25 2014 chalie_a
** Last update Mon Apr 28 06:44:24 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include "lem-in.h"

int			add_mouse(t_mouse *elem, t_pos *pos, int i)
{
  t_mouse		*newelem;

  if (!(newelem = malloc(sizeof(t_mouse))))
    return (FAILURE);
  newelem->nb = i;
  newelem->location = pos->start;
  newelem->previous = pos->start;
  newelem->prev = elem->prev;
  newelem->next = elem;
  elem->prev->next = newelem;
  elem->prev = newelem;
  return (SUCCESS);
}


t_mouse			*init_mouse()
{
  t_mouse		*root;

  if (!(root = malloc(sizeof(t_mouse))))
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}

t_room		*get_next_location(t_node *root, t_room *actual, t_pos *pos, t_mouse *mouse)
{
  t_node	*tmp;
  t_room	*ret;

  ret = actual;
  tmp = root;
  while ((tmp = tmp->next) != root)
    {
      if (tmp->node == pos->end &&
	  (actual != pos->start || pos->end->visited == 0))
	{
	  ret = tmp->node;
	  break ;
	}
      if (tmp->node->visited == 0 && tmp->node != actual &&
	  tmp->node->coeff > 0 && tmp->node != mouse->previous)
	if (ret == actual || tmp->node->coeff > ret->coeff)
	  ret = tmp->node;
    }
  mouse->previous = actual;
  actual->visited = 0;
  ++(ret->visited);
  return (ret);
}

int		delete_node(t_mouse *root, t_mouse *tmp, t_pos *pos)
{
  t_mouse	*save;

  save = tmp->next;
  tmp->prev->next = tmp->next;
  tmp->next->prev = tmp->prev;
  free(tmp);
  return (action_mouse(root, save, pos));
}

int		action_mouse(t_mouse *root, t_mouse *tmp, t_pos *pos)
{
  if (tmp == root)
    return (SUCCESS);
  if (tmp->location == pos->end)
    return (delete_node(root, tmp, pos));
  tmp->location = get_next_location(tmp->location->links, tmp->location, pos, tmp);
  if (tmp->location != tmp->previous)
    printf("P%d-%s ", tmp->nb, tmp->location->name);
  return (action_mouse(root, tmp->next, pos));
}

int		start_migration(t_room *root, t_pos *pos)
{
  t_mouse	*mouse;
  int		i;
  int		j = -1;
  int		dead;

  dead = 0;
  i = -1;
  if (!(mouse = init_mouse()))
    return (FAILURE);
  while (i++ < pos->nb)
    add_mouse(mouse, pos, i);
    while (dead < pos->nb)
    {
      action_mouse(mouse, mouse->next,  pos);
      dead += pos->end->visited;
      printf("\n");
      ++j;
      pos->end->visited = 0;
      //usleep(100000);
    }
    clean_all(root, pos, mouse);
  return (SUCCESS);
}
