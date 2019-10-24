//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn bàsic VS2019 MULTIFINESTRA amb OpenGL, interfície MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Setembre 2018)
// material.cpp : Funcions de definició de les propietats de reflectivitat dels objectes.

#include "stdafx.h"
#include "material.h"

// Tipus de materials que es seleccionen a la funció SeleccionaMaterial
MATERIAL  materials[MAX_MATERIALS] =
{
	{//Default
		{0.2f, 0.2f, 0.2f, 1.0f},	// Ambient
		{0.8f, 0.8f, 0.8f, 1.0f},	// Difusse
		{0.0f, 0.0f, 0.0f, 1.0f},	// Specular
		{0.0f, 0.0f, 0.0f, 1.0f},	// Emission
		0							// Shinniness
	},
	{//Material base
		{0, 0, 0.75f, 1},
		{0, 0, 0.75f, 1},
		{0.0f, 0.5f, 1, 1},
		{0, 0, 0, 1},
		20
	},

	{//Metall Obscur
		{0, 0, 0, 1},
		{0.5f, 0.5f, 0.5f, 1},
		{0.7f, 0.7f, 0.7f, 1},
		{0, 0, 0, 1},
		100
	},

	{//Vidre
		{0.2f, 0.65f, 0.9f, 0.5},
		{0.3f, 0.75f, 1, 0.5},
		{1, 1, 1, 1},
		{0, 0, 0, 1},
		50
	},

	{//Goma Negra
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		{0.3f, 0.3f, 0.3f, 1},
		{0, 0, 0, 1},
		20
	},

	{//Gespa
		{0, 0.2f, 0, 1},
		{0.1f, 0.5f, 0.2f, 1},
		{0.1f, 0.5f, 0.2f, 1},
		{0, 0, 0, 1},
		0
	},

	{//Metall Groc
		{0.3f, 0.3f, 0.1f, 1},
		{1, 1, 0.25f, 1},
		{1, 1, 0.5f, 1},
		{0, 0, 0, 1},
		128
	},

	{//Llum vermella
		{1, 0, 0, 1},
		{1, 0, 0, 1},
		{1, 0.5f, 0.5f, 1},
		{1, 0, 0, 1},
		128
	},

	{//Llum Groga
		{1.0f, 1.0f, 0, 1},
		{1, 1.0f, 0, 1},
		{1, 1.0f, 0, 1},
		{1, 0.8f, 0, 1},
		128
	},

	{//Llum verda
		{0, 1, 0, 1},
		{0, 1, 0, 1},
		{0.5f, 1, 0.5f, 1},
		{0, 1, 0, 1},
		128
	},

	{// Fitxer
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		{0, 0, 0, 1},
		0
	}

};


/******************************************************************************\
|* SeleccionaMaterialiColor                                                   *|
|* Selecciona un dels materials	                                              *|
\******************************************************************************/
void SeleccionaMaterialiColor(int quin,bool col,bool sw_mater[4],CColor &c_obj)
{
	const float zeros[4]={0.0f,0.0f,0.0f,1.0f};
	float color[4] = { c_obj.r, c_obj.g, c_obj.b, c_obj.a };

	if (!col) glColor4fv(color);
		else if ((quin >= 0) && (quin<MAX_MATERIALS))
				{	// Component d'emissió de llum del material
					glColorMaterial(GL_FRONT, GL_EMISSION);
					if (sw_mater[0]) {	glColor4fv(materials[quin].emission);
										glMaterialfv(GL_FRONT, GL_EMISSION, materials[quin].emission);
									}
						else {	glColor4fv(zeros);
								glMaterialfv(GL_FRONT, GL_EMISSION, zeros);
							}

				// Coeficient de reflectivitat ambient del material
				glColorMaterial(GL_FRONT, GL_AMBIENT);
				if (sw_mater[1]) {	glColor4fv(materials[quin].ambient);
									glMaterialfv(GL_FRONT, GL_AMBIENT, materials[quin].ambient);
								}
					else {	glColor4fv(zeros);
							glMaterialfv(GL_FRONT, GL_AMBIENT, zeros);
						}

				// Coeficient de reflectivitat difusa del material
				glColorMaterial(GL_FRONT, GL_DIFFUSE);
				if (sw_mater[2]) {	glColor4fv(materials[quin].diffuse);
									glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[quin].diffuse);	// Coef. Reflexió Difusa
								}
					else {	glColor4fv(zeros);
							glMaterialfv(GL_FRONT, GL_DIFFUSE, zeros);
						}

				// Coeficient de reflectivitat especular del material
				glColorMaterial(GL_FRONT, GL_SPECULAR);
				if (sw_mater[3]){	glColor4fv(materials[quin].specular);
									glMaterialfv(GL_FRONT, GL_SPECULAR, materials[quin].specular);	// Coef. Reflexió Especular
									glMaterialf(GL_FRONT, GL_SHININESS, materials[quin].shininess);
								}
					else {	glColor4fv(zeros);
							glMaterialfv(GL_FRONT, GL_SPECULAR, zeros);
							glMaterialf(GL_FRONT, GL_SHININESS, 200);
						}
			}
			else {	// Component d'emissió de llum del material
					glColorMaterial(GL_FRONT, GL_EMISSION);
					if (sw_mater[0]) {	glColor4fv(color);
										glMaterialfv(GL_FRONT, GL_EMISSION, color);
									}
						else {	glColor4fv(zeros);
								glMaterialfv(GL_FRONT, GL_EMISSION, zeros);
							}

					// Coeficient de reflectivitat ambient del material
					glColorMaterial(GL_FRONT, GL_AMBIENT);
					if (sw_mater[1]) {	glColor4fv(color);
										glMaterialfv(GL_FRONT, GL_AMBIENT, color);
									}
						else {	glColor4fv(zeros);
								glMaterialfv(GL_FRONT, GL_AMBIENT, zeros);
							}

					// Coeficient de reflectivitat difusa del material
					glColorMaterial(GL_FRONT, GL_DIFFUSE);
					if (sw_mater[2]) {	glColor4fv(color);
										glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
									}
						else {	glColor4fv(zeros);
								glMaterialfv(GL_FRONT, GL_DIFFUSE, zeros);
							}

					// Coeficient de reflectivitat especular del material
					glColorMaterial(GL_FRONT, GL_SPECULAR);
					if (sw_mater[3]) {	glColor4fv(color);
										glMaterialfv(GL_FRONT, GL_SPECULAR, color);
										glMaterialf(GL_FRONT, GL_SHININESS, 128);
									}
						else {	glColor4fv(zeros);
								glMaterialfv(GL_FRONT, GL_SPECULAR, zeros);
								glMaterialf(GL_FRONT, GL_SHININESS, 0);
							}
				}
}


