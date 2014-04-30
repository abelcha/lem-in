/*
** main.c for Project-Master in /home/tovazm/rendu/lem-in/src
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Wed Apr 16 22:50:26 2014 chalie_a
** Last update Mon Apr 28 15:20:56 2014 chalie_a
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include "lem-in.h"

int			get_sharp_value(char *str)
{
  static char	*tab[2] = {"#start", "#end"};
  int			i;

  i = 2;
  while (--i >= 0 && !speed_cmp(tab[i], str));
  return (i);
}

int			get_line_type(char *str)
{
  return (str[1] == '#' ? get_sharp_value(&str[1]) : COMMENT);
}

t_room		*init_root()
{
  t_room	*root;

  if (!(root = malloc(sizeof(t_room))))
    return (NULL);
  root->name = NULL;
  root->links = NULL;
  root->prev = root;
  root->next = root;
  return (root);
}

void		get_start_and_end(t_pos *pos, int type, t_room *newelem)
{
  if (type == START)
    pos->start = newelem;
  if (type == END)
    pos->end = newelem; 
}

int		read_data(t_room *root, t_pos *pos, int prev_type)
{

  int		type;
  char		*str;

   if (!(str = gnl(0)))
     return (SUCCESS);
   printf("%s\n", str);
   type = (*str == '#' ? get_line_type(str) : DATA); 
   if (type == DATA && add_elem(root, str, prev_type, pos) == FAILURE)
     return (FAILURE);
   if (prev_type != DATA)
     get_start_and_end(pos, prev_type, root->prev);
   free(str);
   return (read_data(root, pos, type));
}

int		opt(char *str)
{
  int		opt;

  if (!str)
    return (0);
  if (str[0] == '-' && str[1] == 'O')
    opt = str[2] - '0';
  if (opt >= 0 && opt <= 4)
    return (opt);
  printf("Unreconised option `%s' \n", str); 
  return (FAILURE);
}

int		main(int ac, char **av)
{
  t_room	*root;
  t_pos		*pos;
  char		*str;
  pos = malloc(sizeof(t_pos));
  pos->start = NULL;
  pos->end = NULL;
  str = gnl(0);
  pos->nb = my_atoi(str);
  free(str);
  if (pos->nb <= 0)
    return (FAILURE);
  printf("%d\n", pos->nb);
  if ((pos->opt = opt(av[1])) == FAILURE)
    return (FAILURE);
  root = init_root();
  read_data(root, pos, DATA);
  if (!pos->end || !pos->start)
    return (FAILURE);
  if (random_findpath(root, pos) == FAILURE)
    printf("ERROR\n");
}
