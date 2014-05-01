#ifndef PROTOTYPES_H_
# define PROTOTYPES_H_
int	ant_colony_clustering(t_room *root, t_pos *pos);
void	remember_path(t_room *dest, t_room *tmp);
int	reinit_all(t_room *root, t_room *tmp);
t_node	*rev_get_right_node(t_node *tmp, int limit, int i);
t_node	*get_right_node(t_node *tmp, int limit, int i);
int	get_aco(t_room *root, t_room *start, t_room *end, int max);
void	clean_all(t_room *root, t_pos *pos, t_ant *ant);
t_room	*init_root();
int	opt(char *str);
t_room	*get_next_location(t_pos *pos, t_ant *ant, t_ia *ia);
int	check_recovery(t_ant *ant);
int	start_migration(t_room *root, t_pos *pos);
int	add_affectation(char **stock, t_room *root, t_room *new);
char	**is_affectation(char *str);
int	link_node(t_room *r1, t_room *r2);
int	get_sharp_value(char *str);
int	get_line_type(char *str);
void	get_start_and_end(t_pos *pos, int type, t_room *newelem);
int	read_data(t_room *root, t_pos *pos, int prev_type);
int	add_elem(t_room *elem, char *str, int type, t_pos *pos);

#endif /* !PROTOTYPES_H_ */
