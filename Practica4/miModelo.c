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
modulo miModelo.c
    Representación de mis modelos
    Funciones de dibujo de mis figuras
    Funciones adicionales para cálculos necesarios

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <GL/glut.h> // Libreria de utilidades de OpenGL
#include "practicasIG.h"

using namespace std;

void setModo(int M)
{
  glPolygonMode(GL_FRONT_AND_BACK, M);
}

void drawLight1(){
  GLfloat light1_pos[4] = {-2.0, 2.0, -5.0, 0.0};
  GLfloat light1_amb[4] = {0.0, 0.2, 7.0, 1.0}; //blue ambient
  GLfloat light1_dif[4] = {1.0, 0.8, 1.0, 1.0};
  GLfloat light1_spec[4] = {1.0, 0.8, 1.0, 1.0};
  glLightfv(GL_LIGHT1, GL_POSITION, light1_pos);
  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_amb);
  //glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_dif);
  glLightfv(GL_LIGHT1, GL_SPECULAR, light1_spec);
  glShadeModel(GL_SMOOTH);
  //glMaterialfv(GL_FRONT, GL_AMBIENT, light1_amb);
  //glMaterialfv(GL_FRONT, GL_DIFFUSE, light1_dif);
  glMaterialfv(GL_FRONT, GL_SPECULAR, light1_spec);

}

void setIlum2(bool &I, int n)
{
  if (I == false)
  {
    if (n == 0)
      glEnable(GL_LIGHT0);
    else if (n == 1)
      glEnable(GL_LIGHT1);
      drawLight1();
    I = true;
  }
  else
  {
    if (n == 0)
      glDisable(GL_LIGHT0);
    else if (n==1)
      glDisable(GL_LIGHT1);
    I = false;
  }
}


Vector3D::Vector3D()
{
  X = 0;
  Y = 0;
  Z = 0;
}

Vector3D::Vector3D(float x, float y, float z)
{
  X = x;
  Y = y;
  Z = z;
}

Vector3D &Vector3D::operator=(const Vector3D &otro)
{
  X = otro.X;
  Y = otro.Y;
  Z = otro.Z;

  return *this;
}

Vector3D &Vector3D::operator+=(const Vector3D &otro)
{
  X += otro.X;
  Y += otro.Y;
  Z += otro.Z;

  return *this;
}

Vector3D crossProduct(Vector3D v1, Vector3D v2) // Producto vectorial
{
  float x, y, z;
  x = v1.Y * v2.Z - v2.Y * v1.Z;
  y = (v1.X * v2.Z - v2.X * v1.Z) * -1;
  z = v1.X * v2.Y - v2.X * v1.Y;

  Vector3D vect(x, y, z);
  return vect;
}

Vector3D calculaVector2Pts(Punto p1, Punto p2)
{
  float x, y, z;
  x = p2.x - p1.x;
  y = p2.y - p1.y;
  z = p2.z - p1.z;

  Vector3D vect(x, y, z);
  return vect;
}

Vector3D normalizaVect(Vector3D v)
{
  float modV = sqrt((v.X) * (v.X) + (v.Y) * (v.Y) + (v.Z) * (v.Z));
  if (modV != 1)
  {
    float xn, yn, zn;
    xn = v.X / modV;
    yn = v.Y / modV;
    zn = v.Z / modV;

    Vector3D norm(xn, yn, zn);

    return norm;
  }
  else
  {
    return v;
  }
}

Vector3D calculaNormal(Punto p1, Punto p2, Punto p3)
{
  Vector3D v1 = calculaVector2Pts(p1, p2);
  Vector3D v2 = calculaVector2Pts(p1, p3);
  Vector3D norm = normalizaVect(crossProduct(v1, v2));

  return norm;
}

float color[4] = {0.8, 0.0, 1, 1};
float color2[4] = {0.0, 1, 0.8, 1};

void Cubo::draw()
{
  Punto p1(lado, 0, 0);
  Punto p2(lado, 0, lado);
  Punto p3(0, 0, lado);
  Punto p4(0, 0, 0);
  Punto p5(lado, lado, 0);
  Punto p6(lado, lado, lado);
  Punto p7(0, lado, lado);
  Punto p8(0, lado, 0);

  glBegin(GL_QUADS);
  {
    glColor3f(color[0], color[1], color[2]);
    glNormal3f(-1.0, 0.0, 0.0);
    glVertex3f(p4.x, p4.y, p4.z);
    glVertex3f(p3.x, p3.y, p3.z);
    glVertex3f(p7.x, p7.y, p7.z);
    glVertex3f(p8.x, p8.y, p8.z);

    glNormal3f(1.0, 0.0, 0.0);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p5.x, p5.y, p5.z);
    glVertex3f(p6.x, p6.y, p6.z);
    glVertex3f(p2.x, p2.y, p2.z);
  }
  glEnd();
  glBegin(GL_QUAD_STRIP);
  {
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(p6.x, p6.y, p6.z);
    glVertex3f(p7.x, p7.y, p7.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glVertex3f(p3.x, p3.y, p3.z);

    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p4.x, p4.y, p4.z);

    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(p5.x, p5.y, p5.z);
    glVertex3f(p8.x, p8.y, p8.z);

    glNormal3f(0.0, 1.0, 0.0);
    glVertex3f(p6.x, p6.y, p6.z);
    glVertex3f(p7.x, p7.y, p7.z);
  }
  glEnd();
}

