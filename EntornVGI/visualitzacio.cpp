//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn bàsic VS2019 MULTIFINESTRA amb OpenGL, interfície MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Setembre 2019)
// visualitzacio.cpp : Funcions de visualització i pantalla
// FUNCIONS:	- Iluminació (Iluminacio)
//				- Visualització Ortogràfica (ProjeccioOrto i Ortografica)
//				- Visualització Perspectiva amb coord. esfèriques (ProjeccioPerspectiva(),Vista_Esferica())
//              - Visualització Perspectiva amb navegació per tecles cursor (ProjeccioPerspectiva(),Vista_Navega())
//				- Dibuixar els eixos (deixos)
//				- Incorporar plans de Grid2D (XY, XZ, YZ) i un Grid 3D (grid*())
//				- Dibuixar fons: blanc (FonsW) i negre (Fons)
//				- Carregar imatges de formats compatibles amb DevIL/OpenIL com a textura (loadIMA())
//				- Inicialitzar imatges textura per l'objecte Truck (Init_Textures())
//

#include "stdafx.h"
#include "visualitzacio.h"
#include "escena.h"

// Iluminació: Configurar iluminació de l'escena
void Iluminacio(char ilumin, bool ifix, bool ilu2sides, bool ll_amb, LLUM* lumin, char obj, bool frnt_fcs, bool bc_lin, int step, bool perduda)
{
	//bool ll_amb=true;
	GLfloat angv, angh;

	// Configuració de la font de llum LIGHT0
	GLfloat position[] = { 0.0,0.0,200.0,1.0 };
	GLfloat especular[] = { 0.0,0.0,0.0,1.0 };
	GLfloat dia[] = { .5,.5,.5, 1.0 };
	GLfloat nit[] = { .1,.1,.1, 1.0 };
	GLfloat partida_perduda[] = { .8,.3,.3, 1.0 };

	// Definició de llum ambient segons booleana ll_amb

	//En cas que perduda = TRUE -> l'ambient serà vermell.
	if(perduda) glLightModelfv(GL_LIGHT_MODEL_AMBIENT, partida_perduda);
	else {
		if (ll_amb) glLightModelfv(GL_LIGHT_MODEL_AMBIENT, dia);
		else glLightModelfv(GL_LIGHT_MODEL_AMBIENT, nit);
	}

	// Llum #0 - (+Z)
	if (lumin[0].encesa) {
		if (!ifix) glLightfv(GL_LIGHT0, GL_POSITION, position);
		else {	// Conversió angles graus -> radians
			angv = lumin[0].posicio.alfa * pi / 180;
			angh = lumin[0].posicio.beta * pi / 180;

			// Conversió Coord. esfèriques -> Coord. cartesianes
			position[0] = lumin[0].posicio.R * cos(angh) * cos(angv);
			position[1] = lumin[0].posicio.R * sin(angh) * cos(angv);
			position[2] = lumin[0].posicio.R * sin(angv);
			//position[3]=1.0;
			glLightfv(GL_LIGHT0, GL_POSITION, position);
		}
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lumin[0].difusa);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lumin[0].especular);

		// Coeficients factor atenuació f_att=1/(ad2+bd+c)
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, lumin[0].atenuacio.c);
		glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, lumin[0].atenuacio.b);
		glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, lumin[0].atenuacio.a);
		if (lumin[0].restringida) {
			glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lumin[0].spotdirection);
			glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, lumin[0].cutoff);
			glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, lumin[0].exponent);
		}
		glEnable(GL_LIGHT0);
	}
	else glDisable(GL_LIGHT0);

	// Llum #1 (+X)
	if (lumin[1].encesa) {
		if (!ifix) glLightfv(GL_LIGHT1, GL_POSITION, position);
		else {	// Conversió angles graus -> radians
			angv = lumin[1].posicio.alfa * pi / 180;
			angh = lumin[1].posicio.beta * pi / 180;

			// Conversió Coord. esfèriques -> Coord. cartesianes
			position[0] = lumin[1].posicio.R * cos(angh) * cos(angv);
			position[1] = lumin[1].posicio.R * sin(angh) * cos(angv);
			position[2] = lumin[1].posicio.R * sin(angv);
			position[3] = 1.0;
			glLightfv(GL_LIGHT1, GL_POSITION, position);
		}
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lumin[1].difusa);
		glLightfv(GL_LIGHT1, GL_SPECULAR, lumin[1].especular);

		// Coeficients factor atenuació f_att=1/(ad2+bd+c)
		glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, lumin[1].atenuacio.c);
		glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, lumin[1].atenuacio.b);
		glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, lumin[1].atenuacio.a);
		if (lumin[0].restringida) {
			glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lumin[1].spotdirection);
			glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, lumin[1].cutoff);
			glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, lumin[1].exponent);
		}
		glEnable(GL_LIGHT1);
	}
	else glDisable(GL_LIGHT1);

	// Llum #2 (+Y)
	if (lumin[2].encesa) {
		if (!ifix) glLightfv(GL_LIGHT2, GL_POSITION, position);
		else {	// Conversió angles graus -> radians
			angv = lumin[2].posicio.alfa * pi / 180;
			angh = lumin[2].posicio.beta * pi / 180;

			// Conversió Coord. esfèriques -> Coord. cartesianes
			position[0] = lumin[2].posicio.R * cos(angh) * cos(angv);
			position[1] = lumin[2].posicio.R * sin(angh) * cos(angv);
			position[2] = lumin[2].posicio.R * sin(angv);
			position[3] = 1.0;
			glLightfv(GL_LIGHT2, GL_POSITION, position);
		}
		glLightfv(GL_LIGHT2, GL_DIFFUSE, lumin[2].difusa);
		glLightfv(GL_LIGHT2, GL_SPECULAR, lumin[2].especular);

		// Coeficients factor atenuació f_att=1/(ad2+bd+c)
		glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, lumin[2].atenuacio.c);
		glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, lumin[2].atenuacio.b);
		glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, lumin[2].atenuacio.a);
		if (lumin[2].restringida) {
			glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lumin[2].spotdirection);
			glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, lumin[2].cutoff);
			glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, lumin[2].exponent);
		}
		glEnable(GL_LIGHT2);
	}
	else glDisable(GL_LIGHT2);

	// Llum #3 (Z=Y=X)
	if (lumin[3].encesa) {
		if (!ifix) glLightfv(GL_LIGHT3, GL_POSITION, position);
		else {	// Conversió angles graus -> radians
			angv = lumin[3].posicio.alfa * pi / 180;
			angh = lumin[3].posicio.beta * pi / 180;

			// Conversió Coord. esfèriques -> Coord. cartesianes
			position[0] = lumin[3].posicio.R * cos(angh) * cos(angv);
			position[1] = lumin[3].posicio.R * sin(angh) * cos(angv);
			position[2] = lumin[3].posicio.R * sin(angv);
			position[3] = 1.0;
			glLightfv(GL_LIGHT3, GL_POSITION, position);
		}
		glLightfv(GL_LIGHT3, GL_DIFFUSE, lumin[2].difusa);
		glLightfv(GL_LIGHT3, GL_SPECULAR, lumin[2].especular);

		// Coeficients factor atenuació f_att=1/(ad2+bd+c)
		glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, lumin[3].atenuacio.c);
		glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, lumin[3].atenuacio.b);
		glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, lumin[3].atenuacio.a);
		if (lumin[3].restringida) {
			glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lumin[3].spotdirection);
			glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, lumin[3].cutoff);
			glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, lumin[3].exponent);
		}
		glEnable(GL_LIGHT3);
	}
	else glDisable(GL_LIGHT3);

	// Llum #4 (-Z)
	if (lumin[4].encesa) {
		if (!ifix) glLightfv(GL_LIGHT4, GL_POSITION, position);
		else {	// Conversió angles graus -> radians
			angv = lumin[4].posicio.alfa * pi / 180;
			angh = lumin[4].posicio.beta * pi / 180;

			// Conversió Coord. esfèriques -> Coord. cartesianes
			position[0] = lumin[4].posicio.R * cos(angh) * cos(angv);
			position[1] = lumin[4].posicio.R * sin(angh) * cos(angv);
			position[2] = lumin[4].posicio.R * sin(angv);
			position[3] = 1.0;
			glLightfv(GL_LIGHT4, GL_POSITION, position);
		}
		glLightfv(GL_LIGHT4, GL_DIFFUSE, lumin[4].difusa);
		glLightfv(GL_LIGHT4, GL_SPECULAR, lumin[4].especular);

		// Coeficients factor atenuació f_att=1/(ad2+bd+c)
		glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, lumin[4].atenuacio.c);
		glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, lumin[4].atenuacio.b);
		glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, lumin[4].atenuacio.a);
		if (lumin[4].restringida) {
			glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, lumin[4].spotdirection);
			glLightf(GL_LIGHT4, GL_SPOT_CUTOFF, lumin[4].cutoff);
			glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, lumin[4].exponent);
		}
		glEnable(GL_LIGHT4);
	}
	else glDisable(GL_LIGHT4);

	// Llum #5 
	if (lumin[5].encesa) glEnable(GL_LIGHT5);
	else glDisable(GL_LIGHT5);

	// Llum #6 
	if (lumin[6].encesa) glEnable(GL_LIGHT6);
	else glDisable(GL_LIGHT6);

	// Llum #7 
	if (lumin[7].encesa) glEnable(GL_LIGHT7);
	else glDisable(GL_LIGHT7);

	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Selecció del model d'iluminació segons variable ilumin
	switch (ilumin)
	{
	case PUNTS:
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glEnable(GL_COLOR_MATERIAL);

		// Desactivació de la il.luminació
		glDisable(GL_LIGHTING);
		break;

	case FILFERROS:
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_COLOR_MATERIAL);

		// Desactivació de la il-luminació
		glDisable(GL_LIGHTING);
		break;

	case PLANA:
		if (frnt_fcs) {
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
		}
		else {
			glPolygonMode(GL_BACK, GL_FILL);
			glPolygonMode(GL_FRONT, GL_POINT);
		}

		// Dibuix de les cares front o back com a línies en Il.luminacio PLANA
		if (bc_lin) {
			if (frnt_fcs) {
				glPolygonMode(GL_FRONT, GL_FILL);
				glPolygonMode(GL_BACK, GL_LINE);
			}
			else {
				glPolygonMode(GL_BACK, GL_FILL);
				glPolygonMode(GL_FRONT, GL_LINE);
			}
		}

		// Il.luminació de les cares front i back (GL_TRUE) o només front (GL_FALSE)
		if (ilu2sides) glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		else glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_NORMALIZE);

		// PRÀCTICA 3: Crida a la funció pel càlcul dels vectors normals normals a les cares si l'objecte és un fractal

		// Il.luminació per cares planes
		glShadeModel(GL_FLAT);

		// Activació de la llum
		glEnable(GL_LIGHTING);
		break;

	case GOURAUD:
		if (frnt_fcs) {
			glPolygonMode(GL_FRONT, GL_FILL);
			glPolygonMode(GL_BACK, GL_FILL);
		}
		else {
			glPolygonMode(GL_BACK, GL_FILL);
			glPolygonMode(GL_FRONT, GL_POINT);
		}

		// Dibuix de les cares front o back com a línies en Il.luminacio PLANA
		if (bc_lin) {
			if (frnt_fcs) {
				glPolygonMode(GL_FRONT, GL_FILL);
				glPolygonMode(GL_BACK, GL_LINE);
			}
			else {
				glPolygonMode(GL_BACK, GL_FILL);
				glPolygonMode(GL_FRONT, GL_LINE);
			}
		}

		// Il.luminació de les cares front i back (GL_TRUE) o només front (GL_FALSE)
		if (ilu2sides) glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		else glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE);

		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_NORMALIZE);

		// PRÀCTICA 3: Crida a la funció pel càlcul dels vectors normals normals a les cares si l'objecte és un fractal

		// Il.luminació suau 
		glShadeModel(GL_SMOOTH);

		// Activació de la llum
		glEnable(GL_LIGHTING);
		break;
	}

	// Creació de la llista que dibuixarà els eixos
	//   funció on està codi per dibuixar eixos
	glNewList(EIXOS, GL_COMPILE);
	// Dibuix dels eixos sense il.luminació
	glDisable(GL_LIGHTING);
	// Dibuixar eixos sense textures
	glDisable(GL_TEXTURE_2D);
	deixos();
	if ((ilumin != PUNTS) && (ilumin != FILFERROS)) glEnable(GL_LIGHTING);
	glEndList();
}

