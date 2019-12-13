#pragma once
#include <iostream>

#include "stdafx.h"
#include "constants.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <irrklang/irrKlang.h>
#include "OBJLoader2.h"
irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();
irrklang::ISoundSource* soSalt = SoundEngine->addSoundSourceFromFile("audio/salt.mp3");


//Variables nostre
float x = 5.0f;
float h = 7.5f;

class Mur {
public:
	float m_x;
	float m_y;
	float m_z;
	bool m_ori; //Boole� que emmagatzema la orientaci� del mur
	float m_amplada; //Float que emagatzema la amblada del mur, vaiable que permet crear murs amb dimensions diferents
	bool variableControladoraPunxesBaixant = true;

	bool esUnMurAnimatQueCau = false;


	bool animacioAcabada = false;

	Mur() {
		m_x = m_y = m_z = 0.0;
		m_ori = 0;
		m_amplada = MUR_X;
	}
	Mur(float x, float y, float z, bool o) { //Aquestes coordenades corresponen al centre de l'objecte, per com funciona OpenGL. Per accedir als boundaries, hi ha constants amb la mida del mur
		m_x = x;
		m_y = y;
		m_z = z;
		m_ori = o;
		m_amplada = MUR_X;
	}

	void setMur(float x, float y, float z, bool o, float amlada) {
		m_x = x;
		m_y = y;
		m_z = z;
		m_ori = o;
		m_amplada = amlada;
	}

	void pinta() {
		if (m_ori) {
			//glColor3f(0.5, 0.5, 0.25);
			glPushMatrix();
			glTranslatef(m_x, m_y, m_z);
			glScalef(m_amplada, MUR_Y, MUR_Z);
			glutSolidCube(1.0);
			glPopMatrix();
		}
		else {
			//glColor3f(0.5, 0.5, 0.25);
			glPushMatrix();
			glTranslatef(m_x, m_y, m_z);
			glScalef(MUR_Y, m_amplada, MUR_Z);
			glutSolidCube(1.0);
			glPopMatrix();
		}
	}
	void animacioBaixada()
	{
		m_z = m_z - 0.1851;

	}
	void animacioPujada()
	{
		m_z = m_z + 0.3;

	}
};

class Personatge {
public:
	float m_x;
	float m_y;
	float m_z;
	int m_color;
	bool m_colisio; //s'ha de suprimir
	bool dead = false;
	bool m_colisioX;
	bool m_colisioY;

	float m_x_ant;
	float m_y_ant;


	Personatge() {
		m_x = m_y = m_z = m_x_ant = m_y_ant = 0.0;
		m_color = 0;
		m_colisio = false;
		m_colisioX = false;
		m_colisioY = false;
		/*colisions[0] = false;
		colisions[1] = false;
		colisions[2] = false;
		colisions[3] = false;*/
	}
	Personatge(float x, float y, float z, int c) { //Aquestes coordenades corresponen al centre de l'objecte, per com funciona OpenGL. Per accedir als boundaries, hi ha constants amb la mida del mur
		m_x_ant = m_x = x;
		m_y_ant = m_y = y;
		m_z = z;
		m_color = c;
		m_colisio = false;
		m_colisioX = false;
		m_colisioY = false;
		/*colisions[0] = false;
		colisions[1] = false;
		colisions[2] = false;
		colisions[3] = false;*/
	}

	void pinta() {
		switch (m_color)
		{
		case 0:
			glColor3f(1.0, 1.0, 1.0);
			glPushMatrix();
			glTranslatef(m_x, m_y, m_z);
			glScalef(PG_X, PG_Y, PG_Z);
			glutSolidCube(1.0);
			glPopMatrix();
			//glColor4f(1, 1, 1, 1);
			break;
		case 1:
			glColor3f(1.0, 0.0, 1.0);
			glPushMatrix();
			glTranslatef(m_x, m_y, m_z);
			glScalef(PG_X, PG_Y, PG_Z);
			glutSolidCube(1.0);
			glPopMatrix();
			break;
		case 2:
			glColor3f(1.0, 1.0, 0.0);
			glPushMatrix();
			glTranslatef(m_x, m_y, m_z);
			glScalef(PG_X, PG_Y, PG_Z);
			glutSolidCube(1.0);
			glPopMatrix();
			break;

		default:
			break;
		}
	}
};

