#ifndef PROTOTYPES_H_
# define PROTOTYPES_H_

int	ant_colony_clustering(t_room *root, t_pos *pos);
/*t_node	*get_right_node(t_node *tmp, int limit, int i);
t_room	*get_next_node(t_node *root, t_room *actual, int row);
void	remember_path(t_room *start, t_room *end);
int	get_paths(t_room *tmp, t_room *start, t_room *end, int i);
int	get_aco(t_room *root, t_room *start, t_room *end, int i);*/
int	reinit_all(t_room *root, t_room *tmp);
int	ant_colony_clustering(t_room *root, t_pos *pos);
void	clean_all(t_room *root, t_pos *pos, t_ant *ant);
void	remember_path(t_room *dest, t_room *tmp);
int	reinit_all(t_room *root, t_room *tmp);
void	display_node(t_node *root);
void	display_room(t_room *root, t_pos *pos);
int	get_sharp_value(char *str);
int	get_line_type(char *str);
t_room	*init_root();
void	get_start_and_end(t_pos *pos, int type, t_room *newelem);
int	read_data(t_room *root, t_pos *pos, int prev_type);
int	opt(char *str);
int	create_link(t_node *elem, t_room *room);
int	existing_node(t_room *r1, t_room *r2);
int	link_node(t_room *r1, t_room *r2);
int	add_ant(t_ant *elem, t_pos *pos, int i);
t_ant	*init_ant();
//t_room	*get_random_node(t_node *tmp, t_node *root, t_room *actual, t_ant *ant);
//t_room	*get_next_location(t_node *root, t_room *actual, t_pos *pos, t_ant *ant);
int	delete_node(t_ant *root, t_ant *tmp, t_pos *pos, int i);
int	watchdog(int *s_nb, char **s_name, t_ant *ant, int cpt);
int	check_recovery(t_ant *ant);
int	action_ant(t_ant *root, t_ant *tmp, t_pos *pos, int i);
int	start_migration(t_room *root, t_pos *pos);
int	nb_param(char **stock, int i);
int	add_declaration(t_room *room, char *str);
t_room	*find_room(char *str, t_room *tmp, t_room *root);
int	add_affectation(char **stock, t_room *root, t_room *new);
char	**is_affectation(char *str);
void	link_rooms(t_room *elem, t_room *newelem);
t_node	*init_links();
int	add_elem(t_room *elem, char *str, int type, t_pos *pos);
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

#endif /* !PROTOTYPES_H_ includes */
