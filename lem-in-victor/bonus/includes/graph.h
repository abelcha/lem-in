#ifndef		GRAPH_H_
# define	GRAPH_H_

# define WIDTH		1600
# define HEIGHT	        1600
# define KEY_ESC	27

typedef struct	s_node
{
  struct s_room	*node;
  struct s_node	*next;
  struct s_node	*prev;
}		t_node;

typedef struct	s_room
{
  int		x;
  int		y;
  int		coeff;
  int		visited;
  int		nb_nodes;
  int		curr_node;
  char		*name;
  struct s_room	*previous;
  struct s_node	*links;
  struct s_room	*next;
  struct s_room	*prev;
}		t_room;

typedef struct	s_ia
{
  int		arrived;
  int		tt_ant;
  int		tt_loop;
  int		curr_loop;
  int		recovery_mode;
}		t_ia;

typedef struct	s_pos
{
  int		opt;
  int		nb;
  t_room	*start;
  t_room	*end;
}		t_pos;

typedef struct	s_ant
{
  int		nb;
  struct s_room	*location;
  struct s_room	*previous;
  struct s_ant	*prev;
  struct s_ant	*next;
}		t_ant;

#endif		/* !GRAPH_H_ */