void Piramide::draw()
{
  Punto top(lado / 2, alto, lado / 2);
  Punto p1(lado, 0, 0);
  Punto p2(lado, 0, lado);
  Punto p3(0, 0, lado);
  Punto p4(0, 0, 0);

  glBegin(GL_QUADS); // cuadrado base
  {
    glColor3f(color2[0], color2[1], color2[2]);
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glVertex3f(p3.x, p3.y, p3.z);
    glVertex3f(p4.x, p4.y, p4.z);
  }
  glEnd();

  // trazaNormal(norm1, p1, top, p2);

  glBegin(GL_TRIANGLES); // caras triangulares
  {
    Vector3D norm1 = calculaNormal(p1, top, p2);
    glNormal3f(norm1.X, norm1.Y, norm1.Z);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(top.x, top.y, top.z);
    glVertex3f(p2.x, p2.y, p2.z);

    Vector3D norm2 = calculaNormal(p4, top, p1);
    glNormal3f(norm2.X, norm2.Y, norm2.Z);
    glVertex3f(p4.x, p4.y, p4.z); // p4
    glVertex3f(top.x, top.y, top.z);
    glVertex3f(p1.x, p1.y, p1.z); // p1

    Vector3D norm3 = calculaNormal(p3, top, p4);
    glNormal3f(norm3.X, norm3.Y, norm3.Z);
    glVertex3f(p3.x, p3.y, p3.z); // p3
    glVertex3f(top.x, top.y, top.z);
    glVertex3f(p4.x, p4.y, p4.z); // p4

    Vector3D norm4 = calculaNormal(p2, top, p3);
    glNormal3f(norm4.X, norm4.Y, norm4.Z);
    glVertex3f(p2.x, p2.y, p2.z); // p2
    glVertex3f(top.x, top.y, top.z);
    glVertex3f(p3.x, p3.y, p3.z); // p3
  }
  glEnd();
}

void PrismaPentagonal::draw()
{
  float pent[5][3], pent2[5][3];
  float ang;

  for (int i = 0; i < 5; i++) // cálculo de vértices del pentágono base
  {
    ang = i * ang_c; // para cada ángulo
    pent[i][0] = cos(ang);
    pent[i][1] = 0;
    pent[i][2] = sin(ang);
  }

  for (int i = 0; i < 5; i++) // vértices del pentágono superior
  {
    ang = i * ang_c;
    pent2[i][0] = cos(ang);
    pent2[i][1] = alto;
    pent2[i][2] = sin(ang);
  }

  glBegin(GL_TRIANGLE_STRIP); // pentágono base
  {
    glNormal3f(0.0, -1.0, 0.0);
    glVertex3fv(pent[0]);
    glVertex3fv(pent[2]);
    glVertex3fv(pent[3]);

    glVertex3fv(pent[1]);
    glVertex3fv(pent[3]);
    glVertex3fv(pent[4]);

    glVertex3fv(pent[2]);
    glVertex3fv(pent[4]);
    glVertex3fv(pent[0]);

    glVertex3fv(pent[3]);
    glVertex3fv(pent[0]);
    glVertex3fv(pent[1]);

    glVertex3fv(pent[4]);
    glVertex3fv(pent[1]);
    glVertex3fv(pent[2]);
  }
  glEnd();

  glBegin(GL_TRIANGLE_STRIP); // pentágono superior
  {
    glNormal3f(0.0, 1.0, 0.0);
    glVertex3fv(pent2[0]);
    glVertex3fv(pent2[3]);
    glVertex3fv(pent2[2]);

    glVertex3fv(pent2[1]);
    glVertex3fv(pent2[4]);
    glVertex3fv(pent2[3]);

    glVertex3fv(pent2[2]);
    glVertex3fv(pent2[0]);
    glVertex3fv(pent2[4]);

    glVertex3fv(pent2[3]);
    glVertex3fv(pent2[1]);
    glVertex3fv(pent2[0]);

    glVertex3fv(pent2[4]);
    glVertex3fv(pent2[2]);
    glVertex3fv(pent2[1]);
  }
  glEnd();

  glBegin(GL_QUADS); // cálculo de caras rectangulares laterales
  {
    Punto p11(pent[0][0], pent[0][1], pent[0][2]);
    Punto p12(pent[1][0], pent[1][1], pent[1][2]);
    Punto p13(pent[2][0], pent[2][1], pent[2][2]);
    Punto p14(pent[3][0], pent[3][1], pent[3][2]);
    Punto p15(pent[4][0], pent[4][1], pent[4][2]);

    Punto p21(pent2[0][0], pent2[0][1], pent2[0][2]);
    Punto p22(pent2[1][0], pent2[1][1], pent2[1][2]);
    Punto p23(pent2[2][0], pent2[2][1], pent2[2][2]);
    Punto p24(pent2[3][0], pent2[3][1], pent2[3][2]);
    Punto p25(pent2[4][0], pent2[4][1], pent2[4][2]);

    Vector3D n1 = calculaNormal(p11, p21, p22);
    glNormal3f(n1.X, n1.Y, n1.Z);
    glVertex3fv(pent[0]);
    glVertex3fv(pent2[0]);
    glVertex3fv(pent2[1]);
    glVertex3fv(pent[1]);

    Vector3D n2 = calculaNormal(p12, p22, p23);
    glNormal3f(n2.X, n2.Y, n2.Z);
    glVertex3fv(pent[1]);
    glVertex3fv(pent2[1]);
    glVertex3fv(pent2[2]);
    glVertex3fv(pent[2]);

    Vector3D n3 = calculaNormal(p13, p23, p24);
    glNormal3f(n3.X, n3.Y, n3.Z);
    glVertex3fv(pent[2]);
    glVertex3fv(pent2[2]);
    glVertex3fv(pent2[3]);
    glVertex3fv(pent[3]);

    Vector3D n4 = calculaNormal(p14, p24, p25);
    glNormal3f(n4.X, n4.Y, n4.Z);
    glVertex3fv(pent[3]);
    glVertex3fv(pent2[3]);
    glVertex3fv(pent2[4]);
    glVertex3fv(pent[4]);

    Vector3D n5 = calculaNormal(p15, p25, p21);
    glNormal3f(n5.X, n5.Y, n5.Z);
    glVertex3fv(pent[4]);
    glVertex3fv(pent2[4]);
    glVertex3fv(pent2[0]);
    glVertex3fv(pent[0]);
  }
  glEnd();
}

