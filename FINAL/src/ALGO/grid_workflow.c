/*
** bruteforce.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Fri Apr 25 05:17:27 2014 chalie_a
** Last update Fri May  2 09:36:25 2014 chalie_a
*/

#include "lem_in.h"

typedef int             (*ptrft)(t_room *, t_room *, t_room *, int);

int			ant_colony_clustering(t_room *root, t_pos *pos)
{
  static const ptrft	exec_aco[2] = {get_aco, rev_get_aco};
  t_room		*beg_end[2];
  int			max;
  int			i;

  i = -1;
  beg_end[0] = pos->start;
  beg_end[1] = pos->end;
  max = pos->nb * pos->nb;
  pos->opt = 5 - pos->opt;
  while (++i < 2)
    {
      if (exec_aco[i](root, beg_end[i], beg_end[(i + 1) % 2], max) == FAILURE)
	return (FAILURE);
      reinit_all(root, root->next);
    }
  return (SUCCESS);
}
