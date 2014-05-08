/*
** start_migration.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sun Apr 27 07:27:25 2014 chalie_a
** Last update Sun May  4 23:31:51 2014 beau_v
*/

#include "lem_in.h"

static int		is_legit(const t_room *curr,
				 const t_ant *ant)
{
  if (curr->visited == 0
      && curr != ant->location
      && curr->coeff > 0
      && curr != ant->previous)
    return (TRUE);
  return (FALSE);
}

static t_room		*get_random_node(t_node *tmp,
					 const t_ant *ant)
{
  t_room		*ret;

  ret = ant->location;
  while ((tmp = tmp->next) != ant->location->links)
    if (is_legit(tmp->node, ant) == TRUE && (ret = tmp->node))
      if (my_rand(0, 10) == 3)
	return (tmp->node);
  return (ret);
}

static t_room		*find_location(const t_pos *pos, const t_ant *ant)
{
  t_node		*tmp;
  t_room		*ret;

  ret = ant->location;
  tmp = ant->location->links;
  while ((tmp = tmp->next) != ant->location->links)
    if (tmp->node == pos->end)
      return (tmp->node);
    else if (is_legit(tmp->node, ant) == TRUE &&
	     (ret == ant->location || tmp->node->coeff >= ret->coeff))
      ret = tmp->node;
  return (ret);
}

t_room			*get_next_location(t_pos *pos, t_ant *ant, t_ia *ia)
{
  t_node		*tmp;
  t_room		*ret;

  ret = ant->location;
  tmp = ant->location->links;
  ret = ia->recovery_mode ? get_random_node(tmp, ant) :
    find_location(pos, ant);
  ant->previous = ant->location;
  ant->location->visited = 0;
  ++(ret->visited);
  return (ret);
}