class Event {
public:
	float m_x;
	float m_y;
	float m_z;
	bool m_colisio;

	bool m_colisioX;
	bool m_colisioY;

	float m_x_ant;
	float m_y_ant;

	int m_tipus;
	bool m_en_curs = false;
	float m_direccio = HOR;
	int indexMurAnimatEnLlista = 1000;
	bool m_animacioIniciada = false;
	bool eventFinalitzat = false;
	/*
	TIPUS
	si tipus=-3 --------> event mur que cau del cel
	si tipus=-2 --------> event final de partida
	si tipus=-4 --------> event mur que puja de l'infern


	*/

	Event()
	{
		m_x = m_y = m_z = m_x_ant = m_y_ant = 0.0;
		m_colisio = false;
		m_colisioX = false;
		m_colisioY = false;
		m_tipus = -2;//Per defecte inicialitzo a la final ja creada per no generar big problems
	}

	Event(float x, float y, float z, int tipus, float direccio) { //Aquestes coordenades corresponen al centre de l'objecte, per com funciona OpenGL. Per accedir als boundaries, hi ha constants amb la mida del mur
		m_x_ant = m_x = x;
		m_y_ant = m_y = y;
		m_z = z;

		m_colisio = false;
		m_colisioX = false;
		m_colisioY = false;

		m_tipus = tipus;

		m_direccio = direccio;
	}

	void pinta() {

		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(m_x, m_y, m_z);
		glScalef(E_X, E_Y, E_Z);
		glutSolidCube(1.0);
		glPopMatrix();
		//glColor4f(1, 1, 1, 1);
	}

	void setTipus(int tipus)
	{
		m_tipus = tipus;
	}

	void actua(Mur& mur)
	{
		if (m_tipus == -3 && m_animacioIniciada)
		{

			if (m_en_curs)
			{
				mur.animacioBaixada();
				if (mur.m_z <= h)
				{
					m_en_curs = false;
					m_animacioIniciada = false;
					eventFinalitzat = true;
					mur.animacioAcabada = true;
				}
			}

		}


	}
};


float angle = 0.0;

void circularMovimentShrek(float moviment[], bool movDir[], float rotShrek[], bool pausa)
{
	if (!pausa) {

		moviment[0] -= 10 * cos(angle);
		moviment[1] -= 10 * sin(angle);


		if (angle >= 360)
		{
			angle = 0;

		}

		angle += 0.005;
		rotShrek[0] = 1;
		//rotShrek[2] = angle * 18*pi;
	}
}


class Shrek {
public:
	objl::Loader* m_loader;
	float* m_moviment;
	bool* m_movDir;
	float* m_rotShrek;
	int* m_texturID;
	int m_tipusMov;
	float m_posicioIniciX;
	float m_posicioIniciY;
	float m_posicioFinalX;
	float m_posicioFinalY;
	float m_posicioZ;

	float m_pos_x;
	float m_pos_y;
	float m_pos_z;

	bool m_ori;


