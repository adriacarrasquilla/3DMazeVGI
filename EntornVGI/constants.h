//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn b�sic VS2019 MULTIFINESTRA amb OpenGL, interf�cie MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Setembre 2019)
// constants.h : Definici� de constants compartides a
//				 CENtornVGIView.cpp, visualitzacio.cpp i escena.cpp


#ifndef CONST_H
#define CONST_H

//--------------- VGI: Tipus de Projecci�
#define CAP ' '
#define AXONOM 'A'
#define ORTO 'O'
#define PERSPECT 'P'
#define IMA_PICK 3
#define PASSEIG_V 4


//--------------- VGI: Tipus de Polars (per la Visualitzaci� Interactiva)
#define POLARZ 'Z'
#define POLARY 'Y'
#define POLARX 'X'

//-------------- VGI: Tipus d'Objectes 
#define CAMIO 'm'
#define CILINDRE 'y'
#define CUB 'c'
#define CUB_RGB 'C'
#define C_BEZIER '2'
#define C_LEMNISCATA 'K'
#define C_LEMNISCATA2D 'W'
#define C_BSPLINE 'q'
#define ESFERA 'e'
#define O_FRACTAL 'f'
#define HIDROAVIO 'H'
#define ICOSAEDRE 'i'
#define ROBOT 'u'
#define TETERA 't'
#define TIE 'I'
#define TORUS 'o'
#define TRUCK 'T'
#define VAIXELL 'v'
#define OBJ3DS '3'		// Objecte format 3DS
#define OBJOBJ '4'		// Objecte format OBJ

#define MUR 'M'

//-------------- VGI: Tipus d'Iluminacio
#define PUNTS 'P'
#define FILFERROS 'f'
#define PLANA 'p'
#define GOURAUD 'g'

//-------------- VGI: Objectes precompilats OpenGL amb glNewList
#define EIXOS 1			// Eixos
#define FRACTAL 2		// Fractal
#define OBJECTE3DS 3	// Objecte 3DS sense textures
#define OBJECTE3DST 4	// Objecte 3DS amb textures
#define OBJECTEOBJ 5	// Objecte OBJ sense textures
#define OBJECTEOBJT 6   // Objecte OBJ amb textures

// -------------- VGI: Definici� dels valors del pla near i far del Volum de Visualitzaci� en Perspectiva
const double p_near = 1.0;
const double p_far = 50000.0;

//-------------- VGI: Tipus d'Objectes Picking
#define PICKCAP 0
#define PICKFAR 1
#define PICKVAIXELL 2 
#define PICKHIDRO 3 

// -------------- VGI: CONSTANTS TEXTURES
// Nombre m�xim de textures
#define NUM_MAX_TEXTURES 10

// Tipus de textures
#define CAP ' '
#define FUSTA 'F'
#define MARBRE 'M'
#define METALL 'E'
#define FITXER 'f'
#define FITXERBMP 'f'
#define FITXERIMA 'I'

// --------------  VGI: NOMBRE DE LLUMS: Nombre de Llums de l'aplicaci�, les d'OpenGL
const int NUM_MAX_LLUMS = 8;

// Permet prendre les funcions _s enlloc de les deprecated (strcpy -> strcpy_s). Ja definit
//#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1

// Elimina missatges warning que venen de crides deprecated (strcpy -> strcpy_s).
//#define _CRT_SECURE_NO_WARNINGS //-> Posat a "Project"->"Properties"->"Configuration properties"->"C/C++"->"Preprocessor"->"Preprocessor definitions".

// -------------- VGI: SHADERS --> Tipus de Shaders
#define CAP_SHADER ' '
#define GOURAUD_SHADER 'G'
#define PHONG_SHADER 'P'
#define GOURAUD_TOON 'g'
#define PHONG_TOON 'p'
#define FILE_SHADER 'f'

//--------------- VGI: Valor constant de pi
const double pi = 3.14159;
const double TWOPI = 2 * pi;
const double PID2 = pi / 2;
//const double pi=3.14159265358979323846264338327950288419716939937510f;

// --------------- GMS. GRID
#define GRID_SIZE 50	// Maximum size of the grid in OpenGL World Coordenates unities.
#define PAS_GRID 1		// Step to shift the grid planes.

// --------------- VGI. TRUCK: Resoluci� de les rodes (Nombre de divisions del cilindre i discos)
#define RESOLUCIO_RODA 16

// --------------- VGI. Maxim tamany del fractal
//#define FMAX 512


// --------------- VGI. Mides i orientaci� del mur i del jugador
#define MUR_X 20.0
#define MUR_Y 5.0
#define MUR_Z 15.0
#define HOR 0
#define VER 1
#define PG_X 0.1
#define PG_Y 0.1
#define PG_Z 0.1




/* --------------- VGI: Estructura coordenada 2D (Ja definida en Visual Studio 2010)
struct CPoint
{   GLint x;
	GLint y;
};
*/

// --------------- VGI: Estructura coordenada 3D
struct CPunt3D
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat w;
};

// --------------- GMS: 3M�scara booleana sobre coordenades 3D
struct CMask3D
{
	bool x;
	bool y;
	bool z;
	bool w;
};

// --------------- VGI: Estructura de color R,G,B,A
struct CColor
{
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
};

// --------------- VGI: Estructura coordenada Esf�rica 3D
struct CEsfe3D
{
	GLfloat R;
	GLfloat alfa;
	GLfloat beta;
};

// --------------- VGI: INSTANCIA (TG d'instanciaci� d'un objecte)
struct INSTANCIA
{
	CPunt3D VTras;	// Vector de Traslaci�
	CPunt3D VScal;	// Vector d'Escalatge
	CPunt3D VRota;	// Vector de Rotaci�
};

// --------------- VGI: Coeficients equaci� d'atenuaci� de la llum fatt=1/(ad2+bd+c)
struct CAtenua
{
	GLfloat a;
	GLfloat b;
	GLfloat c;
};

// --------------- VGI: Estructura de coeficients de reflectivitat de materials
struct MATERIAL
{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat emission[4];
	GLfloat shininess;
};

// --------------- VGI: Estructura font de llum
struct LLUM
{
	bool encesa;		// Booleana que controla si la llum �s encesa [TRUE] o no [FALSE]
	CEsfe3D posicio;	// Posici� d ela foont de llum en coordenades esf�riques.
	GLfloat difusa[4];	// Intensitat difusa de la font de llum (r,g,b,a)
	GLfloat especular[4];	// Intensitat especular de la font de llum (r,g,b,a)
	CAtenua atenuacio;		// Coeficients de l'equaci� d'atenuaci� de la llum fatt=1/(ad2+bd+c)
	bool restringida;		// Booleana que indica si la font de llum �s restringida [TRUE] i per tant s�n v�lids els coeficients posteriors o no [FALSE].
	GLfloat spotdirection[3];	// vector de direci� de la font de llum restringida (x,y,z).
	GLfloat cutoff;			// Angle d'obertura de la font de llum restringida.
	GLfloat exponent;		// Exponent que indica l'atenuaci� de la font del centre de l'eix a l'exterior, segons model de Warn.
};

#endif