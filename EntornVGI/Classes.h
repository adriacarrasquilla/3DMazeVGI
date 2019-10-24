#pragma once
#include <iostream>

#include "stdafx.h"
#include "constants.h"

class Mur {
public:
	float m_x;
	float m_y;
	float m_z;
	bool m_ori; //Boole� que emmagatzema la orientaci� del mur
	Mur() {
		m_x = m_y = m_z = 0.0;
		m_ori = 0;
	}
	Mur(float x, float y, float z, bool o) { //Aquestes coordenades corresponen al centre de l'objecte, per com funciona OpenGL. Per accedir als boundaries, hi ha constants amb la mida del mur
		m_x = x;
		m_y = y;
		m_z = z;
		m_ori = o;
	}

	void pinta() {
		if (m_ori) {
			glColor3f(0.5, 0.5, 0.25);
			glPushMatrix();
			glTranslatef(m_x, m_y, m_z);
			glScalef(MUR_X, MUR_Y, MUR_Z);
			glutSolidCube(1.0);
			glPopMatrix();
		}
		else {
			glColor3f(0.5, 0.5, 0.25);
			glPushMatrix();
			glTranslatef(m_x, m_y, m_z);
			glScalef(MUR_Y, MUR_X, MUR_Z);
			glutSolidCube(1.0);
			glPopMatrix();
		}
	}
};

class Personatge {
public:
	float m_x;
	float m_y;
	float m_z;
	int m_color;
	Personatge() {
		m_x = m_y = m_z = 0.0;
		m_color = 0;
	}
	Personatge(float x, float y, float z, int c) { //Aquestes coordenades corresponen al centre de l'objecte, per com funciona OpenGL. Per accedir als boundaries, hi ha constants amb la mida del mur
		m_x = x;
		m_y = y;
		m_z = z;
		m_color = c;
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
			break;
		case 1:
			glColor3f(1.0, 0.0, 0.0);
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
std::vector<Mur> initMurs(); /*{ //propera implementaci�: passar per par�metres el nombre de murs i la matriu rotllo suarez
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