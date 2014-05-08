/*
** swarm_int.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Thu May  1 01:04:05 2014 chalie_a
** Last update Fri May  2 09:53:15 2014 chalie_a
*/

#include <stdio.h>
#include "lem_in.h"

static t_node		*get_right_node(t_node *tmp, int limit, int i)
{
  return (i < limit - 1 ? get_right_node(tmp->next, limit, ++i) : tmp);
}

static t_room		*get_next_node(const t_node *root, t_room *actual,
				       const int row)
{
  t_node		*tmp;

  if (actual->curr_node == actual->nb_nodes)
    return (actual->previous);
  tmp = get_right_node(root->next, ++actual->curr_node, 0);
  if (tmp->node == actual->previous)
    return (get_next_node(root, actual, row));
  if (tmp->node->visited != row)
    {
      tmp->node->previous = actual;
      tmp->node->visited = row;
    }
  return (tmp->node);
}

static int		get_paths(t_room *tmp, const t_room *start,
				  const t_room *end, int max)
{
  static int		cpt = 0;

  ++cpt;
  while (tmp != start)
    if (!(tmp = get_next_node(tmp->links, tmp, cpt)))
      return (_ERROR(IMP_MAP));
    else if ((tmp == end && tmp->curr_node == tmp->nb_nodes) || --max <= 0)
      return (42);
   return (SUCCESS);
}

int			get_aco(t_room *root, t_room *start,
				t_room *end, int max)
{
  int			result;

  result = get_paths(end, start, end, max);
  if (result == FAILURE)
    return (FAILURE);
  else if (result == 42)
    return (SUCCESS);
  remember_path(end, start);
  if (end->curr_node != end->nb_nodes)
    return (get_aco(root, start, end, max));
  reinit_all(root, root->next);
  return (SUCCESS);
}
