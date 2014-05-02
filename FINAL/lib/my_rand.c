/*
** my_rand.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Wed Apr 30 01:27:58 2014 chalie_a
** Last update Fri May  2 09:19:45 2014 chalie_a
*/

#include "lem_in.h"

int		my_rand (int min, int max)
{
  static int	seed = 1;

  seed = A * (seed % (M / A)) - (M % A) * (seed / (M / A));
  if (seed <= 0)
    seed += M;
  return (min + seed % max);
}
