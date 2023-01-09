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
  modulo grua.h

*/
#include <vector>
#include <string.h>


class Grua : public Objeto3D
{
public:
  static float ang0, ang1, longc;
  bool sube = false;
  static bool move;

  Grua(){};

  virtual void draw();

  static void setMove(bool opt);

  static void modParam(float a0, float a1, float lc);

  void GruaCompleta();

  void Estructura();

  void BrazoCompleto();

  void Torre();

  void BrazoLargo();

  void BrazoCorto();

  void Gancho();

  void Cuerda();
};