// -------- Entorn VGI: ORTOGRÀFICA (Funcions Projeccio_Orto i Vista_Ortografica)

// Projeccio_Orto: Definició Viewport i glOrtho 
// ---- Entorn VGI: ATENCIÓ!!. CAL DEFINIR PARÀMETRES DE LA FUNCIÓ
void Projeccio_Orto(int minx, int miny, GLsizei w, GLsizei h)
{
	//glViewport(minx, miny, w, h);
	glViewport(minx, miny, w, h);

	if (h == 0) h = 1;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10.0, 10.0, -10.0, 10.0, -10, 10);
	//glOrtho(-minx/10, minx/10, -miny/10, miny/10, -10, 10);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	// ---- Entorn VGI: ATENCIÓ!!. ESPECIFICACIO DELS PARÀMETRES DE PROJECCIÓ ORTOGRÀFICA
	//			        QUE ES CARREGUEN A LA MATRIU DE PROJECCIÓ GL_PROJECTION
}

// Vista_Ortogràfica: Ilumina i dibuixa l'escena. Crida a la funció gluLookAt segons la variable prj 
//				(planta, alçat, perfil o axonometrica).
void Vista_Ortografica(int prj, GLfloat Raux, CColor col_fons, CColor col_object, char objecte, GLfloat mida, int step,
	bool frnt_fcs, bool oculta, bool testv, bool bck_ln,
	char iluminacio, bool llum_amb, LLUM* lumi, bool ifix, bool il2sides,
	bool eix, CMask3D reixa, CPunt3D hreixa, bool perduda)
{

	// Iluminacio movent-se amb la camara (abans gluLookAt)
	if (!ifix) Iluminacio(iluminacio, ifix, il2sides, llum_amb, lumi, objecte, frnt_fcs, bck_ln, step, perduda);

	// Implementació de planta,alçat,perfil i isomètrica 
	// ---- Entorn VGI: ATENCIÓ!!. ESPECIFICACIO DEL PUNT DE VISTA
	//								Cal definir el punt de vista (gluLookAt) en funció del
	//								tipus de projecció definit a la variable prj.
	switch (prj)
	{
	case 0:
		gluLookAt(-10, -10, -10, 0, 0, 0, 0, 0, 10);
		break;
	case 1:
		gluLookAt(0, 10, 0, 0, 0, 0, 0, 0, 10);
		break;
	case 2:
		gluLookAt(10, 0, 0, 0, 0, 0, 0, 0, 10);
		break;
	case 3:
		gluLookAt(10, 0, 0, 0, 0, 0, 0, 0, 10);
		break;
	}
	// Neteja dels buffers de color i profunditat
	Fons(col_fons);

	// Iluminacio fixe respecte la camara (després gluLookAt)
	if (ifix) Iluminacio(iluminacio, ifix, il2sides, llum_amb, lumi, objecte, frnt_fcs, bck_ln, step, perduda);

	// Test de Visibilitat
	if (testv) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	// Ocultacions (Z-buffer)
	if (oculta) glEnable(GL_DEPTH_TEST);
	else glDisable(GL_DEPTH_TEST);

	// Dibuix de les cares back com a línies en Il.luminacio PLANA i SUAU
	if (bck_ln) glPolygonMode(GL_BACK, GL_LINE);

	// Dibuix dels eixos
	if (eix) glCallList(EIXOS);

	// Dibuixa el grid actiu
	if ((reixa.x) || (reixa.y) || (reixa.z) || (reixa.w)) draw_Grid(reixa, hreixa);
}

