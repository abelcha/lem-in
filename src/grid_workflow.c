/*
** bruteforce.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Fri Apr 25 05:17:27 2014 chalie_a
** Last update Thu May  1 02:21:19 2014 chalie_a
*/

#include "lem_in.h"

int		ant_colony_clustering(t_room *root, t_pos *pos)
{
  int		max;

  max = pos->nb * pos->nb;
  if (get_aco(root, pos->start, pos->end, max) == FAILURE)
    return (FAILURE);
  if (pos->opt <= 1 && rev_get_aco(root, pos->end, pos->start, max) == FAILURE)
    return (FAILURE);
  if (pos->opt <= 2 && get_aco(root, pos->start, pos->end, max) == FAILURE)
    return (FAILURE);
  if (pos->opt <= 3 && rev_get_aco(root, pos->end, pos->start, max) == FAILURE)
    return (FAILURE);
  reinit_all(root, root->next);
  return (SUCCESS);
}
