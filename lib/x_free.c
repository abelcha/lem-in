/*
** x_free.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Thu May  1 10:13:27 2014 chalie_a
** Last update Thu May  1 10:30:28 2014 chalie_a
*/

#include <stdlib.h>

int	x_free(void *ptr)
{
  if (ptr)
    {
      free(ptr);
      ptr = NULL;
    }
  return (42);
}
