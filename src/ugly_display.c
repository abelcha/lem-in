/*
** main.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Wed Apr 16 22:50:26 2014 chalie_a
** Last update Sat Apr 26 21:41:02 2014 chalie_a
*/

#include <stdio.h>
#include "lem-in.h"

void		display_node(t_node *root)
{
  t_node		*tmp;

  tmp = root;
  while ((tmp = tmp->next) != root)
  printf("                             ---> linked with %s\n", tmp->node->name);
}

void		display_room(t_room *root, t_pos *pos)
{
  t_room	*tmp;
  tmp = root;
  printf("fourmis nb = %d\n", pos->nb);
  while ((tmp = tmp->next) != root)
    {
      if (tmp == pos->start)
	printf("START\n");
      if (tmp == pos->end)
	printf("END\n");
      printf("name = %s coeff = %d\n", tmp->name, tmp->coeff);
      display_node(tmp->links);
    }
}