/******************************************************************************\
|* SeleccionaMaterial                                                         *|
|* Selecciona un dels materials	                                              *|
\******************************************************************************/
void SeleccionaMaterial(int quin,bool sw_mater[4])
{
	const float zeros[4]={0.0f,0.0f,0.0f,1.0f};
	
	if ((quin >= 0) && (quin<MAX_MATERIALS))
		{	// Component d'emissió de llum del material
			glColorMaterial(GL_FRONT, GL_EMISSION);
			if (sw_mater[0]) {	glColor4fv(materials[quin].emission);
								glMaterialfv(GL_FRONT, GL_EMISSION, materials[quin].emission);
							}
				else {	glColor4fv(zeros);
						glMaterialfv(GL_FRONT, GL_EMISSION, zeros);
					}

		// Coeficient de reflectivitat ambient del material
		glColorMaterial(GL_FRONT, GL_AMBIENT);
		if (sw_mater[1]) {	glColor4fv(materials[quin].ambient);
							glMaterialfv(GL_FRONT, GL_AMBIENT, materials[quin].ambient);
						}
			else {	glColor4fv(zeros);
					glMaterialfv(GL_FRONT, GL_AMBIENT, materials[quin].ambient);
				}

		// Coeficient de reflectivitat difusa del material
		glColorMaterial(GL_FRONT, GL_DIFFUSE);
		if (sw_mater[2]) {	glColor4fv(materials[quin].diffuse);
							glMaterialfv(GL_FRONT, GL_DIFFUSE, materials[quin].diffuse);	// Coef. Reflexió Difusa
						}
			else {	glColor4fv(zeros);
					glMaterialfv(GL_FRONT, GL_DIFFUSE, zeros);
				}

		// Coeficient de reflectivitat especular del material
		glColorMaterial(GL_FRONT, GL_SPECULAR);
		if (sw_mater[3]){	glColor4fv(materials[quin].specular);
							glMaterialfv(GL_FRONT, GL_SPECULAR, materials[quin].specular);	// Coef. Reflexió Especular
							glMaterialf(GL_FRONT, GL_SHININESS, materials[quin].shininess);
						}
			else {	glColor4fv(zeros);
					glMaterialfv(GL_FRONT, GL_SPECULAR, zeros);
					glMaterialf(GL_FRONT, GL_SHININESS, 0);
				}
	}
}


