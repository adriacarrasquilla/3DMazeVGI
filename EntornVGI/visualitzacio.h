//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn bàsic VS2019 MULTIFINESTRA amb OpenGL, interfície MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Setembre 2019)
// visualitzacio.h : Interface de visualitzacio.cpp
//

#ifndef GLVIS_H
#define GLVIS_H

/* ------------------------------------------------------------------------- */
/*                                Funcions                                   */
/* ------------------------------------------------------------------------- */

// Entorn VGI: Il.luminació
void Iluminacio(char ilumin, bool ifix, bool ilu2sides, bool ll_amb, LLUM* lumin, char obj, bool frnt_fcs, bool bc_lin, int step);

// Entorn VGI: Projecció Ortografica;
void Projeccio_Orto(int minx, int miny, GLsizei w, GLsizei h);
void Vista_Ortografica(int prj, GLfloat Raux, CColor col_fons, CColor col_object, char objecte, GLfloat mida, int step,
	bool frnt_fcs, bool oculta, bool testv, bool bck_ln, char iluminacio, bool llum_amb, LLUM* lumin,
	bool ifix, bool il2sides, bool eix, CMask3D reixa, CPunt3D hreixa);

// Entorn VGI: Projecció Perspectiva
void Projeccio_Perspectiva(int, int, GLsizei, GLsizei, float);
void Vista_Esferica(CEsfe3D opv, char VPol, bool pant, CPunt3D tr, CPunt3D trF,
	CColor col_fons, CColor col_object, char objecte, double mida, int step,
	bool frnt_fcs, bool oculta, bool testv, bool bck_ln, char iluminacio, bool llum_amb, LLUM* lumin,
	bool ifix, bool il2sides, bool eix, CMask3D reixa, CPunt3D hreixa);

void Vista_Navega(CPunt3D pv, bool pvb, GLfloat n[3], GLfloat v[3], bool pant, CPunt3D tr, CPunt3D trF,
	CColor col_fons, CColor col_object, char objecte, bool color, int step,
	bool frnt_fcs, bool oculta, bool testv, bool bck_ln, char iluminacio, bool llum_amb, LLUM* lumin,
	bool ifix, bool il2sides, bool eix, CMask3D reixa, CPunt3D hreixa);

// Entorn VGI: Càrrega TG
void instancia(bool TR, INSTANCIA tg, INSTANCIA tgF);

// Entorn VGI: Dibuix dels eixos de coordenades
void deixos(void);

// Entorn VGI: GRID (gridXY, gridYZ, gridXZ, gridXYZ) -------------------------
void draw_Grid(CMask3D quadricula, CPunt3D hquadricula);
void gridXY(int size, GLfloat h);
void gridXZ(int size, GLfloat h);
void gridYZ(int size, GLfloat h);
void gridXYZ(int size);

// Entorn VGI: Esborrats de pantalla a fons variable (Fons), negre (Fons) o a blanc (FonsW)
void Fons(CColor int_fons);
void FonsN(void);
void FonsB(void);

// Entorn VGI: Carregar fitxer imatge de formats admesos per la llibreria DevIL/OpenIL 
//				com a textura
GLint loadIMA_SOIL(char* filename);
GLint loadIMA_ILUT(char* filename);
void SetTextureParameters(GLint IDText, bool extensT, bool filterT, bool blendT, bool genMipmpT);

// Entorn VGI: Textures Objecte Truck
//void Init_Textures();

//----------------- FUNCIONS LLIBRERIA GLU
#define __glPi 3.14159265358979323846

void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx,
	GLdouble centery, GLdouble centerz, GLdouble upx, GLdouble upy,
	GLdouble upz);

void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);

static void __gluMakeIdentityf(GLfloat m[16]);
static void __gluMakeIdentityd(GLdouble m[16]);
static void normalize(float v[3]);
static void cross(float v1[3], float v2[3], float result[3]);
#endif