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
	int nptsU, CPunt3D PC_u[MAX_PATCH_CORBA], GLfloat pasCS, bool sw_PC, float mov[], std::vector<Mur> llista, Personatge& pg, float cel[], objl::Loader loader[], float movimentShrek[][3], bool movDir[][3], float rotacioShrek[][3],
	Event& eventfinal, std::vector<Event>& eventsMursBaixada, std::vector<Mur> punxesAnimadetes, std::vector<Mur> sales, int lifes, int MIDA_I, int MIDA_J, int musica, bool pausa, char lvl, bool &changeLvl);


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
void DoCollisions(std::vector<Mur> llista, Personatge& pg, Event& e, std::vector<Event>& eventMursBaixada, std::vector<Mur>& punxes, std::vector<std::vector<float>>& Shreks);

//funcions shrek
void shrek(objl::Loader loader, float moviment[], bool movDir[], float rotShrek[], int texturID[], int tipusMov, float posicioIniciX, float posicioIniciY, float posicioFinalX, float posicioFinalY, float posicioZ, float& pos_x, float& pos_y, float& pos_z, bool pausa);
void movimentShrek(float moviment[], bool movDir[], float rotShrek[], float posicioIniciY, float posicioFinalY, bool pausa);
void circularMovimentShrek(float moviment[], bool movDir[], float rotShrek[], bool pausa);

void drawBitmapText(char* string, float x, float y, float z);
#endif