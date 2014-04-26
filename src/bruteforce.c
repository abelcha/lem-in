/*
** bruteforce.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Fri Apr 25 05:17:27 2014 chalie_a
** Last update Sun Apr 27 00:36:57 2014 chalie_a
*/

#include <stdio.h>
#include "lem-in.h"


t_room		*get_next_node(t_node *root, t_room *actual, int row)
{
  t_node	*tmp;
  int		i;
  t_room	*ret;

  i = -1;
  if (actual->curr_node == actual->nb_nodes)		//if we explored all possibilities on this node
    {
      printf("yeah we go back\n");			//then we go to the previous node (backtracking)
      return (actual->previous);
    }

  tmp = root->next;
    while (++i < actual->curr_node)
      tmp = tmp->next;
    ++(actual->curr_node);
    if (tmp->node == actual->previous)			//if the node we wanna go is the node we went from
      return (get_next_node(root, actual, row));	// (the nodes are double linked) restart from next node
 
    //  printf("%d == %d\n", tmp->node->visited, row);
    if (tmp->node->visited != row)			// if already NOT visited
      {
	tmp->node->previous = actual;			//we link the "previous" node
	tmp->node->visited = row;
      }
  return (tmp->node);
}

int		remember_path(t_room *end, t_room *tmp)
{
  int		i = 1;

  ++(tmp->coeff);
  while (tmp != end)
    {
      // printf(" %s\n", tmp->name);
       tmp = tmp->previous;
       tmp->coeff += i;
       ++i;
       // sleep(1);
    }
  //  printf(" %s\n", tmp->name);
  return (0);
}

int		random_findpath(t_room *root, t_pos *pos)
{
  t_room	*tmp;
   static int	i = 1;
   if (i == 1)
     printf("parsing done\n");
   tmp = pos->end;
   while (tmp != pos->start)
     { 
  
       tmp = get_next_node(tmp->links, tmp, i);
       if (!tmp)				//tmp == NIL if we explored all possibilities on the root node
	 {
	   printf("Impossible map\n");
	   return (FAILURE);
	 }
       if (tmp == pos->end && tmp->curr_node == tmp->nb_nodes)
	 break ;
       //usleep(4000);
       //printf("actual room = %s\n", tmp->name);
     }
   //printf("FIND PATH %d\n", i);
   remember_path(pos->end, tmp);
   //  printf("%s\n", pos->start->name);
   ++i;

   if (pos->end->curr_node != pos->end->nb_nodes)   // if there's still possibilities
     return (random_findpath(root, pos));		// continue backtracking
   //display_room(root, pos);
   return (SUCCESS);
}
