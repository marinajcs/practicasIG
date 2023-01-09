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

void setIlum(bool &I)
{
  if (I == false)
  {
    glEnable(GL_LIGHT0);
    I = true;
  }
  else
  {
    glDisable(GL_LIGHT0);
    I = false;
  }
}

bool Grua::move{true};
float Grua::ang0{0};
float Grua::ang1{0};
float Grua::longc{1};

bool setMovement(bool opt){
  if (opt == false)
  {
    Grua::setMove(true);
    return true;
  }
  else
  {
    Grua::setMove(false);
    return false;
  }
}

void modParamGrua(float a, float b, float c){
  Grua::modParam(a,b,c);
}
/*
void modAnimSpeed(float a, float b, float c){

}
*/

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