// -------- Entorn VGI: PERSPECTIVA (Funcions Projeccio_Perspectiva i Vista_Esferica)

// Projeccio_Perspectiva: Definició Viewport i gluPerspective
void Projeccio_Perspectiva(int minx, int miny, GLsizei w, GLsizei h, float zoom)
{

	// Definició Viewport
	glViewport(minx, miny, w, h);
	if (h == 0) h = 1;

	// Activació i inicialització matriu PROJECTION
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// PROJECCIO PERSPECTIVA.Definim volum de visualització adaptant-lo 
	//	 a les mides actuals de la finestra windows	

	// Amb gluPerspective
	if (w >= h) 	gluPerspective(60.0, 1.0 * w / h, p_near, p_far + zoom);
	else gluPerspective(60.0 * h / w, 1.0 * w / h, p_near, p_far + zoom);

	// Activació matriu MODELVIEW (tancar matriu PROJECTION)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Perspectiva: Definició gluLookAt amb possibilitat de moure 
//				el punt de vista interactivament amb el ratolí, 
//				ilumina i dibuixa l'escena
void Vista_Esferica(CEsfe3D opv, char VPol, bool pant, CPunt3D tr, CPunt3D trF,
	CColor col_fons, CColor col_object, char objecte, double mida, int step,
	bool frnt_fcs, bool oculta, bool testv, bool bck_ln,
	char iluminacio, bool llum_amb, LLUM* lumi, bool ifix, bool il2sides,
	bool eix, CMask3D reixa, CPunt3D hreixa, bool perduda)
{
	GLfloat cam[3], up[3];

	// Conversió angles radians -> graus
	opv.alfa = opv.alfa * pi / 180;
	opv.beta = opv.beta * pi / 180;

	if (opv.R < 1.0) opv.R = 1.0;

	// Neteja dels buffers de color i profunditat
	Fons(col_fons);

	// Posició càmera i vector cap amunt
	if (VPol == POLARZ) {
		cam[0] = opv.R * cos(opv.beta) * cos(opv.alfa);
		cam[1] = opv.R * sin(opv.beta) * cos(opv.alfa);
		cam[2] = opv.R * sin(opv.alfa);
		up[0] = -cos(opv.beta) * sin(opv.alfa);
		up[1] = -sin(opv.beta) * sin(opv.alfa);
		up[2] = cos(opv.alfa);
	}
	else if (VPol == POLARY) {
		cam[0] = opv.R * sin(opv.beta) * cos(opv.alfa);
		cam[1] = opv.R * sin(opv.alfa);
		cam[2] = opv.R * cos(opv.beta) * cos(opv.alfa);
		up[0] = -sin(opv.beta) * sin(opv.alfa);
		up[1] = cos(opv.alfa);
		up[2] = -cos(opv.beta) * sin(opv.alfa);
	}
	else {
		cam[0] = opv.R * sin(opv.alfa);
		cam[1] = opv.R * cos(opv.beta) * cos(opv.alfa);
		cam[2] = opv.R * sin(opv.beta) * cos(opv.alfa);
		up[0] = cos(opv.alfa);
		up[1] = -cos(opv.beta) * sin(opv.alfa);
		up[2] = -sin(opv.beta) * sin(opv.alfa);
	}

	// Iluminacio movent-se amb la camara (abans glLookAt)
	if (!ifix) Iluminacio(iluminacio, ifix, il2sides, llum_amb, lumi, objecte, frnt_fcs, bck_ln, step, perduda);

	// Opció pan: desplaçament del Centre de l'esfera (pant=1)
	if (pant) glTranslatef(tr.x, tr.y, tr.z);
	glTranslatef(trF.x, trF.y, trF.z);	// Traslació fixada amb la INSERT dins l'opció pan

// Especificació del punt de vista
	gluLookAt(cam[0], cam[1], cam[2], 0., 0., 0., up[0], up[1], up[2]);

	// Iluminacio fixe respecte la camara (després glLookAt)
	if (ifix) Iluminacio(iluminacio, ifix, il2sides, llum_amb, lumi, objecte, frnt_fcs, bck_ln, step, perduda);

	// Test de Visibilitat
	if (testv) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	// Ocultacions (Z-buffer)
	if (oculta) glEnable(GL_DEPTH_TEST);
	else glDisable(GL_DEPTH_TEST);

	// Dibuix de les cares back com a línies en Il.luminacio PLANA i SUAU
	if (bck_ln) glPolygonMode(GL_BACK, GL_LINE);

	//  Dibuix dels eixos
	if (eix) glCallList(EIXOS);

	// Dibuixa el grid actiu
	if ((reixa.x) || (reixa.y) || (reixa.z) || (reixa.w)) draw_Grid(reixa, hreixa);
}


//Vista_Navega: Definició gluLookAt directament per paràmetre, sense esfèriques.
//              amb possibilitat de moure el punt de vista interactivament amb les
//				tecles de cursor per poder navegar.
void Vista_Navega(CPunt3D pv, bool pvb, GLfloat n[3], GLfloat v[3], bool pant, CPunt3D tr, CPunt3D trF,
	CColor col_fons, CColor col_object, char objecte, bool color, int step,
	bool frnt_fcs, bool oculta, bool testv, bool bck_ln,
	char iluminacio, bool llum_amb, LLUM* lumi, bool ifix, bool il2sides,
	bool eix, CMask3D reixa, CPunt3D hreixa, bool perduda)
{
	double altfar = 0;

	// Neteja dels buffers de color i profunditat
	Fons(col_fons);

	// Iluminacio movent-se amb la camara (abans glLookAt)
	if (!ifix) Iluminacio(iluminacio, ifix, il2sides, llum_amb, lumi, objecte, frnt_fcs, bck_ln, step, perduda);

	// Opció pan: desplaçament del Centre de l'esfera (pant=true)
	if (pant) glTranslatef(tr.x, tr.y, tr.z);
	glTranslatef(trF.x, trF.y, trF.z);	// Traslació fixada amb la INSERT dins l'opció pan

// Especificació del punt de vista
	gluLookAt(pv.x, pv.y, pv.z, n[0], n[1], n[2], v[0], v[1], v[2]);

	// Iluminacio fixe respecte la camara (després glLookAt)
	if (ifix) Iluminacio(iluminacio, ifix, il2sides, llum_amb, lumi, objecte, frnt_fcs, bck_ln, step, perduda);

	// Test de Visibilitat
	if (testv) glEnable(GL_CULL_FACE);
	else glDisable(GL_CULL_FACE);

	// Ocultacions (Z-buffer)
	if (oculta) glEnable(GL_DEPTH_TEST);
	else glDisable(GL_DEPTH_TEST);

	// Dibuix de les cares back com a línies en Il.luminacio PLANA i SUAU
	if (bck_ln) glPolygonMode(GL_BACK, GL_LINE);

	// Dibuix dels eixos
	if (eix) glCallList(EIXOS);

	// Dibuixa el grid actiu
	if ((reixa.x) || (reixa.y) || (reixa.z) || (reixa.w)) draw_Grid(reixa, hreixa);
}


// instancia: Aplica Transformacions Geom?triques d'instanciació, segons els par?metres 
//            definits a la persiana Transformacions
void instancia(bool TR, INSTANCIA tg, INSTANCIA tgF)
{

	// Transformacions geometriques sobre objecte (Traslacio, Rotacions i Escalatge)
	if (TR) glTranslatef(tg.VTras.x, tg.VTras.y, tg.VTras.z);
	glTranslatef(tgF.VTras.x, tgF.VTras.y, tgF.VTras.z);	// Traslacio fixada amb la INSERT dins l'opci? Transformacions
	if (TR) glRotatef(tg.VRota.x, 1, 0, 0);
	glRotatef(tgF.VRota.x, 1, 0, 0);					// Rotacio X fixada amb la INSERT dins l'opci? Transformacions
	if (TR) glRotatef(tg.VRota.y, 0, 1, 0);
	glRotatef(tgF.VRota.y, 0, 1, 0);					// Rotacio Y fixada amb la INSERT dins l'opci? Transformacions
	if (TR) glRotatef(tg.VRota.z, 0, 0, 1);
	glRotatef(tgF.VRota.z, 0, 0, 1);					// Rotacio Z fixada amb la INSERT dins l'opci? Transformacions
	if (TR) glScalef(tg.VScal.x, tg.VScal.y, tg.VScal.z);
	glScalef(tgF.VScal.x, tgF.VScal.y, tgF.VScal.z);	// Escalatge fixada amb la INSERT dins l'opci? Transformacions
}


// deixos: Dibuix dels eixos coordenats
void deixos()
{
	GLuint vboId = 0;	// VBO Index

// vertex coords array for glDrawArrays() =====================================
// The World Coordinates Axes (WCA) are 3 lines, one over X axis (red), one over Y axis (green), one over Z axis(blue),
// the WCA cube consists of 6 vertices (3 axes * 4 vertices = 6 vertices). And, each
// vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
// array is 18 floats (6 * 3 = 18). The size of each float is 4 bytes (72 * 4 = 288 bytes)
	GLfloat vertices[] = { 0.0, 0.0, 0.0, 300.0,   0.0,   0.0,  // X-Axis
						   0.0, 0.0, 0.0,   0.0, 300.0,   0.0,	// Y-Axis
						   0.0, 0.0, 0.0,   0.0,   0.0, 300.0 }; // Z-Axis

	GLfloat colors[] = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0,   // Red color (X-Axis)
						 0.0, 1.0, 0.0, 0.0, 1.0, 0.0,	 // Green color (Y-Axis)
						 0.0, 1.0, 1.0, 0.0, 1.0, 1.0 }; // Blue color (Z-Axis)

// Doblar el gruix de la linia dels eixos.
	glLineWidth(2.0);

	// Create vertex buffer objects, you need to delete them when program exits
	// Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
	// glBufferDataARB with NULL pointer reserves only memory space.
	// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
	// target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
	glGenBuffersARB(1, &vboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(colors), 0, GL_STATIC_DRAW_ARB);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(vertices), vertices);   // copy vertices starting from 0 offest
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices), sizeof(colors), colors);  // copy colors after vertices

