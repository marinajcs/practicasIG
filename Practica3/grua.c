/*	Prácticas de Informática Gráfica

  Grupo C					Curso 2022-23

  Codigo base para la realización de las practicas de IG

  Estudiante: Marina Jun Carranza Sánchez

=======================================================
  G. Arroyo, J.C. Torres
  Dpto. Lenguajes y Sistemas Informticos
  (Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details
 http://www.gnu.org/copyleft/gpl.html

=======================================================/
modulo grua.c

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <GL/glut.h> // Libreria de utilidades de OpenGL
#include "practicasIG.h"

using namespace std;

float orange[4] = {1.0, 0.5, 0.0, 0.0};
float red[4] = {1.0, 0.0, 0.0, 0.0};
float gray[4] = {0.6, 0.6, 0.6, 0.6};
float brown[4] = {0.3, 0.0, 0.0, 0.1};

void Grua::modParam(float a0, float a1, float lc)
{
  ang0 += a0;
  ang1 += a1;

  if (a0 != 0 && ang0 > 360)
  {
    ang0 -= 360;
  }
  else if (a0 != 0 && ang0 < 0)
  {
    ang0 += 360;
  }

  if (a0 != 0 && ang1 > 360)
  {
    ang1 -= 360;
  }
  else if (a0 != 0 && ang1 < 0)
  {
    ang1 += 360;
  }

  if ((longc + lc) < 10 && (longc + lc) >= 0)
  {
    longc += lc;
  }
}

void Grua::setMove(bool opt)
{
  move = opt;
}

void Grua::draw()
{
  if (move)
  {
    modParam(1, 5, 0);

    if (longc > 10)
      sube = true;

    if (longc < 1)
      sube = false;

    if (sube)
      longc -= 0.1;
    else
      longc += 0.1;
  }
  GruaCompleta();
}

void Grua::GruaCompleta()
{
  glPushMatrix();
  Estructura();
  glPopMatrix();

  glTranslatef(0, 10.5, 0);
  glRotatef(ang0, 0, 1, 0);

  glPushMatrix();
  BrazoCompleto();
  glPopMatrix();
}

void Grua::Estructura()
{
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orange);

  glRotatef(-90, 1, 0, 0);

  creaEstructura(0, 0, 0, 0, 0, 10, 1, 1, 10);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);

  paralelepipedo(0, 0, 10, 0, 0, 10.5, 1, 1);
}

void Grua::BrazoCompleto()
{
  glPushMatrix();

  Torre();

  glPopMatrix();

  glTranslatef(0, 0, 9.5);

  glPushMatrix();

  BrazoLargo();

  glPopMatrix();

  glTranslatef(0, 0.2, -15);

  glPushMatrix();
  BrazoCorto();
  glPopMatrix();
}

void Grua::Torre()
{
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orange);

  glRotatef(-90, 1, 0, 0);

  creaTorre(0, 0, 0, 0, 0, 3, 1, 1, 3);
}

void Grua::BrazoLargo()
{
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orange);

  glPushMatrix();
  glRotatef(-180, 0, 1, 0);
  creaBrazo(0, 0, 0, 0, 0, 9, 1, 9);
  glPopMatrix();

  glRotatef(90, 1, 0, 0);
  glTranslatef(0, -0.5, 0);

  glPushMatrix();
  Gancho();
  glPopMatrix();
}

void Grua::BrazoCorto()
{
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, orange);
  glRotatef(90, 0, 0, 1);
  creaEstructura(0, 0, 0, 0, 0, 5, 1, 0.4, 5);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
  glRotatef(-90, 0, 1, 0);
  glTranslatef(0.5, 0, 0.2);
  paralelepipedo(0, 0, 0, 0, 0, 0.7, 1, 1);
}

void Grua::Gancho()
{
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
  paralelepipedo(0, 0, 0, 0, 0, 0.2, 1, 1);

  glPushMatrix();
  Cuerda();
  glPopMatrix();
}

void Grua::Cuerda()
{
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, brown);
  glPushMatrix();
  glScalef(1, 1, longc);

  cilindro(0, 0, 0, 0, 0, 1, 0.1);
  glPopMatrix();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
  glTranslatef(0, 0, (longc - 1));
  glRotatef(ang1, 0, 0, 1);

  glPushMatrix();
  glRotatef(-90, 1, 0, 0);
  glTranslatef(0, -1, 0);
  creaGancho(0, 0, 0, 1);
  glPopMatrix();
}
