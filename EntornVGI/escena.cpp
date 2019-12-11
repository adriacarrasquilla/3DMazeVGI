﻿//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn b�sic VS2019 MULTIFINESTRA amb OpenGL, interf�cie MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Setembre 2019)
// escena.cpp : Aqui es on ha d'anar el codi de les funcions que 
//              dibuixin les escenes.
//
//    Versi� 2.0:	- Objectes Cub, Esfera, Tetera (primitives libreria GLUT) i Truck (cami� americ� fet per alumnes)
//
//	  Versi� 2.2:	- Objectes Cub, Esfera, Tetera definides en fitxer font glut_geometry amb altres primitives GLUT
//
//	  Versi� 2.5:	- Objectes cubRGB i Tie (nau Star Wars fet per alumnes)
//

#include "stdafx.h"
#include "material.h"
#include "visualitzacio.h"
#include "escena.h"
#include <string>
#include <time.h>
#include "glut_font.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
		   /*VARIABLE GLOBAL PER ANIMACIO DE MUR QUE BAIXA*/
bool ActivacioIniciEnCursOJaRealitzada = false;
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

//SO

irrklang::ISoundSource* soAmbient = SoundEngine->addSoundSourceFromFile("audio/minecraft_lofi.mp3");
irrklang::ISoundSource* soVictoria = SoundEngine->addSoundSourceFromFile("audio/all_star.mp3");
irrklang::ISoundSource* soDerrota = SoundEngine->addSoundSourceFromFile("audio/shittyflute.mp3");
irrklang::ISoundSource* soColisio = SoundEngine->addSoundSourceFromFile("audio/damage.mp3");
irrklang::ISoundSource* soLvl1 = SoundEngine->addSoundSourceFromFile("audio/poke.mp3"); //Pokemon
irrklang::ISoundSource* soLvl2 = SoundEngine->addSoundSourceFromFile("audio/bonetrousle.mp3"); //medium
irrklang::ISoundSource* soLvl3 = SoundEngine->addSoundSourceFromFile("audio/epic.mp3"); //epic
irrklang::ISoundSource* soLvl4 = SoundEngine->addSoundSourceFromFile("audio/megalovania.mp3"); //final boss


bool i = true;
bool i_d = false;
bool i_v = false;
bool temps_once = false;

int temps_menu = 0; /// de moment assumeixo que el leaderboard no existeix :)

//TEXT ESCENA
void drawBitmapText(const char* string, float x, float y, float z)
{
	const char* c;
	glRasterPos3f(x, y, z);

	for (c = string; *c != '\n'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, *c);
	}
}

//TEXT STROKE XULO GUAPO PRECIOS
void drawStrokeText(const char* string, int x, int y, int z)
{
	const char* c;
	//ES POT TRACTAR COM SI FOS UNA "TEXTURA":
	glPushMatrix();	
	glTranslatef(x, y + 8, z);
	glScalef(0.09f, -0.08f, z);

	for (c = string; *c != '\n'; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}

Leaderboard leaderboard;
int puntuacio = 0;
float temps = 0.0;
float temps_final = 0.0;
float temps_pausa = 0.0;
clock_t tp = 0.0;
//float angle = 0.0;
clock_t begin_time = clock();
bool reset_clock = true;

std::string remove_zeros(std::string temps) {
	std::string res = "";
	int count = 0;
	for (auto x : temps)
	{
		res = res + x;
		count++;
		if (x == '.') {
			res = res + temps[count] + temps[count + 1] + temps[count + 2];
			break;
		}
	}
	return res;
}

// Variables de color i reflexi� de materials pels objectes d'escena
CColor color_objecte;
bool reflexio_material, sw_materials[4];


//bool * CheckColisioMurPg(Mur m, Personatge p) {
bool* CheckColisioMurPg(Mur m, Personatge p) {
	bool colisions[4]; //0 dreta 1 esquerra 2 amunt 3 avall
	bool colXY[2] = { false };
	if (m.m_ori) {

		// Collision x-axis?
		bool collisionX = m.m_x + (MUR_X / 2) >= p.m_x - (PG_X / 2) &&
			p.m_x + (PG_X / 2) >= m.m_x - (MUR_X / 2);
		// Collision y-axis?
		bool collisionY = m.m_y + (MUR_Y / 2) >= p.m_y - (PG_Y / 2) &&
			p.m_y + (PG_Y / 2) >= m.m_y - (MUR_Y / 2);
		// Collision only if on both axes

		//return collisionX && collisionY;

		if (collisionX && collisionY) {
			/// Colisions eix X
			/// Colisió paret dreta
			colisions[0] = p.m_x + (PG_X / 2) >= m.m_x + (MUR_X / 2) && p.m_x - (PG_X / 2) <= m.m_x + (MUR_X / 2);
			/// Colisió paret esquerra
			colisions[1] = p.m_x + (PG_X / 2) >= m.m_x - (MUR_X / 2) && p.m_x - (PG_X / 2) <= m.m_x - (MUR_X / 2);

			/// Colisions eix Y
			/// Colisió paret amunt
			colisions[2] = p.m_y + (PG_Y / 2) >= m.m_y - (MUR_Y / 2) && p.m_y - (PG_Y / 2) <= m.m_y - (MUR_Y / 2);
			/// Colisió paret avall
			colisions[2] = p.m_y + (PG_Y / 2) >= m.m_y + (MUR_Y / 2) && p.m_y - (PG_Y / 2) <= m.m_y + (MUR_Y / 2);

			colXY[0] = colisions[0] || colisions[1];
			colXY[1] = colisions[2] || colisions[3];
		}
	}
	else {

		// Collision x-axis?
		bool collisionX = m.m_x + (MUR_Y / 2) >= p.m_x - (PG_X / 2) &&
			p.m_x + (PG_X / 2) >= m.m_x - (MUR_Y / 2);
		// Collision y-axis?
		bool collisionY = m.m_y + (MUR_X / 2) >= p.m_y - (PG_Y / 2) &&
			p.m_y + (PG_Y / 2) >= m.m_y - (MUR_X / 2);
		// Collision only if on both axes
		//return collisionX && collisionY;

		if (collisionX && collisionY) {
			/// Colisions eix X
			/// Colisió paret dreta
			colisions[0] = p.m_x + (PG_X / 2) >= m.m_x + (MUR_Y / 2) && p.m_x - (PG_X / 2) <= m.m_x + (MUR_Y / 2);
			/// Colisió paret esquerra
			colisions[1] = p.m_x + (PG_X / 2) >= m.m_x - (MUR_Y / 2) && p.m_x - (PG_X / 2) <= m.m_x - (MUR_Y / 2);

			/// Colisions eix Y
			/// Colisió paret amunt
			colisions[2] = p.m_y + (PG_Y / 2) >= m.m_y - (MUR_X / 2) && p.m_y - (PG_Y / 2) <= m.m_y - (MUR_X / 2);
			/// Colisió paret avall
			colisions[2] = p.m_y + (PG_Y / 2) >= m.m_y + (MUR_X / 2) && p.m_y - (PG_Y / 2) <= m.m_y + (MUR_X / 2);

			colXY[0] = colisions[0] || colisions[1];
			colXY[1] = colisions[2] || colisions[3];
		}
	}
	return colXY;
}

bool CheckColisioEvent(Event e, Personatge p) {
	bool collisionX = e.m_x + (E_X / 2) >= p.m_x - (PG_X / 2) &&
		p.m_x + (PG_X / 2) >= e.m_x - (E_X / 2);
	// Collision y-axis?
	bool collisionY = e.m_y + (E_Y / 2) >= p.m_y - (PG_Y / 2) &&
		p.m_y + (PG_Y / 2) >= e.m_y - (E_Y / 2);

	return collisionX && collisionY;
}

bool CheckColisioPunxes(Mur m, Personatge p) {
	bool onTrap = m.m_x + (MUR_X / 2) >= p.m_x - (PG_X / 2) &&
		p.m_x + (PG_X / 2) >= m.m_x - (MUR_X / 2) && m.m_y + (MUR_Y / 2) >= p.m_y - (PG_Y / 2) &&
		p.m_y + (PG_Y / 2) >= m.m_y - (MUR_Y / 2);
	return onTrap && (m.m_z > -5);
}

bool CheckColisioShrek(Shrek shrek, Personatge p) {
	/*
	float mida = 5.5;
	glPushMatrix();
	glTranslatef(shrek[0], shrek[1], shrek[2] + 7.5);
	glScalef(20.0, mida, mida);
	glutSolidCube(1.0);7
	glPopMatrix();
	*/
	/*
	bool collisionX = shrek[0] + (SH_X / 2) >= p.m_x - (PG_X / 2) && p.m_x + (PG_X / 2) >= shrek[0] - (SH_X / 2);
	// Collision y-axis?
	bool collisionY = shrek[1] + (SH_Y / 2) >= p.m_y - (PG_Y / 2) && p.m_y + (PG_Y / 2) >= shrek[1] - (SH_Y / 2);
	*/
	if (shrek.m_ori) {
		bool collisionX = shrek.m_pos_x + (SH_X / 2) >= p.m_x - (PG_X / 2) && p.m_x + (PG_X / 2) >= shrek.m_pos_x - (SH_X / 2);
		// Collision y-axis?
		bool collisionY = shrek.m_pos_y + (SH_Y / 2) >= p.m_y - (PG_Y / 2) && p.m_y + (PG_Y / 2) >= shrek.m_pos_y - (SH_Y / 2);

		return collisionX && collisionY;
	}
	else {
		bool collisionX = shrek.m_pos_x + (SH_Y / 2) >= p.m_x - (PG_X / 2) && p.m_x + (PG_X / 2) >= shrek.m_pos_x - (SH_Y / 2);
		// Collision y-axis?
		bool collisionY = shrek.m_pos_y + (SH_X / 2) >= p.m_y - (PG_Y / 2) && p.m_y + (PG_Y / 2) >= shrek.m_pos_y - (SH_X / 2);

		return collisionX && collisionY;
	}
}

void DoCollisions(std::vector<Mur> llista, Personatge& pg, Event& e, std::vector<Event>& eventMursBaixada, std::vector<Mur>& punxes, std::vector<Shrek> v_Shreks)//std::vector<std::vector<float>>& Shreks)
{
	pg.m_colisioX = false;
	pg.m_colisioY = false;

	bool* colXY;
	for (int i = 0; i < llista.size(); i++)
	{
		if (llista[i].m_z <= 10.0f)
		{
			colXY = CheckColisioMurPg(llista[i], pg);
			if (colXY[0])
			{
				pg.m_colisioX = true;
				if (llista[i].esUnMurAnimatQueCau && !llista[i].animacioAcabada) {
					pg.dead = true;
					SoundEngine->play2D(soColisio, GL_FALSE);
					break;
				}
			}
			if (colXY[1])
			{
				pg.m_colisioY = true;
				if (llista[i].esUnMurAnimatQueCau && !llista[i].animacioAcabada) {
					pg.dead = true;
					SoundEngine->play2D(soColisio, GL_FALSE);
					break;
				}
			}
		}
	}
	if (pg.m_colisioX)
		pg.m_color = 1;
	else if (pg.m_colisioY)
		pg.m_color = 2;
	else
		pg.m_color = 0;

	if (CheckColisioEvent(e, pg)) {
		e.m_colisio = true;
	}
	else
		e.m_colisio = false;

	for (int i = 0; i < eventMursBaixada.size(); i++)
	{
		if (CheckColisioEvent(eventMursBaixada[i], pg)) {
			if (!eventMursBaixada[i].eventFinalitzat)
			{
				eventMursBaixada[i].m_colisio = true;

				eventMursBaixada[i].m_animacioIniciada = true;
			}
		}
		else
			eventMursBaixada[i].m_colisio = false;
	}
	for (int i = 0; i < punxes.size(); i++) {
		if (CheckColisioPunxes(punxes[i], pg)) {
			pg.dead = true;
			SoundEngine->play2D(soColisio, GL_FALSE);
			break;
		}
	}

	for (int i = 0; i < v_Shreks.size(); i++) {
		if (CheckColisioShrek(v_Shreks[i], pg)) {
			pg.dead = true;
			SoundEngine->play2D(soColisio, GL_FALSE);
			break;
		}
	}

}

void skybox(int texturID[], float cel[]) {
	//Cara left
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, texturID[11]);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(750.0f + cel[0], 0.0f + cel[1], 0.0f + cel[2]);
	glScalef(5.0f, 1500.0f, 1500.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//Cara right
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, texturID[10]);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(-750.0f + cel[0], 0.0f + cel[1], 0.0f + cel[2]);
	glScalef(5.0f, 1500.0f, 1500.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//Cara bot
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, texturID[13]);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0.0f + cel[0], 0.0f + cel[1], -750.0f + cel[2]);
	glScalef(1500.0f, 1500.0f, 5.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//Cara top
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, texturID[12]);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0.0f + cel[0], 0.0f + cel[1], 750.0f + cel[2]);
	glScalef(-1500.0f, -1500.0f, 5.0f);
	glutSolidCube(1.0);
	glPopMatrix();

	//Cara back
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, texturID[15]);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0.0f + cel[0], 750.0f + cel[1], 0.0f + cel[2]);
	glScalef(-1500.0f, 0.0f, 1500.0f);
	glutSolidCube(1.0);
	glPopMatrix();


	//Cara front
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glBindTexture(GL_TEXTURE_2D, texturID[14]);
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);


	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(0.0f + cel[0], -750.0f + cel[1], 0.0f + cel[2]);
	glScalef(1500.0f, 0.0f, 1500.0f);
	glutSolidCube(1.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


}

