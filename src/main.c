/*
** main.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Wed Apr 16 22:50:26 2014 chalie_a
** Last update Sun May  4 21:28:18 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "lem_in.h"

static t_room		*init_root()
{
  t_room		*root;

  if (!(root = malloc(sizeof(t_room))))
    return (NULL);
  root->name = NULL;
  root->links = NULL;
  root->prev = root;
  root->next = root;
  return (root);
}

static int		opt(char *str)
{
  int			opt;

  opt = 1;
  if (!str)
    return (opt);
  if (str[0] == '-' && str[1] == 'O')
    opt = str[2] - '0';
  if (opt >= 0 && opt <= 4)
    return (opt);
  return (_ERROR(INV_OPT));
}

int			main(int ac, char **av)
{
  char			*str;
  t_room		*root;
  t_pos			*pos;

  root = init_root();
  pos = calloc(1, sizeof(t_pos));
  if (!root || !pos)
    return (FAILURE);
  str = gnl(0);
  pos->nb_ant = my_atoi(str);
  if (pos->nb_ant <= 0)
    return (_ERROR(INV_NB));
  x_free(str);
  printf("%d\n", pos->nb_ant);
  if ((pos->opt = opt(av[1])) == FAILURE)
    return (FAILURE);
  read_data(root, pos, DATA);
  if (!pos->end || !pos->start || !pos->start->name || !pos->end->name)
    return (_ERROR(INV_MAP));
  if (ant_colony_clustering(root, pos) == SUCCESS)
    start_migration(root, pos);
  return (SUCCESS);
}
