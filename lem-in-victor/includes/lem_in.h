/*
** prop.h for prop in /home/durand_u/rendu/lem-in
** 
** Made by durand_u
** Login   <durand_u@epitech.net>
** 
** Started on  Sat Mar 29 14:41:44 2014 durand_u
** Last update Thu May  1 21:52:42 2014 beau_v
*/

#ifndef LEM_IN_H_
# define LEM_IN_H_



typedef struct		s_node
{
  struct s_room		*node;
  struct s_node		*next;
  struct s_node		*prev;
}			t_node;

typedef struct		s_room
{
  int			x;
  int			y;
  int			z;
  int			coeff;
  int			visited;
  int			nb_nodes;
  int			curr_node;
  char			*name;
  struct s_room		*previous;
  struct s_node		*links;
  struct s_room		*next;
  struct s_room		*prev;
}			t_room;

typedef struct		s_ia
{
  int			arrived;
  int			tt_ant;
  int			tt_loop;
  int			curr_loop;
  int			recovery_mode;
}			t_ia;


typedef struct		s_pos
{
  int			opt;
  int			nb;
  t_room		*start;
  t_room		*end;
}			t_pos;

typedef struct		s_ant
{
  int			nb;
  struct s_room		*location;
  struct s_room		*previous;
  struct s_ant		*prev;
  struct s_ant		*next;
}			t_ant;


#define	SUCCESS		1
#define FAILURE		-1
#define TRUE		1
#define FALSE		-1
#define COMMENT		7
#define END		0
#define START		1
#define DEC		' '
#define AFF		'-'
#define DATA		42
#define RUNNING		6

#define W		&& (printf("WWWWWWWWWWWWWW\n"))
#define O		&& (printf("OOOOOOOOOOOOO\n"))
#define Y		&& (printf("YYYYYYYYYYYYYY\n"))
#define X		printf("XXXXXXXXXXXX\n");
#define A		printf("AAAAAAAAAAAA\n");
#define Z		printf("ZZZZZZZZZZZZ\n");
#define _ERROR(...)	fprintf(stderr, __VA_ARGS__) ? -1 : FAILURE
#define THREE_PARAM(s)	(!s[0] || !s[1] || !s[2] || s[3]) ? FALSE : TRUE

#include "prototypes.h"

int	x_free(void *ptr);
int	get_aco(t_room *, t_room *, t_room *, int);
int	rev_get_aco(t_room *, t_room *, t_room *, int);
int	random_findpath(t_room *, t_pos *);
int	start_migration(t_room *, t_pos *);
void	display_room(t_room *room, t_pos *pos);
char	*gnl(int);
char	**to_tab(char *, int, char);
int	speed_cmp(char *, char *);
t_node	*init_link();
int	link_room(t_room *, t_room *);
int	link_node(t_room *, t_room *);
int	add_elem(t_room *, char *, int, t_pos *);
int	get_rooms(t_room *);
int	fill_list(t_room *, char *);

#endif /* !LEM_IN_H_ */
