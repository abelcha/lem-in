#ifndef PROTOTYPES_H_
# define PROTOTYPES_H_
if (scalar @ARGV < 3);
if ($end == $home);
if (scalar @ARGV < 3);
int	ant_colony_clustering(t_room *root, t_pos *pos);
void	remember_path(t_room *dest, t_room *tmp);
int	reinit_all(t_room *root, t_room *tmp);
void	clean_all(t_room *root, t_pos *pos, t_ant *ant);
t_room	*init_root();
int	opt(char *str);
t_room	*get_next_location(t_pos *pos, t_ant *ant, t_ia *ia);
int	check_recovery(t_ant *ant);
int	start_migration(t_room *root, t_pos *pos);
int	add_affectation(char **stock, t_room *root);
char	**is_affectation(char *str);
int	link_node(t_room *r1, t_room *r2);
int	get_sharp_value(char *str);
int	get_line_type(char *str);
void	get_start_and_end(t_pos *pos, int type, t_room *newelem);
int	read_data(t_room *root, t_pos *pos, int prev_type);
int	add_elem(t_room *elem, char *str);
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

#endif /* !PROTOTYPES_H_ */
