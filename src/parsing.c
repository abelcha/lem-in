/*
** parsing.c for yoloswag in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sat Apr  5 17:24:10 2014 chalie_a
** Last update Sat Apr  5 23:08:27 2014 chalie_a
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

void		show_list(t_room *root)
{
  t_room	*tmp;

  tmp = root;
  while ((tmp = tmp->next) != root)
    printf("name = %s x = %d, y = %d\n", tmp->name, tmp->x, tmp->y);
}

int		is_number(char *str)
{
  int		i;

  i = -1;
  while (str[++i])
    if (str[i] < '0' || str[i] > '9')
      return (FALSE);
  return (TRUE);
}

int		get_value(char *str)
{
  if (is_number(str) == FALSE)
    return (FAILURE);
  return (atoi(str));
}

int		get_x_and_y(t_room *list, char **stock)
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

int		fill_list(t_room *list, char *buffer)
{
  char		**stock;

  if (!(stock = to_tab(buffer, 0, ' ')))
    return (FAILURE);
  if (THREE_PARAM(stock) == FALSE)
    return (FAILURE);
  list->name = stock[0];
  list->line = buffer;
  return (get_x_and_y(list, stock));
}
int		add_in_list(t_room *root, char *buffer)
{
  t_room	*new_elem;

  if (!(new_elem = malloc(sizeof(t_room))))
    return (FAILURE);
  if (fill_list(new_elem, buffer) == FAILURE)
    return (FAILURE);
  new_elem->prev = root->prev;
  new_elem->next = root;
  root->prev->next = new_elem;
  root->prev = new_elem;
  return (SUCCESS);
}

int		get_sharp(char *str, int flag)
{

  if (str[1] == '#')
    if (!strncmp(str, "##start", 6))
      return (flag == START ? FAILURE : START);
    else if (!strncmp(str, "##end", 5))
      return (END);
    else
      return (FAILURE);   
  else
    return (START);
}

int		get_status(char *buffer, int flag)
{
  if (buffer[0] == '#')
    return (get_sharp(buffer, flag));
  return (RUNNING);
}

int		get_rooms(t_room *root)
{
  char		*buffer;
  int		flag;

  flag = 0;
  while ((buffer = gnl(STDIN_FILENO)))
    if ((flag = get_status(buffer, flag)) == FAILURE)
      return (FAILURE); 
    else if (flag == RUNNING && add_in_list(root, buffer) == FAILURE)
      return (FAILURE);
    else if (flag == END)
      return (END);
  return (FAILURE);
}
      
int		main(void)
{
  t_room	*root;

  root = init_root();
  if (get_rooms(root) == FAILURE)
    return (FAILURE);
  show_list(root);
}