// Bind VBOs with IDs and set the buffer offsets of the bound VBOs.
// When buffer object is bound with its ID, all pointers in gl*Pointer()
// are treated as offset instead of real pointer.
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

	// Enable Vertex and Color Arrays
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	// Before draw, specify vertex and color arrays with their offsets
	glColorPointer(3, GL_FLOAT, 0, (void*)sizeof(vertices));
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_LINES, 0, 6);
	/*
	// Eix X (vermell)
		glColor3f(1.0,0.0,0.0);
		glBegin(GL_LINES);
		 glVertex3f(0.0,0.0,0.0);
		 glVertex3f(300.0,0.0,0.0);
		glEnd();

	// Eix Y (verd)
		glColor3f(0.0,1.0,0.0);
		glBegin(GL_LINES);
		 glVertex3f(0.0,0.0,0.0);
		 glVertex3f(0.0,300.0,0.0);
		glEnd();

	// Eix Z (blau)
		glColor3f(0.0,1.0,1.0);
		glBegin(GL_LINES);
		 glVertex3f(0.0,0.0,0.0);
		 glVertex3f(0.0,0.0,300.0);
		glEnd();

	*/

	glDisableClientState(GL_VERTEX_ARRAY);  // Disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);

	// It is good idea to release VBOs with ID 0 after use.
	// Once bound with 0, all pointers in gl*Pointer() behave as real
	// pointer, so, normal vertex array operations are re-activated
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glDeleteBuffersARB(1, &vboId);

	// Restaurar el gruix de la linia dels eixos
	glLineWidth(1.0);
}


