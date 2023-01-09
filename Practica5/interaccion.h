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

=======================================================

	 modelo.h
*/

void pick(int x, int y);

void dibujoEscena();
/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja(void);

/**
	Funcion de fondo
**/
void idle(int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel();

class Objeto3D
{
public:
	GLuint texId = 0;
	unsigned char *imgptr;
	unsigned alto, ancho;

	virtual void draw() = 0; // Dibuja el objeto

	void setTexture(const char *img_name);
	void loadTexture();
	void freeTexture();
};
