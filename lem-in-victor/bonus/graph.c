/*
** main.c for Project-Master in /home/beau_v/Test/Lem-in/Lem-in
** 
** Made by beau_v
** Login   <victor.beau@epitech.eu>
** 
** Started on  Thu May  1 20:54:41 2014 beau_v
** Last update Fri May  2 01:05:08 2014 beau_v
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include "lem_in.h"
#include "graph.h"

static const GLfloat	light_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
static const GLfloat	light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
static const GLfloat	light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
static const GLfloat	light_position[] = {2.0f, 5.0f, 5.0f, 0.0f};
static const GLfloat	mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
static const GLfloat	mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
static const GLfloat	mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
static const GLfloat	high_shininess[] = {100.0f};

t_room		*root;
int		window;
float		lx = 0.0f;
float		lz = -1.0f;
float		x = 0.0f;
float		z = 5.0f;
float		red = 1.0f;
float		blue = 1.0f;
float		green = 1.0f;
float		angle = 0.0f;
float		deltaAngle = 0.0f;
int		xOrigin = -1;

static void	resize(int width, int height)
{
  float		ratio;

  if (height == 0)
    height = 1;
  ratio = width * 1.0 / height;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, width, height);
  gluPerspective(45.0f, ratio, 0.1f, 100.0f);
  glMatrixMode(GL_MODELVIEW);
}

static void	keyboard_events(int key, int xx, int yy)
{
  float	fraction;
  
  fraction = 0.4f;
  if (key == GLUT_KEY_LEFT)
    {
      angle -= 0.04f;
      lx = sin(angle);
      lz = -cos(angle);
    }
  if (key == GLUT_KEY_RIGHT)
    {
      angle += 0.04f;
      lx = sin(angle);
      lz = -cos(angle);
    }
  if (key == GLUT_KEY_UP)
    {
      x += lx * fraction;
      z += lz * fraction;
    }
  if (key == GLUT_KEY_DOWN)
    {
      x -= lx * fraction;
      z -= lz * fraction;
    }
}

void	keyboard_escape(unsigned char key, int x, int y)
{
  if (key == KEY_ESC)
    {
      glutDestroyWindow(window);
      exit (0);
    }
}

#define ROW	75

void		draw_cylindre(GLUquadric *quadric, t_room *tmp)
{
  int	i = 0;
  float	x_p;
  float	y_p;
  float	z_p;
  float	z;
  float	x;
  float	y;

  z_p = ((float)tmp->prev->z - (float)tmp->z) / ROW;
  x_p = ((float)tmp->prev->x - (float)tmp->x) / ROW;
  y_p = ((float)tmp->prev->y - (float)tmp->y) / ROW;
  x = (float)tmp->x;
  y = (float)tmp->y;
  z = (float)tmp->z;
  while (i++ < ROW)
    {
      glPushMatrix();
      glTranslated(x, y, z);
      glColor4d(165.0, 82.0, 76.0, 0.0);
      gluQuadricDrawStyle(quadric, GLU_SILHOUETTE);
      gluCylinder(quadric, 2, 2, 10, 20, 20);
      /*      gluSphere(quadric, 0.4, 20, 20);*/
      glPopMatrix();
      x = x + x_p;
      y = y + y_p;
      z = z + z_p;
    }
}

void		draw_sphere(int x, int y, int z, GLUquadric *quadric)
{
  glPushMatrix();
  glTranslated(x, y, z);
  glColor4d(0.0, 10.0, 1.0, 0.0);
  gluQuadricDrawStyle(quadric, GLU_SILHOUETTE);
  gluSphere(quadric, 1.5, 40, 40);
  glPopMatrix();
}

void		draw_quadrics()
{
  GLUquadric	*quadric;
  int		i = 0;
  float		x = 0;
  t_room	*tmp;
  int		prev_x;
  int		prev_y;
  int		flag;

  quadric = gluNewQuadric();
  tmp = root;
  while ((tmp = tmp->next) != root)
    {
      tmp->z = tmp->z ? my_rand(0, 10) : tmp->z;
      draw_sphere(tmp->x, tmp->y, tmp->z,  quadric);
      /*      if (tmp != root->next)
	      draw_cylindre(quadric, tmp);*/
    }

  /*  glPushMatrix();
  glTranslated(0, 1, 1.0);
  glColor4d(1.0, 1.0, 1.0, 1.0);
  gluQuadricDrawStyle(quadric, GLU_LINE);
  gluSphere(quadric, 10, 40, 40);
  glPopMatrix();

  glPushMatrix();
  glTranslated(1, 0.9, 0.0);
  glColor4d(1.0, 1.0, 1.0, 1.0);
  gluQuadricDrawStyle(quadric, GLU_LINE);
  gluCylinder(quadric, 2, 2, 10, 20, 20);
  glPopMatrix();*/

  gluDeleteQuadric(quadric);
}

static void	display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
  gluLookAt(x, 1.0f, z, x + lx, 1.0f, z + lz, 0.0f, 1.0f, 0.0f);

  draw_quadrics();

  glutSwapBuffers();
}

void		create_good_env()
{
  glClearColor(0, 0, 0, 0);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

void mouseMove(int x, int y)
{
  if (xOrigin >= 0)
    {
      deltaAngle = (x - xOrigin) * 0.001f;
      lx = sin(angle + deltaAngle);
      lz = -cos(angle + deltaAngle);
    }
}

void mouseButton(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
    {
      if (state == GLUT_UP)
	{
	  angle += deltaAngle;
	  xOrigin = -1;
	}
      else 
	xOrigin = x;
    }
}

int		make_coffee(int argc, char **argv, t_room *room, t_pos *pos)
{
  root = room;
  glutInit(&argc, argv);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(30, 30);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  window = glutCreateWindow("Lem-in");
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutIdleFunc(display);
  glutKeyboardFunc(keyboard_escape);
  glutSpecialFunc(keyboard_events);
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMove);
  create_good_env();
  glutMainLoop();
  return (EXIT_SUCCESS);
}
