/*
** shared.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Thu May  1 01:03:49 2014 chalie_a
** Last update Fri May  2 00:47:52 2014 chalie_a
*/

#include <stdio.h>
#include "lem_in.h"

void		remember_path(t_room *dest, t_room *tmp)
{
  int		i = 1;
  t_room	*save;

  while (tmp && tmp != dest)
    {
      tmp->coeff += i++;
      save = tmp;
      tmp = tmp->previous;
      save->previous = NULL;
    }
}

int		reinit_all(t_room *root, t_room *tmp)
{
  tmp->previous = NULL;
  tmp->visited = 0;
  tmp->curr_node = 0;
  return (tmp != root ? reinit_all(root, tmp->next) : 0);
}