//Metode que corrobora si s'ha de crear un mur animació de caiguda o no fa falta
bool activavioDeMurCaiguda(Mur& murCaiguda, std::vector<Mur>& llista, bool& ActivacioIniciEnCursOJaRealitzada)
{

	float x = 5.0f; //Coordenada
	float h = 7.5f; //Altura

	if (!ActivacioIniciEnCursOJaRealitzada)
	{
		murCaiguda.setMur(-x - x / 2, x * 2, h * 5.0f, HOR, 3 * x);
		llista.push_back(murCaiguda);
		//murCaiguda.pinta();
		ActivacioIniciEnCursOJaRealitzada = true;
	}

	return ActivacioIniciEnCursOJaRealitzada;


}

void punxes(std::vector<Mur> punxesAnimadetes, objl::Loader loader)
{
	for (int i = 0; i < punxesAnimadetes.size(); i++)
	{
		glPushMatrix();
		float x = punxesAnimadetes[i].m_x;
		float y = punxesAnimadetes[i].m_y;
		float z = punxesAnimadetes[i].m_z;
		glTranslatef(x, y, z);
		glRotatef(90, 1, 0, 0);
		glScalef(0.001f, 0.001f, 0.001f);
		glBegin(GL_TRIANGLES);

		for (int i = 0; i < loader.LoadedVertices.size(); i++)
		{
			glVertex3f(loader.LoadedVertices[i].Position.X, loader.LoadedVertices[i].Position.Y, loader.LoadedVertices[i].Position.Z);
		}
		glEnd();

		glPopMatrix();
	}
}


void tauleta(objl::Loader loader, int texturID[], float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(90, 1, 0, 0);
	glScalef(2.5f, 2.5f, 2.5f);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texturID[18]);

	glBegin(GL_TRIANGLE_STRIP);

	for (int ii = 0; ii < loader.LoadedMeshes.size(); ii++)
	{

		for (int i = 0; i < loader.LoadedMeshes[ii].Vertices.size(); i++)
		{
			glTexCoord2f(loader.LoadedMeshes[ii].Vertices[i].TextureCoordinate.X, loader.LoadedMeshes[ii].Vertices[i].TextureCoordinate.Y); glVertex3f(loader.LoadedMeshes[ii].Vertices[i].Position.X, loader.LoadedMeshes[ii].Vertices[i].Position.Y, loader.LoadedMeshes[ii].Vertices[i].Position.Z);
		}

	}

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void globus(objl::Loader loader, int texturID[], float x, float y, float z, float colorRed, float colorGreen, float colorBlue)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(90, 1, 0, 0);
	glScalef(100.0f, 100.0f, 100.0f);
	glPushAttrib(GL_CURRENT_BIT);
	glColor3f(colorRed, colorGreen, colorBlue);

	//glBindTexture(GL_TEXTURE_2D, texturID[19]);

	glBegin(GL_TRIANGLES);

	for (int i = 0; i < loader.LoadedVertices.size(); i++)
	{
		glVertex3f(loader.LoadedVertices[i].Position.X, loader.LoadedVertices[i].Position.Y, loader.LoadedVertices[i].Position.Z);
	}
	glEnd();

	glPopAttrib();

	glPopMatrix();

}

void HUDSquare()
{
	//Cuadrat HUD
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(1.9, 1.29, -3);
	glColor3f(0.345f, 0.608f, 0.0f);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(1.5, 0, 0);
	glVertex3f(1.5, 1.5, 0);
	glVertex3f(0, 1.5, 0);
	glEnd();
	glPopMatrix();
	//Quadrat extern
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(1.8, 1.19, -3);
	glColor3f(0.55f, 0.55f, 0.51f);
	glBegin(GL_QUADS);
	glVertex3f(0, 0, 0);
	glVertex3f(1.5, 0, 0);
	glVertex3f(1.5, 1.5, 0);
	glVertex3f(0, 1.5, 0);
	glEnd();
	glPopMatrix();
}

