#pragma once
#include <iostream>

#include "stdafx.h"
#include "constants.h"
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

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
		m_z = m_z - 0.2;

	}
	void animacioPujada()
	{
		m_z = m_z + 0.2;

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

/*std::vector<Mur> initMurs(); /*{ //propera implementaci�: passar per par�metres el nombre de murs i la matriu rotllo suarez
	//de moment, inicialitzaci� "manual"

	Mur * llista = new Mur[6];

	Mur prova1(10.0f, 2.5f, 7.5f, 1);
	llista[0] = prova1;
	Mur prova2(30.0f, 2.5f, 7.5f, 1);
	llista[1] = prova2;
	Mur prova3(10.0f, 22.5f, 7.5f, 1);
	llista[2] = prova3;
	Mur prova4(17.5f, 35.0f, 7.5f, 0);
	llista[3] = prova4;
	Mur prova5(37.5f, 35.0f, 7.5f, 0);
	llista[4] = prova5;
	Mur prova6(37.5f, 15.0f, 7.5f, 0);
	llista[5] = prova6;

	return llista;
}*/

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
				}
			}

		}


	}
};


/*	//Moviment shreck == -5
	float Posicio_x_inicial = 4 * x * 1;
	float Posicio_y_inicial = 4 * x * 2;

	float Posicio_x_final = 4 * x * 4;
	float Posicio_y_final = 4 * x * 2;
	
	*/


/*CLASSE LEADERBOARD*/

int CONST_VALOR = 300;
std::string path_leaderboard = "res/leaderboard.txt";

class Leaderboard {

public:
	Leaderboard();
	Leaderboard(int vides, float temps) { m_vides = vides; m_temps = temps; };
	~Leaderboard() { m_leaderboard.clear(); };

	int m_vides;
	float m_temps;
	int m_puntuacio;
	std::vector<int> m_leaderboard;

	//Funció que calcula els punts un cop s'ha acabat la partida. SI MORT (VIDES = 0) -> PUNTUACIO = 0
	void calcula_punts() 
	{
		m_puntuacio = m_vides * CONST_VALOR - m_temps;
		if (m_puntuacio < 0) m_puntuacio = CONST_VALOR;
	};

	/*Inicialitza la leaderboard cada cop que s'encen el joc.*/
	void init_leaderboard() 
	{
		std::string score;
		std::ifstream fitxer;
		fitxer.open(path_leaderboard);

		if (fitxer.is_open()) {
			while (getline(fitxer, score)) {
				m_leaderboard.push_back(stoi(score));
			}
			fitxer.close();
		}
	};

	/*ACTUALITZA LA LEADERBOARD EN CAS QUE M_PUNTUACIO SIGUI UN RECORD*/
	void actualitza_leaderboard() 
	{
	
		auto min_puntuacio = std::min_element(m_leaderboard.begin(), m_leaderboard.end());
		if (m_puntuacio > * min_puntuacio) *min_puntuacio = m_puntuacio;
		std::sort(m_leaderboard.begin(), m_leaderboard.end(), std::greater<int>());

		std::ofstream fitxer;
		fitxer.open(path_leaderboard);
		for (int score : m_leaderboard) fitxer << std::to_string(score) << std::endl;

		fitxer.close();

	};

};