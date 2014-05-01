/*
** main.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Wed Apr 16 22:50:26 2014 chalie_a
** Last update Fri May  2 01:15:43 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "lem_in.h"

t_room		*init_root()
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

int		opt(char *str)
{
  int		opt;

  if (!str)
    return (1);
  if (str[0] == '-' && str[1] == 'O')
    opt = str[2] - '0';
  if (opt >= 0 && opt <= 4)
    return (opt);
  return (_ERROR("Unreconised option `%s' \n", str));
}

int		main(int ac, char **av)
{
  t_room	*root;
  t_pos		*pos;
  char		*str;

  (void)ac;
  pos = calloc(1, sizeof(t_pos));
  str = gnl(0);
  pos->nb = my_atoi(str);
  x_free(str);
  if (pos->nb <= 0)
    return (_ERROR("Error : Invalid ant number.\n"));
  printf("%d\n", pos->nb);
  if ((pos->opt = opt(av[1])) == FAILURE)
    return (FAILURE);
  root = init_root();
  read_data(root, pos, DATA);
  if (!pos->end || !pos->start || !pos->start->name || !pos->end->name)
    return (_ERROR("Error : Invalid map\n"));
  if (ant_colony_clustering(root, pos) == SUCCESS)
    start_migration(root, pos);
  return (SUCCESS);
}