// ------------------- GRID (gridXY, gridYZ, gridXZ, gridXYZ) -------------------------

void draw_Grid(CMask3D quadricula, CPunt3D hquadricula)
{
	// Switch on transparency to draw the grid over the scene
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Grids drawing
	if (quadricula.w) gridXYZ(GRID_SIZE);
	{	if (quadricula.x) gridXY(GRID_SIZE, hquadricula.z);
	if (quadricula.y) gridXZ(GRID_SIZE, hquadricula.y);
	if (quadricula.z) gridYZ(GRID_SIZE, hquadricula.x);
	}

	// Switch off transparency
	glDisable(GL_BLEND);
}


// gridXY: Construeix un grid XY de tamany size amb pas 1 situat una alçada h de l'eiz Z.
void gridXY(int size, GLfloat h)
{
	int i;
	//CColor col;
	//bool ref_mat;
	//bool sw_mat[4];

// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, colors;		// Definició vectors dinàmics per a vertexs i colors 
	vertices.resize(0);		colors.resize(0);	// Reinicialitzar vectors

	//ref_mat = false;
	//sw_mat[0] = false;	sw_mat[1] = true;	sw_mat[2] = true;	sw_mat[3] = false;

// Eix X
	//glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	//col.r = 1.0f;	col.g = 0.0f;	col.b = 0.0f;	col.a = 0.5f;
	//SeleccionaColor(ref_mat, sw_mat, col);
	for (i = -size; i < size + 1; i++)
	{	//glBegin(GL_LINES);
		colors.push_back(1.0);			colors.push_back(0.0);			colors.push_back(0.0);
		//glVertex3f(i, -size, h);	// glVertex3f(i, -0.5f, 0.0f);
		vertices.push_back(-i);	vertices.push_back(-size);	vertices.push_back(h);

		colors.push_back(1.0);			colors.push_back(0.0);			colors.push_back(0.0);
		//glVertex3f(i, +size, h);	// glVertex3f(i, +0.5f, 0.0f);
		vertices.push_back(-i);	vertices.push_back(+size);	vertices.push_back(h);

		//glEnd();
	}

	// Eix Y
		//glColor4f(0.0f, 1.0, 0.0f, 0.5f);
		//col.r = 0.0f;	col.g = 1.0f;	col.b = 0.0f;	col.a = 0.5f;
		//SeleccionaColor(ref_mat, sw_mat, col);
	for (i = -size; i < size + 1; i++)
	{	//glBegin(GL_LINES);
		colors.push_back(0.0);			colors.push_back(1.0);			colors.push_back(0.0);
		//glVertex3f(-size, i, h);		// glVertex3f(-0.5f, i, 0.0f);
		vertices.push_back(-size);	vertices.push_back(i);		vertices.push_back(h);

		colors.push_back(0.0);		colors.push_back(1.0);		colors.push_back(0.0);
		//glVertex3f(+size, i, h);		// glVertex3f(+0.5f, i, 0.0f);
		vertices.push_back(+size);	vertices.push_back(i);		vertices.push_back(h);
		glEnd();
	}

	// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.

	draw_GL_LINES_VBO(vertices, colors, nv / 2);
}

