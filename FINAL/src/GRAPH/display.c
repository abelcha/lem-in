/*
** display.c for Project-Master in /home/beau_v/Test/Rendu_lem_in/lem-in/FINAL/src/GRAPH
** 
** Made by beau_v
** Login   <victor.beau@epitech.eu>
** 
** Started on  Sun May  4 02:17:06 2014 beau_v
** Last update Sun May  4 03:48:36 2014 beau_v
*/

#include <GL/glut.h>
#include <math.h>
#include "lem_in.h"
#include "graph.h"

# define MOD    p->nb * 2
# define S_SIZE	(15 % ((MOD) / 9))

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

static void	init_cylinder(t_room *tmp)
{
  t_coord	coord;

  coord.o1 = (float)tmp->prev->x - (float)tmp->x;
  coord.o2 = (float)tmp->prev->y - (float)tmp->y;
  coord.o3 = (float)tmp->prev->z - (float)tmp->z;
  coord.pipe_lenght = sqrt(coord.o1 * coord.o1 + coord.o2 *
			   coord.o2 + coord.o3 * coord.o3);
  coord.o1 = coord.o1 / coord.pipe_lenght; /* normalize */
  coord.o2 = coord.o2 / coord.pipe_lenght;
  coord.o3 = coord.o3 / coord.pipe_lenght;
  coord.a1 = coord.o1; /* normalized cylinder vector + normalized target vector */
  coord.a2 = coord.o2;
  coord.a3 = 1 + coord.o3;
  if ((coord.a1 == 0.0) && (coord.a2 == 0.0) && (coord.a3 == 0.0)) /* exception! */
    coord.a1 = 1;
  draw_cylinder(&coord, tmp);
}

static void	draw_sphere(t_room *tmp, t_pos *p)
{
  GLUquadric	*quadric;

  quadric = gluNewQuadric();
  glPushMatrix();
  glTranslated(tmp->x, tmp->y , tmp->z);
  if (tmp == p->end)
    glColor4d(RED);
    //    glColor3d(1, 0, 0);
  else if (tmp == p->start)
    glColor4d(BLUE);
    //    glColor3d(0, 0, 1);
  else
    glColor4d(GREEN);
    //    glColor3d(0, 1, 0);
  gluQuadricDrawStyle(quadric, GLU_SILHOUETTE);
  gluSphere(quadric, S_SIZE, 40, 40);
  glPopMatrix();
  gluDeleteQuadric(quadric);
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
      if (tmp != root->next)
     	init_cylinder(tmp);
    }
}
