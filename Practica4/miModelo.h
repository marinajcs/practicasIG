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
  modulo miModelo.h

*/
#include <vector>
#include <string.h>

struct Punto
{
  float x, y, z;

  Punto(){
    x = 0;
    y = 0;
    z = 0;
  }

  Punto(float c1, float c2, float c3)
  {
    x = c1;
    y = c2;
    z = c3;
  }
};

struct PuntoInt
{
  int a, b, c;

  PuntoInt(){
    a = 0;
    b = 0;
    c = 0;
  }

  PuntoInt(int c1, int c2, int c3)
  {
    a = c1;
    b = c2;
    c = c3;
  }
};

/**
	Función que establece el modo de visualización (puntos, líneas y relleno)
**/
void setModo(int M);

void drawLight1();

/**
	Función que (des)activa la iluminación
**/
void setIlum2(bool &I, int n);


class Vector3D
{
public:
  float X, Y, Z;

  Vector3D();

  Vector3D(float x, float y, float z);

  Vector3D &operator=(const Vector3D &otro);

  Vector3D &operator+=(const Vector3D &otro);
};

/**
	Funcion de cálculo del producto vectorial
**/
Vector3D crossProduct(Vector3D v1, Vector3D v2);

/**
	Funcion de cálculo del vector formado por dos puntos
**/
Vector3D calculaVector2Pts(Punto p1, Punto p2);

/**
	Funcion de normalización de un vector
**/
Vector3D normalizaVect(Vector3D v);

/**
	Funcion de cálculo de la normal al plano formado por tres puntos
**/
Vector3D calculaNormal(Punto p1, Punto p2, Punto p3);

class Cubo : public Objeto3D
{
public:
  float lado;

  virtual void draw();
};

class Piramide : public Objeto3D
{
public:
  float lado, alto;

  virtual void draw();
};

class PrismaPentagonal : public Objeto3D
{
public:
  float ang_c, alto;

  virtual void draw();
};


class Dado : public Objeto3D
{
public:
  float lado;

  virtual void draw();
};

