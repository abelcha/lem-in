/*
** graph.c for Project-Master in /home/beau_v/Test/Rendu_lem_in/lem-in/FINAL/src/GRAPH
** 
** Made by beau_v
** Login   <victor.beau@epitech.eu>
** 
** Started on  Sun May  4 02:15:54 2014 beau_v
** Last update Sun May  4 20:09:17 2014 beau_v
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

t_room		*root;
t_pos		*p;

float	x_timer = 0.0;
float	y_timer = 0.0;
float	z_timer = 0.0;
float	x_ptimer = 0.0;
float	y_ptimer = 0.0;
float	z_ptimer = 0.0;
int	animating = 0;
int	yolo = 42;

void	try_dis_shit(t_coord *coord, GLUquadric	*sphere_ant)
{
  glPushMatrix();

  glTranslated(x_timer, y_timer, z_timer);

  glRotatef(180, coord->a1, coord->a2, coord->a3);

  glColor4d(165.0, 82.0, 76.0, 0.0);

  gluSphere(sphere_ant, 0.3, 20, 20);

  glPopMatrix();
}

void	draw_test(t_coord *coord, t_room *r1, t_room *r2)
{
  int	i = 0;
  GLUquadric	*sphere_ant;

  sphere_ant = gluNewQuadric();
  if (yolo == 42)
    {
      printf(" initialise lol\n");
      x_timer = (float)r1->x;
      y_timer = (float)r1->y;
      z_timer = (float)r1->z;
      x_ptimer = ((float)r2->x - (float)r1->x) / ROW;
      y_ptimer = ((float)r2->y - (float)r1->y) / ROW;
      z_ptimer = ((float)r2->z - (float)r1->z) / ROW;
      yolo = 0;
    }
  //  printf("TRY ME\n");
  try_dis_shit(coord, sphere_ant);
  //printf("FML\n");
  gluDeleteQuadric(sphere_ant);
}

void update(int value)
{
  static int cpt = 0;

  printf("x_timer : %lf\n", x_timer);
  printf("y_timer : %lf\n", y_timer);
  printf("z_timer : %lf\n", z_timer);
  printf("x_ptimer : %lf\n", x_ptimer);
  printf("y_ptimer : %lf\n", y_ptimer);
  printf("z_ptimer : %lf\n", z_ptimer);
  if (++cpt < ROW + 1)
    {
      printf("ca passe dans ta mere\n");
      x_timer = x_timer + x_ptimer;
      y_timer = y_timer + y_ptimer;
      z_timer = z_timer + z_ptimer;
    }
  else
    {
      printf("yolo remis a 42\n");
      yolo = 42;
      cpt = 0;
    }
  printf("x_timer_up : %lf\n", x_timer);
  printf("x_ptimer_up : %lf\n", x_ptimer);
  glutTimerFunc(5, update, 0);
  glutPostRedisplay();
}

static void	reshape(int w, int h)
{
  if (h == 0)
    h = 1;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
  glMatrixMode(GL_MODELVIEW);
}

static void	create_good_env()
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

static void	display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  camera();
  create_good_env();
  draw_quadrics(root, p);

  draw_ants(p->start, p->end);

  glFlush();

  glutSwapBuffers();
  glutPostRedisplay();
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

int		make_coffee(int argc, char **argv, t_room *room, t_pos *pos)
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