	bool m_direccioHoritzontal=true;
public:
	Shrek(objl::Loader* loader, int texturID[], int tipusMov, 
		float posicioIniciX, float posicioIniciY, float posicioFinalX, float posicioFinalY, 
		float posicioZ, float pos_x, float pos_y, float pos_z, bool ori, bool direccioHoritzontal=true)
	{

		m_loader = loader;
		m_moviment = new float[3]{ 0,0,0 };
		m_movDir = new bool[3]{ false,false,false };
		if (tipusMov > 1) {
			m_rotShrek = new float[3]{ 0.0,-1.0,0.0 };
		}
		else {
			m_rotShrek = new float[3]{ 0.0,0.0,0.0 };
		}
		m_texturID = texturID;
		m_tipusMov = tipusMov;
		m_posicioIniciX = posicioIniciX;
		m_posicioIniciY = posicioIniciY;
		m_posicioFinalX = posicioFinalX;
		m_posicioFinalY = posicioFinalY;
		m_posicioZ = posicioZ;
		m_pos_x = 0;
		m_pos_y = 0;
		m_pos_z = 0;
		m_ori = ori;

		m_direccioHoritzontal = direccioHoritzontal;
	}

	void pinta(bool pausa) {
		glPushMatrix();

		if (m_tipusMov == 0)
		{
			movimentShrek(pausa);
		}
		if (m_tipusMov == 1)
		{
			circularMovimentShrek(m_moviment, m_movDir, m_rotShrek, pausa);
		}

		if (m_direccioHoritzontal)
		{
			//Translació inicial + moviment
			glTranslatef( m_posicioIniciX + m_moviment[0],m_posicioIniciY + m_moviment[1], m_posicioZ + m_moviment[2]);
			m_pos_x = m_posicioIniciX + m_moviment[0]; m_pos_y = m_posicioIniciY + m_moviment[1]; m_posicioZ + m_moviment[2];
			//Rotació inicial
			glRotatef(90, 1, 0, 0);
			//si es mou en vertical
			glRotatef(90, 0, 1, 0);
			//Rotació depenent moviment
			glRotatef(90, 0 + m_rotShrek[0], 0 + m_rotShrek[1], 0 + m_rotShrek[2]);
		}
		else
		{
			//Translació inicial + moviment
			glTranslatef(m_posicioIniciX + m_moviment[0], m_posicioIniciY + m_moviment[1], m_posicioZ + m_moviment[2]);
			m_pos_x = m_posicioIniciX + m_moviment[0]; m_pos_y = m_posicioIniciY + m_moviment[1]; m_posicioZ + m_moviment[2];
			//Rotació inicial
			glRotatef(90, 1, 0, 0);
			//si es mou en vertical
			//Rotació depenent moviment
			glRotatef(90, 0 + m_rotShrek[0], 0 + m_rotShrek[1], 0 + m_rotShrek[2]);
		}
		if (m_tipusMov == 1)
		{
			glRotatef(90, 0, 0, 1);
			glRotatef(90, -1, 0, 0);
			glScalef(0.2f, 0.2f, 0.2f);
		}
		if (m_tipusMov == 5)
		{
			glScalef(0.2f, 0.2f, 0.2f);
		}
		//glScalef(8.0f, 8.0f, 8.0f);
		glScalef(14.0f, 14.0f, 14.0f);

		//textura 16 shrek, 17 shrekShirt
		glEnable(GL_TEXTURE_2D);


		glBindTexture(GL_TEXTURE_2D, m_texturID[16]);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_loader->LoadedMeshes[0].Vertices.size(); i++)
		{
			glTexCoord2f(m_loader->LoadedMeshes[0].Vertices[i].TextureCoordinate.X, 
				m_loader->LoadedMeshes[0].Vertices[i].TextureCoordinate.Y); 
			glVertex3f(m_loader->LoadedMeshes[0].Vertices[i].Position.X, m_loader->LoadedMeshes[0].Vertices[i].Position.Y, 
				m_loader->LoadedMeshes[0].Vertices[i].Position.Z);
		}
		glEnd();


		glBindTexture(GL_TEXTURE_2D, m_texturID[17]);

		glBegin(GL_TRIANGLES);
		for (int i = 0; i < m_loader->LoadedMeshes[1].Vertices.size(); i++)
		{
			glTexCoord2f(m_loader->LoadedMeshes[1].Vertices[i].TextureCoordinate.X, m_loader->LoadedMeshes[1].Vertices[i].TextureCoordinate.Y); glVertex3f(m_loader->LoadedMeshes[1].Vertices[i].Position.X, m_loader->LoadedMeshes[1].Vertices[i].Position.Y, m_loader->LoadedMeshes[1].Vertices[i].Position.Z);
		}
		glEnd();


