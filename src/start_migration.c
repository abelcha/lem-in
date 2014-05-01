/*
** start_migration.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sun Apr 27 07:27:25 2014 chalie_a
** Last update Thu May  1 03:13:33 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include "lem_in.h"

#define SAVE_BUFF	32

int			recovery_mode;

int			add_ant(t_ant *elem, t_pos *pos, int i)
{
  t_ant		*newelem;

  if (!(newelem = malloc(sizeof(t_ant))))
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

  if (!(root = malloc(sizeof(t_ant))))
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}

int		delete_node(t_ant *root, t_ant *tmp, t_pos *pos, int i)
{
  t_ant	*save;

  save = tmp->next;
  tmp->prev->next = tmp->next;
  tmp->next->prev = tmp->prev;
  free(tmp);
  return (action_ant(root, save, pos, i));
}

int		watchdog(int *s_nb, char **s_name, t_ant *ant, int cpt)
{
  int		i;

  i = -1;
  while (++i <  SAVE_BUFF)
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

t_room		*get_next_location(t_pos *pos, t_ant *ant)
{
  t_node	*tmp;
  t_room	*ret;

  ret = ant->location;
  tmp = ant->location->links;
  if (!recovery_mode)
    while ((tmp = tmp->next) != ant->location->links)
      {
	if (tmp->node == pos->end &&
	  (ant->location != pos->start || pos->end->visited == 0))
	  {
	    ret = tmp->node;
	    break ;
	  }
	if (tmp->node->visited == 0 && tmp->node != ant->location &&
	    tmp->node->coeff > 0 && tmp->node != ant->previous)
	  if (ret == ant->location || tmp->node->coeff > ret->coeff)
	  ret = tmp->node;
      }
  else
    ret = get_random_node(tmp, ant);
  ant->previous = ant->location;
  ant->location->visited = 0;
  ++(ret->visited);
  return (ret);
}


int		action_ant(t_ant *root, t_ant *tmp, t_pos *pos, int i)
{
  if (tmp == root)
    return (printf("\n"));
  if (tmp->location == pos->end)
    return (delete_node(root, tmp, pos, i));
  tmp->location = get_next_location(pos, tmp);
  if (i == 0)
    recovery_mode = check_recovery(tmp);
  if (tmp->location != tmp->previous)
    printf("P%d-%s ", tmp->nb, tmp->location->name);
  return (action_ant(root, tmp->next, pos, ++i));
}

int		start_migration(t_room *root, t_pos *pos)
{
  t_ant	*ant;
  int		i;
  int		j = -1;
  int		dead;

  dead = 0;
  i = -1;
  recovery_mode = 0;
  if (!(ant = init_ant()))
    return (FAILURE);
  while (++i < pos->nb + 1)
    add_ant(ant, pos, i);
  while (dead < pos->nb + 1)
    {
      action_ant(ant, ant->next, pos, 0);
      dead += pos->end->visited;
      pos->end->visited = 0;
    }
  clean_all(root, pos, ant);
  return (SUCCESS);
}
