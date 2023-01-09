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
modulo objetoPly.c
  Clase ObjetoPly que lee archivos ply y los dibuja de 2 modos
  Clase Revolución que hereda de ObjetoPly, permite dibujar perfiles al revolucionar N copias

*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <GL/glut.h> // Libreria de utilidades de OpenGL
#include "practicasIG.h"

using namespace std;

ObjetoPly::ObjetoPly(const char *filename)
{
  vector<float> vertply;

  ply::read(filename, vertply, caras);

  nvert = vertply.size() / 3;
  ncaras = caras.size() / 3;

  vertices.resize(nvert);
  triangulos.resize(ncaras);

  Punto veraux;
  PuntoInt caraux;

  for (int i = 0; i < nvert; i++)
  {
    veraux.x = vertply[i * 3];
    veraux.y = vertply[i * 3 + 1];
    veraux.z = vertply[i * 3 + 2];
    vertices[i] = veraux;
  }

  for (int i = 0; i < ncaras; i++)
  {
    caraux.a = caras[i * 3];
    caraux.b = caras[i * 3 + 1];
    caraux.c = caras[i * 3 + 2];
    triangulos[i] = caraux;
  }

  normales.resize(triangulos.size());
  normvert.resize(vertices.size());
}

void ObjetoPly::draw()
{
  if (draw_opt == 0)
  { // flat

    glShadeModel(GL_FLAT);
    glBegin(GL_TRIANGLES);
    {
      for (int i = 0; i < triangulos.size(); i++)
      {
        // cálculo normales caras
        Vector3D norm = calculaNormal(vertices[triangulos[i].a], vertices[triangulos[i].b], vertices[triangulos[i].c]);
        normales.push_back(norm);

        glNormal3f(norm.X, norm.Y, norm.Z);
        glVertex3f(vertices[triangulos[i].a].x, vertices[triangulos[i].a].y, vertices[triangulos[i].a].z);
        glVertex3f(vertices[triangulos[i].b].x, vertices[triangulos[i].b].y, vertices[triangulos[i].b].z);
        glVertex3f(vertices[triangulos[i].c].x, vertices[triangulos[i].c].y, vertices[triangulos[i].c].z);
      }
    }
    glEnd();
  }
  else if (draw_opt == 1)
  {

    glShadeModel(GL_SMOOTH);
    glBegin(GL_TRIANGLES);
    {
      // cálculo normales vértices
      for (int i = 0; i < triangulos.size(); i++)
      {
        Vector3D norm = calculaNormal(vertices[triangulos[i].a], vertices[triangulos[i].b], vertices[triangulos[i].c]);
        normales[i] = norm;

        normvert[triangulos[i].a] += normales[i];
        normvert[triangulos[i].b] += normales[i];
        normvert[triangulos[i].c] += normales[i];
      }

      for (int i = 0; i < normvert.size(); i++)
      {
        normvert[i] = normalizaVect(normvert[i]);
      }

      for (int i = 0; i < triangulos.size(); i++)
      {
        glNormal3f(normvert[triangulos[i].a].X, normvert[triangulos[i].a].Y, normvert[triangulos[i].a].Z);
        glVertex3f(vertices[triangulos[i].a].x, vertices[triangulos[i].a].y, vertices[triangulos[i].a].z);

        glNormal3f(normvert[triangulos[i].b].X, normvert[triangulos[i].b].Y, normvert[triangulos[i].b].Z);
        glVertex3f(vertices[triangulos[i].b].x, vertices[triangulos[i].b].y, vertices[triangulos[i].b].z);

        glNormal3f(normvert[triangulos[i].c].X, normvert[triangulos[i].c].Y, normvert[triangulos[i].c].Z);
        glVertex3f(vertices[triangulos[i].c].x, vertices[triangulos[i].c].y, vertices[triangulos[i].c].z);
      }
    }
    glEnd();
  }
}

void ObjetoPly::setDrawOption(int opt)
{
  if (opt == 0 || opt == 1)
  {
    draw_opt = opt;
  }
}

void Revolucion::setNCopies(int nc){
  if (nc > 5){
    N = nc;
  }
}

Revolucion::Revolucion(const char *filename)
{
  std::vector<float> vertply;

  ply::read_vertices(filename, vertply);

  int nv = vertply.size() / 3;

  perfiles.resize(nv);

  Punto paux;

  for (int i = 0; i < nv; i++)
  {
    paux.x = vertply[i * 3];
    paux.y = vertply[i * 3 + 1];
    paux.z = vertply[i * 3 + 2];
    perfiles[i] = paux;
  }

  float rad = 2.0 * M_PI / N;

  // creación lista vértices
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < nv; j++)
    {
      Punto vert;
      vert.x = perfiles[j].x * cos(i * rad);
      vert.y = perfiles[j].y;
      vert.z = -perfiles[j].x * sin(i * rad);

      vertices.push_back(vert);
    }
  }

  // creación lista triángulos
  triangulos.resize(N * 2 * nv); // 2 triángulos * n_vértices

  for (int i = 0; i < (N - 1); i++)
  {
    for (int j = 0; j < nv - 1; j++)
    {
      int k = i * nv + j;

      // Triángulos impares
      PuntoInt paux;
      paux.a = k;
      paux.b = (i + 1) * nv + j;
      paux.c = ((i + 1) * nv + (j + 1));
      triangulos.push_back(paux);

      // Triángulos pares
      PuntoInt paux1;
      paux1.a = k;
      paux1.b = ((i + 1) * nv + (j + 1));
      paux1.c = k + 1;
      triangulos.push_back(paux1);
    }
  }
  

  // conecta último perfil con el original (el primero) para cerrar la figura
  for (int i = 0; i < nv - 1; i++)
  {
    PuntoInt paux0;
    paux0.a = i + (N - 1) * nv;
    paux0.b = i;
    paux0.c = i + 1;
    triangulos.push_back(paux0);

    PuntoInt paux1;
    paux1.a = i + (N - 1) * nv;
    paux1.b = i + 1;
    paux1.c = (i + 1) + (N - 1) * nv;
    triangulos.push_back(paux1);
  }
  

  normales.resize(triangulos.size());
  normvert.resize(vertices.size());
}

void Revolucion::draw()
{
  ObjetoPly::draw();
}
