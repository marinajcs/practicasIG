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
modulo interaccion.c
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

void ColorSeleccion(int i, int comp)
{
  unsigned char r = (i & 0xFF);
  unsigned char g = (comp & 0xFF);
  glColor3ub(r, g, 0);
}

void pick(int x, int y)
{
  GLint viewport[4];
  unsigned char px[4];

  glGetIntegerv(GL_VIEWPORT, viewport);
  glDisable(GL_DITHER);
  glDisable(GL_LIGHTING);

  dibujoEscena();

  glEnable(GL_LIGHTING);
  glEnable(GL_DITHER);
  glFlush();
  glFinish();

  glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, px);

  printf("Pixel color: %d, %d, %d:", px[0], px[1], px[2]);

  glutPostRedisplay();
}

void Objeto3D::setTexture(const char *img_name)
{

  imgptr = LeerArchivoJPEG(img_name, ancho, alto);
}

void Objeto3D::loadTexture()
{
  glGenTextures(1, &texId);
  glBindTexture(GL_TEXTURE_2D, texId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  // transferir datos a GPU
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ancho, alto, 0, GL_RGB, GL_UNSIGNED_BYTE, imgptr);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texId);
}

void Objeto3D::freeTexture()
{
  glDeleteTextures(1, &texId);
}

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

Cubo *cubo;
char filename2[] = "plys/big_dodge.ply";
char filename3[] = "plys/perfil.ply";

char imgname1[] = "imgs/dado.jpg";
char cantext[] = "imgs/lata.jpg";
char tapainf[] = "imgs/tapainf.jpg";
char tapasup[] = "imgs/tapasup.jpg";
char filecan[] = "plys/lata-pcue.ply";
char filecantop[] = "plys/lata-psup.ply";
char filecanbot[] = "plys/lata-pinf.ply";

ObjetoPly *bigdodge;
Revolucion *peon;
Grua grua;

Dado *dado;
Revolucion *lata;
Revolucion *lata_inf;
Revolucion *lata_sup;

/**	void initModel()

Inicializa el modelo y las variables globales

**/
void initModel()
{
  cubo = new Cubo();
  cubo->lado = 1;

  bigdodge = new ObjetoPly(filename2);
  peon = new Revolucion(filename3);

  dado = new Dado();
  dado->lado = 1;
  dado->setTexture(imgname1);
  dado->loadTexture();

  lata = new Revolucion(filecan);
  lata->setTexture(cantext);
  lata->loadTexture();
  lata_inf = new Revolucion(filecanbot);
  lata_inf->setTexture(tapainf);
  lata_inf->loadTexture();
  lata_sup = new Revolucion(filecantop);
  lata_sup->setTexture(tapasup);
  lata_sup->loadTexture();
}

/**	void drawLight0( void )

Procedimiento de creación de fuente de luz con esfera

**/
void drawLight0()
{
  float color1[4] = {1.0, 1.0, 0.0, 1};
  float color2[4] = {0.0, 0.2, 1.0, 1};
  GLfloat light0_pos[4] = {5.0, 5.0, 10.0, 0.0};
  GLfloat light1_pos[4] = {-2.0, 2.0, -5.0, 0.0};

  glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
  // al no especificar más parámetros, toma los que asigna por defecto
  /*
    GLUquadric *quad1, *quad2;
    quad1 = gluNewQuadric();
    quad2 = gluNewQuadric();
  */
  glPushMatrix();
  {
    // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color1);
    glTranslatef(light0_pos[0], light0_pos[1], light0_pos[2]);
    // gluSphere(quad1, 0.25, 40, 40);
  }
  glPopMatrix();
  glPushMatrix();
  {
    // glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);
    glTranslatef(light1_pos[0], light1_pos[1], light1_pos[2]);
    // gluSphere(quad2, 0.25, 40, 40);
  }
  glPopMatrix();
}

void vistaOrtogonal()
{
  // glView
}

void dibujoEscena()
{
  GLfloat pos[4] = {5.0, 5.0, 10.0, 0.0};
  float color[4] = {0.8, 0.0, 9, 0.5};
  float color2[4] = {0.0, 1, 0.8, 1};
  float color3[4] = {1, 0.7, 0.5, 1};
  float color4[4] = {0.9, 0.9, 0.9, 0.9};
  float color5[4] = {0.15, 0.15, 0.15, 0.15};
  float color6[4] = {0.0, 1.0, 0.0, 0.0};
  float none[] = {0.0, 0.0, 0.0, 0.0};
  float mat_dif[] = {0.2, 0.5, 0.8, 1.0};
  float mat_spec[] = {1.0, 1.0, 1.0, 1.0};
  float mat_amb[] = {0.7, 0.7, 0.7, 1.0};

  glPushMatrix(); // Apila la transformacion geometrica actual

  glClearColor(0.0, 0.0, 0.0, 1.0); // Fija el color de fondo a negro

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion(); // Carga transformacion de visualizacion

  glLightfv(GL_LIGHT0, GL_POSITION, pos); // Declaracion de luz. Colocada aqui esta fija en la escena

  // drawLight0();

  ejesCoordenadas.draw(); // Dibuja los ejes

  //______________________PRÁCTICA-5_____________________

  glTranslatef(0, 0, 3);

  dado->draw();

  glTranslatef(0, 0, -3);

  lata_inf->setDrawOption(1);
  lata_sup->setDrawOption(1);

  glRotatef(120, 0, 1, 0);

  lata_inf->draw();
  lata_sup->drawTexture();
  lata->drawTexture();

  glRotatef(-120, 0, 1, 0);

  glTranslatef(12, 0, 0);

  glPushMatrix();
  bigdodge->materialSettings(0, mat_dif); // diffuse only
  bigdodge->materialSettings(1, none);
  bigdodge->materialSettings(2, none);
  glPopMatrix();

  bigdodge->draw();

  glTranslatef(0, 0, 5);

  glPushMatrix();
  peon->materialSettings(2, color6);
  glPopMatrix();
  peon->setDrawOption(1);
  peon->draw();

  glTranslatef(5, 0, -5);
  grua.setMove(false);
  grua.draw();

  glTranslatef(-10, 0, 0);

  //------------------------------------------------------

  glPointSize(6);

  glPopMatrix(); // Desapila la transformacion geometrica
}

/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/
void Dibuja(void)
{
  dibujoEscena();

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