// dibuixa_EscenaGL: Dibuix de l'escena amb comandes GL
void dibuixa_EscenaGL(char objecte, CColor col_object, bool ref_mat, bool sw_mat[4], bool textur, GLint texturID[NUM_MAX_TEXTURES], bool textur_map,
	int nptsU, CPunt3D PC_u[MAX_PATCH_CORBA], GLfloat pasCS, bool sw_PC, float mov[], std::vector<Mur> llista, Personatge& pg, float cel[], objl::Loader loader[],
	float movimentShrek[], bool movDir[], float rotShrek[], float movimentShrek2[], bool movDir2[], float rotShrek2[], Event& eventfinal, std::vector<Event>& eventsMursBaixada, std::vector<Mur> punxesAnimadetes, std::vector<Mur> sales,
	int lifes, int MIDA_I, int MIDA_J, int musica, bool pausa, char lvl, bool& changeLvl, std::vector<Shrek> v_Shreks, bool& menu)
{
	float altfar = 0;
	soAmbient->setDefaultVolume(0.7);
	soLvl2->setDefaultVolume(0.1);
	soLvl3->setDefaultVolume(0.4);
	soLvl4->setDefaultVolume(0.3);
	// Assignaci� de les variables de color i reflexi� als valors de les variables per par�metre
	color_objecte = col_object;
	reflexio_material = ref_mat;
	for (int i = 0; i < 4; i++) sw_materials[i] = sw_mat[i];

	if (texturID[0] != -1) SetTextureParameters(texturID[0], true, true, textur_map, false);
	if (textur) glEnable(GL_TEXTURE_2D);
	else glDisable(GL_TEXTURE_2D);
	if (changeLvl) i = true;

	switch (objecte)
	{

		// Mur
	case MUR:
	{
		//if (!pausa) {
		if (i && musica == 0 && lvl == 1) {
			SoundEngine->stopAllSoundsOfSoundSource(soAmbient);
			SoundEngine->stopAllSoundsOfSoundSource(soDerrota);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl2);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl3);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl1);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl4);

			soLvl1->setDefaultVolume(0.1f);
			SoundEngine->play2D(soLvl1, GL_TRUE);
			i = false;
			changeLvl = false;
			i_d = true;
			i_v = true;
			if (!reset_clock) begin_time = clock();
			tp = 0.0;
			leaderboard.set_const_valor(300);
		}
		else if (i && musica == 0 && lvl == 2) {
			SoundEngine->stopAllSoundsOfSoundSource(soAmbient);
			SoundEngine->stopAllSoundsOfSoundSource(soDerrota);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl2);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl3);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl1);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl4);

			SoundEngine->play2D(soLvl2, GL_TRUE);
			i = false;
			changeLvl = false;
			i_d = true;
			i_v = true;
			begin_time = clock();
			tp = 0.0;
			leaderboard.set_const_valor(500);
		}
		else if (i && musica == 0 && lvl == 3) {
			SoundEngine->stopAllSoundsOfSoundSource(soAmbient);
			SoundEngine->stopAllSoundsOfSoundSource(soDerrota);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl2);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl3);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl1);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl4);

			SoundEngine->play2D(soLvl3, GL_TRUE);
			i = false;
			changeLvl = false;
			i_d = true;
			i_v = true;
			begin_time = clock();
			tp = 0.0;
			leaderboard.set_const_valor(800);
		}
		else if (i && musica == 0 && lvl == 4) {
			SoundEngine->stopAllSoundsOfSoundSource(soAmbient);
			SoundEngine->stopAllSoundsOfSoundSource(soDerrota);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl2);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl3);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl1);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl4);

			SoundEngine->play2D(soLvl4, GL_TRUE);
			i = false;
			changeLvl = false;
			i_d = true;
			i_v = true;
			begin_time = clock();
			tp = 0.0;
			leaderboard.set_const_valor(1000);
		}
		else if (i_v && musica == 1) {

			SoundEngine->play2D(soVictoria, GL_TRUE);
			SoundEngine->stopAllSoundsOfSoundSource(soAmbient);
			SoundEngine->stopAllSoundsOfSoundSource(soDerrota);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl2);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl3);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl1);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl4);

			temps_final = float(clock() - begin_time + tp) / CLOCKS_PER_SEC;
			leaderboard.init_leaderboard(lvl);
			puntuacio = leaderboard.calcula_punts(lifes, temps_final);
			leaderboard.actualitza_leaderboard();
			i_v = false;
		}
		else if (i_d && musica == 2) {

			SoundEngine->play2D(soDerrota, GL_TRUE);
			SoundEngine->stopAllSoundsOfSoundSource(soAmbient);
			SoundEngine->stopAllSoundsOfSoundSource(soVictoria);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl2);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl3);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl1);
			SoundEngine->stopAllSoundsOfSoundSource(soLvl4);

			temps_final = float(clock() - begin_time + tp) / CLOCKS_PER_SEC;

			i_d = false;
		}




		glClearColor(0.5294f, 0.8078f, 0.9216f, 0.71f);
		glClear(GL_COLOR_BUFFER_BIT);


		//Textura parets

		glColor3f(1.0, 1.0, 1.0);

		glDisable(GL_TEXTURE_2D);
		GLfloat sPlane2[4] = { 10.00f, 0.00f, 0.00f, 10.00f };
		GLfloat tPlane2[4] = { 0.00f, 10.00f, 10.00f, 0.00f };


		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glBindTexture(GL_TEXTURE_2D, texturID[8]);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);


		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		//Animació mur caiguda
		Mur murCaiguda;
		ActivacioIniciEnCursOJaRealitzada = activavioDeMurCaiguda(murCaiguda, llista, ActivacioIniciEnCursOJaRealitzada);
		//animacioMurQueCauInici = ActivacioIniciEnCursOJaRealitzada;
		if (ActivacioIniciEnCursOJaRealitzada)
		{
			llista.back().animacioBaixada();

		}



		glEnable(GL_TEXTURE_2D);
		for (int i = 0; i < llista.size(); i++) {
			llista[i].pinta();
		}
		for (int i = 0; i < sales.size(); i++) {
			sales[i].pinta();
		}
		punxes(punxesAnimadetes, loader[1]);

		//
		//Textures terra
		glDisable(GL_TEXTURE_2D);
		GLfloat sPlane[4] = { 10.00f, 0.00f, 10.00f, 0.00f };
		GLfloat tPlane[4] = { 0.00f, 10.00f, 0.00f, 0.00f };
		glBindTexture(GL_TEXTURE_2D, texturID[9]);

		glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glEnable(GL_TEXTURE_2D);

		//Terra del laberint
		glPushMatrix();
		glTranslatef(50.0f, 50.0f, -5.0f);
		glScalef(MIDA_I * 8 * 5.0F, MIDA_J * 8 * 5.0F, 10.0f);
		glutSolidCube(1.0);
		glPopMatrix();

		/*
		glPushMatrix();
			glTranslatef(50.0f, 50.0f, -5.0f);
			glScalef(250.0f, 250.0f, 10.0f);
			glutSolidCube(1.0);
		glPopMatrix();
		*/

		// Terra de la sala de la derrota
		glPushMatrix();
		glTranslatef(120.0f, 62.5f, -62.5f);
		glScalef(45.0f, 45.0f, 10.0f);
		glutSolidCube(1.0);
		glPopMatrix();

		// Terra de la sala de la victòria
		glPushMatrix();
		glTranslatef(70.0f, 62.5f, -62.5f);
		glScalef(45.0f, 45.0f, 10.0f);
		glutSolidCube(1.0);
		glPopMatrix();


		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);



		skybox(texturID, cel);

		// S H R E K S

			//float Shreks[1][3];

			/* EI AIXÒ ÉS COM FUNCIONAVA ABANS, A VEURE SI AMB EL CANVI SEGUEIX
			std::vector<std::vector<float>> Shreks;


			// SHREK ENEMIC 1
			std::vector<float> Shrek1(3, 0);
			Shreks.push_back(Shrek1);
			shrek(loader[0], movimentShrek, movDir, rotShrek, texturID, 0, Posicio_x_inicial, Posicio_y_inicial, Posicio_x_final, Posicio_y_final, 0.0, Shreks[0][0], Shreks[0][1], Shreks[0][2], pausa);
			*/

			/*float mida = 5.5;
			glPushMatrix();
			glTranslatef(Shreks[0][0], Shreks[0][1], Shreks[0][2] + 7.5);
			glScalef(20.0, mida, 14.0);
			glutSolidCube(1.0);
			glPopMatrix();
			*/

		for (int i = 0; i < v_Shreks.size(); i++) {
			printf("pos: %d", v_Shreks[i].m_pos_x);
			v_Shreks[i].pinta(pausa);
		}

		// SHREKS SALA DERROTA

		//Shrek skizo del gif
		//shrek(loader[0], movimentShrek, movDir, rotShrek, texturID, 1, 135.0, 62.5, 130.0, 62.5, -57.5);

		// de moment, un i estàtic  

		/*float noMov[3] = { 0.0, 0.0, 0.0 };
		float noRot[3] = { 0.0, -1.0, 0.0 };
		float Shrek2[3]; // NO ESTÀ A Shreks PERQUÈ NO CAL CALCULAR-NE LA COL·LISIÓ
		//shrek(loader[0], noMov, movDir, noRot, texturID, 2, 135.0, 62.5, 130.0, 62.5, -57.5, Shrek2[0], Shrek2[1], Shrek2[2]);
		shrek(loader[0], noMov, movDir, noRot, texturID, 2, 77.5, 120.0, 77.5, 120.0, -57.5, Shrek2[0], Shrek2[1], Shrek2[2], pausa);
		*/

		//Shrek fora de v_Shreks perquè no en calculem la col·lisió:
		float noMov[3] = { 0.0, 0.0, 0.0 };
		float noRot[3] = { 0.0, -1.0, 0.0 };
		float Shrek2[3];
		Shrek derrota(&loader[0], noMov, movDir, noRot, texturID, 2, 77.5, 120.0, 77.5, 120.0, -57.5, Shrek2[0], Shrek2[1], Shrek2[2], true);
		derrota.pinta(pausa);
		//Shrek(objl::Loader* loader, float moviment[], bool movDir[], float rotShrek[], int texturID[], int tipusMov, float posicioIniciX, float posicioIniciY, float posicioFinalX, float posicioFinalY, float posicioZ, float& pos_x, float& pos_y, float& pos_z, bool ori)
		bool test[] = { false, false, false };
		float test2[] = { 0,1,0 };
		Shrek victoria(&loader[0], movimentShrek2, movDir2, rotShrek2, texturID, 1, 72.5, 120.0, 72.5, 120.0, -57.5, Shrek2[0], Shrek2[1], Shrek2[2], true);
		victoria.pinta(pausa);
		//Altres objectes
		tauleta(loader[2], texturID, 70.5, 75, -57.5);
		globus(loader[3], texturID, 54.5, 75, -50, 1.0f, 0.0f, 0.0f);
		globus(loader[3], texturID, 59.5, 75, -50, 1.0f, 0.5f, 0.0f);
		globus(loader[3], texturID, 64.5, 75, -50, 1.0f, 1.0f, 0.0f);
		globus(loader[3], texturID, 69.5, 75, -50, 0.0f, 1.0f, 0.0f);
		globus(loader[3], texturID, 74.5, 75, -50, 0.0f, 0.0f, 1.0f);
		globus(loader[3], texturID, 79.5, 75, -50, 0.25f, 0.0f, 0.5f);
		globus(loader[3], texturID, 84.5, 75, -50, 0.5f, 0.0f, 1.0f);
		

		//eventfinal.pinta();

		//pg.pinta();
		DoCollisions(llista, pg, eventfinal, eventsMursBaixada, punxesAnimadetes, v_Shreks);

		//HUD Quadrat
		HUDSquare();

		//Una merda cap tot en la funcio
		if (reset_clock) {
			//Això fa que el temps es posi a 0 quan es comença una partida.
			//NOTA: al carregar un mapa nou, posar reset_clock = true!!!
			begin_time = clock() - begin_time;
			reset_clock = false;
		}

		temps = float(clock() - begin_time + tp) / CLOCKS_PER_SEC;
		std::string hud_temps = "TEMPS: " + remove_zeros(std::to_string(temps)) + "\n";
		std::string hud_vides = "VIDES: " + std::to_string(lifes) + "\n";
		const char* cstr_temps = hud_temps.c_str();
		const char* cstr_vides = hud_vides.c_str();

		/*HUD TEMPS*/
		if (!i && musica == 0 && !pausa) {
			glPushMatrix();
			glLoadIdentity();
			glColor3f(.0f, .0f, .0f);
			drawBitmapText(cstr_temps, 1.5, 1.09, -2);
			glPopMatrix();
			temps_once = false;
		}
		if (pausa) {
			if (!temps_once) {
				temps_pausa = temps;
				temps_once = true;
			}
			std::string hud_temps_pausa = "TEMPS: " + remove_zeros(std::to_string(temps_pausa)) + "\n";
			const char* cstr_temps_pausa = hud_temps_pausa.c_str();
			begin_time = clock();
			tp = temps_pausa * CLOCKS_PER_SEC;
			glPushMatrix();
			glLoadIdentity();
			glColor3f(.0f, .0f, .0f);
			drawBitmapText(cstr_temps_pausa, 1.5, 1.09, -2);
			glPopMatrix();

			glPushMatrix();
			glLoadIdentity();
			glColor3f(1.0f, 1.0f, 1.0f);
			drawBitmapText("PAUSE\n", -0.3, 0.15, -2);
			drawBitmapText("PREM LA TECLA PER:\n", -0.3, 0.1, -2);
			drawBitmapText("P - REPRENDRE EL JOC\n", -0.3, 0.05, -2);
			drawBitmapText("1 - PASSAR AL SEGUENT NIVELL\n", -0.3, 0.0, -2);
			drawBitmapText("2 - REINICIAR EL NIVELL ACTUAL\n", -0.3, -0.05, -2);
			drawBitmapText("3 - SORTIR DEL JOC\n", -0.3, -0.1, -2);
			glPopMatrix();
		}

		/*HUD VIDES*/
		glPushMatrix();
		glLoadIdentity();
		glColor3f(1.0f, 1.0f, 1.0f);
		drawBitmapText(cstr_vides, 1.5, 1.05, -2);
		glPopMatrix();


		//MISATGES VICTORY / DEFEAT
		if (musica == 0) {
			temps_menu = 0;
		}

		if (!i_v && musica == 1) {

			std::string tf = "TEMPS: " + remove_zeros(std::to_string(temps_final)) + "\n";
			const char* cstr_tf = tf.c_str();

			if (temps_menu < 700) {
				glPushMatrix();
				glLoadIdentity();
				glColor3f(.0f, 0.8f, .0f);
				drawBitmapText("VICTORIA\n", -0.15, 0, -2);
				glPopMatrix();
				std::string punts = "PUNTUACIO: " + std::to_string(puntuacio) + "\n";
				const char* cstr_punts = punts.c_str();
				glPushMatrix();
				glLoadIdentity();
				glColor3f(.0f, 0.8f, .0f);
				drawBitmapText(cstr_punts, -0.15, 0.5, -2);
				glPopMatrix();
			}
			else {
				glPushMatrix();
				glLoadIdentity();
				glColor3f(1.0f, 1.0f, 1.0f);
				drawBitmapText("VICTORIA\n", -0.3, 0.1, -2);
				drawBitmapText("PREM LA TECLA PER:\n", -0.3, 0.05, -2);
				drawBitmapText("1 - PASSAR AL SEGUENT NIVELL\n", -0.3, 0.0, -2);
				drawBitmapText("2 - REINICIAR EL NIVELL ACTUAL\n", -0.3, -0.05, -2);
				drawBitmapText("3 - SORTIR DEL JOC\n", -0.3, -0.1, -2);
				glPopMatrix();
				menu = true;
			}

			glPushMatrix();
			glLoadIdentity();
			glColor3f(.0f, 0.8f, .0f);
			drawBitmapText(cstr_tf, 1.5, 1.09, -2);
			glPopMatrix();

		}
		else if (!i_d && musica == 2) {

			std::string tf = "TEMPS: " + remove_zeros(std::to_string(temps_final)) + "\n";
			const char* cstr_tf = tf.c_str();

			if (temps_menu < 700) {
				glPushMatrix();
				glLoadIdentity();
				glColor3f(1.0f, .0f, .0f);
				drawBitmapText("DERROTA\n", -0.1, 0, -2);
				glPopMatrix();
				temps_menu++;
			}
			else {
				glPushMatrix();
				glLoadIdentity();
				glColor3f(1.0f, 1.0f, 1.0f);
				drawBitmapText("DERROTA\n", -0.3, 0.1, -2);
				drawBitmapText("PREM LA TECLA PER:\n", -0.3, 0.05, -2);
				drawBitmapText("1 - PASSAR AL SEGUENT NIVELL\n", -0.3, 0.0, -2);
				drawBitmapText("2 - REINICIAR EL NIVELL ACTUAL\n", -0.3, -0.05, -2);
				drawBitmapText("3 - SORTIR DEL JOC\n", -0.3, -0.1, -2);
				glPopMatrix();
				menu = true;
			}

			glPushMatrix();
			glLoadIdentity();
			glColor3f(.0f, 0.8f, .0f);
			drawBitmapText(cstr_tf, 1.5, 1.09, -2);
			glPopMatrix();

		}
		//}
		break;
	}

	// Cub RGB
	case CUB_RGB:
	{
		glClearColor(0.5294f, 0.8078f, 0.9216f, 0.71f);
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(1.0, 1.0, 1.0);

		//Textura


		glDisable(GL_TEXTURE_2D);
		GLfloat sPlane2[4] = { 10.00f, 0.00f, 0.00f, 10.00f };
		GLfloat tPlane2[4] = { 0.00f, 10.00f, 10.00f, 0.00f };
		//glBindTexture(GL_TEXTURE_2D, texturID[8]);

		//glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane2);
		//glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane2);

		//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);
		glBindTexture(GL_TEXTURE_2D, texturID[8]);
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);


		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);



		glEnable(GL_TEXTURE_2D);


		glPushMatrix();
		glTranslatef(10.0f, 2.5f, 7.5f);
		glScalef(20.0f, 5.0f, 15.0f);
		glutSolidCube(1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(30.0f, 2.5f, 7.5f);
		glScalef(20.0f, 5.0f, 15.0f);
		glutSolidCube(1.0);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(10.0f, 22.5f, 7.5f);
		glScalef(20.0f, 5.0f, 15.0f);
		glutSolidCube(1.0);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(17.5f, 35.0f, 7.5f);
		glScalef(5.0f, 20.0f, 15.0f);
		glutSolidCube(1.0);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(37.5f, 35.0f, 7.5f);
		glScalef(5.0f, 20.0f, 15.0f);
		glutSolidCube(1.0);
		glPopMatrix();


		glPushMatrix();
		glTranslatef(37.5f, 15.0f, 7.5f);
		glScalef(5.0f, 20.0f, 15.0f);
		glutSolidCube(1.0);
		glPopMatrix();

		//glDisable(GL_TEXTURE_GEN_S);
		//glDisable(GL_TEXTURE_GEN_T);

		//Terra

		//Textures terra
		glDisable(GL_TEXTURE_2D);
		GLfloat sPlane[4] = { 10.00f, 0.00f, 10.00f, 0.00f };
		GLfloat tPlane[4] = { 0.00f, 10.00f, 0.00f, 0.00f };
		glBindTexture(GL_TEXTURE_2D, texturID[9]);

		glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glEnable(GL_TEXTURE_2D);


		//Objecte terra
		glPushMatrix();
		glTranslatef(50.0f, 50.0f, -7.5f);
		glScalef(100.0f, 100.0f, 15.0f);
		glutSolidCube(1.0);
		glPopMatrix();

		glDisable(GL_TEXTURE_2D);
		/*

		glDisable(GL_TEXTURE_2D);
		GLfloat sPlane3[4] = { 1.00f, 0.00f, 1.00f, 0.00f };
		GLfloat tPlane3[4] = { 0.00f, 1.00f, 0.00f, 0.00f };
		glBindTexture(GL_TEXTURE_2D, texturID[7]);

		glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane3);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane3);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glEnable(GL_TEXTURE_2D);


		//Objecte cel
		glPushMatrix();
		glTranslatef(50.0f, 50.0f, 50.5f);
		glScalef(10000.0f, 10000.0f, 1.0f);
		glutSolidCube(1.0);
		glPopMatrix();


		*/







		break;
	}
	// Dibuix de l'objecte TIE (Nau enemiga Star Wars)
	case TIE:
		tie();
		break;

		// Dibuix del Truck
	case TRUCK:
		glDisable(GL_TEXTURE_2D);
		truck(textur, texturID);
		sea();
		break;

		// Dibuix de l'objecte 3DS
	case OBJ3DS:
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
		//SeleccionaMaterialiColor(MAT_CAP, ref_mat, sw_mat, col_object);
		SeleccionaColor(ref_mat, sw_mat, col_object);
		// Dibuix de l'objecte 3DS amb textures (OBJECTE3DST) o sense textures (OBJECTE3DS)
		if (textur) glCallList(OBJECTE3DST);
		else glCallList(OBJECTE3DS);
		break;

		// Dibuix de l'objecte OBJ
	case OBJOBJ:
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
		//SeleccionaMaterialiColor(MAT_CAP, ref_mat, sw_mat, col_object);
		SeleccionaColor(ref_mat, sw_mat, col_object);
		// Objecte OBJ: Dibuix de l'objecte OBJ amb textures (OBJECTEOBJT) o sense textures (OBJECTEOBJ)
		if (textur) glCallList(OBJECTEOBJT);
		else glCallList(OBJECTEOBJ);
		break;

		// Corba Bezier
	case C_BEZIER:
		// Dibuixar Punts de Control
		if (sw_PC)
		{
			glColor3f(1.0, 0.0, 0.0);
			for (int i = 0; i < nptsU; i++)
			{
				glPushMatrix();
				glTranslatef(PC_u[i].x, PC_u[i].y, PC_u[i].z);
				glutSolidSphere(5.0, 20, 20);
				glPopMatrix();
			}
		}
		SeleccionaColor(ref_mat, sw_mat, col_object);
		//draw_Bezier_Curve(PC_u, nptsU, PAS_BEZIER,false);
		draw_Bezier_Curve(PC_u, nptsU, pasCS, false);
		break;

		// Corba Lemniscata
	case C_LEMNISCATA:
		//glColor3f(1.0,1.0,1.0);
		SeleccionaColor(ref_mat, sw_mat, col_object);
		//draw_Lemniscata(800, 10.0);
		draw_Lemniscata(800, pasCS * 20.0);
		break;

		// Corba Spline
	case C_BSPLINE:
		// Dibuixar Punts de Control
		if (sw_PC)
		{
			glColor3f(1.0, 0.0, 0.0);
			for (int i = 0; i < nptsU; i++)
			{
				glPushMatrix();
				glTranslatef(PC_u[i].x, PC_u[i].y, PC_u[i].z);
				glutSolidSphere(5.0, 20, 20);
				glPopMatrix();
			}
		}
		SeleccionaColor(ref_mat, sw_mat, col_object);
		//draw_BSpline_Curve(PC_u, nptsU, PAS_BSPLINE);
		draw_BSpline_Curve(PC_u, nptsU, pasCS);
		break;

		// Dibuix de la resta d'objectes
	default:
		// Definici� propietats de reflexi� (emissi�, ambient, difusa, especular) del material.
		//SeleccionaMaterialiColor(MAT_CAP, ref_mat, sw_mat, col_object);
		SeleccionaColor(ref_mat, sw_mat, col_object);
		dibuixa(objecte);
		break;
	}

	// Enviar les comandes gr�fiques a pantalla
	//	glFlush();
}


