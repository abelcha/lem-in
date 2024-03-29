/*
** graph_parsing.c for Project-Master in /home/tovazm/rendu/lem-in/FINAL
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sun May  4 11:08:00 2014 chalie_a
** Last update Sun May  4 23:26:41 2014 beau_v
*/

#include <stdlib.h>
#include <stdio.h>
#include "lem_in.h"
#include "graph.h"

extern t_pos		*p;
extern char		*last_line;
t_move			*move;

static void		d_free(char **stock)
{
  int			i;

  i = -1;
  while (stock[++i])
    x_free(stock[i]);
  x_free(stock);
}

int			add_movement(t_move *elem, t_room *r1, t_room *r2)
{
  t_move		*newelem;

  if (!(newelem = calloc(1, sizeof(t_move))))
    return (FAILURE);
  newelem->r1 = r1;
  newelem->r2 = r2;
  newelem->prev = elem->prev;
  newelem->next = elem;
  elem->prev->next = newelem;
  elem->prev = newelem;
  return (SUCCESS);
}

static int		get_each_movement(char **stock, t_room **tab, t_room *root)
{
  int			i;
  char			**op;
  int			ant_nb;
  t_room		*target;

  i = -1;
  while (stock && stock[++i])
    {
      if (!(op = to_tab(&stock[i][1], 0, '-')))
	return (FAILURE);
      if (!op[0] || !op[0][0] || !op[1])
	return (FAILURE);
      if ((ant_nb = my_atoi(op[0])) == 0)
	return (FAILURE);
      if (!(target = find_room(op[1], root->next, root)))
	return (FAILURE);
      if (add_movement(move, tab[ant_nb], target) == FAILURE)
	return (FAILURE);
      tab[ant_nb] = target;
      d_free(op);
    }
  d_free(stock);
  return (SUCCESS);
}

t_move			*init_move()
{
  t_move		*root;

  if (!(root = malloc(sizeof(t_move))))
    return (NULL);
  root->prev = root;
  root->next = root;
  return (root);
}

int			get_movement(t_room *root)
{
  char			*str;
  char			**stock;
  t_room		**tab;

  if (!(tab = init_ant()))
    return (FAILURE);
  if (!(move = init_move()))
    return (FAILURE);
  if (!(stock = to_tab(last_line, 0, ' ')))
      return (FAILURE);
  if (get_each_movement(stock, tab, root) == FAILURE)
    return (FAILURE);
  while ((str = gnl(0)))
    {
      if (!(stock = to_tab(str, 0, ' ')))
	return (FAILURE);
      if (get_each_movement(stock, tab, root) == FAILURE)
	return (FAILURE);
      x_free(str);
    }
  x_free(tab);
  return (SUCCESS);
}
