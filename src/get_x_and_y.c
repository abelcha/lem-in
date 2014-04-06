/*
** get_x_and_y.c for olo in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sun Apr  6 11:02:58 2014 chalie_a
** Last update Sun Apr  6 11:07:41 2014 chalie_a
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "lem-in.h"

static int		is_number(const char *str)
{
  register short	i;

  i = -1;
  while (str[++i])
    if (str[i] < '0' || str[i] > '9')
      return (FALSE);
  return (TRUE);
}

static int		get_value(char *str)
{
  if (is_number(str) == FALSE)
    return (FAILURE);
  return (atoi(str));
}

static int		get_x_and_y(t_room *list, char **stock)
{
  list->x = get_value(stock[1]);
  list->y = get_value(stock[2]);
  if (list->x < 0 || list->y < 0)
    return (FAILURE);
  free(stock[1]);
  free(stock[2]);
  free(stock);
  return (SUCCESS);
}

int			fill_list(t_room *list, char *buffer)
{
  char			**stock;

  if (!(stock = to_tab(buffer, 0, ' ')))
    return (FAILURE);
  if (THREE_PARAM(stock) == FALSE)
    return (FAILURE);
  list->name = stock[0];
  list->line = buffer;
  return (get_x_and_y(list, stock));
}