// gridXZ: Construeix un grid YZ de tamany size amb pas 1 situat una alçada h de l'eiz Z.
void gridXZ(int size, GLfloat h)
{
	int i;
	//CColor col;
	//bool ref_mat;
	//bool sw_mat[4];

// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, colors;		// Definició vectors dinàmics per a vertexs i colors 
	vertices.resize(0);		colors.resize(0);	// Reinicialitzar vectors

	//ref_mat = false;
	//sw_mat[0] = false;	sw_mat[1] = true;	sw_mat[2] = true;	sw_mat[3] = false;

// Eix X
	//glColor4f(1.0f, 0.0, 0.0f, 0.5f);
	//col.r = 1.0f;	col.g = 0.0f;	col.b = 0.0f;	col.a = 0.5f;
	//SeleccionaColor(ref_mat, sw_mat, col);
	for (i = -size; i < size + 1; i++)
	{	//glBegin(GL_LINES);
		colors.push_back(1.0);			colors.push_back(0.0);			colors.push_back(0.0);
		// glVertex3f(i, h, -size);
		vertices.push_back(i);	vertices.push_back(h);		vertices.push_back(-size);

		colors.push_back(1.0);			colors.push_back(0.0);			colors.push_back(0.0);
		//glVertex3f(i, h, +size); 
		vertices.push_back(i);	vertices.push_back(h);		vertices.push_back(+size);
		//glEnd();
	}

	// Eix Z
		//glColor4f(0.0f, 1.0, 1.0f, 0.5f);
		//col.r = 0.0f;	col.g = 1.0f;	col.b = 1.0f;	col.a = 0.5f;
		//SeleccionaColor(ref_mat, sw_mat, col);
	for (i = -size; i < size + 1; i++)
	{	//glBegin(GL_LINES);
		colors.push_back(0.0);			colors.push_back(1.0);			colors.push_back(1.0);
		//glVertex3f(-size, h, i);
		vertices.push_back(-size);	vertices.push_back(h);		vertices.push_back(i);

		colors.push_back(0.0);			colors.push_back(1.0);			colors.push_back(1.0);
		//glVertex3f(size, h, i);
		vertices.push_back(size);	vertices.push_back(h);		vertices.push_back(i);
		//glEnd();
	}

	// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.

	draw_GL_LINES_VBO(vertices, colors, nv / 2);
}


// gridYZ: Construeix un grid YZ de tamany size amb pas 1 situat una alçada h de l'eiz Z.
void gridYZ(int size, GLfloat h)
{
	int i;
	//CColor col;
	//bool ref_mat;
	//bool sw_mat[4];

// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, colors;		// Definició vectors dinàmics per a vertexs i colors 
	vertices.resize(0);		colors.resize(0);	// Reinicialitzar vectors

	//ref_mat = false;
	//sw_mat[0] = false;	sw_mat[1] = true;	sw_mat[2] = true;	sw_mat[3] = false;

// Eix Y
	//glColor4f(0.0f, 1.0, 0.0f, 0.5f);
	//col.r = 0.0f;	col.g = 1.0f;	col.b = 0.0f;	col.a = 0.5f;
	//SeleccionaColor(ref_mat, sw_mat, col);
	for (i = -size; i < size + 1; i++)
	{	//glBegin(GL_LINES);
		colors.push_back(0.0);			colors.push_back(1.0);			colors.push_back(0.0);
		//glVertex3f(h, i, -size);	// glVertex3f(0.0f, i, -0.5f);
		vertices.push_back(h);	vertices.push_back(i);		vertices.push_back(-size);

		colors.push_back(0.0);			colors.push_back(1.0);			colors.push_back(0.0);
		//glVertex3f(h, i, +size);	// glVertex3f(0.0f, i, 0.5f);
		vertices.push_back(h);	vertices.push_back(i);		vertices.push_back(+size);

		//glEnd();
	}

	// Eix Z
		//glColor4f(0.0f, 1.0, 1.0f, 0.5f);
		//col.r = 0.0f;	col.g = 1.0f;	col.b = 1.0f;	col.a = 0.5f;
		//SeleccionaColor(ref_mat, sw_mat, col);
	for (i = -size; i < size + 1; i++)
	{	//glBegin(GL_LINES);
		colors.push_back(0.0);			colors.push_back(1.0);			colors.push_back(1.0);
		//glVertex3f(h, -size, i);		// glVertex3f(0.0, -0.5f, i);
		vertices.push_back(h);	vertices.push_back(-size);		vertices.push_back(i);

		colors.push_back(0.0);			colors.push_back(1.0);			colors.push_back(1.0);
		//glVertex3f(h, +size, i);		// glVertex3f(0.0f, 0.5f, i);
		vertices.push_back(h);	vertices.push_back(+size);		vertices.push_back(i);
		//glEnd();
	}

	// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.

	draw_GL_LINES_VBO(vertices, colors, nv / 2);
}


