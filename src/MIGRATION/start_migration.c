/*
** start_migration.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sun Apr 27 07:27:25 2014 chalie_a
** Last update Thu May  1 14:46:06 2014 chalie_a
*/

#include <stdlib.h>
#include "lem_in.h"

static int		add_ant(t_ant *elem, t_pos *pos,
				const int i)
{
  t_ant			*newelem;

  if (!(newelem = calloc(1, sizeof(t_ant))))
    return (FAILURE);
  newelem->nb = i + 1;
  newelem->location = pos->start;
  newelem->previous = pos->start;
  newelem->prev = elem->prev;
  newelem->next = elem;
  elem->prev->next = newelem;
  elem->prev = newelem;
  return (SUCCESS);
}


static t_ant		*init_ant()
{
  t_ant			*root;

  if (!(root = calloc(1, sizeof(t_ant))))
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}

int			start_migration(t_room *root, t_pos *pos)
{
  t_ant			*ant;
  t_ia			*ia;

  ant = init_ant();
  ia = calloc(1, sizeof(t_ia));
  if (!ant || !ia)
    return (FAILURE);
  while (ia->tt_ant++ < pos->nb + 1)
    add_ant(ant, pos, ia->tt_ant);
  ant->nb = pos->nb * ia->tt_ant;
  migration_loop(pos, ia, ant);
  clean_all(root, pos, ant);
  return (SUCCESS);
}
