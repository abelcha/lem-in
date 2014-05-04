/*
** main.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Wed Apr 16 22:50:26 2014 chalie_a
** Last update Sun May  4 22:25:59 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include "lem_in.h"

static int			nb_param(char **stock, int i)
{
  return (stock[i] ? nb_param(stock, ++i) : i);
}

static t_room			*find_room(char *str, t_room *tmp,
					   const t_room *root)
{
  if (!speed_cmp(str, tmp->name))
      return (tmp);
  if ((tmp = tmp->next) != root)
    return (find_room(str, tmp, root));
  _ERROR(INV_ROOM);
  return (NULL);
}

int				add_affectation(char **stock, t_room *root)
{
  t_room			*r1;
  t_room			*r2;

  if (!stock || nb_param(stock, 0) != 2)
    return (FAILURE);
  if (!(r1 = find_room(stock[0], root->next, root)))
    return (FAILURE);
  if (!(r2 = find_room(stock[1], root->next, root)))
    return (FAILURE);
  x_free(stock[0]);
  x_free(stock[1]);
  x_free(stock);
  return (link_node(r1, r2));
}

char				**is_affectation(char *str)
{
  char				**stock;
  int				i;

  i = -1;
  stock = NULL;
  stock = to_tab(str, 0, '-');
  if (!stock || nb_param(stock, 0) != 2)
    {
      while (stock[++i])
	x_free(stock[i]);
      x_free(stock);
      stock = NULL;
    }
  return (stock);
}
