/*
** start_migration.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sun Apr 27 07:27:25 2014 chalie_a
** Last update Mon Apr 28 01:48:19 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include "lem-in.h"

int			add_mouse(t_mouse *elem, t_pos *pos, int i)
{
  t_mouse		*newelem;

  if (!(newelem = malloc(sizeof(t_mouse))))
    return (FAILURE);
  newelem->nb = i;
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

t_room		*get_next_location(t_node *root, t_room *actual, t_pos *pos, t_mouse *mouse)
{
  t_node	*tmp;
  t_room	*ret;

  ret = actual;
  tmp = root;
  while ((tmp = tmp->next) != root)
    {
      // if the target is the end room && its not the first room or nobody came to the end
      if (tmp->node == pos->end && (actual != pos->start || pos->end->visited == 0))
	{
	  //  printf("%s == %s , %d == 0\n",tmp->node->name,  pos->start->name, pos->end->visited);
	  ret = tmp->node;
	  //pos->end->visited = 1;
	  break ;
	}
      //      printf("node == %s prev = %s\n", tmp->node->name, mouse->previous->name);
      if (tmp->node->visited == 0 && tmp->node != actual && tmp->node->coeff > 0 && tmp->node != mouse->previous)
	{
	  //  printf("\t\t\tfindaroom\n");
	  ret = tmp->node;
	}
    }
  mouse->previous = actual;
  actual->visited = 0;
  ++(ret->visited);
  if (ret != actual)
      printf("P%d-%s ", mouse->nb, ret->name);
  //   printf("            %s --> %s\n", actual == pos->start ? "START" : actual == pos->end ? "END" : actual->name, 
  //   	   ret == pos->start ? "START" : ret == pos->end ? "END" : ret->name);
  return (ret);
}

int		action_mouse(t_mouse *root, t_pos *pos)
{
  t_mouse	*tmp;

  tmp = root->next;
  while ((tmp = tmp->next) != root)
    {
      //  printf("mouse nb : %d\n", tmp->nb);
      //usleep(100000);
      if (tmp->location != pos->end)
	tmp->location = get_next_location(tmp->location->links, tmp->location, pos, tmp);
    }
  return (SUCCESS);
}

int		start_migration(t_room *root, t_pos *pos)
{
  t_mouse	*mouse;
  int		i;
  int		j = -1;
  int		dead;

  dead = 0;
  i = -1;
  // printf("%s == %s\n", pos->start->name, pos->end->name);
  if (!(mouse = init_mouse()))
    return (FAILURE);

  while (i++ < pos->nb)
    add_mouse(mouse, pos, i);
  // printf("end  %d == %d\n", pos->end->visited, pos->nb);
  while (dead < pos->nb)
    {
      //printf("\ndead == %d round %d\n",dead, ++j);
      //  sleep(2); 
      action_mouse(mouse, pos);
      //printf("end->visited = %d\n", pos->end->visited);
	dead += pos->end->visited;
	printf("\n");
	++j;
	pos->end->visited = 0;
    }
  printf("\ndead == %d round %d\n",dead, ++j);
  return (SUCCESS);
}
