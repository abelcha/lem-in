/*
** bruteforce.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Fri Apr 25 05:17:27 2014 chalie_a
** Last update Sun Apr 27 07:24:08 2014 chalie_a
*/

#include <stdio.h>
#include "lem-in.h"


t_node		*r_get_right_node(t_node *tmp, int limit, int i)
{
   return (i < limit ? r_get_right_node(tmp->next, limit, ++i) : tmp);
}

t_room		*r_get_next_node(t_node *root, t_room *actual, int row)
{
  t_node	*tmp;
 
  if (actual->curr_node == actual->nb_nodes)
    return (actual->previous);
  tmp = r_get_right_node(root->next, actual->curr_node, 0);	// go to the last explored node + 1
  ++(actual->curr_node);
  if (tmp->node == actual->previous)			//if the node we wanna go is the node we went from
    return (r_get_next_node(root, actual, row));	// (the nodes are double linked) restart from next node
  if (tmp->node->visited != row)			// if already NOT visited
    {
      tmp->node->previous = actual;			//we link the "previous" node
      tmp->node->visited = row;				// L-> to avoid useless loop (ex 1-5-1-2 --> 1-2)
    }
  return (tmp->node);
}

void		r_remember_path(t_room *start, t_room *end)
{
  int		i = 1;

  while (end != start)
    {
      end->coeff += i;
      ++i;
      end = end->previous;
    }
}

int		r_backtracking(t_room *tmp, t_room *start, t_room *end, int i)
{
   while (tmp != start)
     {
       tmp = r_get_next_node(tmp->links, tmp, i);
       if (!tmp)				//tmp == NIL if we explored all possibilities on the root node
	 {
	   printf("Impossible map\n");
	   return (FAILURE);
	 }
       if (tmp == end && tmp->curr_node == tmp->nb_nodes)	//No more possibilities but there's paths
	 return (42);
    }
   return (SUCCESS);
}


int		r_get_coeff(t_room *root, t_room *start, t_room *end, int i)
{
  t_room	*tmp;
  int		result;

  printf("tamerelagrossechienne\n");
  result = r_backtracking(end, start, end, i);
  if (result == FAILURE)
    return (FAILURE);
  else if (result == 42)
    return (SUCCESS);
  r_remember_path(end, start);
  ++i;
  printf("FIND_PATH\n");
  if (end->curr_node != end->nb_nodes)			// if there's still possibilities
    return (r_get_coeff(root, start, end, ++i));		// continue r_backtracking
   return (SUCCESS);
}
