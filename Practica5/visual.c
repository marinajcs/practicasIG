/*	Prácticas de Informática Gráfica

  Grupo C					Curso 2022-23

  Codigo base para la realización de las practicas de IG

  Estudiante: Marina Jun Carranza Sánchez

  Programa principal
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
modulo visual.c
    Inicialización de ventana X
    Transformación de visualización
    Transformación de proyección

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h> // Libreria de utilidades de OpenGL
#include "practicasIG.h"
//================================================ VARIABLES

/**

Angulos de rotacion de la camara.

**/

float view_rotx = 30, view_roty = 45;

extern float viewAngX, viewAngY;
extern std::vector<float> viewPos;

/**

Distancia de la cámara

**/

float D = 10;

/**

Tamaño de la ventana X

**/

float anchoVentana, altoVentana;

/** 	void setCamara()

Cambia los parámetros de la cámara en el modulo visual

**/
void setCamara(float ax, float ay, float d)
{
  viewAngX = ax;
  viewAngY = ay;

  D = d;
}

/** 	void transformacionVisualizacion()

Fija la transformacion de visualizacion en funcion de los angulos de rotacion view_rotx,
view_roty y el desplazamiento de la camara D.

La cámara mira al origen de coordenadas a una distancia D desde la posición angular view_rotx,
view_roty;

**/

void transformacionVisualizacion()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(0, 0, -D);

  glRotatef(viewAngX, 1.0, 0.0, 0.0);
  glRotatef(viewAngY, 0.0, 1.0, 0.0);

  viewPos[2] = D;
  glTranslatef(-viewPos[0],-viewPos[1],-viewPos[2]);
}

/**	void fijaProyeccion()

Fija la transformacion de proyeccion en funcion del tamaño de la ventana y del tipo de proyeccion

**/
void fijaProyeccion()
{
  float calto; // altura de la ventana corregida

  if (anchoVentana > 0)
    calto = altoVentana / anchoVentana;
  else
    calto = 1;

  glFrustum(-1, 1, -calto, calto, 1.5, 1500);

  glMatrixMode(GL_MODELVIEW);
  // A partir de este momento las transformaciones son de modelado.
  glLoadIdentity();
}

/**	void inicializaVentana(GLsizei ancho,GLsizei alto)

Inicializa el viewport para que ocupe toda la ventana X, y llama a fijaProyeccion.

**/

void inicializaVentana(GLsizei ancho, GLsizei alto)
{
  altoVentana = alto;
  anchoVentana = ancho;

  glViewport(0, 0, ancho, alto); // Establecemos el Viewport usando la nueva anchura y altura de la ventana X

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  fijaProyeccion(); // Cargamos la transformacion de proyeccion
}

void setViewType(int t)
{
  float ancho = anchoVentana;
  float alto = altoVentana;
  float fact = 1.0;

  if (t == 1)
  { // planta
    //glViewport(0, alto / 2, ancho / 2, alto / 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.25, 1.25, -1.25, 1.25, -20, 20);

    glRotatef(90, 1, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }
  else if (t == 2)
  { // alzado
    //glViewport(0, 0, ancho/2, alto/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-10,10, -10, 10, -100, 100);
/*
    glRotatef(60, 1, 0, 0);
    glRotatef(45,0,1, 0);
*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
  }
  else if (t == 3)
  { // perfil
    glViewport(ancho / 2, alto / 2, ancho / 2, alto / 2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-5 * fact, 5 * fact, -5 * fact, 5 * fact, -100, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }
}
