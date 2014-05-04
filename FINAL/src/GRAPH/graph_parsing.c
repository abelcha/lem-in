/*
** graph_parsing.c for Project-Master in /home/tovazm/rendu/lem-in/FINAL
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sun May  4 11:08:00 2014 chalie_a
** Last update Sun May  4 11:46:27 2014 chalie_a
*/

#include <stdlib.h>
#include <stdio.h>
#include "lem_in.h"
#include "graph.h"

extern t_pos	*p;
extern t_room	*root;

static t_room		**init_ant()
{
  t_room		**tab;
  int			i;

  i = 0;
  if (!(tab = calloc(p->nb + 10, sizeof(t_ant))))
    return (NULL);
  while (++i < p->nb + 5)
    tab[i] = p->start;
  return (tab);
}

static void		d_free(char **stock)
{
  int			i;

  i = -1;
  while (stock[++i])
    x_free(stock[i]);
  x_free(stock);
}

static t_room		*find_room(char *str, t_room *tmp,
				   const t_room *root)
{
  if (!speed_cmp(str, tmp->name))
    return (tmp);
  if ((tmp = tmp->next) != root)
    return (find_room(str, tmp, root));
  return (NULL);
}

static int		get_each_movement(char **stock, t_room **tab)
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
      printf("from room %s to room %s\n", tab[ant_nb]->name, target->name);
      // move_ant(tab[ant_nb], target); 
      tab[ant_nb] = target;
      d_free(op);
    }
  d_free(stock);
  return (SUCCESS);
}

int			get_movement()
{
  char			*str;
  char			**stock;
  t_room		**tab;

  if (!(tab = init_ant()))
    return (FAILURE);
  while ((str = gnl(0)))
    {
      if (!(stock = to_tab(str, 0, ' ')))
	return (FAILURE);
      if (get_each_movement(stock, tab) == FAILURE)
	return (FAILURE);
      x_free(str);
    }
  x_free(tab);  
}
