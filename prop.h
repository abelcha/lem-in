/*
** prop.h for prop in /home/durand_u/rendu/lem-in
** 
** Made by durand_u
** Login   <durand_u@epitech.net>
** 
** Started on  Sat Mar 29 14:41:44 2014 durand_u
** Last update Sat Mar 29 14:48:25 2014 durand_u
*/

typedef struct	s_room				// Juste une proposition
{
  int		link[nb_salles];		// 1 si il y a un lien, 0 sinon
  int		x;
  int		y;
  int		pres;				// Il y a une fourmie dedans ou pas ?
  int		inc_pres;			// A t'on prévu d'y mettre une fourmie à ce tour ?
}		t_room;
