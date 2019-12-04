//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Entorn Basic)
//******** Marc Vivet, Carme Julià, Débora Gil, Enric Martí  (Octubre 2019)
// normals.h : interface de normals.cpp
//             Declaracions de les funcions de càlcul de 
//			   vectors normals per la visualització dels fractals 


#ifndef NORMALS
#define NORMALS

// -------------- Entorn VGI: Referència a les quadrícules zz i normals, definides
//                            a fractals.cpp.
extern float zz[513][513];
extern float normalsC[513][513][3];
extern float normalsV[513][513][3];

// normal: Càlcul del producte vectorial normalitzat de dos vectors v1,v2.
//         Resultat a la variable n.
void normal(float v1[3], float v2[3], float n[3]);


#endif
