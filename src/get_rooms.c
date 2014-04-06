/*
** parsing.c for yoloswag in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Sat Apr  5 17:24:10 2014 chalie_a
** Last update Sun Apr  6 11:43:15 2014 chalie_a
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "lem-in.h"

static int	add_in_list(t_room *root, char *buffer)
{
  t_room	*new_elem;

  new_elem = malloc(sizeof(t_room));
  if (!new_elem || !buffer)
    return (FAILURE);
  if (fill_list(new_elem, buffer) == FAILURE)
    return (FAILURE);
  new_elem->prev = root->prev;
  new_elem->next = root;
  root->prev->next = new_elem;
  root->prev = new_elem;
  return (SUCCESS);
}

static int	get_sharp(char *str, const short flag)
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

static int	get_status(char *buffer, short flag)
{
  if (buffer[0] == '#')
    return (get_sharp(buffer, flag));
  return (RUNNING);
}

int		get_rooms(t_room *root)
{
  char		*buffer;
  short		flag;

  flag = 0;
  while ((buffer = gnl(STDIN_FILENO)))
    if ((flag = get_status(buffer, flag)) == FAILURE)
      return (FAILURE); 
    else if (flag == RUNNING && add_in_list(root, buffer) == FAILURE)
      return (FAILURE);
    else if (flag == END)
      return (add_in_list(root, gnl(STDIN_FILENO)));
  return (FAILURE);
}
