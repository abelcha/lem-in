#ifndef PROTOTYPES_H_
# define PROTOTYPES_H_

#include "lem_in.h"

int     x_free(void *ptr);                                                                                            
int     speed_cmp(char *s, char *s2);                                                                                 
int     my_strcmp(char *s1, char *s2);                                                                                
int     my_strlen(char *str);                                                                                         
char    *my_strcat(char *s1, char *s2);                                                                               
char    *my_strcpy(char *dest, char *src);                                                                            
char    *my_strdup(char *str);                                                                                        
char    **to_tab(char *s, int cpt, char sep);                                                                         
int     my_rand (int min, int max);                                                                                   
int     my_atoi(char *str);                                                                                           
char    *gnl(const int fd);     

int	ant_colony_clustering(t_room *root, t_pos *pos);
void	remember_path(t_room *dest, t_room *tmp);
int	reinit_all(t_room *root, t_room *tmp);
t_room	*get_random_node(t_node *tmp, t_ant *ant);
int	is_legit(t_room *curr, t_room *ret, t_ant *ant);
t_room	*find_location(t_pos *pos, t_ant *ant, t_ia *ia);
t_room	*get_next_location(t_pos *pos, t_ant *ant, t_ia *ia);
t_node	*rev_get_right_node(t_node *tmp, int limit, int i);
int	rev_get_aco(t_room *root, t_room *start, t_room *end, int max);
t_node	*get_right_node(t_node *tmp, int limit, int i);
int	get_aco(t_room *root, t_room *start, t_room *end, int max);
void	clean_all(t_room *root, t_pos *pos, t_ant *ant);
int	get_sharp_value(char *str);
int	get_line_type(char *str);
t_room	*init_root();
void	get_start_and_end(t_pos *pos, int type, t_room *newelem);
int	read_data(t_room *root, t_pos *pos, int prev_type);
int	opt(char *str);
int	delete_node(t_ant *root, t_ant *tmp, t_pos *pos, t_ia *ia);
int	action_ant(t_ant *root, t_ant *tmp, t_pos *pos, t_ia *ia);
int	migration_loop(t_pos *pos, t_ia *ia, t_ant *ant);
int	watchdog(int *s_nb, char **s_name, t_ant *ant, int cpt);
int	check_recovery(t_ant *ant);
int	add_ant(t_ant *elem, t_pos *pos, int i);
t_ant	*init_ant();
int	start_migration(t_room *root, t_pos *pos);
int	create_link(t_node *elem, t_room *room);
int	existing_node(t_room *r1, t_room *r2);
int	link_node(t_room *r1, t_room *r2);
int	nb_param(char **stock, int i);
int	add_declaration(t_room *room, char *str);
t_room	*find_room(char *str, t_room *tmp, t_room *root);
int	add_affectation(char **stock, t_room *root, t_room *new);
char	**is_affectation(char *str);
void	link_rooms(t_room *elem, t_room *newelem);
t_node	*init_links();
int	add_elem(t_room *elem, char *str, int type, t_pos *pos);
int	add_ant(t_ant *elem, t_pos *pos, int i);
t_ant	*init_ant();
int	delete_node(t_ant *root, t_ant *tmp, t_pos *pos, t_ia *ia);
int	watchdog(int *s_nb, char **s_name, t_ant *ant, int cpt);
int	check_recovery(t_ant *ant);
t_room	*get_random_node(t_node *tmp, t_ant *ant);
int	is_legit(t_room *curr, t_room *ret, t_ant *ant);
t_room	*find_location(t_pos *pos, t_ant *ant, t_ia *ia);
t_room	*get_next_location(t_pos *pos, t_ant *ant, t_ia *ia);
int	action_ant(t_ant *root, t_ant *tmp, t_pos *pos, t_ia *ia);
int	migration_loop(t_pos *pos, t_ia *ia, t_ant *ant);
int	start_migration(t_room *root, t_pos *pos);

#endif /* !PROTOTYPES_H_ */