// dibuixa: Funci� que dibuixa objectes simples de la llibreria GLUT segons obj
void dibuixa(char obj)
{
	switch (obj)
	{

		// Cub
	case CUB:
	{
		glDisable(GL_TEXTURE_2D);
		//		glColor3f(1.0,1.0,1.0);
		glPushMatrix();
		//textura




		//els cubs
		glScalef(5.0f, 20.0f, 5.0f);
		glutSolidCube(1.0);
		/*
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		*/



		glTranslatef(1.0f, 1.0f, 0.0f);
		glutSolidCube(1.0);
		glPopMatrix();
		break;
	}


	// Esfera
	case ESFERA:
		//		glColor3f(1.0,1.0,1.0);	
		glPushMatrix();
		glScalef(5.0f, 5.0f, 5.0f);
		gluSphere(1.0, 40, 40);
		glPopMatrix();
		break;

		// Tetera
	case TETERA:
		//		glColor3f(1.0,1.0,1.0);
		glPushMatrix();
		//glScalef(5.0f,5.0f,5.0f);
		glutSolidTeapot(1.0);
		glPopMatrix();
		break;
	}
}


// OBJECTE Truck amb imatges textura si s�n actives
// Truck: Par�metres:
//    - textu: Flag de textures activades o no.
//    - VTextu: Vector d'imatges textura.
void truck(bool textu, GLint VTextu[NUM_MAX_TEXTURES])
{

	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 20.0f);

	// MOTOR
	// Textura carrosseria
	if (textu)
	{
		GLfloat sPlane[4] = { 0.05f, 0.0f, 0.00f, 0.250f };
		GLfloat tPlane[4] = { 0.00f, 0.05f, 0.1f, 0.00f };
		// Activar textura planxa
		glBindTexture(GL_TEXTURE_2D, VTextu[5]);

		glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glEnable(GL_TEXTURE_2D);
	}

	// Color carrosseria sense textura
	glColor4f(0.5f, 0.7f, 1.0f, 0.5f);

	glPushMatrix();
	glScalef(2.0f, 4.4f, 2.0f);
	glutSolidCube(10.0f);
	glPopMatrix();

	// CABINA
	// Cabina inferior
	glPushMatrix();
	glTranslatef(0.0f, 32.0f, 0.0f);
	glScalef(4.0f, 2.0f, 2.0f);
	glutSolidCube(10.0f);
	glPopMatrix();

	// Cabina superior
	glPushMatrix();
	glTranslatef(0.0f, 32.0f, 15.0f);
	glScalef(2.0f, 2.0f, 1.0f);
	glutSolidCube(10.0f);
	glPopMatrix();

	// Cabina trasera
	glPushMatrix();
	glTranslatef(0.0f, 49.5f, 12.5f);
	glScalef(4.0f, 1.5f, 4.5f);
	glutSolidCube(10.0f);
	glPopMatrix();

	// CANTONADES
	// Cantonada esquerra
	glPushMatrix();
	glTranslatef(10.0f, 22.0f, -10.0f);

	glBegin(GL_QUADS);  // Cara de 4 costats
	glNormal3f(200.0f, 200.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f); //P1
	glVertex3f(10.0f, 0.0f, 20.0f); //P2
	glVertex3f(0.0f, -10.0f, 20.0f); //P3
	glVertex3f(0.0f, -10.0f, 0.0f); //P4
	glEnd();

	glBegin(GL_POLYGON);  // Triangle d'abaix
	glNormal3f(0.0f, 0.0f, -200.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);  // T1
	glVertex3f(10.0f, 0.0f, 0.0f);  // P1
	glVertex3f(0.0f, -10.0f, 0.0f); // P4
	glEnd();

	glBegin(GL_POLYGON);  // Triangle de dalt
	glNormal3f(0.0f, 0.0f, 200.0f);
	glVertex3f(0.0f, 0.0f, 20.0f);	// T2
	glVertex3f(0.0f, -10.0f, 20.0f); // P3
	glVertex3f(10.0f, 0.0f, 20.0f);  // P2
	glEnd();
	glPopMatrix();

	// Cantonada dreta
	glPushMatrix();
	glTranslatef(-10.0f, 22.0f, -10.0f);
	glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);

	glBegin(GL_QUADS);  // Cara de 4 costats
	glNormal3f(200.0f, 200.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f); //P1
	glVertex3f(10.0f, 0.0f, 20.0f); //P2
	glVertex3f(0.0f, -10.0f, 20.0f); //P3
	glVertex3f(0.0f, -10.0f, 0.0f); //P4
	glEnd();

	glBegin(GL_POLYGON);  // Triangle d'abaix
	glNormal3f(0.0f, 0.0f, -200.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);  // T1
	glVertex3f(10.0f, 0.0f, 0.0f);  // P1
	glVertex3f(0.0f, -10.0f, 0.0f); // P4
	glEnd();

	glBegin(GL_POLYGON);  // Triangle de dalt
	glNormal3f(0.0f, 0.0f, 200.0f);
	glVertex3f(0.0f, 0.0f, 20.0f);	// T2
	glVertex3f(0.0f, -10.0f, 20.0f); // P3
	glVertex3f(10.0f, 0.0f, 20.0f);  // P2
	glEnd();
	glPopMatrix();


	// PROTECCIONS DE RODA
	// Textura Proteccions de roda (metall)
	//	if (textu)
	//		{				
	//			glBindTexture(GL_TEXTURE_2D,VTextu[5]) ;
	//			glEnable(GL_TEXTURE_2D) ;
	//			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
	//			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_SPHERE_MAP);
	//			glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
	//			glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
	//			}

	// Color proteccions roda sense textura
	glColor4f(0.5f, 0.7f, 1.0f, 0.5f);

	// Protecci� de roda esquerra
	glPushMatrix();
	glTranslatef(10.0f, 0.0f, 3.0f);
	glBegin(GL_QUADS);
	//  glNormal3f(200.0f, 200.0f, 0.0f);
	glVertex3f(7.0f, -5.0f, 0.0f);
	glVertex3f(7.0f, 5.0f, 0.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glVertex3f(0.0f, -5.0f, 0.0f);

	glVertex3f(7.0f, -12.0f, -8.0f);
	glVertex3f(7.0f, -5.0f, 0.0f);
	glVertex3f(0.0f, -5.0f, 0.0f);
	glVertex3f(0.0f, -12.0f, -8.0f);

	glVertex3f(0.0f, 15.0f, -10.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glVertex3f(7.0f, 5.0f, 0.0f);
	glVertex3f(7.0f, 15.0f, -10.0f);

	glVertex3f(7.5f, -5.0f, -3.0f);
	glVertex3f(7.5f, 5.0f, -3.0f);
	glVertex3f(7.0f, 5.0f, 0.0f);
	glVertex3f(7.0f, -5.0f, 0.0f);

	glVertex3f(7.5f, -12.0f, -8.0f);
	glVertex3f(7.5f, -5.0f, -3.0f);
	glVertex3f(7.0f, -5.0f, 0.0f);
	glVertex3f(7.0f, -12.0f, -8.0f);

	glVertex3f(7.0f, 15.0f, -10.0f);
	glVertex3f(7.0f, 5.0f, 0.0f);
	glVertex3f(7.5f, 5.0f, -3.0f);
	glVertex3f(7.5f, 15.0f, -10.0f);

	glEnd();
	glPopMatrix();

	// Protecci� de roda dreta
	glPushMatrix();
	glTranslatef(-16.0f, 0.0f, 3.0f);
	glBegin(GL_QUADS);
	//  glNormal3f(200.0f, 200.0f, 0.0f);
	glVertex3f(7.0f, -5.0f, 0.0f);
	glVertex3f(7.0f, 5.0f, 0.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glVertex3f(0.0f, -5.0f, 0.0f);

	glVertex3f(7.0f, -12.0f, -8.0f);
	glVertex3f(7.0f, -5.0f, 0.0f);
	glVertex3f(0.0f, -5.0f, 0.0f);
	glVertex3f(0.0f, -12.0f, -8.0f);

	glVertex3f(0.0f, 15.0f, -10.0f);
	glVertex3f(0.0f, 5.0f, 0.0f);
	glVertex3f(7.0f, 5.0f, 0.0f);
	glVertex3f(7.0f, 15.0f, -10.0f);

	glVertex3f(7.5f, -5.0f, -3.0f);
	glVertex3f(7.5f, 5.0f, -3.0f);
	glVertex3f(7.0f, 5.0f, 0.0f);
	glVertex3f(7.0f, -5.0f, 0.0f);

	glVertex3f(7.5f, -12.0f, -8.0f);
	glVertex3f(7.5f, -5.0f, -3.0f);
	glVertex3f(7.0f, -5.0f, 0.0f);
	glVertex3f(7.0f, -12.0f, -8.0f);

	glVertex3f(7.0f, 15.0f, -10.0f);
	glVertex3f(7.0f, 5.0f, 0.0f);
	glVertex3f(7.5f, 5.0f, -3.0f);
	glVertex3f(7.5f, 15.0f, -10.0f);
	glEnd();
	glPopMatrix();

	// Textura Reixeta Motor
	if (textu)
	{
		GLfloat sPlane[4] = { 0.05f, 0.25f, 0.00f, 0.00f };
		GLfloat tPlane[4] = { 0.00f, 0.25f, 0.05f, 0.00f };
		// Activar textura
		glBindTexture(GL_TEXTURE_2D, VTextu[3]);

		glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_TEXTURE_2D);
	}

	// Color reixeta motor sense textura
	glColor4f(0.5f, 0.7f, 1.0f, 0.5f);

	// Reixeta Motor
	glPushMatrix();
	glTranslatef(0.0f, -22.0f, 0.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-10.0f, -2.0f, -10.0f);
	glTexCoord2f(1.0f, 0.00f);
	glVertex3f(10.0f, -2.0f, -10.0f);
	glTexCoord2f(1.0f, 1.0);
	glVertex3f(10.0f, -2.0f, 10.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-10.0f, -2.0f, 10.0f);
	glEnd();
	glPopMatrix();

	// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

	// Color eix sense textura
	glColor4f(0.1f, 0.4f, 1.0f, 0.5f);

	// Eix Davanter
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -10.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -13.0f);
	gluCylinder(2.0, 2.0, 26.0f, 6, 1);
	glPopMatrix();

	// Roda Dreta Davantera
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, -10.0f);
	neumatic(textu, VTextu);
	glPopMatrix();

	// Roda Esquerra Davantera
	glPushMatrix();
	glTranslatef(17.0f, 0.0f, -10.0f);
	neumatic(textu, VTextu);
	glPopMatrix();

	// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

	// FARS	
	// Color fars sense textura
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);

	// Far Esquerra	
	glPushMatrix();
	glTranslatef(-13.5f, -17.0f, -8.0f);
	glScalef(7.0f, 2.0f, 4.0f);
	glutSolidCube(1.0f);
	glPopMatrix();

	// Far dret
	glPushMatrix();
	glTranslatef(13.5f, -17.0f, -8.0f);
	glScalef(7.0f, 2.0f, 4.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Per a la textura
	glutSolidCube(1.0f);
	glPopMatrix();

	// Textura frontal fars
	if (textu)
	{
		GLfloat sPlane[4] = { 0.15f, 0.0f, 0.0f, 0.5f };
		GLfloat tPlane[4] = { 0.0f, 0.35f, 0.25f, 0.15f };
		// Activar textura
		glBindTexture(GL_TEXTURE_2D, VTextu[4]);

		glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_TEXTURE_2D);
	}

	// Color frontal fars sense textura
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

	// Frontal far dret
	glPushMatrix();
	glTranslatef(-13.5f, -16.5f, -8.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.5f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 0.00f);
	glVertex3f(3.5f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 1.0);
	glVertex3f(3.5f, -2.0f, 2.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.5f, -2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	// Frontal far esquerre
	glPushMatrix();
	glTranslatef(13.5f, -16.5f, -8.0f);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.5f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 0.00f);
	glVertex3f(3.5f, -2.0f, -2.0f);
	glTexCoord2f(1.0f, 1.0);
	glVertex3f(3.5f, -2.0f, 2.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-3.5f, -2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

	// VIDRE CABINA (SENSE TEXTURA)
	// Activar transpar�ncia
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	// Color vidre cabina sense textura
	glColor4f(0.3f, 0.8f, 0.7f, 0.5f);

	// Vidre
	glPushMatrix();
	glTranslatef(0.0f, 22.0f, 10.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 00.0f, -10.0f);

	glBegin(GL_QUADS);  // Cara de 4 costats
	glNormal3f(200.0f, 200.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f); //P1
	glVertex3f(10.0f, 0.0f, 20.0f); //P2
	glVertex3f(0.0f, -10.0f, 20.0f); //P3
	glVertex3f(0.0f, -10.0f, 0.0f); //P4
	glEnd();

	glBegin(GL_POLYGON);  // Triangle d'abaix
	glNormal3f(0.0f, 0.0f, -200.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);  // T1
	glVertex3f(10.0f, 0.0f, 0.0f);  // P1
	glVertex3f(0.0f, -10.0f, 0.0f); // P4
	glEnd();

	glBegin(GL_POLYGON);  // Triangle de dalt
	glNormal3f(0.0f, 0.0f, 200.0f);
	glVertex3f(0.0f, 0.0f, 20.0f);	// T2
	glVertex3f(0.0f, -10.0f, 20.0f); // P3
	glVertex3f(10.0f, 0.0f, 20.0f);  // P2
	glEnd();
	glPopMatrix();

	// Desactivar transpar�ncia
	glDisable(GL_BLEND);

	// TUBS D'ESCAPAMENT (SENSE TEXTURA)
	// Color tub d'escapament sense textura
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);

	// Tub d'escapament esquerre
	glPushMatrix();
	glTranslatef(18.0f, 42.0f, 10.0f);
	gluCylinder(2.0f, 2.0f, 40.0f, 12, 1);
	glPopMatrix();

	// Tub d'escapament dret
	glPushMatrix();
	glTranslatef(-18.0f, 42.0f, 10.0f);
	gluCylinder(2.0f, 2.0f, 40.0f, 12, 1);
	glPopMatrix();

	// CARROSSERIA
	// Textura carrosseria
	if (textu)
	{
		GLfloat sPlane[4] = { 0.05f, 0.0f, 0.00f, 0.250f };
		GLfloat tPlane[4] = { 0.00f, 0.05f, 0.1f, 0.00f };

		// Activar textura
		glBindTexture(GL_TEXTURE_2D, VTextu[5]);

		glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_TEXTURE_2D);
	}

	// Color porta-eix motriu sense textura
	glColor4f(0.5f, 0.7f, 1.0f, 0.5f);

	// Porta-eix motriu mig
	glPushMatrix();
	glTranslatef(0.0f, 82.0f, -5.0f);
	glScalef(1.0f, 5.0f, 1.0f);
	glutSolidCube(10.0f);
	glPopMatrix();

	if (textu) glDisable(GL_TEXTURE_2D);

	// Conjunt eixos i rodes eix mig
	glPushMatrix();
	// Despla�ament Eix Mig
	glTranslatef(0.0f, 72.0f, 0.0f);

	// Color eix sense textura
	glColor4f(0.1f, 0.4f, 1.0f, 0.5f);

	// Eix Mig Davanter
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -10.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -13.0f);
	gluCylinder(2.0f, 2.0f, 26.0f, 6, 1);
	glPopMatrix();

	// Roda Dreta Davantera Eix Mig Davanter
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, -10.0f);
	neumatic(textu, VTextu);
	glPopMatrix();

	// Roda Esquerra Davantera Eix Mig Davanter
	glPushMatrix();
	glTranslatef(17.0f, 0.0f, -10.0f);
	neumatic(textu, VTextu);
	glPopMatrix();

	// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

	// Despla�ament entre dos eixos
	glTranslatef(0.0f, 25.0f, 0.0f);

	// Color eix sense textura
	glColor4f(0.1f, 0.4f, 1.0f, 0.5f);

	// Eix Mig Darrera
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -10.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -13.0f);
	gluCylinder(2.0, 2.0, 26.0f, 6, 1);
	glPopMatrix();

	// Roda Dreta Davantera Eix Mig Darrera
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, -10.0f);
	neumatic(textu, VTextu);
	glPopMatrix();

	// Roda Esquerra Davantera Eix Mig Darrera
	glPushMatrix();
	glTranslatef(17.0f, 0.0f, -10.0f);
	neumatic(textu, VTextu);
	glPopMatrix();

	// Fi conjunt d'eixos i rodes eix mig
	glPopMatrix();

	// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

	// REMOLC	
	// Textura carrosseria
	if (textu)
	{
		GLfloat sPlane[4] = { 0.05f, 0.0f, 0.00f, 0.250f };
		GLfloat tPlane[4] = { 0.00f, 0.05f, 0.1f, 0.00f };

		// Activar textura
		glBindTexture(GL_TEXTURE_2D, VTextu[5]);

		glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_TEXTURE_2D);
	}


	// Color plataforma sense textura
	glColor4f(0.5f, 0.7f, 1.0f, 0.5f);

	// Plataforma
	glPushMatrix();
	glTranslatef(0.0f, 127.0f, 4.0f);
	glScalef(3.0f, 14.0f, 0.8f);
	glutSolidCube(10.0f);
	glPopMatrix();

	// Textura Cisterna
	if (textu)
	{
		glBindTexture(GL_TEXTURE_2D, VTextu[6]);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_2D);
	}

	// Color cisterna sense textura
	glColor4f(0.9f, 0.9f, 1.0f, 0.5f);

	// Cisterna
	glPushMatrix();
	glTranslatef(0.0f, 60.0f, 20.0f);
	glScalef(0.75f, 1.0f, 0.5f);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	// Part de davant
	gluCylinder(20.0f, 25.0f, 5.0f, 25, 1);
	glPushMatrix();
	glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
	gluDisk(0.0f, 20.0f, 25, 1);
	glPopMatrix();
	// Part Central
	glTranslatef(0.0f, 0.0f, 5.0f);
	gluCylinder(25, 25, 125.0f, 25, 1);
	// Part Darrera
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 125.0f);
	gluCylinder(25.0f, 20.0f, 5.0f, 25, 1);
	glTranslatef(0.0f, 0.0f, 5.0f);
	gluDisk(0.0f, 20.0f, 25, 1);
	glPopMatrix();
	glPopMatrix();

	// Desactivar textura
	//	if (textu) glDisable(GL_TEXTURE_2D);

	// Textura planxa
	if (textu)
	{
		GLfloat sPlane[4] = { 0.05f, 0.0f, 0.00f, 0.250f };
		GLfloat tPlane[4] = { 0.00f, 0.05f, 0.1f, 0.00f };
		// Activar textura planxa
		glBindTexture(GL_TEXTURE_2D, VTextu[5]);

		glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_TEXTURE_2D);
	}

	// Color porta-eix motriu
	glColor4f(0.5f, 0.7f, 1.0f, 0.5f);

	// Porta-eix motriu darrera
	glPushMatrix();
	glTranslatef(0.0f, 172.0f, -5.0f);
	glScalef(1.0f, 5.0f, 1.0f);
	glutSolidCube(10.0f);
	glPopMatrix();

	// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

	// Conjunt eixos i rodes eix darrera
	glPushMatrix();

	// Despla�ament Eix Darrera
	glTranslatef(0.0f, 162.0f, 0.0f);

	// Color eix sense textura
	glColor4f(0.1f, 0.4f, 1.0f, 0.5f);

	// Eix Darrera Davanter
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -10.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -13.0f);
	gluCylinder(2.0, 2.0, 26.0f, 6, 1);
	glPopMatrix();

	// Roda Dreta Davantera Eix Darrera Davanter
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, -10.0f);
	neumatic(textu, VTextu);
	glPopMatrix();

	// Roda Esquerra Davantera Eix Darrera Davanter
	glPushMatrix();
	glTranslatef(17.0f, 0.0f, -10.0f);
	neumatic(textu, VTextu);
	glPopMatrix();

	// Desactivar textura
	if (textu) glDisable(GL_TEXTURE_2D);

	// Despla�ament entre dos eixos
	glTranslatef(0.0f, 25.0f, 0.0f);

	// Color eix sense textura
	glColor4f(0.1f, 0.4f, 1.0f, 0.5f);

	// Eix Darrera Darrera
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -10.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 0.0f, -13.0f);
	gluCylinder(2.0f, 2.0f, 26.0f, 6, 1);
	glPopMatrix();

	// Roda Dreta Davantera Eix Darrera Darrera
	glPushMatrix();
	glTranslatef(-10.0f, 0.0f, -10.0f);
	neumatic(textu, VTextu);
	glPopMatrix();

	// Roda Esquerra Davantera Eix Darrera Darrera
	glPushMatrix();
	glTranslatef(17.0f, 0.0f, -10.0f);
	neumatic(textu, VTextu);
	glPopMatrix();
	// Fi conjunt eixos i rodes eix darrera
	glPopMatrix();

	// Fi dibuix Truck
	glPopMatrix();

	// Restaurar textura[0]
	if (textu)
	{
		glBindTexture(GL_TEXTURE_2D, VTextu[0]);
		// Desactivar genaraci� autom�tica de coordenades textura
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
		//		glTexGeni(GL_S,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
		//		glTexGeni(GL_T,GL_TEXTURE_GEN_MODE,GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_2D);
	}
}


