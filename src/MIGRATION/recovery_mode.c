/*
** start_migration.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sun Apr 27 07:27:25 2014 chalie_a
** Last update Thu May  1 13:35:10 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include "lem_in.h"

#define SAVE_BUFF	16

int		watchdog(int *s_nb, char **s_name, t_ant *ant, int cpt)
{
  int		i;

  i = -1;
  while (++i < SAVE_BUFF)
    if (s_nb[i] == ant->nb && s_name[i] == ant->location->name)
      return (FAILURE);
  return (SUCCESS);
}

int		check_recovery(t_ant *ant)
{
  static int	s_nb[SAVE_BUFF + 1];
  static char	*s_name[SAVE_BUFF + 1];
  static int	i = -1;

  i = (i + 1 % SAVE_BUFF);
  if (watchdog(s_nb, s_name, ant, i) == FAILURE)
    return (42);
  s_nb[i % SAVE_BUFF] = ant->nb;
  s_name[i % SAVE_BUFF] = ant->location->name;
  return (0);
}
