/*
** draw.c for Project-Master in /home/beau_v/Test/FULL_LEM/lem-in/FINAL/src/GRAPH
** 
** Made by beau_v
** Login   <victor.beau@epitech.eu>
** 
** Started on  Sun May  4 23:13:26 2014 beau_v
** Last update Sun May  4 23:16:36 2014 beau_v
*/

#include <GL/glut.h>
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

void		create_good_env()
{
  glClearColor(0, 0, 0, 1);
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

void		reshape(int w, int h)
{
  if (h == 0)
    h = 1;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
  glMatrixMode(GL_MODELVIEW);
}

void		init_camera_pos()
{
  int		i;

  i = 0;
  while (i++ < 60)
    zoom(2);
  i = 0;
  while (i++ < 8)
    rotate(3);
  i = 0;
  while (i++ < 6)
    rotate(2);
}