// Dibuix de roda
// neumatic: Par�metres:
//    - textur: Flag de textures activades o no.
//    - VTextur: Vector d'imatges textura.
void neumatic(bool textur, GLint VTextur[NUM_MAX_TEXTURES])
{
	// Textura neum�tic
	if (textur)
	{
		// Activar textura neum�tic
		glBindTexture(GL_TEXTURE_2D, VTextur[1]);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_2D);
	}

	// Color neum�tic sense textura
	glColor4f(0.2f, 0.2f, 0.2f, 0.5f);

	glPushMatrix();
	// Tapa inferior neum�tic
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	gluDisk(5.0f, 10.0f, RESOLUCIO_RODA, 1);

	// Dibuix de la llanta
	llanta(textur, VTextur);

	// Textura neum�tic
	if (textur)
	{
		// Activar textura neum�tic
		glBindTexture(GL_TEXTURE_2D, VTextur[1]);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_2D);
	}

	// Color neum�tic sense textura
	glColor4f(0.2f, 0.2f, 0.2f, 0.5f);

	// Gruix del neum�tic
	glTranslatef(0.0f, 0.0f, -6.0f);
	gluCylinder(10.0f, 10.0f, 6.0f, RESOLUCIO_RODA, 1);
	// Tapa superior neum�tic
	glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
	gluDisk(5.0f, 10.0f, RESOLUCIO_RODA, 1);
	// Dibuix de la llanta
	llanta(textur, VTextur);
	glPopMatrix();

	// Desactivar textures
	//	if (textur) glDisable(GL_TEXTURE_2D);

}

