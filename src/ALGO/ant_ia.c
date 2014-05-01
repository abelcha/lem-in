/*
** start_migration.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sun Apr 27 07:27:25 2014 chalie_a
** Last update Thu May  1 13:33:47 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include "lem_in.h"

t_room		*get_random_node(t_node *tmp, t_ant *ant)
{
  t_room	*ret;

  ret = ant->location;
  while ((tmp = tmp->next) != ant->location->links)
    {
      if (tmp->node->visited == 0 && tmp->node != ant->location && 
	  tmp->node->coeff > 0 && tmp->node != ant->previous)
	{
	  ret = tmp->node;
	  if (my_rand(0, 10) == 3)
	    break;
	}
    }
  return (ret);
}

int		is_legit(t_room *curr, t_room *ret, t_ant *ant)
{
  if ((ret == ant->location || curr->coeff > ret->coeff)
      && curr->visited == 0
      && curr != ant->location
      &&  curr->coeff > 0
      && curr != ant->previous)
    return (TRUE);
  return (FALSE);
}

t_room		*find_location(t_pos *pos, t_ant *ant, t_ia *ia)
{
  t_node	*tmp;
  t_room	*ret;

  ret = ant->location;
  tmp = ant->location->links;
  while ((tmp = tmp->next) != ant->location->links)
    if (tmp->node == pos->end &&
	(ant->location != pos->start || pos->end->visited == 0))
      return (tmp->node);
    else if (is_legit(tmp->node, ret, ant) == TRUE)
      ret = tmp->node;
  return (ret);
}

t_room		*get_next_location(t_pos *pos, t_ant *ant, t_ia *ia)
{
  t_node	*tmp;
  t_room	*ret;

  ret = ant->location;
  tmp = ant->location->links;
  ret = ia->recovery_mode ? get_random_node(tmp, ant) :
    find_location(pos, ant, ia);
  ant->previous = ant->location;
  ant->location->visited = 0;
  ++(ret->visited);
  return (ret);
}
