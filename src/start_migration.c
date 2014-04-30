/*
** start_migration.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sun Apr 27 07:27:25 2014 chalie_a
** Last update Wed Apr 30 02:41:49 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include "lem-in.h"

#define SAVE_BUFF	128

int			recovery_mode;

int			add_mouse(t_mouse *elem, t_pos *pos, int i)
{
  t_mouse		*newelem;

  if (!(newelem = malloc(sizeof(t_mouse))))
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


t_mouse			*init_mouse()
{
  t_mouse		*root;

  if (!(root = malloc(sizeof(t_mouse))))
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}

t_room		*get_random_node(t_node *tmp, t_node *root, t_room *actual, t_mouse *mouse)
{
  t_room	*ret;

  ret = actual;
  while ((tmp = tmp->next) != root)
    {
      if (tmp->node->visited == 0 && tmp->node != actual && 
	  tmp->node->coeff > 0 && tmp->node != mouse->previous)
	{
	  ret = tmp->node;
	  if (my_rand(0, 10) == 3)
	    break;
	}
    }
  return (ret);
}

t_room		*get_next_location(t_node *root, t_room *actual, t_pos *pos, t_mouse *mouse)
{
  t_node	*tmp;
  t_room	*ret;

  ret = actual;
  tmp = root;
  if (!recovery_mode)
    while ((tmp = tmp->next) != root)
      {
	if (tmp->node == pos->end &&
	  (actual != pos->start || pos->end->visited == 0))
	  {
	    ret = tmp->node;
	    break ;
	  }
	if (tmp->node->visited == 0 && tmp->node != actual &&
	    tmp->node->coeff > 0 && tmp->node != mouse->previous)
	  if (ret == actual || tmp->node->coeff > ret->coeff || recovery_mode)
	  ret = tmp->node;
      }
  else
    ret = get_random_node(tmp, root, actual, mouse);
  mouse->previous = actual;
  actual->visited = 0;
  ++(ret->visited);
  return (ret);
}

int		delete_node(t_mouse *root, t_mouse *tmp, t_pos *pos, int i)
{
  t_mouse	*save;

  save = tmp->next;
  tmp->prev->next = tmp->next;
  tmp->next->prev = tmp->prev;
  free(tmp);
  return (action_mouse(root, save, pos, i));
}

int		watchdog(int *s_nb, char **s_name, t_mouse *mouse, int cpt)
{
  int		i;

  i = -1;
  while (++i <  SAVE_BUFF)
    if (s_nb[i] == mouse->nb && s_name[i] == mouse->location->name)
      return (FAILURE);
  return (SUCCESS);
}

int		check_recovery(t_mouse *mouse)
{
  static int	s_nb[SAVE_BUFF + 1];
  static char	*s_name[SAVE_BUFF + 1];
  static int	i = -1;

  i = (i + 1 % SAVE_BUFF);
  if (watchdog(s_nb, s_name, mouse, i) == FAILURE)
    return (42);
  s_nb[i % SAVE_BUFF] = mouse->nb;
  s_name[i % SAVE_BUFF] = mouse->location->name;
  return (0);
}

int		action_mouse(t_mouse *root, t_mouse *tmp, t_pos *pos, int i)
{
  if (tmp == root)
    return (SUCCESS);
  if (tmp->location == pos->end)
    return (delete_node(root, tmp, pos, i));
  tmp->location = get_next_location(tmp->location->links, tmp->location, pos, tmp);
  if (i == 0)
    recovery_mode = check_recovery(tmp);
  if (tmp->location != tmp->previous)
    printf("P%d-%s ", tmp->nb, tmp->location->name);
  return (action_mouse(root, tmp->next, pos, ++i));
}

int		start_migration(t_room *root, t_pos *pos)
{
  t_mouse	*mouse;
  int		i;
  int		j = -1;
  int		dead;

  dead = 0;
  i = -1;
  recovery_mode = 0;
  if (!(mouse = init_mouse()))
    return (FAILURE);
  while (++i < pos->nb + 1)
    add_mouse(mouse, pos, i);
  while (dead < pos->nb + 1)
    {
      action_mouse(mouse, mouse->next, pos, 0);
      dead += pos->end->visited;
      printf("\n");
      pos->end->visited = 0;
    }
  clean_all(root, pos, mouse);
  return (SUCCESS);
}