// Dibuix de la llanta de la roda
// llanta: Par�metres:
//    - textur: Flag de textures activades o no.
//    - VTextur: Vector d'imatges textura.
void llanta(bool textur, GLint VTextur[NUM_MAX_TEXTURES])
{

	// Textura de la llanta
	if (textur)
	{
		GLfloat sPlane[4] = { 0.0f, -0.1f, 0.5f, 0.5f };
		GLfloat tPlane[4] = { 0.1f, 0.0f, 0.5f, 0.5f };
		// Activar la textura
		glBindTexture(GL_TEXTURE_2D, VTextur[2]);

		glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
		glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		glEnable(GL_TEXTURE_2D);
	}

	// Dibuix de la llanta (disc de radi 5 de color clar)
	glColor4f(0.7f, 0.7f, 0.7f, 0.5f);
	gluDisk(0.0f, 5.0f, RESOLUCIO_RODA, 1);

}


// Mar amb ondulacions
void sea(void)
{
	int i, j, step, it1, it2;
	//     GLfloat pi=3.14159;
	float angle, delay;
	CColor color;

	// Aigua amb ondulacions simulades a partir de normals sinusoidals
	step = 5;
	delay = 0;
	it1 = 0;

	//   SeleccionaMaterial(MAT_DEFAULT);	
	float h = 2 * pi * step / 500;
	for (j = -250; j < 250 - step; j = j + step)
	{

		delay = 1.0 * h * it1;

		it2 = 0;
		//glColor3f(0.5f, 0.4f, 0.9f);
		color.r = 0.5f;	color.g = 0.4f;	color.b = 0.9f;
		SeleccionaColor(reflexio_material, sw_materials, color);

		for (i = -250; i < 250 - step; i = i + step)
		{
			glBegin(GL_POLYGON);
			angle = 1.0 * it2 * h * 15;
			glNormal3f(-cos(angle), 0, 1);
			glVertex3f(i, j, 0);

			angle = 1.0 * (it2 + 1) * h * 15;
			glNormal3f(-cos(angle), 0, 1);
			glVertex3f(i + step, j, 0);

			angle = 1.0 * (it2 + 1) * h * 15;
			glNormal3f(-cos(angle), 0, 1);
			glVertex3f(i + step, j + step, 0);
			glEnd();

			glBegin(GL_POLYGON);
			angle = 1.0 * it2 * h * 15;
			glNormal3f(-cos(angle), 0, 1);
			glVertex3f(i, j, 0);

			angle = 1.0 * (it2 + 1) * h * 15;
			glNormal3f(-cos(angle), 0, 1);
			glVertex3f(i + step, j + step, 0);

			angle = 1.0 * it2 * h * 15;
			glNormal3f(-cos(angle), 0, 1);
			glVertex3f(i, j + step, 0);
			glEnd();
			it2++;
		}
		it1++;
	}

}