		glDisable(GL_TEXTURE_2D);

		glPopMatrix();
	}
	void movimentShrek(bool pausa)
	{
		if (!pausa) 
		{
			if (m_direccioHoritzontal)
			{
				if (m_movDir[1] == true)
				{
					m_moviment[1] += 0.2;
					if (m_moviment[1]> m_posicioFinalY - m_posicioIniciY)
					{
						m_movDir[1] = false;
						m_rotShrek[1] = -1;
						
					}
				}
				else
				{
					m_moviment[1] -= 0.2;
					if (m_moviment[1] < 0)
					{
						m_movDir[1] = true;
						m_rotShrek[1] = 1;
					}
				}
			}
			else
			{

				if (m_movDir[0] == true)
				{
					m_moviment[0] += 0.2;
					if (m_moviment[0]  > m_posicioFinalX- m_posicioIniciX)
					{
						m_movDir[0] = false;
						m_rotShrek[1] = -1;
					}
				}
				else
				{
					m_moviment[0] -= 0.2;
					if ( m_moviment[0] < 0)
					{
						m_movDir[0] = true;
						m_rotShrek[1] = 1;
					}
				}
			}

			
		}
	}

};





/*CLASSE LEADERBOARD*/
class Leaderboard {

public:
	
	Leaderboard() { m_CONST_VALOR = 0; m_puntuacio = 0; m_path_leaderboard = ""; }
	~Leaderboard() { m_leaderboard.clear(); };

	int m_CONST_VALOR;
	int m_puntuacio;
	std::string m_path_leaderboard;
	std::vector<int> m_leaderboard;
	
	void set_const_valor(int const_valor) { m_CONST_VALOR = const_valor; }
	//Carrega el fitxer de dades leaderboard a partir d'un nivell seleccionat
	void set_leaderboard(int nivell) {
		if (nivell == 1) m_path_leaderboard = "res/leaderboard1.txt";
		else if (nivell == 2) m_path_leaderboard = "res/leaderboard2.txt";
		else if (nivell == 3) m_path_leaderboard = "res/leaderboard3.txt";
		else if (nivell == 4) m_path_leaderboard = "res/leaderboard4.txt";
	}

	//Funció que calcula els punts un cop s'ha acabat la partida. SI MORT (VIDES = 0) -> PUNTUACIO = 0
	int calcula_punts(int vides, float temps) 
	{
		m_puntuacio = vides * m_CONST_VALOR - temps;
		if (m_puntuacio < 0) m_puntuacio = m_CONST_VALOR;
		return m_puntuacio;
	}


	/*Inicialitza la leaderboard cada cop que s'encen el joc.*/
	void init_leaderboard(int nivell)
	{
		set_leaderboard(nivell);

		std::string score;

		std::ifstream fitxer;

		fitxer.open(m_path_leaderboard);
		m_leaderboard.clear();
		if (fitxer.is_open()) {
			while (getline(fitxer, score)) {
				m_leaderboard.push_back(stoi(score));
			}
			fitxer.close();
		}

	}

	/*ACTUALITZA LA LEADERBOARD EN CAS QUE M_PUNTUACIO SIGUI UN RECORD*/
	void actualitza_leaderboard() 
	{
		
		std::ofstream fitxer;

		auto min_puntuacio = std::min_element(m_leaderboard.begin(), m_leaderboard.end());
		if (m_puntuacio > * min_puntuacio) *min_puntuacio = m_puntuacio;
		std::sort(m_leaderboard.begin(), m_leaderboard.end(), std::greater<int>());

		fitxer.open(m_path_leaderboard);
		for (int score : m_leaderboard) fitxer << std::to_string(score) << std::endl;
		fitxer.close();

	}

};