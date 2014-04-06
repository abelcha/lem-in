/*
** parsing.c for yoloswag in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sat Apr  5 17:24:10 2014 chalie_a
** Last update Sun Apr  6 11:07:51 2014 chalie_a
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "lem-in.h"

static t_room		*init_root()
{
  t_room		*init;

  if (!(init = malloc(sizeof(*init))))
    return (NULL);
  init->prev = init;
  init->next = init;
  return (init);
}

static void	show_list(t_room *root)
{
  t_room	*tmp;

  tmp = root;
  while ((tmp = tmp->next) != root)
    printf("name = %s x = %d, y = %d\n", tmp->name, tmp->x, tmp->y);
}
  
int		main(void)
{
  t_room	*root;

  root = init_root();
  if (get_rooms(root) == FAILURE)
    return (FAILURE);
  show_list(root);
}
