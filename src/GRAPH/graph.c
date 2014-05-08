/*
** graph.c for Project-Master in /home/beau_v/Test/Rendu_lem_in/lem-in/FINAL/src/GRAPH
** 
** Made by beau_v
** Login   <victor.beau@epitech.eu>
** 
** Started on  Sun May  4 02:15:54 2014 beau_v
** Last update Mon May  5 09:39:01 2014 chalie_a
*/

#include <GL/glut.h>
#include <math.h>
#include "lem_in.h"
#include "graph.h"

extern t_move		*move;
t_room			*root;
t_pos			*p;
float			x_timer = 0.0;
float			y_timer = 0.0;
float			z_timer = 0.0;
float			x_ptimer = 0.0;
float			y_ptimer = 0.0;
float			z_ptimer = 0.0;
int			timer_flag = 42;

void			make_ants(t_coord *coord)
{
  glPushMatrix();
  glTranslated(x_timer, y_timer, z_timer);
  glRotatef(180, coord->a1, coord->a2, coord->a3);
  glColor4d(165.0, 82.0, 76.0, 0.0);
  glutWireSphere(0.3, 12, 12);
  glPopMatrix();
}

void			draw_test(t_coord *coord, t_room *r1, t_room *r2)
{
  if (timer_flag == 42)
    {
      x_timer = (float)r1->x;
      y_timer = (float)r1->y;
      z_timer = (float)r1->z;
      x_ptimer = ((float)r2->x - (float)r1->x) / ROW;
      y_ptimer = ((float)r2->y - (float)r1->y) / ROW;
      z_ptimer = ((float)r2->z - (float)r1->z) / ROW;
      timer_flag = 0;
    }
  make_ants(coord);
}

void			 update(int value)
{
  static int		cpt = 0;

  if (++cpt < ROW + 1)
    {
      x_timer = x_timer + x_ptimer;
      y_timer = y_timer + y_ptimer;
      z_timer = z_timer + z_ptimer;
    }
  else
    {
      timer_flag = 42;
      cpt = 0;
    }
  glutTimerFunc(5, update, 0);
  glutPostRedisplay();
}

static void		display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  camera();
  create_good_env();
  draw_quadrics(root, p);
    if (timer_flag == 42)
    if (!move->next->r1)
      exit(0);
    else
    move = move->next;
  draw_ants(move->r1, move->r2);
  glFlush();
  glutSwapBuffers();
  glutPostRedisplay();
}

int			make_coffee(int argc, char **argv, t_room *room, t_pos *pos)
{
  root = room;
  p = pos;
  glutInit(&argc, argv);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition(100, 100);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow("Lem-in");
  glutDisplayFunc(display);
  init_camera_pos();
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(5, update, 0);
  glutMainLoop();
  return (EXIT_SUCCESS);
}
