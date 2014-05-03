/*
** start_migration.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sun Apr 27 07:27:25 2014 chalie_a
** Last update Thu May  1 13:31:18 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include "lem_in.h"

#define SAVE_BUFF	16

int			add_ant(t_ant *elem, t_pos *pos, int i)
{
  t_ant		*newelem;

  if (!(newelem = calloc(1, sizeof(t_ant))))
    return (FAILURE);
  newelem->nb = i + 1;
  newelem->location = pos->start;
  newelem->previous = pos->start;
  newelem->prev = elem->prev;
  newelem->next = elem;
  elem->prev->next = newelem;
  elem->prev = newelem;
  return (SUCCESS);
}


t_ant			*init_ant()
{
  t_ant		*root;

  if (!(root = calloc(1, sizeof(t_ant))))
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}

int		delete_node(t_ant *root, t_ant *tmp, t_pos *pos, t_ia *ia)
{
  t_ant		*save;

  save = tmp->next;
  tmp->prev->next = tmp->next;
  tmp->next->prev = tmp->prev;
  x_free(tmp);
  return (action_ant(root, save, pos, ia));
}

int		watchdog(int *s_nb, char **s_name, t_ant *ant, int cpt)
{
  int		i;

  i = -1;
  while (++i < SAVE_BUFF)
    if (s_nb[i] == ant->nb && s_name[i] == ant->location->name)
      return (FAILURE);
  return (SUCCESS);
}

int		check_recovery(t_ant *ant)
{
  static int	s_nb[SAVE_BUFF + 1];
  static char	*s_name[SAVE_BUFF + 1];
  static int	i = -1;

  i = (i + 1 % SAVE_BUFF);
  if (watchdog(s_nb, s_name, ant, i) == FAILURE)
    return (42);
  s_nb[i % SAVE_BUFF] = ant->nb;
  s_name[i % SAVE_BUFF] = ant->location->name;
  return (0);
}


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


int		action_ant(t_ant *root, t_ant *tmp, t_pos *pos, t_ia *ia)
{
  if (tmp == root)
    return (printf("\n"));
  if (tmp->location == pos->end)
    return (delete_node(root, tmp, pos, ia));
  tmp->location = get_next_location(pos, tmp, ia);
  if (ia->curr_loop == 0)
    ia->recovery_mode = check_recovery(tmp);
  if (tmp->location != tmp->previous)
    printf(ia->curr_loop == 0 ? "P%d-%s" : " P%d-%s",
	   tmp->nb, tmp->location->name);
  (ia->curr_loop)++;
  return (action_ant(root, tmp->next, pos, ia));
}

int		migration_loop(t_pos *pos, t_ia *ia, t_ant *ant)
{
  while (ia->arrived < pos->nb + 1 && ++(ia->tt_loop) < ant->nb)
    {
      pos->end->visited = 0;
      ia->curr_loop = 0;
      if (action_ant(ant, ant->next, pos, ia) == FAILURE)
	return (FAILURE);
      ia->arrived += pos->end->visited;
    }
}

int		start_migration(t_room *root, t_pos *pos)
{
  t_ant		*ant;
  t_ia		*ia;

  ant = init_ant();
  ia = calloc(1, sizeof(t_ia));
  if (!ant || !ia)
    return (FAILURE);
  while (ia->tt_ant++ < pos->nb + 1)
    add_ant(ant, pos, ia->tt_ant);
  ant->nb = pos->nb * ia->tt_ant;
  migration_loop(pos, ia, ant);
  clean_all(root, pos, ant);
  return (SUCCESS);
}
