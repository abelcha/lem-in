/*
** my_rand.c for Project-Master in /home/tovazm/rendu/lem-in
** 
** Made by chalie_a
** Login   <abel@chalier.me>
** 
** Started on  Wed Apr 30 01:27:58 2014 chalie_a
** Last update Wed Apr 30 02:00:31 2014 chalie_a
*/

 #include <stdio.h>
  
#define M 2147483647
#define A 16807
#define Q (M / A)
#define R (M % A)
 
int		my_rand (int min, int max)
 {
   static int	seed = 1;

   seed = A * (seed % Q) - R * (seed / Q);
   if (seed <= 0)
     seed += M;
   return (min + seed % max);
 }
 