/******************************************************************************\
|* SeleccionaColor                                                         *|
|* Selecciona un dels materials	                                              *|
\******************************************************************************/
void SeleccionaColor(bool col, bool sw_mater[4], CColor &c_obj)
{
	const float zeros[4]={0.0f,0.0f,0.0f,1.0f};
	float color[4] = { c_obj.r, c_obj.g, c_obj.b, c_obj.a };

	glColor4fv(color);	//glColor3f(c_obj.r, c_obj.g, c_obj.b);

// Component de reflectivitat d'emissió de llum del material
	glColorMaterial(GL_FRONT, GL_EMISSION);
	if (sw_mater[0]) {	glColor4fv(color);
						glMaterialfv(GL_FRONT, GL_EMISSION, color); 
					}
		else {	glColor4fv(zeros);
				glMaterialfv(GL_FRONT, GL_EMISSION, zeros);
			}
						
// Component de reflectivitat ambient del material
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	if (sw_mater[1]) {	glColor4fv(color);
						glMaterialfv(GL_FRONT, GL_AMBIENT, color); 
					}
		else {	glColor4fv(zeros);
				glMaterialfv(GL_FRONT, GL_AMBIENT, zeros);
			}
// Component de reflectivitat difusa del material
	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	if (sw_mater[2]) {	glColor4fv(color);
						glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
					}
		else {	glColor4fv(zeros);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, zeros); 
			}
// Component de reflectivitat especular del material
	glColorMaterial(GL_FRONT, GL_SPECULAR);
	if (sw_mater[3]) {	glColor4fv(color);
						glMaterialfv(GL_FRONT, GL_SPECULAR, color);
						glMaterialf(GL_FRONT, GL_SHININESS, 128);
					}
		else {	glColor4fv(zeros);
				glMaterialfv(GL_FRONT, GL_SPECULAR, zeros);
				glMaterialf(GL_FRONT, GL_SHININESS, 0);
			}
}


// llegir_Material: Llegir propietats de material de fitxer segons estructura MATERIAL
//			Retorna l'estructura MATERIAL llegida i un booleà si s'ha trobat el fitxer [TRUE] o no [FALSE].
bool llegir_Material(CString filename,int index)
{ 
	FILE *fd;
	char strMessage[255] = { 0 };
	GLfloat auxemis[4],auxamb[4],auxdiff[4],auxspec[4];
	GLfloat auxshin;

// Inicialitzar variable
	auxamb[0]=0.0f;			auxamb[1]=0.0f;			auxamb[2]=0.0f;			auxamb[3]=1.0f;
	auxemis[0]=0.0f;		auxemis[1]=0.0f;		auxemis[2]=0.0f;		auxemis[3]=1.0f;
	auxdiff[0]=0.0f,		auxdiff[1]=0.0f;		auxdiff[2]=0.0f;		auxdiff[3]=1.0f;
	auxspec[0]=0.0f;		auxspec[1]=0.0f;		auxspec[2]=0.0f;		auxspec[3]=1.0f;
	auxshin=0.0f;

	// Conversió variable w_char --> char *
	//	wcstombs(nomf,filename.GetBuffer(3),90);
	char *nomf = reinterpret_cast<char *> (filename.GetBuffer(3));

//if ( (fd=fopen(nomf,"rt"))==NULL)			// VS6.0
if ( (fopen_s(&fd,nomf,"rt"))!=0)			// VS2005
	{	
		sprintf_s(strMessage, "Unable to find the file: %s!", nomf);
		//		MessageBox(NULL, strMessage, "Error", MB_OK);
		LPCWSTR texte1 = reinterpret_cast<LPCWSTR> (strMessage);
		LPCWSTR texte2 = reinterpret_cast<LPCWSTR> ("Error");
		MessageBox(NULL, texte1, texte2, MB_OK);
		return false;
	}

fscanf(fd,"%f %f %f %f \n",&auxemis[0],&auxemis[1],&auxemis[2],&auxemis[3]);
fscanf(fd,"%f %f %f %f \n",&auxamb[0],&auxamb[1],&auxamb[2],&auxamb[3]);
fscanf(fd,"%f %f %f %f \n",&auxdiff[0],&auxdiff[1],&auxdiff[2],&auxdiff[3]);
fscanf(fd,"%f %f %f %f \n",&auxspec[0],&auxspec[1],&auxspec[2],&auxspec[3]);
fscanf(fd,"%f \n",&auxshin);

fclose(fd);

materials[index].emission[0]=auxemis[0];	materials[index].emission[1]=auxemis[1];
materials[index].emission[2]=auxemis[2];	materials[index].emission[3]=auxemis[3];

materials[index].ambient[0]=auxamb[0];		materials[index].ambient[1]=auxamb[1];
materials[index].ambient[2]=auxamb[2];		materials[index].ambient[3]=auxamb[3];

materials[index].diffuse[0]=auxdiff[0];		materials[index].diffuse[1]=auxdiff[1];
materials[index].diffuse[2]=auxdiff[2];		materials[index].diffuse[3]=auxdiff[3];

materials[index].specular[0]=auxspec[0];	materials[index].specular[1]=auxspec[1];
materials[index].specular[2]=auxspec[2];	materials[index].specular[3]=auxspec[3];

materials[index].shininess=auxshin;
return true;

}
