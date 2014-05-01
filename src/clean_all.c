/*
** clean_all.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Mon Apr 28 05:52:54 2014 chalie_a
** Last update Mon Apr 28 15:18:29 2014 chalie_a
*/

#include <stdlib.h>
#include "lem_in.h"

static int	x_free(void *ptr)
{
  if (ptr)
    {
      free(ptr);
      ptr = NULL;
    }
  return (42);
}

static void	free_nodes(t_node *root)
{
  t_node	*tmp;
  t_node	*save;

  if (!root)
    return ;
  save = root->prev;
  tmp = root;
  while ((tmp = tmp->next) != root)
    x_free(tmp->prev);
  x_free(save);
}

static void	free_ants(t_ant *root)
{
  t_ant	*tmp;
  t_ant	*save;

  if (!root)
    return ;
  save = root->prev;
  tmp = root;
  while ((tmp = tmp->next) != root)
    x_free(tmp->prev);
  x_free(save);
}


static void	free_rooms(t_room *root)
{
  t_room	*tmp;
  t_room	*save;

  if (!root)
    return ;
  save = root->prev;
  tmp = root;
  while ((tmp = tmp->next) != root)
    {
      x_free(tmp->prev->name);
      free_nodes(tmp->prev->links);
      x_free(tmp->prev);
    }
  x_free(save->name);
  free_nodes(save->links); 
  x_free(save);
}

void		clean_all(t_room *root, t_pos *pos, t_ant *ant)
{
  free_ants(ant);
  free(pos);
  free_rooms(root);
}
