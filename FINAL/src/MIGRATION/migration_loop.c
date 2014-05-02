/*
** start_migration.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sun Apr 27 07:27:25 2014 chalie_a
** Last update Fri May  2 09:32:49 2014 chalie_a
*/

#include <stdio.h>
#include "lem_in.h"

static int		action_ant(t_ant *root, t_ant *tmp,
				   t_pos *pos, t_ia *ia)
{
  if (tmp == root)
    return (ia->curr_loop ? printf("\n") : SUCCESS);
  if (tmp->location == pos->end)
    return (delete_node(root, tmp, pos, ia));
  tmp->location = get_next_location(pos, tmp, ia);
  if (ia->curr_loop == 0)
    ia->recovery_mode = check_recovery(tmp);
  if (tmp->location != tmp->previous)
    printf(++(ia->curr_loop) == 1 ? "P%d-%s" : " P%d-%s",
	   tmp->nb, tmp->location->name);
  return (action_ant(root, tmp->next, pos, ia));
}

int			delete_node(t_ant *root, t_ant *tmp,
				    t_pos *pos, t_ia *ia)
{
  t_ant			*save;

  save = tmp->next;
  tmp->prev->next = tmp->next;
  tmp->next->prev = tmp->prev;
  x_free(tmp);
  return (action_ant(root, save, pos, ia));
}

int			migration_loop(t_pos *pos, t_ia *ia,
				       t_ant *ant)
{
  while (ia->arrived < pos->nb + 1 && ++(ia->tt_loop) < ant->nb)
    {
      pos->end->visited = 0;
      ia->curr_loop = 0;
      if (action_ant(ant, ant->next, pos, ia) == FAILURE)
	return (FAILURE);
      ia->arrived += pos->end->visited;
    }
  return (SUCCESS);
}
