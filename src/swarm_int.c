/*
** swarm_int.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Thu May  1 01:04:05 2014 chalie_a
** Last update Thu May  1 01:52:03 2014 chalie_a
*/

#include <stdio.h>
#include "lem_in.h"

t_node		*get_right_node(t_node *tmp, int limit, int i)
{
  return (i < limit - 1 ? get_right_node(tmp->next, limit, ++i) : tmp);	// ~= while loop
}

t_room		*get_next_node(const t_node *root, t_room *actual,
			       const int row)
{
  t_node	*tmp;
 
  if (actual->curr_node == actual->nb_nodes)			//if we explored all the possibilities on this node
    return (actual->previous);					//we go back to the previous node
  tmp = get_right_node(root->next, ++actual->curr_node, 0);	// go to the last explored node + 1
  if (tmp->node == actual->previous)			//if the node we wanna go is the node we went from
    return (get_next_node(root, actual, row));		// (the nodes are double linked) restart from next node
  if (tmp->node->visited != row)			// if already NOT visited
    {
      tmp->node->previous = actual;			//we link the "previous" node
      tmp->node->visited = row;				// L-> to avoid useless loop (ex 1-5-1-2 --> 1-2)
    }
  return (tmp->node);
}

int		get_paths(t_room *tmp, const t_room *start,
			  const t_room *end, int max)
{
  static int	cpt = 0;

  ++cpt;
  while (tmp != start)
    if (!(tmp = get_next_node(tmp->links, tmp, cpt)))
      return (_ERROR("Error : Impossible map\n"));
    else if ((tmp == end && tmp->curr_node == tmp->nb_nodes) || --max <= 0)
      return (42);
   return (SUCCESS);
}

int		get_aco(t_room *root, t_room *start, t_room *end, int max)
{
  t_room	*tmp;
  int		result;

  result = get_paths(end, start, end, max);
  if (result == FAILURE)
    return (FAILURE);
  else if (result == 42)
    return (SUCCESS);
  remember_path(end, start);				// increment coeff on the visited rooms
  if (end->curr_node != end->nb_nodes)			// if there's still possibilities
    return (get_aco(root, start, end, max));		// continue get_paths
  reinit_all(root, root->next);
  return (SUCCESS);
}
