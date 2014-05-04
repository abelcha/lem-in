/*
** main.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Wed Apr 16 22:50:26 2014 chalie_a
** Last update Sun May  4 20:14:19 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "lem_in.h"

static t_room	*init_root()
{
  t_room	*root;

  if (!(root = malloc(sizeof(t_room))))
    return (NULL);
  root->name = NULL;
  root->links = NULL;
  root->prev = root;
  root->next = root;
  return (root);
}

int		main(int ac, char **av)
{
  char		*str;
  t_room	*root;
  t_pos		*pos;

  if (!(pos = calloc(1, sizeof(t_pos))))
    return (FAILURE);
  str = gnl(0);
  pos->nb_ant = my_atoi(str);
  x_free(str);
  if (pos->nb_ant <= 0)
    return (_ERROR(INV_NB));
  if (!(root = init_root()))
    return (FAILURE);
  read_data(root, pos, DATA);
  if (!pos->end || !pos->start || !pos->start->name || !pos->end->name)
    return (_ERROR(INV_MAP));
  return (make_coffee(ac, av, root, pos));
}
