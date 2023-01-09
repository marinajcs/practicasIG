/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: 

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

	entradaTeclado.h
*/


/**	
	Funcion de captura de eventos pulsacion de tecla correspondiente a caracter alfanumerico
	K: codigo ascii del caracter
	x: posicion del cursor en coordenadas de pantalla cuando se pulso la tecla
	y: posicion del cursor en coordenadas de pantalla cuando se pulso la tecla
**/
void letra (unsigned char k, int x, int y);

/**
	Funcion de captura de eventos pulsacion de caracteres especiales y de control
	K: codigo del control pulsado (se definen como constantes en glut.h)
	x: posicion del cursor en coordenadas de pantalla cuando se pulso la tecla
	y: posicion del cursor en coordenadas de pantalla cuando se pulso la tecla
**/
void especial (int k, int x, int y);
