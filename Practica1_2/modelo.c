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
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> // Libreria de utilidades de OpenGL
#include "practicasIG.h"

class Ejes : Objeto3D
{
public:
  float longitud = 30;
  // Dibuja el objeto
  void draw()
  {
    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    {
      glColor3f(0, 1, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(0, longitud, 0);

      glColor3f(1, 0, 0);
      glVertex3f(0, 0, 0);
      glVertex3f(longitud, 0, 0);

      glColor3f(0, 0, 1);
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, longitud);
    }
    glEnd();
    glEnable(GL_LIGHTING);
  }
};

Ejes ejesCoordenadas;

Cubo cubo;
Piramide piramide;
PrismaPentagonal pentagon;
char filename1[] = "plys/beethoven.ply";
char filename2[] = "plys/big_dodge.ply";
char filename3[] = "plys/perfil.ply";

ObjetoPly beethoven(filename1);
ObjetoPly bigdodge(filename2);
Revolucion peon(filename3);

/**	void initModel()

Inicializa el modelo y las variables globales

**/
void initModel()
{
  cubo.lado = 1;
  piramide.lado = 1;
  piramide.alto = 2;
  pentagon.ang_c = 1.25664; // en radianes, 72º ángulo central
  pentagon.alto = 1.5;
}

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja(void)
{
  static GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0}; // Posicion de la fuente de luz

  float color[4] = {0.8, 0.0, 1, 1};
  float color2[4] = {0.0, 1, 0.8, 1};
  float color3[4] = {1, 0.7, 0.5, 1};
  float color4[4] = {0.9, 0.9, 0.9, 0.9};
  float color5[4] = {0.15, 0.15, 0.15, 0.15};

  glPushMatrix(); // Apila la transformacion geometrica actual

  glClearColor(0.0, 0.0, 0.0, 1.0); // Fija el color de fondo a negro

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion(); // Carga transformacion de visualizacion

  glLightfv(GL_LIGHT0, GL_POSITION, pos); // Declaracion de luz. Colocada aqui esta fija en la escena

  ejesCoordenadas.draw(); // Dibuja los ejes

/*
//-------------------DEFENSA PRÁCTICA 1-------------------

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

  cubo.draw();

  glTranslatef(2, 0, 0);

  cubo.draw();

  glTranslatef(2, 0, 0);

  cubo.draw();

  glTranslatef(2, 0, 0);

  cubo.draw();

  glTranslatef(2, 0, 0);

  cubo.draw();

  glTranslatef(2, 0, 0);

  cubo.draw();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);

  glTranslatef(-10, 1, 0);

  piramide.draw();

  glTranslatef(2, 0, 0);

  piramide.draw();

  glTranslatef(2, 0, 0);

  piramide.draw();

  glTranslatef(2, 0, 0);

  piramide.draw();

  glTranslatef(2, 0, 0);

  piramide.draw();

  glTranslatef(2, 0, 0);

  piramide.draw();
*/

//----------------------DEFENSA PRÁCTICA 2----------------------------------

glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color5);

  peon.setDrawOption(1);

  peon.draw();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color4);

  glTranslatef(3, 0, 0);

  peon.setDrawOption(0);

  peon.draw();

/*
  //____________________PRÁCTICA-1_______________________

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

  cubo.draw();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);

  glTranslatef(2, 0, 0);

  piramide.draw();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);

  glTranslatef(3,0,2);

  pentagon.draw();

  //------------------------------------------------------
*/

  //____________________PRÁCTICA-2________________________

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

  glTranslatef(-10,2,3);

  beethoven.setDrawOption(1);

  beethoven.draw();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);

  glTranslatef(20,0,1);

  bigdodge.draw();

  //--------------------------------------------------

  glPointSize(6);

  glPopMatrix(); // Desapila la transformacion geometrica

  glutSwapBuffers(); // Intercambia el buffer de dibujo y visualizacion
}

/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle(int v)
{
  glutPostRedisplay();        // Redibuja
  glutTimerFunc(30, idle, 0); // Vuelve a activarse dentro de 30 ms
}
