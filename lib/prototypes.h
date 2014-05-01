#ifndef PROTOTYPES_H_
# define PROTOTYPES_H_
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