// gridXYZ: Construeix un grid 3D de tamany size amb pas 1.
void gridXYZ(int size)
{
	int i, j;
	//CColor col;
	//bool ref_mat;
	//bool sw_mat[4];

// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, colors;		// Definició vectors dinàmics per a vertexs i colors 
	vertices.resize(0);		colors.resize(0);	// Reinicialitzar vectors

	//ref_mat = false;
	//sw_mat[0] = false;	sw_mat[1] = true;	sw_mat[2] = true;	sw_mat[3] = false;

	for (j = -size; j < size; j++)
	{
		// Eix X
				//glColor4f(1.0f, 0.0, 0.0f, 0.5f);
				//col.r = 1.0f;	col.g = 0.0f;	col.b = 0.0f;	col.a = 0.5f;
				//SeleccionaColor(ref_mat, sw_mat, col);
		for (i = -size; i <= size; i++)
		{	//glBegin(GL_LINES);
			colors.push_back(1.0);			colors.push_back(0.0);			colors.push_back(0.0);
			//glVertex3f(i, -size, j);	// glVertex3f(i, -0.5f, z);
			vertices.push_back(i);	vertices.push_back(-size);		vertices.push_back(j);

			colors.push_back(1.0);			colors.push_back(0.0);			colors.push_back(0.0);
			//glVertex3f(i, +size, j);	// glVertex3f(i, +0.5f, z);
			vertices.push_back(i);	vertices.push_back(+size);		vertices.push_back(j);
			//glEnd();
		}

		// Eix Y
				//glColor4f(0.0f, 1.0, 0.0f, 0.5f);
				//col.r = 0.0f;	col.g = 1.0f;	col.b = 0.0f;	col.a = 0.5f;
				//SeleccionaColor(ref_mat, sw_mat, col);
		for (i = -size; i <= size; i++)
		{	//glBegin(GL_LINES);
			colors.push_back(0.0);			colors.push_back(1.0);			colors.push_back(0.0);
			//glVertex3f(-size, i, j);		// glVertex3f(-0.5f, i, z);
			vertices.push_back(-size);	vertices.push_back(i);		vertices.push_back(j);

			colors.push_back(0.0);			colors.push_back(1.0);			colors.push_back(0.0);
			//glVertex3f(+size, i, j);		// glVertex3f(+0.5f, i, z);
			vertices.push_back(+size);	vertices.push_back(i);		vertices.push_back(j);
			//glEnd();
		}
	}

	// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.

	draw_GL_LINES_VBO(vertices, colors, nv / 2);
}



// Fons: Dibuixa el fons variable sefons el color int_fons
void Fons(CColor int_fons)
{
	glClearColor(int_fons.r, int_fons.g, int_fons.b, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_DEPTH_BUFFER_BIT);
	glFlush();
}

// FonsN: Dibuixa el fons negre
void FonsN()
{
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
}

// FonsB: Dibuixa el fons blanc
void FonsB()
{
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glClear(GL_DEPTH_BUFFER_BIT);
	glFlush();
}

// TEXTURES------------------------------------------------------
// loadIMA_SOIL: This function receives as input the image filename and an 
// integer identifier (0 for the first texture) and creates an OpenGL 
// texture which is stored in the global array 'textures'
// It uses SOIL library functions to load the image
// Paràmetres:
//		- filename: Fitxer que conté la imatge de qualsevol format:
//					BMP, JPG, TIFF, TGA, GIF, i d'altres suportats per SOIL
//		- Retorna: Identificador dins la taula textures on volem
//                assignar la imatge
GLint loadIMA_SOIL(char* filename)
{
	FILE* file = NULL;
	int errno;
	char szFilePath[255];
	GLint auxID = -1;

	// Open the image file for reading
	//  file=fopen(nomf,"r");					// Funció Visual Studio 6.0
	errno = fopen_s(&file, filename, "rb");		// Funció Visual 2010

// If the file is empty (or non existent) print an error and return false
// if (file == NULL)
	if (errno != 0)
	{	//	printf("Could not open file '%s'.\n",filename) ;
		return false;
	}

	// Close the image file
	fclose(file);

	// strcpy_s: Conversió variable char* --> char[255]
	strcpy_s(szFilePath, filename); // Copiar path sencer amb nom de fitxer.

// reinterpret_cast: Funció de converió d'una variable char * -> wchar_t *
	wchar_t* nomf = reinterpret_cast <wchar_t*> (szFilePath);


	// SOIL_load_OGL_texture: Funció que llegeix la imatge del fitxer filename
	//				si és compatible amb els formats SOIL (BMP,JPG,GIF,TIF,TGA,etc.)
	//				i defineix la imatge com a textura OpenGL retornant l'identificador 
	//				de textura OpenGL.
	auxID = SOIL_load_OGL_texture
	(filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_DDS_LOAD_DIRECT | SOIL_FLAG_INVERT_Y
	);

	// If execution arrives here it means that all went well. Return true
	return auxID;
}


// TEXTURES------------------------------------------------------
// loadIMA_ILUT: This function receives as input the image filename and an 
// integer identifier (0 for the first texture) and creates an OpenGL 
// texture which is stored in the global array 'textures'
// It uses Devil library functions to load the image
// Paràmetres:
//		- filename: Fitxer que conté la imatge de qualsevol format:
//					BMP, JPG, TIFF, TGA, GIF, i d'altres suportats per OpenIL
//		- Retorna: Identificador dins la taula textures on volem
//                assignar la imatge
GLint loadIMA_ILUT(char* filename)
{
	FILE* file = NULL;
	int errno;
	char szFilePath[255];
	GLint auxID;

	// Open the image file for reading
	//  file=fopen(nomf,"r");					// Funció Visual Studio 6.0
	errno = fopen_s(&file, filename, "rb");		// Funció Visual 2010

// If the file is empty (or non existent) print an error and return false
// if (file == NULL)
	if (errno != 0)
	{
		//	printf("Could not open file '%s'.\n",filename) ;
		return -1;
	}

	// Close the image file
	fclose(file);

	// strcpy_s: Conversió variable char* --> char[255]
	strcpy_s(szFilePath, filename); // Copiar path sencer amb nom de fitxer.

// reinterpret_cast: Funció de converió d'una variable char * -> wchar_t *
	wchar_t* nomf = reinterpret_cast <wchar_t*> (szFilePath);

	// ilutGLLoadImage: Funció que llegeix la imatge del fitxer filename
	//				si és compatible amb els formats DevIL/OpenIL (BMP,JPG,GIF,TIF,TGA,etc.)
	//				i defineix la imatge com a textura OpenGL retornant l'identificador 
	//				de textura OpenGL.
	//	textures[texID] = ilutGLLoadImage(nomf);
	auxID = ilutGLLoadImage(nomf);

	// If execution arrives here it means that all went well. Return true
	return auxID;
}


