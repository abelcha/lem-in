/*
** strings.c for minish in /home/chalie_a/rendu/PSU_2013_minishell1
** 
** Made by chalie_a
** Login   <chalie_a@epitech.eu>
** 
** Started on  Wed Jan  1 03:15:53 2014 chalie_a
** Last update Thu Apr 24 08:24:20 2014 chalie_a
*/

#include <stdlib.h>
#include <string.h>

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  while (str && str[i])
    i++;
  return (i);
}

char	*my_strcat(char *s1, char *s2)
{
  char	*new;
  int	i;
  int	j;
  int	len;

  i = 0;
  j = 0;
  len = my_strlen(s1) + my_strlen(s2);
  new = calloc((len + 1), sizeof(char));
  memset(new, '\0', len + 1);
  while (s1[i])
    {
      new[i] = s1[i];
      i++;
    }
  while (s2[j])
    {
      new[i + j] = s2[j];
      j++;
    }
  return (new);
}

char	*my_strcpy(char *dest, char *src)
{
  int	i;

  i = 0;
  while (dest && src && src[i] != '\0')
    {
      dest[i] = src[i];
      i = i + 1;
    }
  if (i != 0)
    dest[i] = '\0';
  return (dest);
}

char	*my_strdup(char *str)
{
  char	*newstr;

  newstr = calloc((my_strlen(str) + 8), sizeof(char *));
  if (newstr)
    my_strcpy(newstr, str);
  return (newstr);
}
