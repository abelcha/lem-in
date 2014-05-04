/*
** graph.h for Project-Master in /home/beau_v/Test/Rendu_lem_in/lem-in/FINAL/src/GRAPH
** 
** Made by beau_v
** Login   <victor.beau@epitech.eu>
** 
** Started on  Sun May  4 02:35:08 2014 beau_v
** Last update Sun May  4 20:55:54 2014 chalie_a
*/

#ifndef		GRAPH_H_
# define	GRAPH_H_

# include "lem_in.h"

# define WIDTH		1400
# define HEIGHT	        900
# define KEY_ESC	27
# define ROW		200
# define GREEN		0.0, 10.0, 0.0, 0.0
# define RED		10.0, 0.0, 0.0, 0.0
# define BLUE		0.0, 0.0, 10.0, 0.0

typedef struct	s_coord
{
  float a1;
  float	a2;
  float	a3;
  float o1;
  float	o2;
  float	o3;
  float pipe_lenght;
}		t_coord;

typedef struct		s_move
{
  t_room		*r1;
  t_room		*r2;
  struct s_move		*prev;
  struct s_move		*next;
}			t_move;


void		keyboard(unsigned char key, int x, int y);
void		camera(void);
void		draw_quadrics(t_room *root, t_pos *p);
int		make_coffee(int argc, char **argv, t_room *room, t_pos *pos);
void		zoom(int flag);
void		rotate(int flag);

#endif		/* !GRAPH_H_ */