// SetTextureParameters: Funció que configura paràmetres de l'objecte textura IDText 
// Paràmetres:
//		- IDText: Identificador de l'objecte textura a configurar
//		- extensT: Extén la imatge textura fora dels límits normalitzats (0,1) [TRUE] o no [FALSE]
//		- filterT: Aplica filtre linieal a la imatge textura [TRUE] o pren píxel més proper [FALSE]
//		- blendT: Aplica la funció de blending tenint en compte luminància [TRUE] o només la intensitat de la imatge textura [FALSE]
//		- genMipmpT: Implementa mipmaps sobre la imatge textura [TRUE] o no [FALSE]
void SetTextureParameters(GLint IDText, bool extensT, bool filterT, bool blendT, bool genMipmpT)
{
	glBindTexture(GL_TEXTURE_2D, IDText);

	// Funció de Blending de textura
	if (blendT) glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	else glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	// Extensió de textures
	if (extensT) {	// Configuració textura per a que es repereixi més enllà de coordenades (0,0)-(1,1)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}

	// Filtratge de textures
	if (filterT) {	// Filtratge de textures (GL_LINEAR)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		if (genMipmpT) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		else glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}
	else {	// Filtratge de textures (GL_NEAREST)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		if (genMipmpT) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		else glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	// Activació de MipMaps de la imatge textura
	if (genMipmpT) {	// Activació MIPMAP en textures
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	// Activació i inicialització matriu GL_TEXTURE
	//	glMatrixMode(GL_TEXTURE);
	//	glLoadIdentity();
	//	glRotatef(45.0f, 0.0f, 0.0f, 1.0f); // Rotació 45 graus de la imatge textura

	// Activació i inicialització matriu GL_PROJECTION
	//	glMatrixMode(GL_PROJECTION);
}


/* Inicialitzar imatges textures pel Truck
void Init_Textures()
{	loadIMA_ILUT("./textures/vent.bmp",1);

	loadIMA_ILUT("./textures/plat.bmp",2);

	loadIMA_ILUT("./textures/reixeta.bmp",3);

	loadIMA_ILUT("./textures/fars.bmp",4);

	loadIMA_ILUT("./textures/txapa.bmp",5);

	loadIMA_ILUT("./textures/metall.bmp",6);
}
*/

//----------------- FONTS LLIBRERIA GLU

// gluLookAt: Funció defineix matriu de PV i la carrega a l'estructura de matrius OpenGL 
void gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx,
	GLdouble centery, GLdouble centerz, GLdouble upx, GLdouble upy,
	GLdouble upz)
{
	float forward[3], side[3], up[3];
	GLfloat m[4][4];

	forward[0] = centerx - eyex;
	forward[1] = centery - eyey;
	forward[2] = centerz - eyez;

	up[0] = upx;
	up[1] = upy;
	up[2] = upz;

	normalize(forward);

	/* Side = forward x up */
	cross(forward, up, side);
	normalize(side);

	/* Recompute up as: up = side x forward */
	cross(side, forward, up);

	__gluMakeIdentityf(&m[0][0]);
	m[0][0] = side[0];
	m[1][0] = side[1];
	m[2][0] = side[2];

	m[0][1] = up[0];
	m[1][1] = up[1];
	m[2][1] = up[2];

	m[0][2] = -forward[0];
	m[1][2] = -forward[1];
	m[2][2] = -forward[2];

	glMultMatrixf(&m[0][0]);
	glTranslated(-eyex, -eyey, -eyez);
}

// gluLookAt: Funció defineix matriu de Projecció Perspectiva i la carrega a l'estructura de matrius OpenGL 
void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	GLdouble m[4][4];
	double sine, cotangent, deltaZ;
	double radians = fovy / 2 * __glPi / 180;

	deltaZ = zFar - zNear;
	sine = sin(radians);
	if ((deltaZ == 0) || (sine == 0) || (aspect == 0)) {
		return;
	}
	cotangent = cos(radians) / sine;

	__gluMakeIdentityd(&m[0][0]);

	m[0][0] = cotangent / aspect;
	m[1][1] = cotangent;
	m[2][2] = -(zFar + zNear) / deltaZ;
	m[2][3] = -1;
	m[3][2] = -2 * zNear * zFar / deltaZ;
	m[3][3] = 0;
	glMultMatrixd(&m[0][0]);
}


// gluMakeIdentityf: Funció defineix una matriu identitat 
static void __gluMakeIdentityf(GLfloat m[16])
{
	m[0 + 4 * 0] = 1; m[0 + 4 * 1] = 0; m[0 + 4 * 2] = 0; m[0 + 4 * 3] = 0;
	m[1 + 4 * 0] = 0; m[1 + 4 * 1] = 1; m[1 + 4 * 2] = 0; m[1 + 4 * 3] = 0;
	m[2 + 4 * 0] = 0; m[2 + 4 * 1] = 0; m[2 + 4 * 2] = 1; m[2 + 4 * 3] = 0;
	m[3 + 4 * 0] = 0; m[3 + 4 * 1] = 0; m[3 + 4 * 2] = 0; m[3 + 4 * 3] = 1;
}

static void __gluMakeIdentityd(GLdouble m[16])
{
	m[0 + 4 * 0] = 1; m[0 + 4 * 1] = 0; m[0 + 4 * 2] = 0; m[0 + 4 * 3] = 0;
	m[1 + 4 * 0] = 0; m[1 + 4 * 1] = 1; m[1 + 4 * 2] = 0; m[1 + 4 * 3] = 0;
	m[2 + 4 * 0] = 0; m[2 + 4 * 1] = 0; m[2 + 4 * 2] = 1; m[2 + 4 * 3] = 0;
	m[3 + 4 * 0] = 0; m[3 + 4 * 1] = 0; m[3 + 4 * 2] = 0; m[3 + 4 * 3] = 1;
}

static void normalize(float v[3])
{
	float r;

	r = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (r == 0.0) return;

	v[0] /= r;
	v[1] /= r;
	v[2] /= r;
}

static void cross(float v1[3], float v2[3], float result[3])
{
	result[0] = v1[1] * v2[2] - v1[2] * v2[1];
	result[1] = v1[2] * v2[0] - v1[0] * v2[2];
	result[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