// OBJECTE TIE: FETS PER ALUMNES -----------------------------------------------------------------

// Objecte TIE
void tie() {
	Motor();
	Alas();
	Canon();
	Cuerpo();
	Cabina();
};

void Alas()
{
	// Ala 1 Parte central

	//Parte Exterior
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(25.25f, 0.0f, 0.0f);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	glScaled(10.0f, 10.0f, 5.0f);
	gluCylinder(5.0f, 5.0f, 0.5f, 6, 1);
	glPopMatrix();

	//Tapas
	glPushMatrix();
	//	  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(25.25f, 0.0f, 0.0f);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	glScaled(10.0f, 10.0f, 5.0f);
	gluDisk(0.0f, 5.0f, 6, 1);
	glPopMatrix();

	glPushMatrix();
	//	  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(27.75f, 0.0f, 0.0f);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	glScaled(10.0f, 10.0f, 5.0f);
	gluDisk(0.0f, 5.0f, 6, 1);
	glPopMatrix();

	//Parte Interior
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	glTranslated(25.25f, 0.0f, 0.0f);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	glScaled(2.0f, 2.0f, 2.0f);
	gluCylinder(5.0f, 5.0f, 2.0f, 6, 1);
	glPopMatrix();

	//Tapas
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	glTranslatef(25.25f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	gluDisk(0.0f, 5.0f, 6, 1);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	glTranslatef(29.25f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	gluDisk(0.0f, 5.0f, 6, 1);
	glPopMatrix();

	//Decoracion Exterior
	int j;
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	glTranslatef(26.5f, 0.0f, 0.0f);
	glScalef(15.75f, 13.75f, 13.75f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
	for (j = 0; j < 3; j = j + 1)
	{
		glRotatef(60, 0, 0, 1);
		glPushMatrix();
		glScalef(12.7f * 0.583f, 0.1f, 0.3f);
		glutSolidCube(1.0f);
		glPopMatrix();
	}
	glPopMatrix();

	int u;
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	for (u = 0; u < 6; u = u + 1)
	{
		glRotated(60, 1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(26.5f, 0.0f, 43.25f);
		glRotatef(90, 0.0, 0.0, 1.0);
		glScalef(10 * 5.155f, 5.0f, 3.0f);
		glutSolidCube(1.0f);
		glPopMatrix();
	}
	glPopMatrix();

	//Ala 2 Parte central 

	//Parte Exterior
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslated(-27.75f, 0.0f, 0.0f);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	glScaled(10.0, 10.0, 5.0);
	gluCylinder(5.0f, 5.0f, 0.5f, 6, 1);
	glPopMatrix();

	//Tapas
	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(-27.75f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	gluDisk(0.0f, 5.0f, 6, 1);
	glPopMatrix();

	glPushMatrix();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glTranslatef(-25.25f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glScalef(10.0f, 10.0f, 5.0f);
	gluDisk(0.0f, 5.0f, 6, 1);
	glPopMatrix();

	//Parte Interior
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	glTranslatef(-29.25f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	gluCylinder(5.0f, 5.0f, 2.0f, 6, 1);
	glPopMatrix();

	//Tapas
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	glTranslatef(-29.25f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	gluDisk(0.0f, 5.0f, 6, 1);
	glPopMatrix();

	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	glTranslatef(-25.25f, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glScalef(2.0f, 2.0f, 2.0f);
	gluDisk(0.0f, 5.0f, 6, 1);
	glPopMatrix();

	//Decoracion Exterior
	int w;
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	glTranslatef(-26.5f, 0.0f, 0.0f);
	glScalef(15.75f, 13.75f, 13.75f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
	for (w = 0; w < 3; w = w + 1)
	{
		glRotatef(60.0f, 0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glScalef(12.7f * 0.583f, 0.1f, 0.3f);
		glutSolidCube(1.0f);
		glPopMatrix();
	}
	glPopMatrix();


	int h;
	glPushMatrix();
	glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
	for (h = 0; h < 6; h = h + 1)
	{
		glRotated(60, 1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(-26.5f, 0.0f, 43.25f);
		glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
		glScalef(10 * 5.155f, 5.0f, 3.0f);
		glutSolidCube(1.0f);
		glPopMatrix();
	}
	glPopMatrix();
};


void Motor()
{
	//Helices Motor
	int j;
	glPushMatrix();
	glColor4f(0.58f, 0.58f, 0.58f, 0.0f);
	glTranslatef(0.0f, -18.0f, 0.0f);
	glRotated(-90.0f, 0.0f, 0.0f, 1.0f);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	glRotatef(45, 0, 0, 1);
	for (j = 0; j < 6; j = j + 1)
	{
		glRotatef(30, 0, 0, 1);
		glPushMatrix();
		glScalef(12 * 0.583f, 0.1f, 0.3f);
		glutSolidCube(1.0f);
		glPopMatrix();
	}
	glPopMatrix();

	//Soporte Motor
	glPushMatrix();
	glColor4f(0.28f, 0.28f, 0.28f, 0.0f);
	glTranslatef(0.0f, -18.0f, 0.0f);
	glRotated(-90.0f, 0.0f, 0.0f, 1.0f);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(1.0, 5.0, 20, 20);
	glPopMatrix();
};

void Canon()
{

	//Ca�ones

	// Salida ca�on 1
	glPushMatrix();
	glColor4f(0.28f, 0.28f, 0.28f, 0.0f);
	glTranslated(5.0f, 8.0f, -10.0f);
	glRotated(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(1.0f, 0.5f, 5.0f, 60, 1);
	glPopMatrix();

	// Salida ca�on 2
	glPushMatrix();
	glColor4f(0.28f, 0.28f, 0.28f, 0.0f);
	glTranslated(-5.0f, 8.0f, -10.0f);
	glRotated(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(1.0f, 0.5f, 5.0f, 60, 1);
	glPopMatrix();

	// Ca�on 1
	glPushMatrix();
	glColor4f(0.58f, 0.58f, 0.58f, 0.0f);
	glTranslated(5.0f, 10.0f, -10.0f);
	glRotated(-90.0f, 1.0f, 0.0f, 0.0f);
	//gluCylinder(ca�on1, 0.35f, 0.35f, 5.0f, 80, 1);
	gluCylinder(0.35f, 0.35f, 5.0f, 80, 1);
	glPopMatrix();

	//Ca�on 2
	glPushMatrix();
	glColor4f(0.58f, 0.58f, 0.58f, 0.0f);
	glTranslated(-5.0f, 10.0f, -10.0f);
	glRotated(-90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(0.35f, 0.35f, 5.0f, 80, 1);
	glPopMatrix();
}

void Cuerpo()
{
	//Sujeccion de las Alas

	//Lado2
	glPushMatrix();
	glColor4f(0.16f, 0.16f, 0.16f, 1.0f);
	glRotated(-90.0f, 0.0, 1.0, 0.0);
	glRotated(90.0f, 0.0, 0.0, 1.0);
	glScalef(2.0f, 2.0f, 2.5f);
	gluCylinder(4.0f, 2.0f, 10.25f, 40, 1);
	glPopMatrix();

	//X2
	glPushMatrix();
	glColor4f(0.16f, 0.16f, 0.16f, 1.0f);
	glTranslated(-25.0f, 0.0f, 0.0f);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(1.0, 5.0, 20, 20);
	glPopMatrix();

	//Lado 1
	glPushMatrix();
	glColor4f(0.16f, 0.16f, 0.16f, 1.0f);
	glRotated(90.0f, 0.0, 1.0, 0.0);
	glRotated(90.0f, 0.0, 0.0, 1.0);
	glScaled(2.0f, 2.0f, 2.5f);
	gluCylinder(4.0f, 2.0f, 10.25f, 40, 1);
	glPopMatrix();

	//X1
	glPushMatrix();
	glColor4f(0.16f, 0.16f, 0.16f, 1.0f);
	glTranslated(25.25f, 0.0f, 0.0f);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	glutSolidTorus(1.0, 5.0, 20, 20);
	glPopMatrix();

	//Cuerpo
	glPushMatrix();
	glColor4f(0.16f, 0.16f, 0.16f, 1.0f);
	glScaled(1.75f, 1.75f, 1.5f);
	glutSolidSphere(10.0f, 80, 80);
	//gluEsfera(10.0f, 80, 80);
	glPopMatrix();
}

void Cabina()
{
	glEnable(GL_BLEND);

	// Tapa Cabina
	glPushMatrix();
	glColor4f(1.0f, 0.058f, 0.058f, 0.5f);
	glTranslated(0.0f, 19.45f, 0.0f);
	glRotated(-90.0f, 0.0f, 0.0f, 1.0f);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	glScalef(1.75f, 1.75f, 1.75f);
	gluDisk(0.0f, 1.5f, 8, 1);
	glPopMatrix();

	// Cristal Cabina
	glPushMatrix();
	glColor4f(1.0f, 0.058f, 0.058f, 0.5f);
	glTranslated(0.0f, 19.45f, 0.0f);
	glRotated(-90.0f, 0.0f, 0.0f, 1.0f);
	glRotated(90.0f, 0.0f, 1.0f, 0.0f);
	glScaled(1.75f, 1.75f, 1.75f);
	gluCylinder(1.5f, 4.5f, 2.0f, 8, 1);
	glPopMatrix();

	glDisable(GL_BLEND);
}
// FI OBJECTE TIE: FETS PER ALUMNES -----------------------------------------------------------------
