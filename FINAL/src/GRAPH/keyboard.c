/*
** keyboard.c for Project-Master in /home/beau_v/Test/Rendu_lem_in/lem-in/FINAL/src/GRAPH
** 
** Made by beau_v
** Login   <victor.beau@epitech.eu>
** 
** Started on  Sun May  4 02:01:14 2014 beau_v
** Last update Sun May  4 03:34:12 2014 beau_v
*/

#include <GL/glut.h>
#include <math.h>
#include "lem_in.h"
#include "graph.h"

float		xpos = 0;
float		ypos = 0;
float		zpos = 0;
float		xrot = 0;
float		yrot = 0;

void		camera(void)
{
  glRotatef(xrot, 1.0, 0.0, 0.0);
  glRotatef(yrot, 0.0, 1.0, 0.0);
  glTranslated(-xpos, -ypos, -zpos);
}

void		zoom(int flag)
{
  float		xrotrad;
  float		yrotrad;

  if (flag == 1)
    {
      yrotrad = (yrot / 180 * 3.141592654f);
      xrotrad = (xrot / 180 * 3.141592654f); 
      xpos = xpos + sin(yrotrad);
      zpos = zpos - cos(yrotrad);
      ypos = ypos - sin(xrotrad);
    }
  else if (flag == 2)
    {
      yrotrad = (yrot / 180 * 3.141592654f);
      xrotrad = (xrot / 180 * 3.141592654f); 
      xpos = xpos - sin(yrotrad);
      zpos = zpos + cos(yrotrad);
      ypos = ypos + sin(xrotrad);
    }
}

void		rotate(int flag)
{
  if (flag == 1)
    {
      xrot += 1;
      if (xrot > 360)
	xrot -= 360;
    }
  else if (flag == 2)
    {
      xrot -= 1;
      if (xrot < -360)
	xrot += 360;
    }
  else if (flag == 3)
    {
      yrot += 1;
      if (yrot > 360)
	yrot -= 360;
    }
  else if (flag == 4)
    {
      yrot -= 1;
      if (yrot < -360)
	yrot += 360;
    }
}

void		keyboard(unsigned char key, int x, int y)
{
  if (key == 's')
    rotate(1);
  if (key == 'z')
    rotate(2);
  if (key == 'd')
    rotate(3);
  if (key == 'q')
    rotate(4);
  if (key == 'e')
    zoom(1);
  if (key == 'a')
    zoom(2);
  if (key == KEY_ESC)
    exit (0);
}
