/*
** parsing_funcs.c for Project-Master in /home/beau_v/Test/FULL_LEM/lem-in/FINAL/src/GRAPH
** 
** Made by beau_v
** Login   <victor.beau@epitech.eu>
** 
** Started on  Sun May  4 23:22:40 2014 beau_v
** Last update Sun May  4 23:25:46 2014 beau_v
*/

#include <stdlib.h>
#include "lem_in.h"
#include "graph.h"

extern t_pos		*p;

t_room			*find_room(char *str, t_room *tmp,
				   const t_room *root)
{
  if (!speed_cmp(str, tmp->name))
    return (tmp);
  if ((tmp = tmp->next) != root)
    return (find_room(str, tmp, root));
  return (NULL);
}

t_room			**init_ant()
{
  t_room		**tab;
  int			i;

  i = 0;
  if (!(tab = calloc(p->nb_ant + 10, sizeof(t_ant))))
    return (NULL);
  while (++i < p->nb_ant + 5)
    tab[i] = p->start;
  return (tab);
}
