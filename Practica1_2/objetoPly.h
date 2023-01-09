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
  modulo objetoPly.h

*/

#include <vector>

class ObjetoPly : public Objeto3D
{
public:
  std::vector<Punto> vertices;
  std::vector<int> caras;
  std::vector<PuntoInt> triangulos;
  std::vector<Vector3D> normales;
  std::vector<Vector3D> normvert;
  int nvert, ncaras;
  int draw_opt = 0; // flat = 0 (por defecto), smooth = 1

  ObjetoPly(){};

  ObjetoPly(const char * filename);

  virtual void draw();

  void setDrawOption(int opt); // establece el modo de dibujo (flat o smooth)
};


class Revolucion : public ObjetoPly
{
public:
  std::vector<Punto> perfiles; // almacena el perfil original
  int N = 10; //nº copias por defecto

  Revolucion(){};

  Revolucion(const char * filename);

  virtual void draw();

  void setNCopies(int nc); // establece un número de copias mayor que 5

};