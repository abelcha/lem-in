/*
** display.c for Project-Master in /home/beau_v/Test/Rendu_lem_in/lem-in/FINAL/src/GRAPH
** 
** Made by beau_v
** Login   <victor.beau@epitech.eu>
** 
** Started on  Sun May  4 02:17:06 2014 beau_v
** Last update Mon May  5 09:47:19 2014 chalie_a
*/

#include <GL/glut.h>
#include <math.h>
#include "lem_in.h"
#include "graph.h"

# define MOD    p->nb_room * 2
# define S_SIZE	(15 % ((MOD) / 9))

extern int	 yolo;

static void	draw_cylinder(t_coord *coord, t_room *tmp)
{
  GLUquadricObj *cylinder;

  cylinder = gluNewQuadric();
  gluQuadricDrawStyle(cylinder, GLU_LINE);
  glColor3d(1, 1, 1);
  glPushMatrix();
  glTranslated((float)tmp->x, (float)tmp->y, (float)tmp->z);
  glRotatef(180, coord->a1, coord->a2, coord->a3);
  gluCylinder(cylinder, 0.2, 0.2, coord->pipe_lenght, 15, 15);
  glPopMatrix();
  glPushMatrix();
  glTranslated((float)tmp->x, (float)tmp->y, (float)tmp->z);
  glColor3d(1, 1, 1);
  glutWireSphere(0.3, 12, 12);
  glPopMatrix();
  glPushMatrix();
  glTranslated((float)tmp->prev->x, (float)tmp->prev->y, (float)tmp->prev->z);
  glColor3d(1, 1, 1);
  glutWireSphere(0.3, 12, 12);
  glPopMatrix();
  gluDeleteQuadric(cylinder);
}

static void	init_cylinder(t_room *r1, t_room *r2, int flag)
{
  t_coord	coord;

  if (!r1 || !r2)
    return ;
  coord.o1 = (float)r2->x - (float)r1->x;
  coord.o2 = (float)r2->y - (float)r1->y;
  coord.o3 = (float)r2->z - (float)r1->z;
  coord.pipe_lenght = sqrt(coord.o1 * coord.o1 + coord.o2 *
			   coord.o2 + coord.o3 * coord.o3);
  coord.o1 = coord.o1 / coord.pipe_lenght;
  coord.o2 = coord.o2 / coord.pipe_lenght;
  coord.o3 = coord.o3 / coord.pipe_lenght;
  coord.a1 = coord.o1;
  coord.a2 = coord.o2;
  coord.a3 = 1 + coord.o3;
  if ((coord.a1 == 0.0) && (coord.a2 == 0.0) && (coord.a3 == 0.0))
    coord.a1 = 1;
  if (flag == 1)
    draw_cylinder(&coord, r1);
  else
    draw_test(&coord, r1, r2);
}

static void	draw_sphere(t_room *tmp, t_pos *p)
{
  GLUquadric	*quadric;

  quadric = gluNewQuadric();
  glPushMatrix();
  glTranslated(tmp->x, tmp->y , tmp->z);
  if (tmp == p->end)
    glColor4d(RED);
  else if (tmp == p->start)
    glColor4d(BLUE);
  else
    glColor4d(GREEN);
  gluQuadricDrawStyle(quadric, GLU_SILHOUETTE);
  gluSphere(quadric, 0.7, 40, 40);
  glPopMatrix();
  gluDeleteQuadric(quadric);
}


void		draw_ants(t_room *r1, t_room *r2)
{
  init_cylinder(r1, r2, 2);
}

int		get_cylinder(t_room *actual)
{
  t_node	*tmp;

  tmp = actual->links;
  while ((tmp = tmp->next) != actual->links)
    init_cylinder(actual,tmp->node , 1);
}

void		draw_quadrics(t_room *root, t_pos *p)
{
  t_room	*tmp;

  tmp = root;
  while ((tmp = tmp->next) != root)
    {
      tmp->x %= MOD;
      tmp->y %= MOD;
      if (tmp->z == 0)
	tmp->z = my_rand(0, MOD);
      draw_sphere(tmp, p);
      get_cylinder(tmp);
    }
}
