/*
** prop.h for prop in /home/durand_u/rendu/lem-in
** 
** Made by durand_u
** Login   <durand_u@epitech.net>
** 
** Started on  Sat Mar 29 14:41:44 2014 durand_u
** Last update Sun May  4 17:43:47 2014 chalie_a
*/

#ifndef LEM_IN_H_
# define LEM_IN_H_

/*
**	STRUCTS
*/

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
  int			nb_ant;
  int			nb_room;
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

/*
**	MACROS
*/

# define SUCCESS	1
# define FAILURE	-1
# define TRUE		1
# define FALSE		-1
# define COMMENT	7
# define END		0
# define START		1
# define DATA		42
# define SAVE_BUFF	32
# define M		2147483647
# define A		16807

/*
**	ERROR
*/

# define INV_ROOM	"error : no such room `%s'\n", str
# define IMP_MAP	"Error : Impossible map\n"
# define INV_OPT	"Error : Unreconised option `%s' \n", str
# define INV_NB		"Error : Invalid ant number.\n"
# define INV_MAP	"Error : Invalid map\n"
# define _ERROR(...)	fprintf(stderr, __VA_ARGS__) ? -1 : FAILURE

/*
**	PARSER
*/

int	add_affectation(char **stock, t_room *root);
char	**is_affectation(char *str);
int	link_node(t_room *r1, t_room *r2);
int	read_data(t_room *root, t_pos *pos, int prev_type);
int	add_elem(t_room *elem, char *str, t_pos *pos);

/*
**	ALGO
*/

int	get_aco(t_room *root, t_room *start,t_room *end, int max);
int	rev_get_aco(t_room *root, t_room *start,t_room *end, int max);
int	ant_colony_clustering(t_room *root, t_pos *pos);
void	remember_path(t_room *dest, t_room *tmp);
int	reinit_all(t_room *root, t_room *tmp);

/*
**	MIGRATION
*/

int	migration_loop(t_pos *pos, t_ia *ia,t_ant *ant);
int	start_migration(t_room *root, t_pos *pos);
t_room	*get_next_location(t_pos *pos, t_ant *ant, t_ia *ia);
int	check_recovery(t_ant *ant);
int	delete_node(t_ant *root, t_ant *tmp, t_pos *pos, t_ia *ia);
void	clean_all(t_room *root, t_pos *pos, t_ant *ant);

/*
**     LIB
*/

int	x_free(void *ptr);
int	speed_cmp(char *s, char *s2);
int	my_strcmp(char *s1, char *s2);
int	my_strlen(char *str);
char	*my_strcat(char *s1, char *s2);
char	*my_strcpy(char *dest, char *src);
char	*my_strdup(char *str);
char	**to_tab(char *s, int cpt, char sep);
int	my_rand (int min, int max);
int	my_atoi(char *str);
char	*gnl(const int fd);

#endif /* !LEM_IN_H_ */
