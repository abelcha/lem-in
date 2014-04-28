/*
** bruteforce.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Fri Apr 25 05:17:27 2014 chalie_a
** Last update Mon Apr 28 07:43:55 2014 chalie_a
*/

#include <stdlib.h>
#include <stdio.h>
#include "lem-in.h"

int		dead;
char		**lem;

t_room	*find_room(char *, t_room *, t_room *);

void		link(t_node *root, t_room *r1, t_room *r2, int mouse)
{
  t_node	 *tmp;

  tmp = root;
  while ((tmp = tmp->next) != root)
    {
      //printf("%s == %s\n", 
      if (tmp->node == r2)
	return ;
    }
  printf(" no links between room %s and %s on mouse %d\n", r2->name, r1->name, mouse);
  exit(0);
}

int		actualise(int mouse, char *dest, t_room *root, t_pos *pos)
{
  t_room *target;
  t_room *actual;

  target = find_room(dest, root->next, root);
  actual = find_room(lem[mouse], root->next, root);
  if (target->visited != 0 && target != pos->end)
    {
      printf("cannot move %d to room %s, its empty\n", mouse, target->name);
      exit(0);
    }
  link(actual->links, actual, target, mouse);
  lem[mouse] = target->name;
  ++(target->visited);
  actual->visited = 0;
}

int		coffee(char *str, t_room *root, t_pos *pos)
{
  char		**stock;


  stock = to_tab(str, 0, '-');
  actualise(atoi(stock[0]), stock[1], root, pos);

  printf("move mouse %s to place %s\n", stock[0], stock[1]);
  return (0);
}

int		action(char *str, t_room *root, t_pos *pos)
{
  char		**stock;
  int		i;

  i = -1;
  stock = to_tab(str, 0, ' ');
  while (stock[++i])
    coffee(&stock[i][1], root, pos);
  return (0);
}


int		moulinette(t_room *root, t_pos *pos, char *lol)
{
  char		*str;
  int		i = -1;

  lem = calloc(40000, sizeof(char *));
  while (++i < 30000)
    {
      lem[i] = pos->start->name;
    }
  printf("start = %s end = %s\n", pos->start->name, pos->end->name);
  action(lol, root, pos);
  i = -1;
  while ((str = gnl(0)))
    {
      action(str, root, pos);     
      printf("%d / %d\n", pos->end->visited, pos->nb);
      printf("round %d\n", ++i);
    }
  return (0);
}
