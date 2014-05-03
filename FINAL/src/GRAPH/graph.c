#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
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

# define ROW	40
# define MOD    40


t_room		*root;
int		window;
float		xpos = 0;
float		ypos = 0;
float		zpos = 0;
float		xrot = 0;
float		yrot = 0;
float		angle = 0.0;

void camera(void)
{
  glRotatef(xrot, 1.0, 0.0, 0.0);
  glRotatef(yrot, 0.0, 1.0, 0.0);
  glTranslated(-xpos, -ypos, -zpos);
}

void reshape(int w, int h)
{
  if (h == 0)
    h = 1;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
  glMatrixMode(GL_MODELVIEW);
}

void		draw_cylindre(GLUquadric *quadric, t_room *tmp)
{
  int	i = 0;
  float	x_p;
  float	y_p;
  float	z_p;
  float	z;
  float	x;
  float	y;
 
  /* renderCy((float)tmp->x, (float)tmp->y, (float)tmp->z, (float)tmp->prev->x, 
	   (float)tmp->prev->y, (float)tmp->prev->z, 100, 100);
	   return ;*/
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
      gluQuadricDrawStyle(quadric, GLU_POINT);
      //gluCylinder(quadric, 2, 2, 10, 20, 20);
      //gluDisk(quadric, 0.1, 0.3, 10, 10);
      // gluSphere(quadric, 0.1, 10, 10);
      gluCylinder(quadric, 1, 2, 1, 2, 20);
      glPopMatrix();
      x = x + x_p;
      y = y + y_p;
      z = z + z_p;
    }
}

void		draw_sphere(int x, int y, int z, GLUquadric *quadric)
{
  glPushMatrix();
  glTranslated(x, y , z);
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
      tmp->x %= MOD;
      tmp->y %= MOD;
      tmp->z = tmp->z ? my_rand(0, 42) : tmp->z;
      draw_sphere(tmp->x, tmp->y, tmp->z,  quadric);
      if (tmp != root->next)
	draw_cylindre(quadric, tmp);
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


static void	display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  camera();
  create_good_env();
  draw_quadrics();

  glutSwapBuffers();
  angle++;
}

void	keyboard(unsigned char key, int x, int y)
{
  float xrotrad;
  float yrotrad;

  if (key == 's')
    {
      xrot += 1;
      if (xrot >360)
	xrot -= 360;
    }
  if (key == 'z')
    {
      xrot -= 1;
      if (xrot < -360)
	xrot += 360;
    }
  if (key == 'e')
    {
      yrotrad = (yrot / 180 * 3.141592654f);
      xrotrad = (xrot / 180 * 3.141592654f); 
      xpos = xpos + sin(yrotrad);
      zpos = zpos - cos(yrotrad);
      ypos = ypos - sin(xrotrad);
    }
  if (key == 'a')
    {
      yrotrad = (yrot / 180 * 3.141592654f);
      xrotrad = (xrot / 180 * 3.141592654f); 
      xpos = xpos - sin(yrotrad);
      zpos = zpos + cos(yrotrad);
      ypos = ypos + sin(xrotrad);
    }
  if (key == 'd')
    {
      yrot += 1;
      if (yrot > 360)
	yrot -= 360;
    }
  if (key == 'q')
    {
      yrot -= 1;
      if (yrot < -360)
	yrot += 360;
    }
  if (key == 27)
    {
      exit(0);
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
  glutIdleFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  return (EXIT_SUCCESS);
}