void Dado::draw()
{
  Punto p1(lado, 0, 0);
  Punto p2(lado, 0, lado);
  Punto p3(0, 0, lado);
  Punto p4(0, 0, 0);
  Punto p5(lado, lado, 0);
  Punto p6(lado, lado, lado);
  Punto p7(0, lado, lado);
  Punto p8(0, lado, 0);
  float white[4] = {1.0, 1.0, 1.0, 1.0};

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texId);

  glBegin(GL_QUADS);
  {
    //izq, 4
    glNormal3f(-1.0, 0.0, 0.0);
    glTexCoord2f(0.75, 1.0);
    glVertex3f(p4.x, p4.y, p4.z);
    glTexCoord2f(0.75, 0.75);
    glVertex3f(p3.x, p3.y, p3.z);
    glTexCoord2f(0.5, 0.75);
    glVertex3f(p7.x, p7.y, p7.z);
    glTexCoord2f(0.5, 1.0);
    glVertex3f(p8.x, p8.y, p8.z);

    //dch, 3
    glNormal3f(1.0, 0.0, 0.0);
    glTexCoord2f(0.75, 0.25);
    glVertex3f(p1.x, p1.y, p1.z);
    glTexCoord2f(0.5, 0.25);
    glVertex3f(p5.x, p5.y, p5.z);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(p6.x, p6.y, p6.z);
    glTexCoord2f(0.75, 0.5);
    glVertex3f(p2.x, p2.y, p2.z);

    //frente, 2
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(p6.x, p6.y, p6.z);
    glTexCoord2f(0.5, 0.75);
    glVertex3f(p7.x, p7.y, p7.z);
    glTexCoord2f(0.75, 0.75);
    glVertex3f(p3.x, p3.y, p3.z);
    glTexCoord2f(0.75, 0.5);
    glVertex3f(p2.x, p2.y, p2.z);

    //envés, 5
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(p1.x, p1.y, p1.z);
    glTexCoord2f(0.0, 0.75);
    glVertex3f(p4.x, p4.y, p4.z);
    glTexCoord2f(0.25, 0.75);
    glVertex3f(p8.x, p8.y, p8.z);
    glTexCoord2f(0.25, 0.5);
    glVertex3f(p5.x, p5.y, p5.z);

    //superior, 1
    glNormal3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.25, 0.5);
    glVertex3f(p5.x, p5.y, p5.z);
    glTexCoord2f(0.25, 0.75);
    glVertex3f(p8.x, p8.y, p8.z);
    glTexCoord2f(0.5, 0.75);
    glVertex3f(p7.x, p7.y, p7.z);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(p6.x, p6.y, p6.z);
    
    //inferior, 6
    glNormal3f(0.0, -1.0, 0.0);
    glTexCoord2f(1.0, 0.5);
    glVertex3f(p1.x, p1.y, p1.z);
    glTexCoord2f(0.75, 0.5);
    glVertex3f(p2.x, p2.y, p2.z);
    glTexCoord2f(0.75, 0.75);
    glVertex3f(p3.x, p3.y, p3.z);
    glTexCoord2f(1.0, 0.75);
    glVertex3f(p4.x, p4.y, p4.z);
  }
  glEnd();
  glDisable(GL_TEXTURE_2D);

}


