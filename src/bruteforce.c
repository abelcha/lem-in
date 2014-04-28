/*
** bruteforce.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Fri Apr 25 05:17:27 2014 chalie_a
** Last update Mon Apr 28 01:59:30 2014 chalie_a
*/

#include <stdio.h>
#include "lem-in.h"


t_node		*get_right_node(t_node *tmp, int limit, int i)
{
  return (i < limit ? get_right_node(tmp->next, limit, ++i) : tmp);	// ~= while loop
}

t_room		*get_next_node(t_node *root, t_room *actual, int row)
{
  t_node	*tmp;
 
  if (actual->curr_node == actual->nb_nodes)			//if we explored all the possibilities on this node
    return (actual->previous);					//we go back to the previous node
  tmp = get_right_node(root->next, actual->curr_node, 0);	// go to the last explored node + 1
  ++(actual->curr_node);
  if (tmp->node == actual->previous)			//if the node we wanna go is the node we went from
    return (get_next_node(root, actual, row));		// (the nodes are double linked) restart from next node
  if (tmp->node->visited != row)			// if already NOT visited
    {
      tmp->node->previous = actual;			//we link the "previous" node
      tmp->node->visited = row;				// L-> to avoid useless loop (ex 1-5-1-2 --> 1-2)
    }
  return (tmp->node);
}

void		remember_path(t_room *start, t_room *end)
{
  int		i = 1;
  t_room	*save;

  while (end && end != start)
    {
      end->coeff += i++;				// the closest node to the end have a bigger coeff
      save = end;					// copy the current ptr (not double linked)
      end = end->previous;
      save->previous = NULL;				//set the previous pointer to NULL (avoid infinite loop)
    }
}

int		backtracking(t_room *tmp, t_room *start, t_room *end, int i)
{
   while (tmp != start)
     {
       tmp = get_next_node(tmp->links, tmp, i);
       if (!tmp)				//tmp == NIL if we explored all possibilities on the root node
	 {
	   printf("Impossible map\n");
	   return (FAILURE);
	 }
       // if (tmp == end && tmp->curr_node == tmp->nb_nodes)	//No more possibilities but there's paths
	    // return (42);
     }
   return (SUCCESS);
}


int		get_coeff(t_room *root, t_room *start, t_room *end, int i)
{
  t_room	*tmp;
  int		result;

  result = backtracking(end, start, end, i);
  if (result == FAILURE)
    return (FAILURE);
  else if (result == 42)
    return (SUCCESS);
  remember_path(end, start);				// increment coeff on the visited rooms
  ++i;
  if (end->curr_node != end->nb_nodes)			// if there's still possibilities
    return (get_coeff(root, start, end, ++i));		// continue backtracking
  return (SUCCESS);
}

int		reinit_all(t_room *root, t_room *tmp)
{
  tmp->visited = 0;
  tmp->curr_node = 0;
  return (tmp != root ? reinit_all(root, tmp->next) : 0);
}

int		random_findpath(t_room *root, t_pos *pos)
{
  int		i;

    i = 0;
    if (get_coeff(root, pos->end, pos->start, ++i) == FAILURE)
      return (FAILURE);
    reinit_all(root, root->next);
    i = 0;
    if (get_coeff(root, pos->start, pos->end, ++i) == FAILURE)
      return (FAILURE);
    reinit_all(root, root->next); 
    //    display_room(root, pos);
    start_migration(root, pos);   
  return (SUCCESS);
}
