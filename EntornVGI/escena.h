//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn b�sic VS2019 MULTIFINESTRA amb OpenGL, interf�cie MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Setembre 2018)
// escena.h : interface de escena.cpp
//

#ifndef GLSOURCE_H
#define GLSOURCE_H

#include "Classes.h"
#include "OBJLoader2.h"
#include <vector>


/* ------------------------------------------------------------------------- */
/*                            Funcions de les escenes                        */
/* ------------------------------------------------------------------------- */
// Entorn VGI: dibuixa_EscenaGL -> Dibuix de l'escena GL
void dibuixa_EscenaGL(char objecte, CColor col_object, bool ref_mat, bool sw_mat[4], bool textur, GLint texturID[NUM_MAX_TEXTURES], bool textur_map,
	int nptsU, CPunt3D PC_u[MAX_PATCH_CORBA], GLfloat pasCS, bool sw_PC, float mov[], std::vector<Mur> llista, Personatge& pg, float cel[], objl::Loader loader, float movimentShrek[], bool movDir[], float rotacioShrek[], Event& eventfinal, std::vector<Event>& eventsMursBaixada);

// Entorn VGI: dibuixa -> Funci� que dibuixa objectes simples de la llibreria GLUT segons obj
void dibuixa(char obj);

// Entorn VGI: Truck - Objecte fet per alumnes.
void truck(bool textu, GLint VTextu[NUM_MAX_TEXTURES]);
void neumatic(bool textur, GLint VTextur[NUM_MAX_TEXTURES]);
void llanta(bool textur, GLint VTextur[NUM_MAX_TEXTURES]);
void sea(void);

// Entorn VGI: Tie (Nau enemiga Star Wars) - Objecte fet per alumnes.
void tie();
void Alas();
void Motor();
void Canon();
void Cuerpo();
void Cabina();


//Funcions per detectar colisions
bool* CheckColisioMurPg(Mur m, Personatge p);
void DoCollisions(std::vector<Mur> llista, Personatge& pg, Event& e, std::vector<Event>& eventMursBaixada);

//funcions shrek
void shrek(objl::Loader loader, float moviment[], bool movDir[], int texturID[]);
void movimentShrek(float moviment[], bool movDir[]);

void drawBitmapText(char* string, float x, float y, float z);
#endif