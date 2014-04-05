/*
** prop.h for prop in /home/durand_u/rendu/lem-in
** 
** Made by durand_u
** Login   <durand_u@epitech.net>
** 
** Started on  Sat Mar 29 14:41:44 2014 durand_u
** Last update Sat Apr  5 22:01:51 2014 chalie_a
*/

typedef struct		s_room				// Juste une proposition
{
  int			*link;			// 1 si il y a un lien, 0 sinon
  int			x;
  int			y;
  char			*name;
  char			*line;
  struct s_room		*next;
  struct s_room		*prev;
  int			pres;				// Il y a une fourmie dedans ou pas ?
  int			inc_pres;			// A t'on prévu d'y mettre une fourmie à ce tour ?
}			t_room;

#define	SUCCESS		1
#define FAILURE		-1
#define TRUE		1
#define FALSE		-1
#define END		5120486
#define START		846543
#define RUNNING		6848389
#define X		printf("XXXXXXXXXXXX\n");
#define A		printf("AAAAAAAAAAAA\n");
#define Z		printf("ZZZZZZZZZZZZ\n");
#define THREE_PARAM(s)	(!s[0] || !s[1] || !s[2] || s[3]) ? FALSE : TRUE

char	*gnl(int);
char	**to_tab(char *, int, char);
