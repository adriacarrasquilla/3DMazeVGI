//******** PRACTICA VISUALITZACI� GR�FICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn b�sic VS2019 MULTIFINESTRA amb OpenGL, interf�cie MFC i Status Bar
//******** Ferran Poveda, Marc Vivet, Carme Juli�, D�bora Gil, Enric Mart� (Setembre 2019)
// EntornVGIView.cpp: implementaci�n de la clase CEntornVGIView
// FUNCIONS:		- Control del bucle principal (OnPaint)
//					- Control teclat (OnKeyDown)
//					- Control mouse interactiu i botons mouse 
//							(OnLButtomDown, OnRButtomDown, OnMouseMove)
//					- Control opcions de men� (On*, OnUpdate*)
//					- Control de color de fons per teclat (FONS)
//					- Transformacions Geom�triques Interactives via mouse
//
//    Versi� 2.0:	- Canvi de color de l'objecte per teclat (OBJ)
//					- Fixar Transformacions Geom�triques desactivant opcions Transforma (INSERT dins opcions Transforma)
//					- Esborrar Transformacions Geom�triques fixades (DELETE dins opcions Transforma)
//					- Fixar Traslaci� pantalla fora de l'opci� Vista->Pan? (INSERT dins opci� Vista->Pan?)
//					- Esborrar Traslaci� pantalla fixada (DELETE dins opci� Vista->Pan?)
//
//	  Versi� 2.2:	- Opci� VISTA --> Sat�l.lit: Punt de Vista en moviment segons moviment mouse
//
//	  Versi� 2.5:	- Afegits objectes cubRGB i Tie (nau Star Wars fet per alumnes)
//					- Opci� VISTA --> FullScreen?: Opci� FullScreen per men� i per PopUp menu enmig pantalla. T� un bug al restaurar pantalla 
//													normal (inclos men� IDR_MENU_WINDOW)
//

#include "stdafx.h"

// Se pueden definir SHARED_HANDLERS en un proyecto ATL implementando controladores de vista previa, miniatura
// y filtro de b�squeda, y permiten compartir c�digo de documentos con ese proyecto.
#ifndef SHARED_HANDLERS
#include "EntornVGI.h"
#endif

#include "EntornVGIDoc.h"
#include "EntornVGIView.h"
#include "visualitzacio.h"	// Include funcions de projeci� i il.luminaci�
#include "escena.h"			// Include funcions d'objectes OpenGL

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CEntornVGIView

IMPLEMENT_DYNCREATE(CEntornVGIView, CView)

BEGIN_MESSAGE_MAP(CEntornVGIView, CView)
	// Comandos de impresi�n est�ndar
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEntornVGIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_COMMAND(ID_ARXIU_OBRIR_FRACTAL, &CEntornVGIView::OnArxiuObrirFractal)
	ON_COMMAND(ID_ARXIU_OBRIR_FITXER_OBJ, &CEntornVGIView::OnArxiuObrirFitxerObj)
	ON_COMMAND(ID_ARXIU_OBRIR_FITXER_3DS, &CEntornVGIView::OnArxiuObrirFitxer3ds)
	ON_COMMAND(ID_VISTA_Mobil, &CEntornVGIView::OnVistaMobil)
	ON_UPDATE_COMMAND_UI(ID_VISTA_Mobil, &CEntornVGIView::OnUpdateVistaMobil)
	ON_COMMAND(ID_VISTA_ZOOM, &CEntornVGIView::OnVistaZoom)
	ON_UPDATE_COMMAND_UI(ID_VISTA_ZOOM, &CEntornVGIView::OnUpdateVistaZoom)
	ON_COMMAND(ID_VISTA_POLARS_X, &CEntornVGIView::OnVistaPolarsX)
	ON_UPDATE_COMMAND_UI(ID_VISTA_POLARS_X, &CEntornVGIView::OnUpdateVistaPolarsX)
	ON_COMMAND(ID_VISTA_POLARS_Y, &CEntornVGIView::OnVistaPolarsY)
	ON_UPDATE_COMMAND_UI(ID_VISTA_POLARS_Y, &CEntornVGIView::OnUpdateVistaPolarsY)
	ON_COMMAND(ID_VISTA_POLARS_Z, &CEntornVGIView::OnVistaPolarsZ)
	ON_UPDATE_COMMAND_UI(ID_VISTA_POLARS_Z, &CEntornVGIView::OnUpdateVistaPolarsZ)
	ON_COMMAND(ID_VISTA_PAN, &CEntornVGIView::OnVistaPan)
	ON_UPDATE_COMMAND_UI(ID_VISTA_PAN, &CEntornVGIView::OnUpdateVistaPan)
	ON_COMMAND(ID_VISTA_ORIGENPAN, &CEntornVGIView::OnVistaOrigenpan)
	ON_COMMAND(ID_VISTA_NAVEGA, &CEntornVGIView::OnVistaNavega)
	ON_UPDATE_COMMAND_UI(ID_VISTA_NAVEGA, &CEntornVGIView::OnUpdateVistaNavega)
	ON_COMMAND(ID_VISTA_ORIGENNAVEGA, &CEntornVGIView::OnVistaOrigennavega)
	ON_COMMAND(ID_VISTA_EIXOS, &CEntornVGIView::OnVistaEixos)
	ON_UPDATE_COMMAND_UI(ID_VISTA_EIXOS, &CEntornVGIView::OnUpdateVistaEixos)
	ON_COMMAND(ID_PROJECCIO_PERSPECTIVA, &CEntornVGIView::OnProjeccioPerspectiva)
	ON_UPDATE_COMMAND_UI(ID_PROJECCIO_PERSPECTIVA, &CEntornVGIView::OnUpdateProjeccioPerspectiva)
	ON_COMMAND(ID_OBJECTE_CUB, &CEntornVGIView::OnObjecteCub)
	ON_UPDATE_COMMAND_UI(ID_OBJECTE_CUB, &CEntornVGIView::OnUpdateObjecteCub)
	ON_COMMAND(ID_OBJECTE_ESFERA, &CEntornVGIView::OnObjecteEsfera)
	ON_UPDATE_COMMAND_UI(ID_OBJECTE_ESFERA, &CEntornVGIView::OnUpdateObjecteEsfera)
	ON_COMMAND(ID_OBJECTE_TETERA, &CEntornVGIView::OnObjecteTetera)
	ON_UPDATE_COMMAND_UI(ID_OBJECTE_TETERA, &CEntornVGIView::OnUpdateObjecteTetera)
	ON_COMMAND(ID_OBJECTE_TRUCK, &CEntornVGIView::OnObjecteTruck)
	ON_UPDATE_COMMAND_UI(ID_OBJECTE_TRUCK, &CEntornVGIView::OnUpdateObjecteTruck)
	ON_COMMAND(ID_TRANSFORMA_TRASLACIO, &CEntornVGIView::OnTransformaTraslacio)
	ON_UPDATE_COMMAND_UI(ID_TRANSFORMA_TRASLACIO, &CEntornVGIView::OnUpdateTransformaTraslacio)
	ON_COMMAND(ID_TRANSFORMA_ORIGENTRASLACIO, &CEntornVGIView::OnTransformaOrigentraslacio)
	ON_COMMAND(ID_TRANSFORMA_ROTACIO, &CEntornVGIView::OnTransformaRotacio)
	ON_UPDATE_COMMAND_UI(ID_TRANSFORMA_ROTACIO, &CEntornVGIView::OnUpdateTransformaRotacio)
	ON_COMMAND(ID_TRANSFORMA_ORIGENROTACIO, &CEntornVGIView::OnTransformaOrigenrotacio)
	ON_COMMAND(ID_TRANSFORMA_ESCALAT, &CEntornVGIView::OnTransformaEscalat)
	ON_UPDATE_COMMAND_UI(ID_TRANSFORMA_ESCALAT, &CEntornVGIView::OnUpdateTransformaEscalat)
	ON_COMMAND(ID_TRANSFORMA_ORIGENESCALAT, &CEntornVGIView::OnTransformaOrigenescalat)
	ON_COMMAND(ID_TRANSFORMA_MOBILX, &CEntornVGIView::OnTransformaMobilx)
	ON_UPDATE_COMMAND_UI(ID_TRANSFORMA_MOBILX, &CEntornVGIView::OnUpdateTransformaMobilx)
	ON_COMMAND(ID_TRANSFORMA_MOBILY, &CEntornVGIView::OnTransformaMobily)
	ON_UPDATE_COMMAND_UI(ID_TRANSFORMA_MOBILY, &CEntornVGIView::OnUpdateTransformaMobily)
	ON_COMMAND(ID_TRANSFORMA_MOBILZ, &CEntornVGIView::OnTransformaMobilz)
	ON_UPDATE_COMMAND_UI(ID_TRANSFORMA_MOBILZ, &CEntornVGIView::OnUpdateTransformaMobilz)
	ON_COMMAND(ID_OCULTACIONS_TESTVIS, &CEntornVGIView::OnOcultacionsTestvis)
	ON_UPDATE_COMMAND_UI(ID_OCULTACIONS_TESTVIS, &CEntornVGIView::OnUpdateOcultacionsTestvis)
	ON_COMMAND(ID_OCULTACIONS_ZBUFFER, &CEntornVGIView::OnOcultacionsZbuffer)
	ON_UPDATE_COMMAND_UI(ID_OCULTACIONS_ZBUFFER, &CEntornVGIView::OnUpdateOcultacionsZbuffer)
	ON_COMMAND(ID_OCULTACIONS_BACKLINE, &CEntornVGIView::OnOcultacionsBackline)
	ON_UPDATE_COMMAND_UI(ID_OCULTACIONS_BACKLINE, &CEntornVGIView::OnUpdateOcultacionsBackline)
	ON_COMMAND(ID_ILUMINACIO_LLUMFIXE, &CEntornVGIView::OnIluminacioLlumfixe)
	ON_UPDATE_COMMAND_UI(ID_ILUMINACIO_LLUMFIXE, &CEntornVGIView::OnUpdateIluminacioLlumfixe)
	ON_COMMAND(ID_ILUMINACIO_FILFERROS, &CEntornVGIView::OnIluminacioFilferros)
	ON_UPDATE_COMMAND_UI(ID_ILUMINACIO_FILFERROS, &CEntornVGIView::OnUpdateIluminacioFilferros)
	ON_COMMAND(ID_ILUMINACIO_PLANA, &CEntornVGIView::OnIluminacioPlana)
	ON_UPDATE_COMMAND_UI(ID_ILUMINACIO_PLANA, &CEntornVGIView::OnUpdateIluminacioPlana)
	ON_COMMAND(ID_ILUMINACIO_GOURAUD, &CEntornVGIView::OnIluminacioGouraud)
	ON_UPDATE_COMMAND_UI(ID_ILUMINACIO_GOURAUD, &CEntornVGIView::OnUpdateIluminacioGouraud)
	ON_COMMAND(ID_MATERIAL_EMISSIO, &CEntornVGIView::OnMaterialEmissio)
	ON_UPDATE_COMMAND_UI(ID_MATERIAL_EMISSIO, &CEntornVGIView::OnUpdateMaterialEmissio)
	ON_COMMAND(ID_MATERIAL_AMBIENT, &CEntornVGIView::OnMaterialAmbient)
	ON_UPDATE_COMMAND_UI(ID_MATERIAL_AMBIENT, &CEntornVGIView::OnUpdateMaterialAmbient)
	ON_COMMAND(ID_MATERIAL_DIFUSA, &CEntornVGIView::OnMaterialDifusa)
	ON_UPDATE_COMMAND_UI(ID_MATERIAL_DIFUSA, &CEntornVGIView::OnUpdateMaterialDifusa)
	ON_COMMAND(ID_MATERIAL_ESPECULAR, &CEntornVGIView::OnMaterialEspecular)
	ON_UPDATE_COMMAND_UI(ID_MATERIAL_ESPECULAR, &CEntornVGIView::OnUpdateMaterialEspecular)
	ON_COMMAND(ID_ILUMINACIO_TEXTURES, &CEntornVGIView::OnIluminacioTextures)
	ON_UPDATE_COMMAND_UI(ID_ILUMINACIO_TEXTURES, &CEntornVGIView::OnUpdateIluminacioTextures)
	ON_COMMAND(ID_ILUMINACIO_TEXTURA_FITXERIMATGE, &CEntornVGIView::OnIluminacioTexturaFitxerimatge)
	ON_UPDATE_COMMAND_UI(ID_ILUMINACIO_TEXTURA_FITXERIMATGE, &CEntornVGIView::OnUpdateIluminacioTexturaFitxerimatge)
	ON_COMMAND(ID_LLUMS_LLUMAMBIENT, &CEntornVGIView::OnLlumsLlumambient)
	ON_UPDATE_COMMAND_UI(ID_LLUMS_LLUMAMBIENT, &CEntornVGIView::OnUpdateLlumsLlumambient)
	ON_COMMAND(ID_LLUMS_LLUM0, &CEntornVGIView::OnLlumsLlum0)
	ON_UPDATE_COMMAND_UI(ID_LLUMS_LLUM0, &CEntornVGIView::OnUpdateLlumsLlum0)
	ON_COMMAND(ID_SHADERS_SENSE, &CEntornVGIView::OnShadersSense)
	ON_UPDATE_COMMAND_UI(ID_SHADERS_SENSE, &CEntornVGIView::OnUpdateShadersSense)
	ON_COMMAND(ID_SHADERS_GOURAUD, &CEntornVGIView::OnShadersGouraud)
	ON_UPDATE_COMMAND_UI(ID_SHADERS_GOURAUD, &CEntornVGIView::OnUpdateShadersGouraud)
	ON_COMMAND(ID_SHADERS_PHONG, &CEntornVGIView::OnShadersPhong)
	ON_UPDATE_COMMAND_UI(ID_SHADERS_PHONG, &CEntornVGIView::OnUpdateShadersPhong)
	ON_COMMAND(ID_VISTA_SATELIT, &CEntornVGIView::OnVistaSatelit)
	ON_UPDATE_COMMAND_UI(ID_VISTA_SATELIT, &CEntornVGIView::OnUpdateVistaSatelit)
	ON_COMMAND(ID_VISTA_FULLSCREEN, &CEntornVGIView::OnVistaFullscreen)
	ON_UPDATE_COMMAND_UI(ID_VISTA_FULLSCREEN, &CEntornVGIView::OnUpdateVistaFullscreen)
	ON_COMMAND(ID_OBJECTE_CUB_RGB, &CEntornVGIView::OnObjecteCubRGB)
	ON_UPDATE_COMMAND_UI(ID_OBJECTE_CUB_RGB, &CEntornVGIView::OnUpdateObjecteCubRGB)
	ON_COMMAND(ID_OBJECTE_TIE, &CEntornVGIView::OnObjecteTie)
	ON_UPDATE_COMMAND_UI(ID_OBJECTE_TIE, &CEntornVGIView::OnUpdateObjecteTie)
	ON_COMMAND(ID_ILUMINACIO_PUNTS, &CEntornVGIView::OnIluminacioPunts)
	ON_UPDATE_COMMAND_UI(ID_ILUMINACIO_PUNTS, &CEntornVGIView::OnUpdateIluminacioPunts)
	ON_COMMAND(ID_SHADER_LOAD_FILES, &CEntornVGIView::OnShaderLoadFiles)
	ON_UPDATE_COMMAND_UI(ID_SHADER_LOAD_FILES, &CEntornVGIView::OnUpdateShaderLoadFiles)
	ON_COMMAND(ID_OCULTACIONS_FRONTFACES, &CEntornVGIView::OnOcultacionsFrontFaces)
	ON_UPDATE_COMMAND_UI(ID_OCULTACIONS_FRONTFACES, &CEntornVGIView::OnUpdateOcultacionsFrontFaces)
	ON_COMMAND(ID_LLUMS_LLUM1, &CEntornVGIView::OnLlumsLlum1)
	ON_UPDATE_COMMAND_UI(ID_LLUMS_LLUM1, &CEntornVGIView::OnUpdateLlumsLlum1)
	ON_COMMAND(ID_LLUMS_LLUM2, &CEntornVGIView::OnLlumsLlum2)
	ON_UPDATE_COMMAND_UI(ID_LLUMS_LLUM2, &CEntornVGIView::OnUpdateLlumsLlum2)
	ON_COMMAND(ID_LLUMS_LLUM3, &CEntornVGIView::OnLlumsLlum3)
	ON_UPDATE_COMMAND_UI(ID_LLUMS_LLUM3, &CEntornVGIView::OnUpdateLlumsLlum3)
	ON_COMMAND(ID_LLUMS_LLUM4, &CEntornVGIView::OnLlumsLlum4)
	ON_UPDATE_COMMAND_UI(ID_LLUMS_LLUM4, &CEntornVGIView::OnUpdateLlumsLlum4)
	ON_COMMAND(ID_OBJETE_CORBA_BEZIER, &CEntornVGIView::OnObjeteCorbaBezier)
	ON_UPDATE_COMMAND_UI(ID_OBJETE_CORBA_BEZIER, &CEntornVGIView::OnUpdateObjeteCorbaBezier)
	ON_COMMAND(ID_OBJECTE_CORBA_LEMNISCATA, &CEntornVGIView::OnObjecteCorbaLemniscata)
	ON_UPDATE_COMMAND_UI(ID_OBJECTE_CORBA_LEMNISCATA, &CEntornVGIView::OnUpdateObjecteCorbaLemniscata)
	ON_COMMAND(ID_OBJECTE_CORBA_BSPLINE, &CEntornVGIView::OnObjecteCorbaBSpline)
	ON_UPDATE_COMMAND_UI(ID_OBJECTE_CORBA_BSPLINE, &CEntornVGIView::OnUpdateObjecteCorbaBSpline)
	ON_COMMAND(ID_OBJECTE_PUNTS_CONTROL, &CEntornVGIView::OnObjectePuntsControl)
	ON_UPDATE_COMMAND_UI(ID_OBJECTE_PUNTS_CONTROL, &CEntornVGIView::OnUpdateObjectePuntsControl)
	ON_COMMAND(ID_VISTA_GRIDXY, &CEntornVGIView::OnVistaGridXY)
	ON_UPDATE_COMMAND_UI(ID_VISTA_GRIDXY, &CEntornVGIView::OnUpdateVistaGridXY)
	ON_COMMAND(ID_VISTA_GRIDXZ, &CEntornVGIView::OnVistaGridXZ)
	ON_UPDATE_COMMAND_UI(ID_VISTA_GRIDXZ, &CEntornVGIView::OnUpdateVistaGridXZ)
	ON_COMMAND(ID_VISTA_GRIDYZ, &CEntornVGIView::OnVistaGridYZ)
	ON_UPDATE_COMMAND_UI(ID_VISTA_GRIDYZ, &CEntornVGIView::OnUpdateVistaGridYZ)
	ON_COMMAND(ID_VISTA_GRIDXYZ, &CEntornVGIView::OnVistaGridXYZ)
	ON_UPDATE_COMMAND_UI(ID_VISTA_GRIDXYZ, &CEntornVGIView::OnUpdateVistaGridXYZ)
	ON_COMMAND(ID_ILUMINACIO2SIDES, &CEntornVGIView::OnIluminacio2Sides)
	ON_UPDATE_COMMAND_UI(ID_ILUMINACIO2SIDES, &CEntornVGIView::OnUpdateIluminacio2Sides)
	//ON_COMMAND(ID_PROJECCIOORTOGRAFICA, &CEntornVGIView::OnProjeccioortografica)
	//ON_UPDATE_COMMAND_UI(ID_PROJECCIOORTOGRAFICA, &CEntornVGIView::OnUpdateProjeccioortografica)
	ON_COMMAND(ID_OBJECTE_MUR, &CEntornVGIView::OnObjecteMur)
	ON_UPDATE_COMMAND_UI(ID_OBJECTE_MUR, &CEntornVGIView::OnUpdateObjecteMur)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Construcci�n o destrucci�n de CEntornVGIView

CEntornVGIView::CEntornVGIView()
{
	// TODO: agregar aqu� el c�digo de construcci�n
	//	int i = 0;

	//------ Entorn VGI: Inicialitzaci� de les variables globals de CEntornVGIView
	int i;

	// Entorn VGI: Variables de control per Men� Veure->Pantalla Completa 
	fullscreen = false;

	// Entorn VGI: Variables de control per Men� Vista: canvi PV interactiu, Zoom, dibuixar eixos i grid 
	mobil = false;	zzoom = false;	satelit = false;	pan = false;	navega = true;		eixos = false;
	sw_grid = false;
	grid.x = false;	grid.y = false; grid.z = false;		grid.w = false;
	hgrid.x = 0.0;	hgrid.y = 0.0;	hgrid.z = 0.0;		hgrid.w = 0.0;

	// Entorn VGI: Variables opci� Vista->Pan
	fact_pan = 1;
	tr_cpv.x = 0;	tr_cpv.y = 0;	tr_cpv.z = 0;		tr_cpvF.x = 0;	tr_cpvF.y = 0;	tr_cpvF.z = 0;

	// Entorn VGI: Variables de control de l'opci� Vista->Navega?
	n[0] = 0.0;		n[1] = 0.0;		n[2] = 5.0;
	v[0] = 0.0;		v[1] = 0.0;		v[2] = 1.0;
	opvN.x = -3.0;	opvN.y = 12.0;		opvN.z = 5.0;
	angleZ = 0.0;	angleY = 0.0;
	salt = false; salta = 60;

	// Entorn VGI: Variables de control per les opcions de men� Projecci�, Objecte
	projeccio = PERSPECT;			objecte = MUR;

	// Entorn VGI: Variables de control del men� Transforma
	transf = false;		trasl = false;		rota = false;		escal = false;
	fact_Tras = 1;		fact_Rota = 90;
	TG.VTras.x = 0.0;	TG.VTras.y = 0.0;	TG.VTras.z = 0;	TGF.VTras.x = 0.0;	TGF.VTras.y = 0.0;	TGF.VTras.z = 0;
	TG.VRota.x = 0;		TG.VRota.y = 0;		TG.VRota.z = 0;	TGF.VRota.x = 0;	TGF.VRota.y = 0;	TGF.VRota.z = 0;
	TG.VScal.x = 1;		TG.VScal.y = 1;		TG.VScal.z = 1;	TGF.VScal.x = 1;	TGF.VScal.y = 1;	TGF.VScal.z = 1;

	transX = false;	transY = false;	transZ = false;

	// Entorn VGI: Variables de control per les opcions de men� Ocultacions
	front_faces = true;	test_vis = false;	oculta = true;		back_line = false;

	// Entorn VGI: Variables de control del men� Iluminaci�		
	ilumina = PLANA;			ifixe = true;					ilum2sides = false;
	// Reflexions actives: Ambient [1], Difusa [2] i Especular [3]. No actives: Emission [0]. 
	sw_material[0] = false;			sw_material[1] = true;			sw_material[2] = true;			sw_material[3] = true;
	sw_material_old[0] = false;		sw_material_old[1] = true;		sw_material_old[2] = true;		sw_material_old[3] = true;
	textura = false;				t_textura = CAP;				textura_map = true;
	for (i = 0; i < NUM_MAX_TEXTURES; i++) texturesID[i] = -1;

	// Entorn VGI: Variables de control del men� Llums
	// Entorn VGI: Inicialitzaci� variables Llums
	llum_ambient = true;
	perduda = false;
	for (i = 1; i < NUM_MAX_LLUMS; i++) llumGL[i].encesa = false;
	for (i = 0; i < NUM_MAX_LLUMS; i++) {
		llumGL[i].encesa = false;
		llumGL[i].difusa[0] = 1.0f;	llumGL[i].difusa[1] = 1.0f;	llumGL[i].difusa[2] = 1.0f;	llumGL[i].difusa[3] = 1.0f;
		llumGL[i].especular[0] = 1.0f; llumGL[i].especular[1] = 1.0f; llumGL[i].especular[2] = 1.0f; llumGL[i].especular[3] = 1.0f;
	}

	// LLum 0: �tenuaci� constant (c=1), sobre l'eix Z, no restringida.
	llumGL[0].encesa = true;
	llumGL[0].difusa[0] = 1.0f;			llumGL[0].difusa[1] = 1.0f;			llumGL[0].difusa[2] = 1.0f;		llumGL[0].difusa[3] = 1.0f;
	llumGL[0].especular[0] = 1.0f;		llumGL[0].especular[1] = 1.0f;		llumGL[0].especular[2] = 1.0f;	llumGL[0].especular[3] = 1.0f;

	llumGL[0].posicio.R = 160.08;		llumGL[0].posicio.alfa = 62.06;		llumGL[0].posicio.beta = 45.0;		// Posici� llum (x,y,z)=(0,0,75)
	llumGL[0].atenuacio.a = 0.0;		llumGL[0].atenuacio.b = 0.0;		llumGL[0].atenuacio.c = 1.0;		// Llum sense atenuaci� per dist�ncia (a,b,c)=(0,0,1)
	llumGL[0].restringida = false;
	llumGL[0].spotdirection[0] = 0.0;	llumGL[0].spotdirection[1] = 0.0;	llumGL[0].spotdirection[2] = 0.0;
	llumGL[0].cutoff = 0.0;				llumGL[0].exponent = 0.0;

	// LLum 1: Atenuaci� constant (c=1), sobre l'eix X, no restringida.
	llumGL[1].encesa = false;
	llumGL[1].difusa[1] = 1.0f;			llumGL[1].difusa[1] = 1.0f;			llumGL[1].difusa[2] = 1.0f;		llumGL[1].difusa[3] = 1.0f;
	llumGL[1].especular[1] = 1.0f;		llumGL[1].especular[1] = 1.0f;		llumGL[1].especular[2] = 1.0f;	llumGL[1].especular[3] = 1;

	llumGL[1].posicio.R = 75.0;			llumGL[1].posicio.alfa = 0.0;		llumGL[1].posicio.beta = 0.0;// (x,y,z)=(75,0,0)
	llumGL[1].atenuacio.a = 0.0;		llumGL[1].atenuacio.b = 0.0;		llumGL[1].atenuacio.c = 1.0;
	llumGL[1].restringida = false;
	llumGL[1].spotdirection[0] = 0.0;	llumGL[1].spotdirection[1] = 0.0;	llumGL[1].spotdirection[2] = 0.0;
	llumGL[1].cutoff = 0.0;				llumGL[1].exponent = 0.0;

	// LLum 2: Atenuaci� constant (c=1), sobre l'eix Y, no restringida.
	llumGL[2].encesa = false;
	llumGL[2].difusa[1] = 1.0f;			llumGL[2].difusa[1] = 1.0f;			llumGL[2].difusa[2] = 1.0f;		llumGL[2].difusa[3] = 1.0f;
	llumGL[2].especular[1] = 1.0f;		llumGL[2].especular[1] = 1.0f;		llumGL[2].especular[2] = 1.0f;	llumGL[2].especular[3] = 1;

	llumGL[2].posicio.R = 75.0;			llumGL[2].posicio.alfa = 0.0;		llumGL[2].posicio.beta = 90.0;	// (x,y,z)=(0,75,0)
	llumGL[2].atenuacio.a = 0.0;		llumGL[2].atenuacio.b = 0.0;		llumGL[2].atenuacio.c = 1.0;
	llumGL[2].restringida = false;
	llumGL[2].spotdirection[0] = 0.0;	llumGL[2].spotdirection[1] = 0.0;	llumGL[2].spotdirection[2] = 0.0;
	llumGL[2].cutoff = 0.0;				llumGL[2].exponent = 0.0;

	// LLum 3: Atenuaci� constant (c=1), sobre l'eix Y=X, no restringida.
	llumGL[3].encesa = false;
	llumGL[3].difusa[1] = 1.0f;			llumGL[2].difusa[1] = 1.0f;			llumGL[3].difusa[2] = 1.0f;		llumGL[3].difusa[3] = 1.0f;
	llumGL[3].especular[1] = 1.0f;		llumGL[2].especular[1] = 1.0f;		llumGL[3].especular[2] = 1.0f;	llumGL[3].especular[3] = 1;

	llumGL[3].posicio.R = 75.0;			llumGL[3].posicio.alfa = 45.0;		llumGL[3].posicio.beta = 45.0;// (x,y,z)=(75,75,75)
	llumGL[3].atenuacio.a = 0.0;		llumGL[3].atenuacio.b = 0.0;		llumGL[3].atenuacio.c = 1.0;
	llumGL[3].restringida = false;
	llumGL[3].spotdirection[0] = 0.0;	llumGL[3].spotdirection[1] = 0.0;	llumGL[3].spotdirection[2] = 0.0;
	llumGL[3].cutoff = 0.0;				llumGL[3].exponent = 0.0;

	// LLum 4: Atenuaci� constant (c=1), sobre l'eix -Z, no restringida.
	llumGL[4].encesa = false;
	llumGL[4].difusa[1] = 1.0f;			llumGL[4].difusa[1] = 1.0f;			llumGL[4].difusa[2] = 1.0f;		llumGL[4].difusa[3] = 1.0f;
	llumGL[4].especular[1] = 1.0f;		llumGL[4].especular[1] = 1.0f;		llumGL[4].especular[2] = 1.0f;	llumGL[4].especular[3] = 1;

	llumGL[4].posicio.R = 75.0;			llumGL[4].posicio.alfa = -90.0;		llumGL[4].posicio.beta = 0.0;// (x,y,z)=(0,0,-75)
	llumGL[4].atenuacio.a = 0.0;		llumGL[4].atenuacio.b = 0.0;		llumGL[4].atenuacio.c = 1.0;
	llumGL[4].restringida = false;
	llumGL[4].spotdirection[0] = 0.0;	llumGL[4].spotdirection[1] = 0.0;	llumGL[4].spotdirection[2] = 0.0;
	llumGL[4].cutoff = 0.0;				llumGL[4].exponent = 0.0;

	// LLum #5:
	llumGL[5].encesa = false;
	llumGL[5].difusa[1] = 1.0f;			llumGL[5].difusa[1] = 1.0f;			llumGL[5].difusa[2] = 1.0f;		llumGL[5].difusa[3] = 1.0f;
	llumGL[5].especular[1] = 1.0f;		llumGL[5].especular[1] = 1.0f;		llumGL[5].especular[2] = 1.0f;	llumGL[5].especular[3] = 1;

	llumGL[5].posicio.R = 0.0;			llumGL[5].posicio.alfa = 0.0;		llumGL[5].posicio.beta = 0.0; // Cap posici� definida
	llumGL[5].atenuacio.a = 0.0;		llumGL[5].atenuacio.b = 0.0;		llumGL[5].atenuacio.c = 1.0;
	llumGL[5].restringida = false;
	llumGL[5].spotdirection[0] = 0.0;	llumGL[5].spotdirection[1] = 0.0;	llumGL[5].spotdirection[2] = 0.0;
	llumGL[5].cutoff = 0.0;				llumGL[5].exponent = 0.0;

	// LLum #6: Llum Vaixell, configurada a la funci� vaixell() en escena.cpp.
	llumGL[6].encesa = false;
	llumGL[6].difusa[1] = 1.0f;			llumGL[6].difusa[1] = 1.0f;			llumGL[6].difusa[2] = 1.0f;		llumGL[6].difusa[3] = 1.0f;
	llumGL[6].especular[1] = 1.0f;		llumGL[6].especular[1] = 1.0f;		llumGL[6].especular[2] = 1.0f;	llumGL[6].especular[3] = 1;

	llumGL[6].posicio.R = 0.0;			llumGL[6].posicio.alfa = 0.0;		llumGL[6].posicio.beta = 0.0; // Cap posici� definida, definida en funci� vaixell() en escena.cpp
	llumGL[6].atenuacio.a = 0.0;		llumGL[6].atenuacio.b = 0.0;		llumGL[6].atenuacio.c = 1.0;
	llumGL[6].restringida = false;
	llumGL[6].spotdirection[0] = 0.0;	llumGL[6].spotdirection[1] = 0.0;	llumGL[6].spotdirection[2] = 0.0;
	llumGL[6].cutoff = 0.0;				llumGL[6].exponent = 0.0;

	// LLum #7: Llum Far, configurada a la funci� faro() en escena.cpp.
	llumGL[7].encesa = false;
	llumGL[7].difusa[1] = 1.0f;		llumGL[7].difusa[1] = 1.0f;			llumGL[7].difusa[2] = 1.0f;		llumGL[7].difusa[3] = 1.0f;
	llumGL[7].especular[1] = 1.0f;		llumGL[7].especular[1] = 1.0f;		llumGL[7].especular[2] = 1.0f;	llumGL[7].especular[3] = 1;

	llumGL[7].posicio.R = 0.0;			llumGL[7].posicio.alfa = 0.0;		llumGL[7].posicio.beta = 0.0; // Cap posici� definida, definida en funci� faro() en escena.cpp
	llumGL[7].atenuacio.a = 0.0;		llumGL[7].atenuacio.b = 0.0;		llumGL[7].atenuacio.c = 1.0;
	llumGL[7].restringida = false;
	llumGL[7].spotdirection[0] = 0.0;	llumGL[7].spotdirection[1] = 0.0;	llumGL[7].spotdirection[2] = 0.0;
	llumGL[7].cutoff = 0.0;				llumGL[7].exponent = 0.0;

	// Entorn VGI: Variables de control del men� Shaders
	sw_shader = GOURAUD;				shader_menu = GOURAUD;				shader_program = 0;

	// Entorn VGI: Variables de control dels botons de mouse
	m_PosEAvall = (0, 0);		m_PosDAvall = (0, 0);
	m_ButoEAvall = true;		m_ButoDAvall = false;
	m_EsfeEAvall.R = 0.0;		m_EsfeEAvall.alfa = 0.0;	m_EsfeEAvall.beta = 0.0;
	m_EsfeIncEAvall.R = 0.0;	m_EsfeIncEAvall.alfa = 0.0;	m_EsfeIncEAvall.beta = 0.0;

	// Entorn VGI: Variables que controlen par�metres visualitzaci�: Mides finestra Windows i PV
	w = 0;				h = 0;								// Mides finestra
	w_old = 0;			h_old = 0;							// Copia mides finestre per a FullScreen
	OPV.R = 15.0;		OPV.alfa = 0.0;		OPV.beta = 0.0;	// Origen PV en esf�riques
	Vis_Polar = POLARZ;

	// Entorn VGI: Color de fons i de l'objecte
	fonsR = true;		fonsG = true;		fonsB = true;
	c_fons.r = 0.0;		c_fons.g = 0.0;		c_fons.b = 0.0;
	sw_color = false;
	col_obj.r = 1.0;	col_obj.g = 1.0;	col_obj.b = 1.0;		col_obj.a = 1.0;

	// Entorn VGI: Objecte 3DS
	Ob3DS = NULL;

	// Entorn VGI: Objecte OBJ
	ObOBJ = NULL;

	// VGI: OBJECTE --> Corba B-Spline i Bezier
	npts_T = 0;
	for (i = 0; i < MAX_PATCH_CORBA; i = i++)
	{
		PC_t[i].x = 0.0;
		PC_t[i].y = 0.0;
		PC_t[i].z = 0.0;
	}

	pas_CS = PAS_BSPLINE;
	sw_Punts_Control = false;

	// Entorn VGI: Variables del Timer
	t = 0;			anima = false;

	// Entorn VGI: Variables de l'objecte FRACTAL
	t_fractal = CAP;	soroll = 'C';
	pas = 64;			pas_ini = 64;
	sw_il = true;		palcolFractal = false;

	// Entorn VGI: Altres variables
	mida = 1.0;			nom = "";		buffer = "";

	// Entorn VGI: Inicialitzaci� de les llibreries DevIL per a la c�rrega de textures i fitxers .3DS
	ilInit();					// Inicialitzar llibreria IL
	iluInit();					// Inicialitzar llibreria ILU
	ilutRenderer(ILUT_OPENGL);	// Inicialitzar llibreria ILUT per a OpenGL

// Entorn VGI: Definir desplegable per a Full Screen
	ContextMenu = new CMenu();
	if (!ContextMenu->LoadMenu(IDR_MENU_WINDOW))	AfxMessageBox(_T("Fail to create context menu"));

	//Inicialització murs
	llista_murs = initMurs();
	sales_v_d = CreaSales();
	Personatge nou(opvN.x, opvN.y, opvN.z-2.5f, 0);
	personatge = nou;
	
	num_murs = llista_murs.size();

	// Vides Jugador
	lifes = 3;

} 

CEntornVGIView::~CEntornVGIView()
{
}

BOOL CEntornVGIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: modificar aqu� la clase Window o los estilos cambiando
	//  CREATESTRUCT cs

	// An OpenGL window must be created with the following flags and must not
	// include CS_PARENTDC for the class style.
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// Impresi�n de CEntornVGIView

void CEntornVGIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEntornVGIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Preparaci�n predeterminada
	return DoPreparePrinting(pInfo);
}

void CEntornVGIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: agregar inicializaci�n adicional antes de imprimir
}

void CEntornVGIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: agregar limpieza despu�s de imprimir
}

void CEntornVGIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

/////////////////////////////////////////////////////////////////////////////
// Diagn�sticos de CEntornVGIView

#ifdef _DEBUG
void CEntornVGIView::AssertValid() const
{
	CView::AssertValid();
}

void CEntornVGIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEntornVGIDoc* CEntornVGIView::GetDocument() const // La versi�n de no depuraci�n est� alineada
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEntornVGIDoc)));
	return (CEntornVGIDoc*)m_pDocument;
}
#endif //_DEBUG


/////////////////////////////////////////////////////////////////////////////
// Controladores de mensaje de CEntornVGIView

int CEntornVGIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Agregue aqu� su c�digo de creaci�n especializado

		//CDC* pDC = GetDC();
		//m_glRenderer.CreateGLContext(pDC);
	m_pDC = new CClientDC(this);

	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	// Entorn VGI: Format del pixel que millor s'ajusti al descrit en pfd
		//int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);
	int nPixelFormat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);

	if (!nPixelFormat)
	{
		::MessageBoxW(NULL, L"Error en SetPixelFormat", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);		// This sends a message telling the program to quit
		return false;
	}

	// Activaci� format pixel per al contexte dispositiu
		//BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);
	BOOL bResult = SetPixelFormat(m_pDC->GetSafeHdc(), nPixelFormat, &pfd);

	if (!bResult)
	{
		::MessageBoxW(NULL, L"Error en SetPixelFormat", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);		// This sends a message telling the program to quit
		return false;
	}

	// Entorn VGI: Creaci� contexte generaci� OpenGL
		// m_hRC=wglCreateContext(m_hDC);
	m_hRC = wglCreateContext(m_pDC->GetSafeHdc());
	if (!m_hRC)
	{
		::MessageBoxW(NULL, L"Error en GL Rendering Context", L"Error", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);		// This sends a message telling the program to quit
		return false;
	}

	// OPENGL 2.0 - OPENGL 3.0 **********************************************************
		// --- OpenGL 3.x ---
	HGLRC tempContext = wglCreateContext(m_pDC->GetSafeHdc());
	wglMakeCurrent(m_pDC->GetSafeHdc(), tempContext);

	//Get access to modern OpenGL functionality from this old style context.
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit())
	{
		AfxMessageBox(_T("GLEW could not be initialized!"));
		return FALSE;
	}

	//InitAPI();

	//	if (glewIsExtensionSupported("GLEW_ARB_vertex_shader"))
	//	AfxMessageBox(_T("INFO: GLEW_ARB_vertex_shader supported, proceeding\n"));
	//	else AfxMessageBox(_T("INFO: GLEW_ARB_vertex_shader NOT supported, proceeding\n"));
	//
	//	if (glewIsExtensionSupported("GLEW_ARB_fragment_shader"))
	//	AfxMessageBox(_T("INFO: GLEW_ARB_fragment_shader supported, proceeding\n"));
	//	else AfxMessageBox(_T("INFO: GLEW_ARB_fragment_shader NOT supported, proceeding\n"));
	//
	if (glewIsSupported("GL_VERSION_2_0")) //(GLEW_VERSION_2_0)
	{
	} //AfxMessageBox(_T("INFO: OpenGL 2.0 supported!. Proceed\n"));
	else
	{
		AfxMessageBox(_T("INFO: OpenGL 2.0 not supported!. Exit\n"));
		//return EXIT_FAILURE;
	}


	int major, minor;
	GetGLVersion(&major, &minor);

	if (major < 3 || (major == 3 && minor < 2))
		AfxMessageBox(_T("OpenGL 3.2 is not supported!. Exit\n"));
	//	else 
	//		AfxMessageBox(_T("OpenGL 3.2 is supported!. Proceed"));

	int attribs[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, major,
		WGL_CONTEXT_MINOR_VERSION_ARB, minor,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,// | WGL_CONTEXT_DEBUG_BIT_ARB,
		WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB, //0x9126 , 0x00000001,
		0
	};

	PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if (wglCreateContextAttribsARB != NULL)
	{
		m_hrc = wglCreateContextAttribsARB(m_pDC->GetSafeHdc(), 0, attribs);
	}

	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hrc);

	// Entorn VGI: Inicialitzaci� de funcions de shaders per a OpenGL 2.0
	InitAPI();

	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(tempContext);

	if (!m_hrc)
	{
		AfxMessageBox(_T("OpenGL 3.x RC was not created!"));
		return false;
	}

	// Permet la coexistencia d'altres contextes de generaci�
	wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);

	//Vigilar aqui que he posat aixo
	//OnObjecteCubRGB();
	OnObjecteMur();

	return true;
}

void CEntornVGIView::InitAPI()
{
	/*	Vendor, Renderer, Version, Shading Laguage Version i Extensions suportades per la placa gr�fica gravades en fitxer extensions.txt
		CString nomf;
		nomf = "extensions.txt";
		char *nomfitxer = CString2Char(nomf);
		char* str = (char*)glGetString(GL_VENDOR);
		FILE* f = fopen(nomfitxer, "w");
		if(f)	{	fprintf(f,"VENDOR: %s\n",str);
					str = (char*)glGetString(GL_RENDERER);
					fprintf(f, "RENDERER: %s\n", str);
					str = (char*)glGetString(GL_VERSION);
					fprintf(f, "VERSION: %s\n", str);
					str = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
					fprintf(f, "SHADING_LANGUAGE_VERSION: %s\n", str);
					str = (char*)glGetString(GL_EXTENSIONS);
					fprintf(f, "EXTENSIONS: %s\n", str);
					fclose(f);
				}
		*/

		// Program
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	glUniform1iv = (PFNGLUNIFORM1IVPROC)wglGetProcAddress("glUniform1iv");
	glUniform2iv = (PFNGLUNIFORM2IVPROC)wglGetProcAddress("glUniform2iv");
	glUniform3iv = (PFNGLUNIFORM3IVPROC)wglGetProcAddress("glUniform3iv");
	glUniform4iv = (PFNGLUNIFORM4IVPROC)wglGetProcAddress("glUniform4iv");
	glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	glUniform1fv = (PFNGLUNIFORM1FVPROC)wglGetProcAddress("glUniform1fv");
	glUniform2fv = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform2fv");
	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)wglGetProcAddress("glVertexAttrib1f");
	glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)wglGetProcAddress("glVertexAttrib1fv");
	glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)wglGetProcAddress("glVertexAttrib2fv");
	glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)wglGetProcAddress("glVertexAttrib3fv");
	glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)wglGetProcAddress("glVertexAttrib4fv");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)wglGetProcAddress("glGetActiveUniform");

	// Shader
	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");

	// VBO
	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
}

void CEntornVGIView::GetGLVersion(int* major, int* minor)
{
	// for all versions
	char* ver = (char*)glGetString(GL_VERSION); // ver = "3.2.0"

	*major = ver[0] - '0';
	if (*major >= 3)
	{
		// for GL 3.x
		glGetIntegerv(GL_MAJOR_VERSION, major);		// major = 3
		glGetIntegerv(GL_MINOR_VERSION, minor);		// minor = 2
	}
	else
	{
		*minor = ver[2] - '0';
	}

	// GLSL
	ver = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);	// 1.50 NVIDIA via Cg compiler
}


void CEntornVGIView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Agregue aqu� su c�digo de controlador de mensajes
	CDC* pDC = GetDC();
	ReleaseDC(pDC);
}


void CEntornVGIView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Agregue aqu� su c�digo de controlador de mensajes

	// A resize event occured; cx and cy are the window's new width and height.
	// Find the OpenGL change size function given in the Lab 1 notes and call it here

	// Entorn VGI: MODIFICACI� ->Establim les mides de la finestra actual
	w = cx;
	h = cy;

}


void CEntornVGIView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	//m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}


/////////////////////////////////////////////////////////////////////////////
// Dibujo de CEntornVGIView

void CEntornVGIView::OnDraw(CDC* /*pDC*/)
{

	// TODO: agregar aqu� el c�digo de dibujo para datos nativos

	CEntornVGIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
}


void CEntornVGIView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
// TODO: Agregue aqu� su c�digo de controlador de mensajes
	GLfloat vpv[3] = { 0.0, 0.0, 1.0 };

	// Entorn VGI: Activaci� el contexte OpenGL
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	// Cridem a les funcions de l'escena i la projecci� segons s'hagi 
	// seleccionat una projecci� o un altra
	switch (projeccio)
	{
	case AXONOM:
		// PROJECCI� AXONOM�TRICA
		// Activaci� del retall de pantalla
		glEnable(GL_SCISSOR_TEST);

		// Retall
		glScissor(0, 0, w, h);
		glViewport(0, 0, w, h);

		// Aqu� farem les crides per a definir Viewport, Projecci� i C�mara: INICI -------------------------

		// Aqu� farem les cridesper a definir Viewport, Projecci� i C�mara:: FI -------------------------
				// Dibuixar Model (escena)
		glPushMatrix();
		configura_Escena();     // Aplicar Transformacions Geometriques segons persiana Transformacio i configurar objectes
		// glScalef();			// Escalat d'objectes, per adequar-los a les vistes ortogr�fiques
		dibuixa_Escena();		// Dibuix geometria de l'escena amb comandes GL.
		glPopMatrix();

		// Intercanvia l'escena al front de la pantalla
		SwapBuffers(m_pDC->GetSafeHdc());
		break;

	case ORTO:
		// PROJECCI� ORTOGR�FICA
		// Activaci� del retall de pantalla
		glEnable(GL_SCISSOR_TEST);

		// Retall
		glViewport(0, 0, w, h);
		glScissor(0, 0, w, h);

		// Fons condicionat al color de fons
		if ((c_fons.r < 0.5) || (c_fons.g < 0.5) || (c_fons.b < 0.5))
			FonsB();
		else
			FonsN();

		// Aqu� farem les quatre crides a ProjeccioOrto i Ortografica per obtenir 
		// les quatre vistes ortogr�fiques
		// ---------- Entorn VGI: DESCOMENTAR QUAN S'IMPLEMENTI PROJECCIO ORTOGR�FICA
		// PLANTA (Inferior Esquerra)
				// Definici� de Viewport, Projecci� i C�mara
		Projeccio_Orto(w / 2, h / 2, w / 2, h / 2);
		Vista_Ortografica(0, OPV.R, c_fons, col_obj, objecte, mida, pas, front_faces, oculta,
			test_vis, back_line, ilumina, llum_ambient, llumGL, ifixe, ilum2sides,
			eixos, grid, hgrid, false);
		// Dibuix de l'Objecte o l'Escena
		glPushMatrix();
		configura_Escena();     // Aplicar Transformacions Geometriques segons persiana Transformacio i configurar objectes
		// glScalef();			// Escalat d'objectes, per adequar-los a les vistes ortogr�fiques (Pr�ctica 2)
		dibuixa_Escena();		// Dibuix geometria de l'escena amb comandes GL.
		glPopMatrix();

		// ISOM�TRICA (Inferior Dreta)
				// Definici� de Viewport, Projecci� i C�mara
		Projeccio_Orto(0, w / 2, w / 2, h / 2);
		Vista_Ortografica(3, OPV.R, c_fons, col_obj, objecte, mida, pas, front_faces, oculta,
			test_vis, back_line, ilumina, llum_ambient, llumGL, ifixe, ilum2sides,
			eixos, grid, hgrid, false);
		// Dibuix de l'Objecte o l'Escena
		glPushMatrix();
		configura_Escena();     // Aplicar Transformacions Geometriques segons persiana Transformacio i configurar objectes
		// glScalef();			// Escalat d'objectes, per adequar-los a les vistes ortogr�fiques (Pr�ctica 2)
		dibuixa_Escena();		// Dibuix geometria de l'escena amb comandes GL.
		glPopMatrix();

		// AL�AT (Superior Esquerra)
				// Definici� de Viewport, Projecci� i C�mara
		Projeccio_Orto(w / 4, h / 4, w / 2, h / 2);
		Vista_Ortografica(1, OPV.R, c_fons, col_obj, objecte, mida, pas, front_faces, oculta,
			test_vis, back_line, ilumina, llum_ambient, llumGL, ifixe, ilum2sides,
			eixos, grid, hgrid, false);
		// Dibuix de l'Objecte o l'Escena
		glPushMatrix();
		configura_Escena();     // Aplicar Transformacions Geom?triques segons persiana Transformacio i configurar objectes
		//glScalef();			// Escalat d'objectes, per adequar-los a les vistes ortogr�fiques (Pr�ctica 2)
		dibuixa_Escena();		// Dibuix geometria de l'escena amb comandes GL.
		glPopMatrix();

		// PERFIL (Superior Dreta)
				// Definici� de Viewport, Projecci� i C�mara
		Projeccio_Orto(0, h / 2, w / 2, h / 2);
		Vista_Ortografica(2, OPV.R, c_fons, col_obj, objecte, mida, pas, front_faces, oculta,
			test_vis, back_line, ilumina, llum_ambient, llumGL, ifixe, ilum2sides,
			eixos, grid, hgrid, false);
		// Dibuix de l'Objecte o l'Escena
		glPushMatrix();
		configura_Escena();     // Aplicar Transformacions Geom?triques segons persiana Transformacio i configurar objectes
		// glScalef();			// Escalat d'objectes, per adequar-los a les vistes ortogr�fiques (Pr�ctica 2)
		dibuixa_Escena();		// Dibuix geometria de l'escena amb comandes GL.
		glPopMatrix();

		// Intercanvia l'escena al front de la pantalla
		SwapBuffers(m_pDC->GetSafeHdc());
		break;

	case PERSPECT:
		// PROJECCI� PERSPECTIVA
		SetTimer(WM_TIMER, 10, NULL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Set Perspective Calculations To Most Accurate
		glDisable(GL_SCISSOR_TEST);		// Desactivaci� del retall de pantalla

		// Definici� de Viewport, Projecci� i C�mara
		Projeccio_Perspectiva(0, 0, w, h, OPV.R);
		if (navega) {
			Vista_Navega(opvN, false, n, v, pan, tr_cpv, tr_cpvF, c_fons, col_obj, objecte, true, pas,
				front_faces, oculta, test_vis, back_line,
				ilumina, llum_ambient, llumGL, ifixe, ilum2sides,
				eixos, grid, hgrid, llumVermella);
		}
		else {
			n[0] = 0;		n[1] = 0;		n[2] = 0;
			Vista_Esferica(OPV, Vis_Polar, pan, tr_cpv, tr_cpvF, c_fons, col_obj, objecte, mida, pas,
				front_faces, oculta, test_vis, back_line, ilumina, llum_ambient, llumGL, ifixe, ilum2sides, eixos, grid, hgrid, false);
		}

		// Dibuix de l'Objecte o l'Escena
		glPushMatrix();
		configura_Escena();     // Aplicar Transformacions Geometriques segons persiana Transformacio i configurar objectes.
		dibuixa_Escena();		// Dibuix geometria de l'escena amb comandes GL.
		glPopMatrix();

		// Intercanvia l'escena al front de la pantalla
		SwapBuffers(m_pDC->GetSafeHdc());
		break;

	default:
		// Entorn VGI: Creaci� de la llista que dibuixar� els eixos Coordenades M�n. Funci� on est� codi per dibuixar eixos	
		glNewList(EIXOS, GL_COMPILE);
		// Dibuix dels eixos sense il.luminaci�
		glDisable(GL_LIGHTING);
		// Dibuixar eixos sense textures
		glDisable(GL_TEXTURE_2D);
		// Desactivar boira
		glDisable(GL_FOG);
		deixos();						// Funci� que dibuixa els Eixos Coordenades M�n
		if (ilumina != FILFERROS) glEnable(GL_LIGHTING);
		if (textura) glEnable(GL_TEXTURE_2D);
		glEndList();

		// Crida a la funci� Fons Blanc
		FonsB();

		// Intercanvia l'escena al front de la pantalla
		SwapBuffers(m_pDC->GetSafeHdc());
		break;
	}

	// Entorn VGI: Activaci� el contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
	wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);

	//  Actualitzar la barra d'estat de l'aplicaci� amb els valors R,A,B,PVx,PVy,PVz
	Barra_Estat();
}


// configura_Escena: Funcio que configura els parametres de Model i dibuixa les
//                   primitives OpenGL dins classe Model
void CEntornVGIView::configura_Escena() {

	// Aplicar Transformacions Geometriques segons persiana Transformacio i Quaternions
	instancia(transf, TG, TGF);
}

// dibuixa_Escena: Funcio que crida al dibuix dels diferents elements de l'escana
void CEntornVGIView::dibuixa_Escena() {

	//	Dibuix geometria de l'escena amb comandes GL.

	bool animacioMurQueCauInici = false;
	dibuixa_EscenaGL(objecte, col_obj, true, sw_material, textura, texturesID, textura_map,
		npts_T, PC_t, pas_CS, sw_Punts_Control, prova_moviment, llista_murs, personatge, cel, loader, movimentShrek, movDir, rotacioShrek, eventfinal, eventsMursBaixada, punxesAnimadetes, sales_v_d, lifes, MidaLaberint_Fila,MidaLaberint_Columna);

	void dibuixa_EscenaGL(char objecte, CColor col_object, bool ref_mat, bool sw_mat[4],
		bool textur, GLint texturID[NUM_MAX_TEXTURES], bool textur_map,
		int nptsU, CPunt3D PC_u[MAX_PATCH_CORBA], GLfloat pasCS, bool sw_PC);

}

// Barra_Estat: Actualitza la barra d'estat (Status Bar) de l'aplicaci� amb els
//      valors R,A,B,PVx,PVy,PVz en Visualitzaci� Interactiva.
void CEntornVGIView::Barra_Estat()
{
	CString sss;
	CEsfe3D OPVAux;
	float PVx, PVy, PVz;
	//GLfloat color;

// Status Bar fitxer fractal
	if (nom != "") GetStatusBar().SetPaneText(0, nom);

	// C�lcul dels valors per l'opci� Vista->Navega
	if (projeccio != CAP && projeccio != ORTO) {
		if (navega)
		{
			OPVAux.R = sqrt(opvN.x * opvN.x + opvN.y * opvN.y + opvN.z * opvN.z);
			OPVAux.alfa = (asin(opvN.z / OPVAux.R) * 180) / pi;
			OPVAux.beta = (atan(opvN.y / opvN.x)) * 180 / pi;
		}
		else {
			OPVAux.R = OPV.R; OPVAux.alfa = OPV.alfa; OPVAux.beta = OPV.beta; //Raux=R; angv=anglev; angh=angleh; 
		}
	}
	else {
		OPVAux.R = OPV.R; OPVAux.alfa = OPV.alfa; OPVAux.beta = OPV.beta; //Raux=R; angv=anglev; angh=angleh; 
	}

	// Status Bar R Origen Punt de Vista
	if (projeccio == CAP) buffer = "       ";
	else if (projeccio == ORTO) buffer = " ORTO   ";
	else if (navega) buffer = " NAV   ";
	else buffer.Format(_T("%.1f"), OPVAux.R);
	sss = _T("R=") + buffer;
	// Refrescar posici� R Status Bar
	GetStatusBar().SetPaneText(1, sss);

	// Status Bar angle alfa Origen Punt de Vista
	if (projeccio == CAP) buffer = "       ";
	else if (projeccio == ORTO) buffer = "ORTO   ";
	else if (navega) buffer = " NAV   ";
	else buffer.Format(_T("%.1f"), OPVAux.alfa);
	sss = _T("a=") + buffer;
	// Refrescar posici� angleh Status Bar
	GetStatusBar().SetPaneText(2, sss);

	// Status Bar angle beta Origen Punt de Vista
	if (projeccio == CAP) buffer = "       ";
	else if (projeccio == ORTO) buffer = "ORTO   ";
	else if (navega) buffer = " NAV   ";
	else buffer.Format(_T("%.1f"), OPVAux.beta);
	sss = _T("�=") + buffer;
	// Refrescar posici� anglev Status Bar
	GetStatusBar().SetPaneText(3, sss);

	// Transformaci� PV de Coord. esf�riques (R,anglev,angleh) --> Coord. cartesianes (PVx,PVy,PVz)
	if (navega) { PVx = opvN.x; PVy = opvN.y; PVz = opvN.z; }
	else {
		if (Vis_Polar == POLARZ) {
			PVx = OPVAux.R * cos(OPVAux.beta * pi / 180) * cos(OPVAux.alfa * pi / 180);
			PVy = OPVAux.R * sin(OPVAux.beta * pi / 180) * cos(OPVAux.alfa * pi / 180);
			PVz = OPVAux.R * sin(OPVAux.alfa * pi / 180);
		}
		else if (Vis_Polar == POLARY) {
			PVx = OPVAux.R * sin(OPVAux.beta * pi / 180) * cos(OPVAux.alfa * pi / 180);
			PVy = OPVAux.R * sin(OPVAux.alfa * pi / 180);
			PVz = OPVAux.R * cos(OPVAux.beta * pi / 180) * cos(OPVAux.alfa * pi / 180);
		}
		else {
			PVx = OPVAux.R * sin(OPVAux.alfa * pi / 180);
			PVy = OPVAux.R * cos(OPVAux.beta * pi / 180) * cos(OPVAux.alfa * pi / 180);
			PVz = OPVAux.R * sin(OPVAux.beta * pi / 180) * cos(OPVAux.alfa * pi / 180);
		}
	}

	// Status Bar PVx
	if (projeccio == CAP) buffer = "       ";
	else if (pan) float2CString(tr_cpv.x);
	else float2CString(PVx);
	sss = _T("PVx=") + buffer;
	// Refrescar posici� PVx Status Bar
	GetStatusBar().SetPaneText(4, sss);

	// Status Bar PVy
	if (projeccio == CAP) buffer = "       ";
	else if (pan) float2CString(tr_cpv.y);
	else float2CString(PVy);
	sss = _T("PVy=") + buffer;
	// Refrescar posici� PVy Status Bar
	GetStatusBar().SetPaneText(5, sss);

	// Status Bar PVz
	if (projeccio == CAP) buffer = "       ";
	else if (pan) float2CString(tr_cpv.z);
	else float2CString(PVz);
	sss = _T("PVz=") + buffer;
	// Refrescar posici� PVz Status Bar
	GetStatusBar().SetPaneText(6, sss);

	// Status Bar per indicar el modus de canvi de color (FONS o OBJECTE)
	sss = " ";
	if (sw_grid) sss = "GRID";
	else if (pan) sss = " PAN";
	else if (navega) sss = " NAV";
	else if (sw_color) sss = " OBJ";
	else sss = "FONS";

	// Refrescar posici� Transformacions en Status Bar
	GetStatusBar().SetPaneText(7, sss);

	// Status Bar per indicar tipus de Transformaci� (TRAS, ROT, ESC)
	sss = " ";
	if (transf) {
		if (rota) sss = "ROT";
		else if (trasl) sss = "TRA";
		else if (escal) sss = "ESC";
	}
	else if ((!sw_grid) && (!pan) && (!navega))
	{	// Components d'intensitat de fons que varien per teclat
		if ((fonsR) && (fonsG) && (fonsB)) sss = " RGB";
		else if ((fonsR) && (fonsG)) sss = " RG ";
		else if ((fonsR) && (fonsB)) sss = " R   B";
		else if ((fonsG) && (fonsB)) sss = "   GB";
		else if (fonsR) sss = " R  ";
		else if (fonsG) sss = "   G ";
		else if (fonsB) sss = "      B";
	}
	// Refrescar posici� Transformacions en Status Bar
	GetStatusBar().SetPaneText(8, sss);

	// Status Bar dels par�metres de Transformaci�, Color i posicions de Robot i Cama
	sss = " ";
	if (transf)
	{
		if (rota)
		{
			buffer.Format(_T("%.1f"), TG.VRota.x);
			sss = _T("  ") + buffer + _T("   ");

			buffer.Format(_T("%.1f"), TG.VRota.y);
			sss = sss + buffer + _T("   ");

			buffer.Format(_T("%.1f"), TG.VRota.z);
			sss = sss + buffer;
		}
		else if (trasl)
		{
			buffer.Format(_T("%.1f"), TG.VTras.x);
			sss = _T("  ") + buffer + _T("   ");

			buffer.Format(_T("%.1f"), TG.VTras.y);
			sss = sss + buffer + _T("   ");

			buffer.Format(_T("%.1f"), TG.VTras.z);
			sss = sss + buffer;
		}
		else if (escal)
		{
			buffer.Format(_T("%.2f"), TG.VScal.x);
			sss = _T(" ") + buffer + _T("  ");

			buffer.Format(_T("%.2f"), TG.VScal.y);
			sss = sss + buffer + _T("  ");

			buffer.Format(_T("%.2f"), TG.VScal.x);
			sss = sss + buffer;
		}
	}
	else if ((!sw_grid) && (!pan) && (!navega))
	{	// Color fons
		if (!sw_color)
		{
			buffer.Format(_T("%.3f"), c_fons.r);
			sss = _T(" ") + buffer + _T("  ");

			buffer.Format(_T("%.3f"), c_fons.g);
			sss = sss + buffer + _T("  ");

			buffer.Format(_T("%.3f"), c_fons.b);
			sss = sss + buffer;
		}
		else
		{	// Color objecte
			buffer.Format(_T("%.3f"), col_obj.r);
			sss = _T(" ") + buffer + _T("  ");

			buffer.Format(_T("%.3f"), col_obj.g);
			sss = sss + buffer + _T("  ");

			buffer.Format(_T("%.3f"), col_obj.b);
			sss = sss + buffer;
		}
	}

	// Refrescar posici� PVz Status Bar
	GetStatusBar().SetPaneText(9, sss);

	// Status Bar per indicar el pas del Fractal
	if (objecte == O_FRACTAL)
	{
		buffer.Format(_T("%.1d"), pas);
		sss = _T("Pas=") + buffer;
	}
	else { sss = "          "; }

	// Refrescar posici� Transformacions en Status Bar
	GetStatusBar().SetPaneText(10, sss);
}

void CEntornVGIView::float2CString(float varf)
{
	float vfloat;
	vfloat = varf;
	if (abs(varf) < 1.0) buffer.Format(_T("%.5f"), varf);
	else if (abs(varf) < 99.0) buffer.Format(_T("%.4f"), varf);
	else if (abs(varf) < 999.0) buffer.Format(_T("%.3f"), varf);
	else if (abs(varf) < 9999.0) buffer.Format(_T("%.2f"), varf);
	else if (abs(varf) < 99999.0) buffer.Format(_T("%.1f"), varf);
	else buffer.Format(_T("%.0f"), varf);

}


/* ------------------------------------------------------------------------- */
/*                                  SHADERS                                  */
/* ------------------------------------------------------------------------- */

/*****************************************************************************
* initializeShaders()
*      Loads custom shader by specifying filename (expects frag/vert pair)
*****************************************************************************/
GLuint CEntornVGIView::initializeShaders(CString filename)
{
	GLuint v, f, p;
	char* vs = NULL, * fs = NULL;
	CString file_Vert, file_Frag;
	int info_log_length = 0, compile_result = 0;
	FILE* fd;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	// Llegir Vertex Shader <filename>.vert
	file_Vert = filename + _T(".vert");
	char* fitxer_Vert = CString2Char(file_Vert);
	vs = textFileRead(fitxer_Vert);

	// Llegir Fragment Shader <filename>.vert
	file_Frag = filename + _T(".frag");
	char* fitxer_Frag = CString2Char(file_Frag);
	fs = textFileRead(fitxer_Frag);

	// Si s'han trobats els fitxers, procedir.
	if ((vs != NULL) && (fs != NULL))
	{
		const char* vv = vs;
		const char* ff = fs;

		glShaderSource(v, 1, &vv, NULL);
		glShaderSource(f, 1, &ff, NULL);

		free(vs);
		free(fs);
		glCompileShader(v);
		glGetShaderiv(v, GL_COMPILE_STATUS, &compile_result);
		// Llista error de compilaci� del Vertex Shader
		if (compile_result == GL_FALSE) {
			GLint maxLength = 0;

			glGetShaderiv(v, GL_INFO_LOG_LENGTH, &maxLength);
			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(v, maxLength, &maxLength, &errorLog[0]);

			AfxMessageBox(_T("Error compilaci� Vertex Shader"));

			// Volcar missatges error a fitxer Compile_Error.VERT
			if ((fd = fopen("GLSL_Error.VERT", "w")) == NULL)
			{
				AfxMessageBox(_T("GLSL_Error.VERT was not opened"));
				return false;
			}
			for (int i = 0; i <= maxLength; i = i++) fprintf(fd, "%c", errorLog[i]);
			fclose(fd);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(v); // Don't leak the shader.
			return 0;
		}

		// Compilaci� Fragment Shader
		glCompileShader(f);
		glGetShaderiv(v, GL_COMPILE_STATUS, &compile_result);

		// Llista error de compilaci� del Vertex Shader
		if (compile_result == GL_FALSE) {
			GLint maxLength = 0;

			glGetShaderiv(v, GL_INFO_LOG_LENGTH, &maxLength);
			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(v, maxLength, &maxLength, &errorLog[0]);

			AfxMessageBox(_T("Error compilaci� Fragment Shader"));

			// Volcar missatges error a fitxer Compile_Error.FRAG
			if ((fd = fopen("GLSL_Error.FRAG", "w")) == NULL)
			{
				AfxMessageBox(_T("GLSL_Error.FRAG was not opened"));
				return false;
			}
			for (int i = 0; i <= maxLength; i = i++) fprintf(fd, "%c", errorLog[i]);
			fclose(fd);

			// Provide the infolog in whatever manor you deem best.
			// Exit with failure.
			glDeleteShader(v); // Don't leak the shader.
			return 0;
		}

		// Creaci� del Program que inclou Vertex i Fragment Shader
		p = glCreateProgram();
		glAttachShader(p, v);	// Relaciona Vertex Shader al Program
		glAttachShader(p, f);	// relaciona Fragment Shader al Program

// Linkedici� del Program
		glLinkProgram(p);

		// Activaci� del Programa
		glUseProgram(p);

		// Retorna refer�ncia al Program creat
		return p;
	}
	else return 0;	// retornar 0 si no s'ha trobat el fitxer.
}


/*****************************************************************************
* loadFileShaders()
*      Loads custom shader by specifying filename (expects frag/vert pair)
*****************************************************************************/
GLuint CEntornVGIView::loadFileShaders(CString file_Vert, CString file_Frag)
{

	GLuint v, f, p;
	char* vs = NULL, * fs = NULL;
	//	CString file_Vert, file_Frag;
	int info_log_length = 0, compile_result = 0;
	FILE* fd;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);

	//	file_Vert = filename + _T(".vert");
	char* fitxer_Vert = CString2Char(file_Vert);

	vs = textFileRead(fitxer_Vert);
	//vs = textFileRead(filename + ".vert");

//	file_Frag = filename + _T(".frag");
	char* fitxer_Frag = CString2Char(file_Frag);

	fs = textFileRead(fitxer_Frag);
	//fs = textFileRead(filename + ".frag");

	const char* vv = vs;
	const char* ff = fs;

	glShaderSource(v, 1, &vv, NULL);
	glShaderSource(f, 1, &ff, NULL);

	free(vs);
	free(fs);
	glCompileShader(v);
	glGetShaderiv(v, GL_COMPILE_STATUS, &compile_result);
	// Llista error de compilaci�
	if (compile_result == GL_FALSE) {
		GLint maxLength = 0;

		glGetShaderiv(v, GL_INFO_LOG_LENGTH, &maxLength);
		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(v, maxLength, &maxLength, &errorLog[0]);

		AfxMessageBox(_T("Error compilaci� Vertex Shader"));

		// Volcar missatges error a fitxer Compile_Error.VERT
		if ((fd = fopen("GLSL_Error.VERT", "w")) == NULL)
		{
			AfxMessageBox(_T("GLSL_Error.VERT was not opened"));
			return false;
		}
		for (int i = 0; i <= maxLength; i = i++) fprintf(fd, "%c", errorLog[i]);
		fclose(fd);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(v); // Don't leak the shader.
		return 0;
	}

	glCompileShader(f);
	glGetShaderiv(f, GL_COMPILE_STATUS, &compile_result);
	// Llista error de compilaci�
	if (compile_result == GL_FALSE) {
		GLint maxLength = 0;

		glGetShaderiv(f, GL_INFO_LOG_LENGTH, &maxLength);
		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(f, maxLength, &maxLength, &errorLog[0]);

		AfxMessageBox(_T("Error compilaci� Fragment Shader"));

		// Volcar missatges error a fitxer Compile_Error.FRAG
		if ((fd = fopen("GLSL_Error.FRAG", "w")) == NULL)
		{
			AfxMessageBox(_T("GLSL_Error.FRAG was not opened"));
			return false;
		}
		for (int i = 0; i <= maxLength; i = i++) fprintf(fd, "%c", errorLog[i]);
		fclose(fd);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(f); // Don't leak the shader.
		return 0;
	}

	p = glCreateProgram();
	glAttachShader(p, v);
	glAttachShader(p, f);

	glLinkProgram(p);
	glUseProgram(p);

	return p;
}


char* CEntornVGIView::textFileRead(char* fn) {
	FILE* fp;
	char* content = NULL;
	int count = 0;
	if (fn != NULL) {
		fp = fopen(fn, "rt");
		if (fp != NULL) {
			fseek(fp, 0, SEEK_END);
			count = ftell(fp);
			rewind(fp);
			if (count > 0) {
				content = (char*)malloc(sizeof(char) * (count + 1));
				count = fread(content, sizeof(char), count, fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
		else {
			AfxMessageBox(_T("Vertex or Fragment Program not found"));
			return NULL;
		}
	}
	return content;
}

/*****************************************************************************
* releaseAllShaders()
*      Unload shaders, return to OpenGL fixed function.
*****************************************************************************/
void CEntornVGIView::releaseAllShaders()
{
	// Entorn VGI: Activaci� del contexte OpenGL
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	glUseProgram(0);

	// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
	wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
}


/* ------------------------------------------------------------------------- */
/*                           CONTROL DEL TECLAT                              */
/* ------------------------------------------------------------------------- */

// OnKeyDown: Funci� de tractament de teclat (funci� que es crida quan es prem una tecla)
//   PAR�METRES:
//    - nChar: Codi del caracter seleccionat
//    - nRepCnt: Nombre de vegades que s'ha apretat la tecla (acceleraci�)
//    - nFlags: Flags d'interrupci� activats.
void CEntornVGIView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Agregue aqu� su c�digo de controlador de mensajes o llame al valor predeterminado
	const float incr = 0.025f;
	float modul = 0;
	GLfloat vdir[3] = { 0, 0, 0 };

	if ((sw_grid) && ((grid.x) || (grid.y) || (grid.z))) Teclat_Grid(nChar, nRepCnt);
	else if (((nChar == 'G') || (nChar == 'g')) && ((grid.x) || (grid.y) || (grid.z))) sw_grid = !sw_grid;
	else if ((!pan) && (!transf) && (!navega))
	{	/*if (!sw_color) Teclat_ColorFons(nChar, nRepCnt);
			else Teclat_ColorObjecte(nChar, nRepCnt);*/ //
		Teclat_Prova_Moviment(nChar, nRepCnt);
	}
	else {
		if (transf)
		{
			if (rota) Teclat_TransRota(nChar, nRepCnt);
			else if (trasl) Teclat_TransTraslada(nChar, nRepCnt);
			else if (escal) Teclat_TransEscala(nChar, nRepCnt);
		}
		if (pan) Teclat_Pan(nChar, nRepCnt);
		else if (navega) Teclat_Navega(nChar, nRepCnt);
		else if (!sw_color) Teclat_ColorFons(nChar, nRepCnt);
		else Teclat_ColorObjecte(nChar, nRepCnt);
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
/*
CODI PER MOURE NINOT
*/
void CEntornVGIView::Teclat_Prova_Moviment(UINT nChar, UINT nRepCnt) {
	switch (nChar)
	{
		// Tecla cursor amunt
	case VK_UP:
		//prova_moviment[1]++;
		personatge.m_y++;
		break;
		// Tecla cursor avall
	case VK_DOWN:
		//prova_moviment[1]--;
		personatge.m_y--;
		break;
		// Tecla cursor esquerra
	case VK_LEFT:
		//prova_moviment[0]--;
		personatge.m_x--;
		break;
		// Tecla cursor dret
	case VK_RIGHT:
		//prova_moviment[0]++;
		personatge.m_x++;
		break;
	}
}


void CEntornVGIView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Agregue aqu� su c�digo de controlador de mensajes o llame al valor predeterminado

	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


// Teclat_ColorObjecte: Teclat pels canvis de color de l'objecte per teclat.
void CEntornVGIView::Teclat_ColorObjecte(UINT nChar, UINT nRepCnt)
{
	const float incr = 0.025f;

	// FRACTAL: Canvi resoluci� del fractal pe tecles '+' i'-'
	if (objecte == O_FRACTAL)
	{
		if (nChar == 109) // Car�cter '-' 
		{
			pas = pas * 2;
			if (pas > 64) pas = 64;
			sw_il = true;
		}
		else if (nChar == 107) // Car�cter '+' 
		{
			pas = pas / 2;
			if (pas < 1) pas = 1;
			sw_il = true;
		}
	}
	//	else 
	if (nChar == VK_DOWN)
	{
		if (fonsR) {
			col_obj.r -= nRepCnt * incr;
			if (col_obj.r < 0.0) col_obj.r = 0.0;
		}
		if (fonsG) {
			col_obj.g -= nRepCnt * incr;
			if (col_obj.g < 0.0) col_obj.g = 0.0;
		}
		if (fonsB) {
			col_obj.b -= nRepCnt * incr;
			if (col_obj.b < 0.0) col_obj.b = 0.0;
		}
	}
	else if (nChar == VK_UP)
	{
		if (fonsR) {
			col_obj.r += nRepCnt * incr;
			if (col_obj.r > 1.0) col_obj.r = 1.0;
		}
		if (fonsG) {
			col_obj.g += nRepCnt * incr;
			if (col_obj.g > 1.0) col_obj.g = 1.0;
		}
		if (fonsB) {
			col_obj.b += nRepCnt * incr;
			if (col_obj.b > 1.0) col_obj.b = 1.0;
		}
	}
	else if (nChar == VK_SPACE)
	{
		if ((fonsR) && (fonsG) && (fonsB)) {
			fonsG = false;
			fonsB = false;
		}
		else if ((fonsR) && (fonsG)) {
			fonsG = false;
			fonsB = true;
		}
		else if ((fonsR) && (fonsB)) {
			fonsR = false;
			fonsG = true;
		}
		else if ((fonsG) && (fonsB)) fonsR = true;
		else if (fonsR) {
			fonsR = false;
			fonsG = true;
		}
		else if (fonsG) {
			fonsG = false;
			fonsB = true;
		}
		else if (fonsB) {
			fonsR = true;
			fonsG = true;
			fonsB = false;
		}
	}
	else if ((nChar == 'o') || (nChar == 'O')) sw_color = true;
	else if ((nChar == 'f') || (nChar == 'F')) sw_color = false;

}


// Teclat_ColorFons: Teclat pels canvis del color de fons.
void CEntornVGIView::Teclat_ColorFons(UINT nChar, UINT nRepCnt)
{
	const float incr = 0.025f;

	// FRACTAL: Canvi resoluci� del fractal pe tecles '+' i'-'
	if (objecte == O_FRACTAL)
	{
		if (nChar == 109) // Car�cter '-' 
		{
			pas = pas * 2;
			if (pas > 64) pas = 64;
			sw_il = true;
		}
		else if (nChar == 107) // Car�cter '+' 
		{
			pas = pas / 2;
			if (pas < 1) pas = 1;
			sw_il = true;
		}
	}
	//	else 
	if (nChar == VK_DOWN) {
		if (fonsR) {
			c_fons.r -= nRepCnt * incr;
			if (c_fons.r < 0.0) c_fons.r = 0.0;
		}
		if (fonsG) {
			c_fons.g -= nRepCnt * incr;
			if (c_fons.g < 0.0) c_fons.g = 0.0;
		}
		if (fonsB) {
			c_fons.b -= nRepCnt * incr;
			if (c_fons.b < 0.0) c_fons.b = 0.0;
		}
	}
	else if (nChar == VK_UP) {
		if (fonsR) {
			c_fons.r += nRepCnt * incr;
			if (c_fons.r > 1.0) c_fons.r = 1.0;
		}
		if (fonsG) {
			c_fons.g += nRepCnt * incr;
			if (c_fons.g > 1.0) c_fons.g = 1.0;
		}
		if (fonsB) {
			c_fons.b += nRepCnt * incr;
			if (c_fons.b > 1.0) c_fons.b = 1.0;
		}
	}
	else if (nChar == VK_SPACE) {
		if ((fonsR) && (fonsG) && (fonsB)) {
			fonsG = false;
			fonsB = false;
		}
		else if ((fonsR) && (fonsG)) {
			fonsG = false;
			fonsB = true;
		}
		else if ((fonsR) && (fonsB)) {
			fonsR = false;
			fonsG = true;
		}
		else if ((fonsG) && (fonsB)) fonsR = true;
		else if (fonsR) {
			fonsR = false;
			fonsG = true;
		}
		else if (fonsG) {
			fonsG = false;
			fonsB = true;
		}
		else if (fonsB) {
			fonsR = true;
			fonsG = true;
			fonsB = false;
		}
	}
	else if ((nChar == 'o') || (nChar == 'O')) sw_color = true;
	else if ((nChar == 'f') || (nChar == 'F')) sw_color = false;
}

// Teclat_Navega: Teclat pels moviments de navegaci�.
void CEntornVGIView::Teclat_Navega(UINT nChar, UINT nRepCnt)
{
	
	GLfloat vdir[3] = { 0, 0, 0 };
	GLfloat upv[3] = { opvN.x, opvN.y, opvN.z };
	GLfloat vdirpan[3] = { 0, 0, 0 };
	float modul = 0;

	// Entorn VGI: Controls de moviment de navegaci�
	vdir[0] = n[0] - opvN.x;
	vdir[1] = n[1] - opvN.y;
	vdir[2] = n[2] - opvN.z;

	normal(n, upv, vdirpan);


	modul = sqrt(vdir[0] * vdir[0] + vdir[1] * vdir[1] + vdir[2] * vdir[2]);
	vdir[0] = vdir[0] / modul;
	vdir[1] = vdir[1] / modul;
	vdir[2] = vdir[2] / modul;

	if (eventfinal.m_colisio) {
		/*  Torna el pg al punt d'inici
		personatge.m_x = -3.0;
		personatge.m_y = 12.0;
		opvN.x = -3.0;	opvN.y = 12.0;		opvN.z = 5.0;
		n[0] = 0.0;		n[1] = 0.0;			n[2] = 5.0;
		*/

		// Porta el pg a la sala de victòria
		personatge.m_x = 70.0;
		personatge.m_y = 62.5;

		opvN.x = 70;				opvN.y = 62.5;			opvN.z = -52.5;
		n[0] = opvN.x + 5.0;		n[1] = opvN.y;			n[2] = opvN.z;

	}


	switch (nChar)
	{
		// Tecla cursor amunt
	case 87:
		
		personatge.m_x += nRepCnt * fact_pan * vdir[0] / 2;
		personatge.m_y += nRepCnt * fact_pan * vdir[1] / 2;
		DoCollisions(llista_murs, personatge, eventfinal, eventsMursBaixada, punxesAnimadetes);
		
		if (personatge.m_colisioX) {
			if (!personatge.m_colisioY) {
				opvN.y = personatge.m_y;
				n[1] += nRepCnt * fact_pan * vdir[1] / 2;
				cel[1] = personatge.m_y;
			}
		}
		else {
			if (!personatge.m_colisioY) {
				opvN.y = personatge.m_y;
				n[1] += nRepCnt * fact_pan * vdir[1] / 2;
				cel[1] = personatge.m_y;
			}
			opvN.x = personatge.m_x;
			n[0] += nRepCnt * fact_pan * vdir[0] / 2;
			cel[0] = personatge.m_x;
		}

		personatge.m_x = opvN.x;
		personatge.m_y = opvN.y;

		if (personatge.dead) {
			personatge.dead = false;
			killPlayer();
		}
		
		break;

		// Tecla cursor avall
	case 83:
		personatge.m_x -= nRepCnt * fact_pan * vdir[0] / 2;
		personatge.m_y -= nRepCnt * fact_pan * vdir[1] / 2;
		DoCollisions(llista_murs, personatge, eventfinal, eventsMursBaixada, punxesAnimadetes);

		if (personatge.m_colisioX) {
			if (!personatge.m_colisioY) {
				opvN.y = personatge.m_y;
				n[1] -= nRepCnt * fact_pan * vdir[1] / 2;
				cel[1] = personatge.m_y;
			}
		}
		else {
			if (!personatge.m_colisioY) {
				opvN.y = personatge.m_y;
				n[1] -= nRepCnt * fact_pan * vdir[1] / 2;
				cel[1] = personatge.m_y;
			}
			opvN.x = personatge.m_x;
			n[0] -= nRepCnt * fact_pan * vdir[0] / 2;
			cel[0] = personatge.m_x;
		}
		
		personatge.m_x = opvN.x;
		personatge.m_y = opvN.y;

		if (personatge.dead) {
			personatge.dead = false;
			killPlayer();
		}

		break;

		// Tecla cursor esquerra
	case 65:
		personatge.m_x -= nRepCnt * fact_pan * vdirpan[0] / 2;
		personatge.m_y -= nRepCnt * fact_pan * vdirpan[1] / 2;
		DoCollisions(llista_murs, personatge, eventfinal, eventsMursBaixada, punxesAnimadetes);

		if (personatge.m_colisioX) {
			if (!personatge.m_colisioY) {
				opvN.y = personatge.m_y;
				n[1] -= nRepCnt * fact_pan * vdirpan[1] / 2;
				cel[1] = personatge.m_y;
			}
		}
		else {
			if (!personatge.m_colisioY) {
				opvN.y = personatge.m_y;
				n[1] -= nRepCnt * fact_pan * vdirpan[1] / 2;
				cel[1] = personatge.m_y;
			}
			opvN.x = personatge.m_x;
			n[0] -= nRepCnt * fact_pan * vdirpan[0] / 2;
			cel[0] = personatge.m_x;
		}

		personatge.m_x = opvN.x;
		personatge.m_y = opvN.y;

		if (personatge.dead) {
			personatge.dead = false;
			killPlayer();
		}
	
		break;

		// Tecla cursor dret
	case 68:
		personatge.m_x += nRepCnt * fact_pan * vdirpan[0] / 2;
		personatge.m_y += nRepCnt * fact_pan * vdirpan[1] / 2;
		DoCollisions(llista_murs, personatge, eventfinal, eventsMursBaixada, punxesAnimadetes);

		if (personatge.m_colisioX) {
			if (!personatge.m_colisioY) {
				opvN.y = personatge.m_y;
				n[1] += nRepCnt * fact_pan * vdirpan[1] / 2;
				cel[1] = personatge.m_y;
			}
		}
		else {
			if (!personatge.m_colisioY) {
				opvN.y = personatge.m_y;
				n[1] += nRepCnt * fact_pan * vdirpan[1] / 2;
				cel[1] = personatge.m_y;
			}
			opvN.x = personatge.m_x;
			n[0] += nRepCnt * fact_pan * vdirpan[0] / 2;
			cel[0] = personatge.m_x;
		}
		
		personatge.m_x = opvN.x;
		personatge.m_y = opvN.y;

		if (personatge.dead) {
			personatge.dead = false;
			killPlayer();
		}
		
		break;

		//tecla K
	case 75:
		killPlayer();
		break;
		// Tecla Inicio
	case VK_HOME:
		opvN.z += nRepCnt * fact_pan;
		n[2] += nRepCnt * fact_pan;
		break;

		// Tecla Fin
	case VK_END:
		opvN.z -= nRepCnt * fact_pan;
		n[2] -= nRepCnt * fact_pan;
		break;

		// Tecla PgUp
	case VK_PRIOR:
		fact_pan /= 2;
		if (fact_pan < 1) fact_pan = 1;
		break;

		// Tecla PgDown
	case VK_NEXT:
		fact_pan *= 2;
		if (fact_pan > 2048) fact_pan = 2048;
		break;

		// Tecla Esc
	case 27:
		OnVistaFullscreen();
		break;
	case VK_SPACE:
		salta = true;
		break;
		//tecla p de pausa
	case 80:
		if (m_ButoEAvall)
		{
			m_ButoEAvall = false;
		}
		else
		{
			m_ButoEAvall = true;
		}
	default:
		break;
	}
}


// Teclat_Pan: Teclat pels moviments de Pan.
void CEntornVGIView::Teclat_Pan(UINT nChar, UINT nRepCnt)
{
	switch (nChar)
	{
		// Tecla cursor amunt
	case VK_UP:
		tr_cpv.y -= nRepCnt * fact_pan;
		if (tr_cpv.y < -100000) tr_cpv.y = 100000;
		break;

		// Tecla cursor avall
	case VK_DOWN:
		tr_cpv.y += nRepCnt * fact_pan;
		if (tr_cpv.y > 100000) tr_cpv.y = 100000;
		break;

		// Tecla cursor esquerra
	case VK_LEFT:
		tr_cpv.x += nRepCnt * fact_pan;
		if (tr_cpv.x > 100000) tr_cpv.x = 100000;
		break;

		// Tecla cursor dret
	case VK_RIGHT:
		tr_cpv.x -= nRepCnt * fact_pan;
		if (tr_cpv.x < -100000) tr_cpv.x = 100000;
		break;

		// Tecla PgUp
	case VK_PRIOR:
		fact_pan /= 2;
		if (fact_pan < 0.125) fact_pan = 0.125;
		break;

		// Tecla PgDown
	case VK_NEXT:
		fact_pan *= 2;
		if (fact_pan > 2048) fact_pan = 2048;
		break;

		// Tecla Insert: Fixar el despla�ament de pantalla (pan)
	case VK_INSERT:
		// Acumular despla�aments de pan (tr_cpv) en variables fixes (tr_cpvF).
		tr_cpvF.x += tr_cpv.x;		tr_cpv.x = 0.0;
		if (tr_cpvF.x > 100000) tr_cpvF.y = 100000;
		tr_cpvF.y += tr_cpv.y;		tr_cpv.y = 0.0;
		if (tr_cpvF.y > 100000) tr_cpvF.y = 100000;
		tr_cpvF.z += tr_cpv.z;		tr_cpv.z = 0.0;
		if (tr_cpvF.z > 100000) tr_cpvF.z = 100000;
		break;

		// Tecla Delete: Inicialitzar el despla�ament de pantalla (pan)
	case VK_DELETE:
		// Inicialitzar els valors de pan tant de la variable tr_cpv com de la tr_cpvF.
		tr_cpv.x = 0.0;			tr_cpv.y = 0.0;			tr_cpv.z = 0.0;
		tr_cpvF.x = 0.0;		tr_cpvF.y = 0.0;		tr_cpvF.z = 0.0;
		break;

	default:
		break;
	}
}

// Teclat_TransEscala: Teclat pels canvis del valor d'escala per X,Y,Z.
void CEntornVGIView::Teclat_TransEscala(UINT nChar, UINT nRepCnt)
{
	switch (nChar)
	{
		// Modificar vector d'Escalatge per teclat (actiu amb Escalat �nicament)
			// Tecla '+' (augmentar tot l'escalat)
	case 107:
		TG.VScal.x = TG.VScal.x * 2;
		if (TG.VScal.x > 8192) TG.VScal.x = 8192;
		TG.VScal.y = TG.VScal.y * 2;
		if (TG.VScal.y > 8192) TG.VScal.y = 8192;
		TG.VScal.z = TG.VScal.z * 2;
		if (TG.VScal.z > 8192) TG.VScal.z = 8192;
		break;

		// Tecla '-' (disminuir tot l'escalat)
	case 109:
		TG.VScal.x = TG.VScal.x / 2;
		if (TG.VScal.x < 0.25) TG.VScal.x = 0.25;
		TG.VScal.y = TG.VScal.y / 2;
		if (TG.VScal.y < 0.25) TG.VScal.y = 0.25;
		TG.VScal.z = TG.VScal.z / 2;
		if (TG.VScal.z < 0.25) TG.VScal.z = 0.25;
		break;

		// Tecla cursor amunt ('8')
	case 104:
		TG.VScal.x = TG.VScal.x * 2;
		if (TG.VScal.x > 8192) TG.VScal.x = 8192;
		break;

		// Tecla cursor avall ('2')
	case 98:
		TG.VScal.x = TG.VScal.x / 2;
		if (TG.VScal.x < 0.25) TG.VScal.x = 0.25;
		break;

		// Tecla cursor esquerra ('4')
	case 100:
		TG.VScal.y = TG.VScal.y / 2;
		if (TG.VScal.y < 0.25) TG.VScal.y = 0.25;
		break;

		// Tecla cursor dret ('6')
	case 102:
		TG.VScal.y = TG.VScal.y * 2;
		if (TG.VScal.y > 8192) TG.VScal.y = 8192;
		break;

		// Tecla HOME ('7')
	case 103:
		TG.VScal.z = TG.VScal.z * 2;
		if (TG.VScal.z > 8192) TG.VScal.z = 8192;
		break;

		// Tecla END ('1')
	case 97:
		TG.VScal.z = TG.VScal.z / 2;
		if (TG.VScal.z < 0.25) TG.VScal.z = 0.25;
		break;

		// Tecla INSERT
	case VK_INSERT:
		// Acumular transformacions Geom�triques (variable TG) i de pan en variables fixes (variable TGF)
		TGF.VScal.x *= TG.VScal.x;	TGF.VScal.y *= TG.VScal.y; TGF.VScal.z *= TG.VScal.z;
		if (TGF.VScal.x > 8192)		TGF.VScal.x = 8192;
		if (TGF.VScal.y > 8192)		TGF.VScal.y = 8192;
		if (TGF.VScal.z > 8192)		TGF.VScal.z = 8192;
		TG.VScal.x = 1.0;				TG.VScal.y = 1.0;			TG.VScal.z = 1.0;
		TGF.VRota.x += TG.VRota.x;	TGF.VRota.y += TG.VRota.y; TGF.VRota.z += TG.VRota.z;
		if (TGF.VRota.x >= 360)		TGF.VRota.x -= 360; 		if (TGF.VRota.x < 0) TGF.VRota.x += 360;
		if (TGF.VRota.y >= 360)		TGF.VRota.y -= 360;		if (TGF.VRota.y < 0) TGF.VRota.y += 360;
		if (TGF.VRota.z >= 360)		TGF.VRota.z -= 360;		if (TGF.VRota.z < 0) TGF.VRota.z += 360;
		TG.VRota.x = 0.0;				TG.VRota.y = 0.0;					TG.VRota.z = 0.0;
		TGF.VTras.x += TG.VTras.x;	TGF.VTras.y += TG.VTras.y; TGF.VTras.z += TG.VTras.z;
		if (TGF.VTras.x < -100000)		TGF.VTras.x = 100000;		if (TGF.VTras.x > 10000) TGF.VTras.x = 100000;
		if (TGF.VTras.y < -100000)		TGF.VTras.y = 100000;		if (TGF.VTras.y > 10000) TGF.VTras.y = 100000;
		if (TGF.VTras.z < -100000)		TGF.VTras.z = 100000;		if (TGF.VTras.z > 10000) TGF.VTras.z = 100000;
		TG.VTras.x = 0.0;		TG.VTras.y = 0.0;		TG.VTras.z = 0.0;
		break;

		// Tecla Delete: Esborrar les Transformacions Geom�triques Calculades
	case VK_DELETE:
		// Inicialitzar els valors de transformacions Geom�triques i de pan en variables fixes.
		TGF.VScal.x = 1.0;		TGF.VScal.y = 1.0;;		TGF.VScal.z = 1.0;
		TG.VScal.x = 1.0;		TG.VScal.y = 1.0;		TG.VScal.z = 1.0;
		TGF.VRota.x = 0.0;		TGF.VRota.y = 0.0;		TGF.VRota.z = 0.0;
		TG.VRota.x = 0.0;		TG.VRota.y = 0.0;		TG.VRota.z = 0.0;
		TGF.VTras.x = 0.0;		TGF.VTras.y = 0.0;		TGF.VTras.z = 0.0;
		TG.VTras.x = 0.0;		TG.VTras.y = 0.0;		TG.VTras.z = 0.0;
		break;

	default:
		break;
	}
}

// Teclat_TransRota: Teclat pels canvis del valor del vector de l'angle de rotaci� per X,Y,Z.
void CEntornVGIView::Teclat_TransRota(UINT nChar, UINT nRepCnt)
{
	switch (nChar)
	{
		// Tecla cursor amunt ('8')
	case 104:
		TG.VRota.x += nRepCnt * fact_Rota;
		if (TG.VRota.x >= 360) TG.VRota.x -= 360;
		break;

		// Tecla cursor avall ('2')
	case 98:
		TG.VRota.x -= nRepCnt * fact_Rota;
		if (TG.VRota.x < 1) TG.VRota.x += 360;
		break;

		// Tecla cursor esquerra ('4')
	case 100:
		TG.VRota.y -= nRepCnt * fact_Rota;
		if (TG.VRota.y < 1) TG.VRota.y += 360;
		break;

		// Tecla cursor dret ('6')
	case 102:
		TG.VRota.y += nRepCnt * fact_Rota;
		if (TG.VRota.y >= 360) TG.VRota.y -= 360;
		break;

		// Tecla HOME ('7')
	case 103:
		TG.VRota.z += nRepCnt * fact_Rota;
		if (TG.VRota.z >= 360) TG.VRota.z -= 360;
		break;

		// Tecla END ('1')
	case 97:
		TG.VRota.z -= nRepCnt * fact_Rota;
		if (TG.VRota.z < 1) TG.VRota.z += 360;
		break;

		// Tecla PgUp ('9')
	case 105:
		fact_Rota /= 2;
		if (fact_Rota < 1) fact_Rota = 1;
		break;

		// Tecla PgDown ('3')
	case 99:
		fact_Rota *= 2;
		if (fact_Rota > 90) fact_Rota = 90;
		break;

		// Modificar vector d'Escalatge per teclat (actiu amb Rotaci�)
			// Tecla '+' (augmentar escalat)
	case 107:
		TG.VScal.x = TG.VScal.x * 2;
		if (TG.VScal.x > 8192) TG.VScal.x = 8192;
		TG.VScal.y = TG.VScal.y * 2;
		if (TG.VScal.y > 8192) TG.VScal.y = 8192;
		TG.VScal.z = TG.VScal.z * 2;
		if (TG.VScal.z > 8192) TG.VScal.z = 8192;
		break;

		// Tecla '-' (disminuir escalat)
	case 109:
		TG.VScal.x = TG.VScal.x / 2;
		if (TG.VScal.x < 0.25) TG.VScal.x = 0.25;
		TG.VScal.y = TG.VScal.y / 2;
		if (TG.VScal.y < 0.25) TG.VScal.y = 0.25;
		TG.VScal.z = TG.VScal.z / 2;
		if (TG.VScal.z < 0.25) TG.VScal.z = 0.25;
		break;

		// Tecla Insert: Acumular transformacions Geom�triques (variable TG) i de pan en variables fixes (variable TGF)
	case VK_INSERT:
		TGF.VScal.x *= TG.VScal.x;	TGF.VScal.y *= TG.VScal.y; TGF.VScal.z *= TG.VScal.z;
		if (TGF.VScal.x > 8192)		TGF.VScal.x = 8192;
		if (TGF.VScal.y > 8192)		TGF.VScal.y = 8192;
		if (TGF.VScal.z > 8192)		TGF.VScal.z = 8192;
		TG.VScal.x = 1.0;				TG.VScal.y = 1.0;			TG.VScal.z = 1.0;
		TGF.VRota.x += TG.VRota.x;	TGF.VRota.y += TG.VRota.y; TGF.VRota.z += TG.VRota.z;
		if (TGF.VRota.x >= 360)		TGF.VRota.x -= 360; 		if (TGF.VRota.x < 0) TGF.VRota.x += 360;
		if (TGF.VRota.y >= 360)		TGF.VRota.y -= 360;		if (TGF.VRota.y < 0) TGF.VRota.y += 360;
		if (TGF.VRota.z >= 360)		TGF.VRota.z -= 360;		if (TGF.VRota.z < 0) TGF.VRota.z += 360;
		TG.VRota.x = 0.0;				TG.VRota.y = 0.0;					TG.VRota.z = 0.0;
		TGF.VTras.x += TG.VTras.x;	TGF.VTras.y += TG.VTras.y; TGF.VTras.z += TG.VTras.z;
		if (TGF.VTras.x < -100000)		TGF.VTras.x = 100000;		if (TGF.VTras.x > 10000) TGF.VTras.x = 100000;
		if (TGF.VTras.y < -100000)		TGF.VTras.y = 100000;		if (TGF.VTras.y > 10000) TGF.VTras.y = 100000;
		if (TGF.VTras.z < -100000)		TGF.VTras.z = 100000;		if (TGF.VTras.z > 10000) TGF.VTras.z = 100000;
		TG.VTras.x = 0.0;		TG.VTras.y = 0.0;		TG.VTras.z = 0.0;
		break;

		// Tecla Delete: Esborrar les Transformacions Geom�triques Calculades
	case VK_DELETE:
		// Inicialitzar els valors de transformacions Geom�triques i de pan en variables fixes.
		TGF.VScal.x = 1.0;	TGF.VScal.y = 1.0;;	TGF.VScal.z = 1.0;
		TG.VScal.x = 1.0;		TG.VScal.y = 1.0;		TG.VScal.z = 1.0;
		TGF.VRota.x = 0.0;	TGF.VRota.y = 0.0;	TGF.VRota.z = 0.0;
		TG.VRota.x = 0.0;		TG.VRota.y = 0.0;		TG.VRota.z = 0.0;
		TGF.VTras.x = 0.0;	TGF.VTras.y = 0.0;	TGF.VTras.z = 0.0;
		TG.VTras.x = 0.0;		TG.VTras.y = 0.0;		TG.VTras.z = 0.0;
		break;

		// Tecla Espaiador
	case VK_SPACE:
		rota = !rota;
		trasl = !trasl;
		break;

	default:
		break;
	}
}


// Teclat_TransTraslada: Teclat pels canvis del valor de traslaci� per X,Y,Z.
void CEntornVGIView::Teclat_TransTraslada(UINT nChar, UINT nRepCnt)
{
	GLfloat vdir[3] = { 0, 0, 0 };
	float modul = 0;

	switch (nChar)
	{
		// Tecla cursor amunt ('8')
	case 104:
		TG.VTras.x -= nRepCnt * fact_Tras;
		if (TG.VTras.x < -100000) TG.VTras.x = 100000;
		break;

		// Tecla cursor avall ('2')
	case 98:
		TG.VTras.x += nRepCnt * fact_Tras;
		if (TG.VTras.x > 10000) TG.VTras.x = 100000;
		break;

		// Tecla cursor esquerra ('4')
	case 100:
		TG.VTras.y -= nRepCnt * fact_Tras;
		if (TG.VTras.y < -100000) TG.VTras.y = -100000;
		break;

		// Tecla cursor dret ('6')
	case 102:
		TG.VTras.y += nRepCnt * fact_Tras;
		if (TG.VTras.y > 100000) TG.VTras.y = 100000;
		break;

		// Tecla HOME ('7')
	case 103:
		TG.VTras.z += nRepCnt * fact_Tras;
		if (TG.VTras.z > 100000) TG.VTras.z = 100000;
		break;

		// Tecla END ('1')
	case 97:
		TG.VTras.z -= nRepCnt * fact_Tras;
		if (TG.VTras.z < -100000) TG.VTras.z = -100000;
		break;

		// Tecla PgUp ('9')
	case 105:
		fact_Tras /= 2;
		if (fact_Tras < 1) fact_Tras = 1;
		break;

		// Tecla PgDown ('3')
	case 99:
		fact_Tras *= 2;
		if (fact_Tras > 100000) fact_Tras = 100000;
		break;

		// Modificar vector d'Escalatge per teclat (actiu amb Traslaci�)
			// Tecla '+' (augmentar escalat)
	case 107:
		TG.VScal.x = TG.VScal.x * 2;
		if (TG.VScal.x > 8192) TG.VScal.x = 8192;
		TG.VScal.y = TG.VScal.y * 2;
		if (TG.VScal.y > 8192) TG.VScal.y = 8192;
		TG.VScal.z = TG.VScal.z * 2;
		if (TG.VScal.z > 8192) TG.VScal.z = 8192;
		break;

		// Tecla '-' (disminuir escalat)
	case 109:
		TG.VScal.x = TG.VScal.x / 2;
		if (TG.VScal.x < 0.25) TG.VScal.x = 0.25;
		TG.VScal.y = TG.VScal.y / 2;
		if (TG.VScal.y < 0.25) TG.VScal.y = 0.25;
		TG.VScal.z = TG.VScal.z / 2;
		if (TG.VScal.z < 0.25) TG.VScal.z = 0.25;
		break;

		// Tecla INSERT
	case VK_INSERT:
		// Acumular transformacions Geom�triques (variable TG) i de pan en variables fixes (variable TGF)
		TGF.VScal.x *= TG.VScal.x;	TGF.VScal.y *= TG.VScal.y; TGF.VScal.z *= TG.VScal.z;
		if (TGF.VScal.x > 8192)		TGF.VScal.x = 8192;
		if (TGF.VScal.y > 8192)		TGF.VScal.y = 8192;
		if (TGF.VScal.z > 8192)		TGF.VScal.z = 8192;
		TG.VScal.x = 1.0;				TG.VScal.y = 1.0;			TG.VScal.z = 1.0;
		TGF.VRota.x += TG.VRota.x;	TGF.VRota.y += TG.VRota.y; TGF.VRota.z += TG.VRota.z;
		if (TGF.VRota.x >= 360)		TGF.VRota.x -= 360; 		if (TGF.VRota.x < 0) TGF.VRota.x += 360;
		if (TGF.VRota.y >= 360)		TGF.VRota.y -= 360;		if (TGF.VRota.y < 0) TGF.VRota.y += 360;
		if (TGF.VRota.z >= 360)		TGF.VRota.z -= 360;		if (TGF.VRota.z < 0) TGF.VRota.z += 360;
		TG.VRota.x = 0.0;				TG.VRota.y = 0.0;					TG.VRota.z = 0.0;
		TGF.VTras.x += TG.VTras.x;	TGF.VTras.y += TG.VTras.y; TGF.VTras.z += TG.VTras.z;
		if (TGF.VTras.x < -100000)		TGF.VTras.x = 100000;		if (TGF.VTras.x > 10000) TGF.VTras.x = 100000;
		if (TGF.VTras.y < -100000)		TGF.VTras.y = 100000;		if (TGF.VTras.y > 10000) TGF.VTras.y = 100000;
		if (TGF.VTras.z < -100000)		TGF.VTras.z = 100000;		if (TGF.VTras.z > 10000) TGF.VTras.z = 100000;
		TG.VTras.x = 0.0;		TG.VTras.y = 0.0;		TG.VTras.z = 0.0;
		break;

		// Tecla Delete: Esborrar les Transformacions Geom�triques Calculades
	case VK_DELETE:
		// Inicialitzar els valors de transformacions Geom�triques i de pan en variables fixes.
		TGF.VScal.x = 1.0;		TGF.VScal.y = 1.0;;		TGF.VScal.z = 1.0;
		TG.VScal.x = 1.0;		TG.VScal.y = 1.0;		TG.VScal.z = 1.0;
		TGF.VRota.x = 0.0;		TGF.VRota.y = 0.0;		TGF.VRota.z = 0.0;
		TG.VRota.x = 0.0;		TG.VRota.y = 0.0;		TG.VRota.z = 0.0;
		TGF.VTras.x = 0.0;		TGF.VTras.y = 0.0;		TGF.VTras.z = 0.0;
		TG.VTras.x = 0.0;		TG.VTras.y = 0.0;		TG.VTras.z = 0.0;
		break;

		// Tecla Espaiador
	case VK_SPACE:
		rota = !rota;
		trasl = !trasl;
		break;

	default:
		break;
	}
}


// Teclat_Grid: Teclat pels despla�aments dels gridXY, gridXZ i gridYZ.
void CEntornVGIView::Teclat_Grid(UINT nChar, UINT nRepCnt)
{
	switch (nChar)
	{
		// Key Up cursor ('8')
	case 104:
		hgrid.x -= nRepCnt * PAS_GRID;
		break;

		// Key Down cursor ('2')
	case 98:
		hgrid.x += nRepCnt * PAS_GRID;
		break;

		// Key Left cursor ('4')
	case 100:
		hgrid.y -= nRepCnt * PAS_GRID;
		break;

		// Key Right cursor ('6')
	case 102:
		hgrid.y += nRepCnt * PAS_GRID;
		break;

		// Key HOME ('7')
	case 103:
		hgrid.z += nRepCnt * PAS_GRID;
		break;

		// Key END ('1')
	case 97:
		hgrid.z -= nRepCnt * PAS_GRID;
		break;

		// Key grid ('G')
	case 'G':
		sw_grid = !sw_grid;
		break;

		/*
		// Key grid ('g')
		case 'g':
		sw_grid = !sw_grid;
		break;
		*/

	default:
		break;
	}
}


/* ------------------------------------------------------------------------- */
/*                           CONTROL DEL RATOLI                              */
/* ------------------------------------------------------------------------- */

// OnLButtonDown: Funci� que es crida quan s'apreta el bot� esquerra del mouse.
void CEntornVGIView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Agregue aqu� su c�digo de controlador de mensajes o llame al valor predeterminado

	// Entorn VGI: Detectem en quina posici� s'ha apretat el bot� esquerra del
	//				mouse i ho guardem a la variable m_PosEAvall i activem flag m_ButoEAvall
	m_ButoEAvall = true;
	m_PosEAvall = point;
	m_EsfeEAvall = OPV;

	CView::OnLButtonDown(nFlags, point);
}


// OnLButtonDown: Funci� que es crida quan deixem d'apretar el bot� esquerra del mouse.
void CEntornVGIView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Agregue aqu� su c�digo de controlador de mensajes o llame al valor predeterminado
	// Entorn VGI: Desactivem flag m_ButoEAvall quan deixem d'apretar bot� esquerra del mouse.
	m_ButoEAvall = false;

	// OPCI� VISTA-->SAT�LIT: C�lcul increment despla�ament del Punt de Vista
	if ((satelit) && (projeccio != ORTO))
	{	//m_EsfeIncEAvall.R = m_EsfeEAvall.R - OPV.R;
		m_EsfeIncEAvall.alfa = 0.01f * (OPV.alfa - m_EsfeEAvall.alfa); //if (abs(m_EsfeIncEAvall.alfa)<0.01) { if ((m_EsfeIncEAvall.alfa)>0.0) m_EsfeIncEAvall.alfa = 0.01 else m_EsfeIncEAvall.alfa=0.01}
		m_EsfeIncEAvall.beta = 0.01f * (OPV.beta - m_EsfeEAvall.beta);
		if (abs(m_EsfeIncEAvall.beta) < 0.01) {
			if ((m_EsfeIncEAvall.beta) > 0.0) m_EsfeIncEAvall.beta = 0.01;
			else m_EsfeIncEAvall.beta = 0.01;
		}
		//if ((m_EsfeIncEAvall.R == 0.0) && (m_EsfeIncEAvall.alfa == 0.0) && (m_EsfeIncEAvall.beta == 0.0)) KillTimer(WM_TIMER);
		//else SetTimer(WM_TIMER, 10, NULL);
	}

	CView::OnLButtonUp(nFlags, point);
}


// OnLButtonDown: Funci� que es crida quan s'apreta el bot� dret del mouse.
void CEntornVGIView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Agregue aqu� su c�digo de controlador de mensajes o llame al valor predeterminado
	// Entorn VGI: Detectem en quina posici� s'ha apretat el bot� esquerra del
	//				mouse i ho guardem a la variable m_PosEAvall i activem flag m_ButoDAvall
	m_ButoDAvall = true;
	m_PosDAvall = point;

	CView::OnRButtonDown(nFlags, point);
}


// OnLButtonDown: Funci� que es crida quan deixem d'apretar el bot� dret del mouse.
void CEntornVGIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	// Entorn VGI: Desactivem flag m_ButoEAvall quan deixem d'apretar bot� esquerra del mouse.
	m_ButoDAvall = false;

	//	ClientToScreen(&point);
	//	OnContextMenu(this, point);

	// Si fullscreen afegir men� per a restaurar Pantalla Normal en posici� del cursor.
	if (fullscreen) {
		ClientToScreen(&point);
		if (ContextMenu->GetSubMenu(0)) {
			CMenu* pSubMenu = ContextMenu->GetSubMenu(0);

			if (fullscreen)	pSubMenu->CheckMenuItem(ID_VISTA_FULLSCREEN, MF_CHECKED);
			else pSubMenu->CheckMenuItem(ID_VISTA_FULLSCREEN, MF_UNCHECKED);
			pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
				point.x, point.y, this);
		}
	}
}


// OnMouseMove: Funci� que es crida quan es mou el mouse. La utilitzem per la 
//				  Visualitzaci� Interactiva amb les tecles del mouse apretades per 
//				  modificar els par�metres de P.V. (R,angleh,anglev) segons els 
//				  moviments del mouse.
//      PARAMETRES: - nFlags: Flags que controlen si el bot� es apretat o no.
//					- point: Estructura (x,y) que d�na la posici� del mouse 
//							 (coord. pantalla) quan el bot� s'ha apretat.
void CEntornVGIView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Agregue aqu� su c�digo de controlador de mensajes o llame al valor predeterminado
	float modul = 0;
	GLfloat vdir[3] = { 0, 0, 0 };

	// TODO: Add your message handler code here and/or call default
	if (m_ButoEAvall && mobil && projeccio != CAP)
	{
		// Entorn VGI: Determinaci� dels angles (en graus) segons l'increment
		//				horitzontal i vertical de la posici� del mouse.
		CSize gir = m_PosEAvall - point;
		m_PosEAvall = point;
		OPV.beta = OPV.beta - gir.cx / 2;
		OPV.alfa = OPV.alfa + gir.cy / 2;

		// Entorn VGI: Control per evitar el creixement desmesurat dels angles.
		if (OPV.alfa >= 360)	OPV.alfa = OPV.alfa - 360;
		if (OPV.alfa < 0)		OPV.alfa = OPV.alfa + 360;
		if (OPV.beta >= 360)	OPV.beta = OPV.beta - 360;
		if (OPV.beta < 0)		OPV.beta = OPV.beta + 360;
		InvalidateRect(NULL, false);
	}
	else if (m_ButoEAvall && navega && (projeccio != CAP && projeccio != ORTO)) // Opci� Navegaci�
	{
		
		if (salta) {
			if (salt < 30) {
				n[2] -= .1;
				opvN.z -= .1;
			}
			else {
				n[2] += .1;
				opvN.z += .1;
			}
			salt--;
			if (salt < 0) {
				salta = false;
				salt = 60;
			}

		}
		
		
		// Entorn VGI: Canviar orientaci� en opci� de Navegaci�
		CSize girn = m_PosEAvall - point;
		angleZ = girn.cx / 2.0;

		//Descomentar per implementar el pitch
		//angleY = girn.cy / 2.0;

		// Entorn VGI: Control per evitar el creixement desmesurat dels angles.
		//if (angleZ >= 360) angleZ = angleZ - 360;
		//if (angleZ < 0)	angleZ = angleZ + 360;
		if (angleZ >= 360) angleZ = angleZ - 360;
		if (angleZ < 0)	angleZ = angleZ + 360;


		if (angleY >= 360) angleY = angleY - 360;
		if (angleY < 0)	angleY = angleY + 360;



		//Càlculs per a fer la rotació del punt
		float angleZRad = angleZ * pi / 180;
		float angleYRad = angleY * pi / 180;

		GLfloat cosa = cos(angleZRad);
		GLfloat sina = sin(angleZRad);

		GLfloat cosb = cos(angleYRad);
		GLfloat sinb = sin(angleYRad);

		GLfloat cosc = cos(0);
		GLfloat sinc = sin(0);

		GLfloat Axx = cosa * cosb;
		GLfloat Axy = cosa * sinb * sinc - sina * cosc;
		GLfloat Axz = cosa * sinb * cosc + sina * sinc;

		GLfloat Ayx = sina * cosb;
		GLfloat Ayy = sina * sinb * sinc + cosa * cosc;
		GLfloat Ayz = sina * sinb * cosc - cosa * sinc;

		GLfloat Azx = -sinb;
		GLfloat Azy = cosb * sinc;
		GLfloat Azz = cosb * cosc;




		n[0] = n[0] - opvN.x;
		n[1] = n[1] - opvN.y;
		n[2] = n[2] - opvN.z; 

		n[0] = n[0] * cos(angleZ * pi / 180) - n[1] * sin(angleZ * pi / 180);
		n[1] = n[0] * sin(angleZ * pi / 180) + n[1] * cos(angleZ * pi / 180);
		n[2] = n[2] * cos(angleY * pi / 180) + n[0] * sin(angleY * pi / 180);

		//AMBDUES MANERES FUNCIONEN
		//n[0] = Axx * n[0] + Axy * n[1] + Axz * n[2];
		//n[1] = Ayx * n[0] + Ayy * n[1] + Ayz * n[2];
		//n[2] = Azx * n[0] + Azy * n[1] + Azz * n[2];

		n[0] = n[0] + opvN.x;
		n[1] = n[1] + opvN.y;
		n[2] = n[2] + opvN.z;

		m_PosEAvall = point;
		InvalidateRect(NULL, false);
	}

	// Entorn VGI: Transformaci� Geom�trica interactiva pels eixos X,Y boto esquerra del mouse.
	else {
		bool transE = transX || transY;
		if (m_ButoEAvall && transE && transf)
		{
			// Calcular increment
			CSize girT = m_PosEAvall - point;
			if (transX)
			{
				long int incrT = girT.cx;
				if (trasl)
				{
					TG.VTras.x += incrT * fact_Tras;
					if (TG.VTras.x < -100000) TG.VTras.x = 100000;
					if (TG.VTras.x > 100000) TG.VTras.x = 100000;
				}
				else if (rota)
				{
					TG.VRota.x += incrT * fact_Rota;
					while (TG.VRota.x >= 360) TG.VRota.x -= 360;
					while (TG.VRota.x < 0) TG.VRota.x += 360;
				}
				else if (escal)
				{
					if (incrT < 0) incrT = -1 / incrT;
					TG.VScal.x = TG.VScal.x * incrT;
					if (TG.VScal.x < 0.25) TG.VScal.x = 0.25;
					if (TG.VScal.x > 8192) TG.VScal.x = 8192;
				}
			}
			if (transY)
			{
				long int incrT = girT.cy;
				if (trasl)
				{
					TG.VTras.y += incrT * fact_Tras;
					if (TG.VTras.y < -100000) TG.VTras.y = 100000;
					if (TG.VTras.y > 100000) TG.VTras.y = 100000;
				}
				else if (rota)
				{
					TG.VRota.y += incrT * fact_Rota;
					while (TG.VRota.y >= 360) TG.VRota.y -= 360;
					while (TG.VRota.y < 0) TG.VRota.y += 360;
				}
				else if (escal)
				{
					if (incrT <= 0) {
						if (incrT >= -2) incrT = -2;
						incrT = 1 / Log2(-incrT);
					}
					else incrT = Log2(incrT);
					TG.VScal.y = TG.VScal.y * incrT;
					if (TG.VScal.y < 0.25) TG.VScal.y = 0.25;
					if (TG.VScal.y > 8192) TG.VScal.y = 8192;
				}
			}
			m_PosEAvall = point;
			InvalidateRect(NULL, false);
		}
	}

	// Entorn VGI: Determinaci� del despla�ament del pan segons l'increment
	//				vertical de la posici� del mouse (tecla dreta apretada).
	if (m_ButoDAvall && pan && (projeccio != CAP && projeccio != ORTO))
	{
		CSize zoomincr = m_PosDAvall - point;
		long int incrx = zoomincr.cx;
		long int incry = zoomincr.cy;

		// Despla�ament pan vertical
		tr_cpv.y -= incry * fact_pan;
		if (tr_cpv.y > 100000) tr_cpv.y = 100000;
		else if (tr_cpv.y < -100000) tr_cpv.y = -100000;

		// Despla�ament pan horitzontal
		tr_cpv.x += incrx * fact_pan;
		if (tr_cpv.x > 100000) tr_cpv.x = 100000;
		else if (tr_cpv.x < -100000) tr_cpv.x = -100000;

		m_PosDAvall = point;
		InvalidateRect(NULL, false);
	}
	// Determinaci� del par�metre R segons l'increment
	//   vertical de la posici� del mouse (tecla dreta apretada)
		//else if (m_ButoDAvall && zzoom && (projeccio!=CAP && projeccio!=ORTO))
	else if (m_ButoDAvall && zzoom && (projeccio != CAP))
	{
		CSize zoomincr = m_PosDAvall - point;
		long int incr = zoomincr.cy / 1.0;

		//		zoom=zoom+incr;
		OPV.R = OPV.R + incr;
		if (OPV.R < 1) OPV.R = 1;
		m_PosDAvall = point;
		InvalidateRect(NULL, false);
	}
	else if (m_ButoDAvall && navega && (projeccio != CAP && projeccio != ORTO))
	{	// Avan�ar en opci� de Navegaci�
		if (m_PosDAvall != point)
		{
			CSize zoomincr = m_PosDAvall - point;

			float incr = zoomincr.cy / 2;
			//			long int incr=zoomincr.cy/2.0;  // Causa assertion en "afx.inl" lin 169
			vdir[0] = n[0] - opvN.x;
			vdir[1] = n[1] - opvN.y;
			vdir[2] = n[2] - opvN.z;
			modul = sqrt(vdir[0] * vdir[0] + vdir[1] * vdir[1] + vdir[2] * vdir[2]);
			vdir[0] = vdir[0] / modul;
			vdir[1] = vdir[1] / modul;
			vdir[2] = vdir[2] / modul;
			opvN.x += incr * vdir[0];
			opvN.y += incr * vdir[1];
			n[0] += incr * vdir[0];
			n[1] += incr * vdir[1];
			m_PosDAvall = point;
			InvalidateRect(NULL, false);
		}
	}

	// Entorn VGI: Transformaci� Geom�trica interactiva per l'eix Z amb boto dret del mouse.
	else if (m_ButoDAvall && transZ && transf)
	{
		// Calcular increment
		CSize girT = m_PosDAvall - point;
		long int incrT = girT.cy;
		if (trasl)
		{
			TG.VTras.z += incrT * fact_Tras;
			if (TG.VTras.z < -100000) TG.VTras.z = 100000;
			if (TG.VTras.z > 100000) TG.VTras.z = 100000;
		}
		else if (rota)
		{
			incrT = girT.cx;
			TG.VRota.z += incrT * fact_Rota;
			while (TG.VRota.z >= 360) TG.VRota.z -= 360;
			while (TG.VRota.z < 0) TG.VRota.z += 360;
		}
		else if (escal)
		{
			if (incrT <= 0) {
				if (incrT >= -2) incrT = -2;
				incrT = 1 / Log2(-incrT);
			}
			else incrT = Log2(incrT);
			TG.VScal.z = TG.VScal.z * incrT;
			if (TG.VScal.z < 0.25) TG.VScal.z = 0.25;
			if (TG.VScal.z > 8192) TG.VScal.z = 8192;
		}

		m_PosDAvall = point;
		InvalidateRect(NULL, false);
	}

	// Do not call CView::OnPaint() for painting messages
	CView::OnMouseMove(nFlags, point);
}

// OnMouseWheel: Funci� que es crida quan es mou el rodet del mouse. La utilitzem per la 
//				  Visualitzaci� Interactiva per modificar el par�metre R de P.V. (R,angleh,anglev) 
//				  segons el moviment del rodet del mouse.
//      PARAMETRES: - nFlags: Flags que controlen si el bot� es apretat o no.
//					- zDelta: Unitats de despla�ament del rodet del mouse.
//					- pt: Estructura (x,y) que d�na la posici� del mouse 
//							 (coord. pantalla) quan el bot� s'ha apretat.
BOOL CEntornVGIView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Agregue aqu� su c�digo de controlador de mensajes o llame al valor predeterminado
	float modul = 0;
	GLfloat vdir[3] = { 0, 0, 0 };

	// Funci� de zoom quan est� activada la funci� pan o les T. Geom�triques
	if ((zzoom) || (transX) || (transY) || (transZ))
	{
		OPV.R = OPV.R + zDelta / 4;
		if (OPV.R < 1) OPV.R = 1;
		InvalidateRect(NULL, false);
	}
	else if (navega)
	{
		vdir[0] = n[0] - opvN.x;
		vdir[1] = n[1] - opvN.y;
		vdir[2] = n[2] - opvN.z;
		modul = sqrt(vdir[0] * vdir[0] + vdir[1] * vdir[1] + vdir[2] * vdir[2]);
		vdir[0] = vdir[0] / modul;
		vdir[1] = vdir[1] / modul;
		vdir[2] = vdir[2] / modul;
		opvN.x += (zDelta / 4) * vdir[0];
		opvN.y += (zDelta / 4) * vdir[1];
		n[0] += (zDelta / 4) * vdir[0];
		n[1] += (zDelta / 4) * vdir[1];
		InvalidateRect(NULL, false);
	}

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


/* ------------------------------------------------------------------------- */
/*					     TIMER (ANIMACI�)									 */
/* ------------------------------------------------------------------------- */
void CEntornVGIView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Agregue aqu� su c�digo de controlador de mensajes o llame al valor predeterminado
	if (salta) {
		if (salt < 30) {
			n[2] -= .1;
			opvN.z -= .1;
		}
		else {
			n[2] += .1;
			opvN.z += .1;
		}
		salt--;
		if (salt < 0) {
			salta = false;
			salt = 60;
		}
	}
	
	for (int i = 0; i < eventsMursBaixada.size(); i++)
	{

		if (eventsMursBaixada[i].m_animacioIniciada)
		{

			if (eventsMursBaixada[i].m_tipus == -3)
			{
				if (eventsMursBaixada[i].m_en_curs)
				{
					eventsMursBaixada[i].actua(llista_murs[eventsMursBaixada[i].indexMurAnimatEnLlista]);
				}
				else
				{
					Mur newMur;
					if (eventsMursBaixada[i].m_direccio == HOR)
					{
						newMur.setMur(eventsMursBaixada[i].m_x - 4 * x - x - x / 2, eventsMursBaixada[i].m_y, eventsMursBaixada[i].m_z * x, HOR, 3 * x);
					}
					else
					{
						newMur.setMur(eventsMursBaixada[i].m_x, eventsMursBaixada[i].m_y + x + x + x+2*x, eventsMursBaixada[i].m_z * x, VER, 3 * x);
					}
					newMur.esUnMurAnimatQueCau = true;
					llista_murs.push_back(newMur);
					eventsMursBaixada[i].indexMurAnimatEnLlista = llista_murs.size() - 1;
					eventsMursBaixada[i].m_en_curs = true;


				}
				//llista_murs[eventsMursBaixada[i].indexMurAnimatEnLlista].pinta();
			}


		}

	}


	for (int i = 0; i < punxesAnimadetes.size(); i++)
	{
		if (punxesAnimadetes[i].variableControladoraPunxesBaixant)
		{
			punxesAnimadetes[i].animacioBaixada();
			if (punxesAnimadetes[i].m_z < -12)
			{
				punxesAnimadetes[i].variableControladoraPunxesBaixant = false;
			}
		}
		else
		{
			punxesAnimadetes[i].animacioPujada();
			if (punxesAnimadetes[i].m_z > -1)
			{
				punxesAnimadetes[i].variableControladoraPunxesBaixant = true;
			}
		}
	}

	if (anima) {
		// Codi de tractament de l'animaci� quan transcorren els ms. del crono.

		// Crida a OnPaint() per redibuixar l'escena
		InvalidateRect(NULL, false);
	}
	else if (satelit) {	// OPCI� SAT�LIT: Increment OPV segons moviments mouse.
		//OPV.R = OPV.R + m_EsfeIncEAvall.R;
		OPV.alfa = OPV.alfa + m_EsfeIncEAvall.alfa;
		while (OPV.alfa > 360) OPV.alfa = OPV.alfa - 360;	while (OPV.alfa < 0) OPV.alfa = OPV.alfa + 360;
		OPV.beta = OPV.beta + m_EsfeIncEAvall.beta;
		while (OPV.beta > 360) OPV.beta = OPV.beta - 360;	while (OPV.beta < 0) OPV.beta = OPV.beta + 360;

		// Crida a OnPaint() per redibuixar l'escena
		InvalidateRect(NULL, false);
	}
	
	InvalidateRect(NULL, false);
	dibuixa_Escena();

	CView::OnTimer(nIDEvent);
}


/* ------------------------------------------------------------------------- */
/*   RECURSOS DE MENU (persianes) DE L'APLICACIO:                            */
/*					1. ARXIUS												 */
/*					2. VEURE: ToolBar, StatusBar, Pantalla Completa			 */
/*					3. VISTA: Punt de Vista, Zoom, Pan Navega i Eixos	     */
/*					4. PROJECCI�                                             */
/*					5. OBJECTE					                             */
/*					6. TRANSFORMA											 */
/*					7. OCULTACIONS											 */
/*					8. IL.LUMINACI�											 */
/*					9. LLUMS												 */
/*				   10. SHADERS												 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/*					1. ARXIUS 												 */
/* ------------------------------------------------------------------------- */

// Obrir fitxer Fractal
void CEntornVGIView::OnArxiuObrirFractal()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	// Entorn VGI: Obrir di�leg de lectura de fitxer (fitxers (*.MNT)
	CFileDialog openMunt(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("MNT Files(*.mnt)|*.mnt|Error Files (*.err)|*err|All Files (*.*)|*.*||"));;

	if (openMunt.DoModal() != IDOK)
		return;                 // stay with old data file
	else nom = openMunt.GetPathName();

	// Entorn VGI: Variable de tipus CString 'nom' cont� el nom del fitxer seleccionat

	// Entorn VGI: Conversi� de la variable CString nom a la variable char *nomfitx, 
	//		compatible amb  les funcions de c�rrega de fitxers fractals
	char* nomfitx = CString2Char(nom);

	// Entorn VGI: Variable de tipus char *nomfitx cont� el nom del fitxer seleccionat


	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


// OnArchivoObrirFitxerObj: Obrir fitxer en format gr�fic OBJ
void CEntornVGIView::OnArxiuObrirFitxerObj()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	//if (ObOBJ != NULL) delete ObOBJ;

	objecte = OBJOBJ;	textura = true;

	// Entorn VGI: Obrir di�leg de lectura de fitxer
	CFileDialog openOBJ(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("OBJ Files(*.obj)|*.obj|Error Files (*.err)|*err|All Files (*.*)|*.*||"));;

	if (openOBJ.DoModal() != IDOK)	return;  // stay with old data file
	else nom = openOBJ.GetPathName();

	// Entorn VGI: Variable de tipus CString 'nom' cont� el nom del fitxer seleccionat

	// Entorn VGI: Conversi� de la variable CString nom a la variable char *nomfitx, 
	//		compatible amb  les funcions de c�rrega de fitxers fractals
	char* nomfitx = CString2Char(nom);

	// i carreguem
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);	// Activem contexte OpenGL

	if (ObOBJ == NULL) ObOBJ = new COBJModel;
	ObOBJ->LoadModel(nomfitx, OBJECTEOBJ, false);	// Carregar objecte OBJ SENSE textura
	ObOBJ->LoadModel(nomfitx, OBJECTEOBJT, true);	// Carregar objecte OBJ AMB textura

	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);	// Desactivem contexte OpenGL

// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);

}

// Obrir fitxer en format gr�fic 3DS
void CEntornVGIView::OnArxiuObrirFitxer3ds()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
		//if(Ob3DS!=NULL) delete Ob3DS;

	objecte = OBJ3DS;	textura = true;

	// Entorn VGI: Obrir di�leg de lectura de fitxer
	CFileDialog open3DS(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("3DS Files(*.3ds)|*.3ds|Error Files (*.err)|*err|All Files (*.*)|*.*||"));;

	if (open3DS.DoModal() != IDOK)	return;  // stay with old data file
	else nom = open3DS.GetPathName();

	// Entorn VGI: Variable de tipus CString 'nom' cont� el nom del fitxer seleccionat

	// Entorn VGI: Conversi� de la variable CString nom a la variable char *nomfitx, 
	//		compatible amb  les funcions de c�rrega de fitxers fractals
	char* nomfitx = CString2Char(nom);

	// i carreguem
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC); // Activem contexte OpenGL

	if (Ob3DS == NULL) Ob3DS = new Obj_3DS;
	Ob3DS->EliminarMemoria();
	Ob3DS->Inicialitzar();
	Ob3DS->Carregar3DS(nomfitx);

	// Precompilaci� de dos objectes nous: OBJECTE3DS: Objecte 3DS sense textures i OBJECTE3DST amb textures,
	Ob3DS->Dibuixa3DS(false, OBJECTE3DS, false);
	Ob3DS->Dibuixa3DS(false, OBJECTE3DST, true);

	wglMakeCurrent(m_pDC->GetSafeHdc(), NULL); // Desactivem contexte OpenGL

//  Entorn VGI: Modificar R per centrar Vista amb mida de l'objecte
	mida = sqrtf(3.0) * 10;
	OPV.R = 0.5 * mida / sin(30 * pi / 180) + p_near;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);

}


/* ------------------------------------------------------------------------- */
/*					2. VEURE: ToolBar, StatusBar, Pantalla Completa         */
/* ------------------------------------------------------------------------- */


/* -------------------------------------------------------------------------------- */
/*					3. VISTA: Pantalla Completa, Punt de Vista, Zoom, Pan i Eixos	*/
/* -------------------------------------------------------------------------------- */


// VISTA: FullScreen (Pantalla Completa-opci� booleana)
void CEntornVGIView::OnVistaFullscreen()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos

	if (!fullscreen) {
		//w_old = w;	h_old = h;	// Guardar mides finestra.
		ShowCursor(false);
		// I note that I go to full-screen mode
		fullscreen = true;
		// remembers the address of the window in which the view was placed (probably a frame)
		saveParent = this->GetParent();
		// assigns a view to a new parent - desktop
		this->SetParent(GetDesktopWindow());
		CRect rect; // it's about the dimensions of the desktop-desktop
		GetDesktopWindow()->GetWindowRect(&rect);
		// I set the window on the desktop
		this->SetWindowPos(&wndTopMost, rect.left, rect.top, rect.right, rect.bottom, SWP_SHOWWINDOW);
	}
	else
	{	// switching off the full-screen mode
		fullscreen = false;
		ShowCursor(true);
		// assigns an old parent view
		this->SetParent(saveParent);
		// I am downloading a pointer to the frame
		// to update it - to make the window lose the full-screen status
		// it was set in the right place
		// I am doing this because I do not know how to memorize the settings
		// windows in the frame - and they change when I turn on the full screen
		// Simple way - Displaying any ControlBar
		// without changing its settings - this is connected with inserting my window
		// tas it was before !! ??

		// Do not include CMainFrame
		//CMainFrame *frm=(CMainFrame *)AfxGetMainWnd();
		//frm->ShowControlBars();
		//frm->RecalcLayout();
		//frm->UpdateWindow();
		//frm->ShowControlBar(&frm->m_wndToolBar, frm->m_wndToolBar.IsVisible(), FALSE);

		//((CMainFrame *)AfxGetMainWnd())->RecalcLayout();
		w = w_old;	h = h_old;	// Restaurar mides finestra per tornar a finestra normal.
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateVistaFullscreen(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (fullscreen) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}




// VISTA: Mobil. Punt de Vista Interactiu (opci� booleana)
void CEntornVGIView::OnVistaMobil()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if ((projeccio != ORTO) || (projeccio != CAP)) mobil = !mobil;
	// Desactivaci� de Transformacions Geom�triques via mouse 
	//		si Visualitzaci� Interactiva activada.	
	if (mobil) {
		transX = false;	transY = false; transZ = false;
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateVistaMobil(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (mobil) 	pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}

// VISTA: Zoom. Zoom Interactiu (opci� booleana)
void CEntornVGIView::OnVistaZoom()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if ((projeccio != ORTO) || (projeccio != CAP)) zzoom = !zzoom;
	// Desactivaci� de Transformacions Geom�triques via mouse 
	//		si Zoom activat.
	if (zzoom) {
		transX = false;	transY = false;	transZ = false;
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateVistaZoom(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (zzoom) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// VISTA: Sat�lit. Vista interactiva i animada en que increment de movimen �s activat per mouse (opci� booleana)
void CEntornVGIView::OnVistaSatelit()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if (projeccio != CAP || projeccio != ORTO) satelit = !satelit;
	if (satelit) mobil = true;
	bool testA = anima;									// Testejar si hi ha alguna animaci� activa apart de Sat�lit.
	//if ((!satelit) && (!testA)) //KillTimer(WM_TIMER);	// Si es desactiva Sat�lit i no hi ha cap animaci� activa es desactiva el Timer.

// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateVistaSatelit(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (satelit) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// VISTA: Polars Eix X cap amunt per a Visualitzaci� Interactiva
void CEntornVGIView::OnVistaPolarsX()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if ((projeccio != CAP) && (!navega)) Vis_Polar = POLARX;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateVistaPolarsX(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (Vis_Polar == POLARX) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// VISTA: Polars Eix Y cap amunt per a Visualitzaci� Interactiva
void CEntornVGIView::OnVistaPolarsY()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if ((projeccio != CAP) && (!navega)) Vis_Polar = POLARY;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateVistaPolarsY(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (Vis_Polar == POLARY) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// VISTA: Polars Eix Z cap amunt per a Visualitzaci� Interactiva
void CEntornVGIView::OnVistaPolarsZ()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if ((projeccio != CAP) && (!navega)) Vis_Polar = POLARZ;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateVistaPolarsZ(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (Vis_Polar == POLARZ) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// VISTA: Mode de Despla�ament horitzontal i vertical per pantalla del Punt de Vista (pan) (opci� booleana)
void CEntornVGIView::OnVistaPan()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if ((projeccio != ORTO) || (projeccio != CAP)) pan = !pan;
	// Desactivaci� de Transformacions Geom�triques via mouse i navega si pan activat
	if (pan) {
		mobil = true;		zzoom = true;
		transX = false;	transY = false;	transZ = false;
		navega = false;
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateVistaPan(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (pan) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}

// Tornar a lloc d'origen
void CEntornVGIView::OnVistaOrigenpan()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if (pan) {
		fact_pan = 1;
		tr_cpv.x = 0;	tr_cpv.y = 0;	tr_cpv.z = 0;
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

// VISTA: Mode de navegaci� sobre un pla amb botons de teclat o de mouse (nav) (opci� booleana)
void CEntornVGIView::OnVistaNavega()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if ((projeccio != ORTO) || (projeccio != CAP)) navega = !navega;
	// Desactivaci� de zoom, mobil, Transformacions Geom�triques via mouse i pan 
	//		si navega activat
	if (navega)
	{
		mobil = false;	zzoom = false;
		transX = false;	transY = false;	transZ = false;
		pan = false;
		tr_cpv.x = 0.0;		tr_cpv.y = 0.0;		tr_cpv.z = 0.0;	// Inicialitzar a 0 despla�ament de pantalla
		tr_cpvF.x = 0.0;	tr_cpvF.y = 0.0;	tr_cpvF.x = 0.0; // Inicialitzar a 0 despla�ament de pantalla
	}
	else {
		mobil = true;
		zzoom = true;
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateVistaNavega(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (navega) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}

// Tornar a lloc d'origen
void CEntornVGIView::OnVistaOrigennavega()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if (navega) {
		n[0] = 0.0;		n[1] = 0.0;		n[2] = 0.0;
		opvN.x = 10.0;	opvN.y = 0.0;		opvN.z = 0.0;
		angleZ = 0.0;
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

// VISTA: Visualitzar eixos coordenades m�n (opci� booleana)
void CEntornVGIView::OnVistaEixos()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	eixos = !eixos;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateVistaEixos(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (eixos) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// VISTA: Visualitzar Grid XY (opci� booleana)
void CEntornVGIView::OnVistaGridXY()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	grid.x = !grid.x;	hgrid.x = 0.0;
	if (grid.x) grid.w = false;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateVistaGridXY(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (grid.x) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}

// VISTA: Visualitzar Grid XZ (opci� booleana)
void CEntornVGIView::OnVistaGridXZ()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	grid.y = !grid.y;	hgrid.y = 0.0;
	if (grid.y) grid.w = false;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateVistaGridXZ(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (grid.y) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// VISTA: Visualitzar Grid YZ (opci� booleana)
void CEntornVGIView::OnVistaGridYZ()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	grid.z = !grid.z;	hgrid.z = 0.0;
	if (grid.z) grid.w = false;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateVistaGridYZ(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (grid.z) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// VISTA: Visualitzar Grid XYZ (opci� booleana)
void CEntornVGIView::OnVistaGridXYZ()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	grid.w = !grid.w;	hgrid.w = 0.0;
	if (grid.w)
	{
		grid.x = false;	grid.y = false;		grid.z = false;
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateVistaGridXYZ(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (grid.w) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);

}


/* ------------------------------------------------------------------------- */
/*					4. PROJECCI�                                             */
/* ------------------------------------------------------------------------- */

std::vector<Mur> CEntornVGIView::CreaSales() {
	std::vector<Mur> llista;
	// Mur: x 20 y 5 z 15
	GLfloat h = -50.0f;
	
	// SALA DERROTA
	llista.push_back(Mur(100.0, 50.0, h, HOR));
	llista.push_back(Mur(100.0, 70.0, h, HOR));
	llista.push_back(Mur(107.5, 82.5, h, VER));
	llista.push_back(Mur(127.5, 82.5, h, VER));
	llista.push_back(Mur(140.0, 75.0, h, HOR));
	llista.push_back(Mur(140.0, 55.0, h, HOR));
	llista.push_back(Mur(132.5, 42.5, h, VER));
	llista.push_back(Mur(112.5, 42.5, h, VER));

	llista.push_back(Mur(100.0, 50.0, h + 15, HOR));
	llista.push_back(Mur(100.0, 70.0, h + 15, HOR));
	llista.push_back(Mur(107.5, 82.5, h + 15, VER));
	llista.push_back(Mur(127.5, 82.5, h + 15, VER));
	llista.push_back(Mur(140.0, 75.0, h + 15, HOR));
	llista.push_back(Mur(140.0, 55.0, h + 15, HOR));
	llista.push_back(Mur(132.5, 42.5, h + 15, VER));
	llista.push_back(Mur(112.5, 42.5, h + 15, VER));



	///SALA VICTÒRIA
	llista.push_back(Mur(50.0, 50.0, h, HOR));
	llista.push_back(Mur(50.0, 70.0, h, HOR));
	llista.push_back(Mur(57.5, 82.5, h, VER));
	llista.push_back(Mur(77.5, 82.5, h, VER));
	llista.push_back(Mur(90.0, 75.0, h, HOR));
	llista.push_back(Mur(90.0, 55.0, h, HOR));
	llista.push_back(Mur(82.5, 42.5, h, VER));
	llista.push_back(Mur(62.5, 42.5, h, VER));

	llista.push_back(Mur(50.0, 50.0, h + 15, HOR));
	llista.push_back(Mur(50.0, 70.0, h + 15, HOR));
	llista.push_back(Mur(57.5, 82.5, h + 15, VER));
	llista.push_back(Mur(77.5, 82.5, h + 15, VER));
	llista.push_back(Mur(90.0, 75.0, h + 15, HOR));
	llista.push_back(Mur(90.0, 55.0, h + 15, HOR));
	llista.push_back(Mur(82.5, 42.5, h + 15, VER));
	llista.push_back(Mur(62.5, 42.5, h + 15, VER));


	return llista;
}

std::vector<Mur> CEntornVGIView::initMurs() { //propera implementació: passar per paràmetres el nombre de murs i la matriu rotllo suarez 
	//de moment, inicialització "manual"
	std::vector<Mur> llista;
	
	/*
	int const MAX_FILA = 7;
	int const MAX_COLUMNA = 5;
	//Versió simple:
	int matriuLaberint[MAX_COLUMNA][MAX_FILA] = {   {-1, 1, 1, 1, 1 ,1, 1},
													{0, 1, 0, 1, 0 ,1, 1},
													{0, 0, -6,-5,-5,-5,-5},
													{ 1, 1, 1, 1, 1, 0, 0},
													{-2,-4,-4, 0, 0, 0, 1} };
	*/
	
	//Mapa gran
	
	int const MAX_FILA = 10;
	int const MAX_COLUMNA = 10;
	int matriuLaberint[MAX_COLUMNA][MAX_FILA] = {	{-1,1,1,1,1,1,1,1,1,1},
													{0,0,-4,0,-4,-4,0,0,0,1},
													{0,0,0,-5,-5,-5,-5,-5,0,1},
													{1,1,1,1,-3,1,1,1,0,1},
													{1,0,0,0,0,0,0,0,0,1},
													{1,0,0,0,0,0,0,0,0,1},
													{1,-3,1,1,1,1,0,1,1,1},
													{1,0,-6,0,0,0,-6,0,0,1},
													{1,0,0,0,-6,0,0,0,0,1},
													{1,1,1,1,1,1,1,1,-2,1},
												};

	
	/*
	int const MAX_FILA = 10;
	int const MAX_COLUMNA = 10;
	//Versió simple:
	int matriuLaberint[MAX_COLUMNA][MAX_FILA] = { { -1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
													{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1 },
													{ 1, 1, 0, 0, 1, 0, 0, 0, 0, 1 },
													{ 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
													{ 1, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
													{ 1, 0, 1, 0, 1, 1, 1, 1, 1, 1 },
													{ 1, 1, 0, 0, 1, 1, 0, 0, 0, 1 },
													{ 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
													{ 1, 0, 0, 0, 0, 0, 0, 1, 0, 1 },
													{ 1,-2, 1, 1, 1, 1, 1, 1, 1, 1 } };
	*/
	//Versió tricky:
	/*
	int matriuLaberint[MAX_COLUMNA][MAX_FILA] = { { 0, 0,-1, 1, 1 },
	{ 0, 0, 1, 0, 1 },
	{ 1, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0 },
	{ 0, 1, 1, 0, 0 },
	{ 0, 0, 1, -2, 1 } };
	*/
	/*
	#####################_NOMENCLATURA DE LAS CASELLLAS_###############
	CASELLA INICI=-1
	CASELLA CAMÍ=0
	CASELLA BLOC=1
	CASELLA FINAL=-2
	CASELLA MUR CIAGUDER HORITZONTAL = -3
	CASELLA MUR CIAGUDER VERTICAL = -4
	CASELLA CAMÍ QUE RECORRE L'SHRECK=-5
	CASELLA PUNXES ANIMADAS=-6
	*/
	float x = 5.0f; //Coordenada
	float h = 7.5f; //Altura
					//glColor3f(0.5, 0.5, 0.25);
					//COORDENADES DE PUNT INICIAL
	int CoordenadaInici_J = 0;
	int CoordenadaInici_I = 0;
	//COORDENADES DE PUNT FINAL
	int CoordenadaEnd_J = 1;
	int CoordenadaEnd_I = 6;
	int bucle1 = 0;
	int bucle2 = 0;

	//7Entrada al laberint
	llista.push_back(Mur(-4 * x, 0, -x , VER));
	llista.push_back(Mur(-4 * x, 4 * x, -x , VER));

	llista.push_back(Mur(-4 * x - x - x / 2, -x - x - x / 2, -x, HOR));
	llista.push_back(Mur(-4 * x - x - x / 2, -x - x / 2 + 8*x, -x, HOR));

	llista.push_back(Mur(-4 * x*2, -4*x, -x, VER));
	llista.push_back(Mur(-4 * x*2, 2*4 * x, -x, VER));

	Mur murEntrada;
	murEntrada.setMur(- 4 * x *2-2*x, +2*x, -4, HOR, 12*x);
	llista.push_back(murEntrada);



	bool camiShrek_ja_creat = false;

	for (int j = 0; j < MAX_COLUMNA; j++)
	{
		for (int i = 0; i < MAX_FILA; i++)
		{
			if (matriuLaberint[j][i] == 1)
			{
				//CAS DE CASELLA BLOC AMB CASELLA CAMI A L'ESQUERRA (i-1)
				if ((i > 0) && (matriuLaberint[j][i - 1] < 1))
				{
					/*//Moviment a coordenada
					glTranslatef((j * 4 + 1)*x, i * 4 * x, h);
					//Transalació a vertical
					glScalef(4 * x, x, 2 * h);
					*/
					llista.push_back(Mur((j * 4 + 1) * x, i * 4 * x, h, VER));
				}
				//CAS DE CASELLA BLOC AMB CASELLA CAMI A BAIX (j-1)
				if ((j > 0) && (matriuLaberint[j - 1][i] < 1))
				{
					/*
					//Moviment a coordenada
					//Versio no simplificada: glTranslatef( 2*x + i * 4 * x, 2*x + x*0,5+ (j-1) * 4 * x, 7.5f);
					glTranslatef(x*(2.5 + (j - 1) * 4), x*(1.5 + (i * 4)), h);
					//Translació a horitzontal
					glScalef(x, 4 * x, 2 * h);
					glutSolidCube(1.0);
					glPopMatrix();
					*/
					llista.push_back(Mur(x * (2.5 + (j - 1) * 4), x * (1.5 + (i * 4)), h, HOR));
				}
			}
			else
			{
				//CAS DE CASELLA CAMI AMB CASELLA BLOC A L'ESQUERRA (i-1)
				if ((i == 0) || (matriuLaberint[j][i - 1] == 1))
				{
					/*
					//Moviment a coordenada
					glTranslatef(j * 4 * x, i * 4 * x, h);
					//Transalació a vertical
					glScalef(4 * x, x, 2 * h);
					*/

					llista.push_back(Mur(j * 4 * x, i * 4 * x, h, VER));
				}
				//CAS DE CASELLA CAMI AMB CASELLA BLOC A SOTA (j-1)
				if ((j == 0) || (matriuLaberint[j - 1][i] == 1))
				{
					if (matriuLaberint[j][i] != -1)
					{
						/*glPushMatrix();
						//Moviment a coordenada
						//Versio no simplificada: glTranslatef( 2*x + i * 4 * x, 2*x + x*0,5+ (j-1) * 4 * x, 7.5f);
						glTranslatef(x*(2.5 + (j - 1) * 4), x*(2.5 + (i * 4)), h);
						//Translació a horitzontal
						glScalef(x, 4 * x, 2 * h);
						*/
						llista.push_back(Mur(x * (2.5 + (j - 1) * 4), x * (2.5 + (i * 4)), h, HOR));
					}
				}
				//CAS LÍMIT DE MAPA LATERAL (i MAX)
				if ((i == (MAX_FILA - 1)) && (matriuLaberint[j][i] != -2))
				{
					/*();
					//Moviment a coordenada
					glTranslatef(j * 4 * x, (i + 1) * 4 * x, h);
					//Transalació a vertical
					glScalef(4 * x, x, 2 * h);
					*/
					llista.push_back(Mur(j * 4 * x, (i + 1) * 4 * x, h, VER));
				}
				//CAS LÍMIT DE MAPA FRONTAL (j MAX)
				if ((j == (MAX_COLUMNA - 1)) && (matriuLaberint[j][i] != -2))
				{
					/*();
					//Moviment a coordenada
					glTranslatef(x*(2.5 + (j) * 4), x*(2.5 + ((i) * 4)), h);
					//Translació a horitzontal
					glScalef(x, 4 * x, 2 * h);
					*/
					Mur prova1(x * (2.5 + j * 4), x * (2.5 + (i * 4)), h, HOR);
					llista.push_back(prova1);
				}

				// Crea mur extra per evitar desplaçament inicial i ja no genera problemes amb textures (mur sbre mur)
				if (matriuLaberint[j][i] == -1)
				{
					Mur murEntrada;
					murEntrada.setMur(j * 4 * x - x - x / 2, (i + 1) * 4 * x, h, VER, x);
					llista.push_back(murEntrada);


					Event eventInicial(j * 4 * x + x + 2 * x, i * 4 * x + 2 * x, h, -3, HOR);
					eventInicial.m_tipus = -3;//mur caiguda
					eventsMursBaixada.push_back(eventInicial);

				}

				else {
					if (matriuLaberint[j][i] == -2)
					{
						Event final(j * 4 * x + x + 2 * x, i * 4 * x + 2 * x, h, matriuLaberint[j][i], HOR);
						eventfinal = final;


						Mur murSortida;
						//mur.setMur((j * 8 * x + (5 * x) / 2, (i + 1) * 4 * x - (4 * x), h, VER, x);
						murSortida.setMur((x * (j * 8 + 5)) / 2, i * 4 * x, h, VER, x);
						llista.push_back(murSortida);
					}
					else if (matriuLaberint[j][i] == -3)
						{
							Event eventMurCaigudor(j * 4 * x + x + 2 * x, i * 4 * x + 2 * x, h, -3, HOR);//cas de mur caiguda
							eventsMursBaixada.push_back(eventMurCaigudor);
						}

						else if (matriuLaberint[j][i] == -4)
						{

							Event eventMurCaigudor(j * 4 * x + x + 2 * x - 2 * x - x / 2, i * 4 * x + 2 * x + 2 * x + x, h, -3, VER);//cas de mur caiguda
							eventsMursBaixada.push_back(eventMurCaigudor);
							//eventMurCaigudor.pinta();

						}
						else if (matriuLaberint[j][i] == -5)
						{

							if (camiShrek_ja_creat)
							{
								Posicio_x_shrek_final = 4 * x * j + x / 2;
								Posicio_y_shrek_final = 4 * x * i;
								
								//Cami de proba shrek casellas
								Mur probaCamiShrek;
								probaCamiShrek.setMur(4 * x * j+x/2, 4 * x * i, -x, VER, x);
								llista.push_back(probaCamiShrek);
							}
							else
							{
								//Moviment shreck == -5
								
								Posicio_x_shrek_inicial = 4 * x * j + x / 2;
								Posicio_y_shrek_inicial = 4 * x * i;
								camiShrek_ja_creat = true;

								
								//Cami de proba shrek casella 1
								Mur probaCamiShrek;
								probaCamiShrek.setMur(4 * x * j + x / 2, 4 * x * i, -x, VER, x);
								llista.push_back(probaCamiShrek);
							}
							
							

						}
						else if (matriuLaberint[j][i] == -6)
						{			
							Mur punxesAnimades;
							punxesAnimades.setMur(4 * x * j + x / 2 , 4 * x * i - x-x, -x/2, VER,3*x);
							punxesAnimadetes.push_back(punxesAnimades);
						}

					
				}

			}


			//bucle1++;
			//if (bucle1 == 2)
			//	break;
		}
		//bucle2++;
		//if (bucle2 == 1)
		//	break;
	}


	MidaLaberint_Fila = MAX_FILA;
	MidaLaberint_Columna =MAX_COLUMNA;
	
	

	return llista;
}


void CEntornVGIView::killPlayer() {

	if(lifes>0)
		lifes--;

	if (lifes <= 0) {
		//GAME OVER
		
		//MOVE THE PLAYER TO THE DEFEAT ROOM
		personatge.m_x = 120.0;
		personatge.m_y = 62.5;
		personatge.m_z = -52.5;
		
		opvN.x = 120.0;				opvN.y = 62.5;			opvN.z = -52.5;
		n[0] = opvN.x + 5.0;		n[1] = opvN.y;			n[2] = opvN.z;

		llumVermella = true;
	}
	else {
		//GO TO STARTING POINT
		personatge.m_x = -3.0;
		personatge.m_y = 12.0;
		opvN.x = -3.0;			opvN.y = 12.0;			opvN.z = 5.0;
		n[0] = opvN.x+5.0;		n[1] = opvN.y;			n[2] = 5.0;
	}
}



// PROJECCI�: Perspectiva
void CEntornVGIView::OnProjeccioPerspectiva()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	projeccio = PERSPECT;
	mobil = true;			zzoom = true;

	//POSSIBLE CRIDA A LA FUNCIÓ QUE LLEGIRIA EL FITXER (AL QUE S'HA D'INCLOURE ABANS DEL BITMAP EL NOMBRE DE MURS)
	//llegirfitxer(filename) o whatever
	
	/*llista_murs = initMurs();
	Personatge nou(n[0], n[1], 3, 0);
	personatge = nou;
	num_murs = llista_murs.size();

	*/
	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);

}

void CEntornVGIView::OnUpdateProjeccioPerspectiva(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (projeccio == PERSPECT) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


/* ------------------------------------------------------------------------- */
/*					5. OBJECTE					                             */
/* ------------------------------------------------------------------------- */

// OBJECTE: Cub
void CEntornVGIView::OnObjecteCub()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos

	objecte = CUB; textura = true;

	texturesID[9] = loadIMA_ILUT("./textures/GrassHD.png");

	//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
	//	Canviar l'escala per a centrar la vista (Ortogr�fica)


	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateObjecteCub(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (objecte == CUB) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// OBJECTE: Cub RGB
void CEntornVGIView::OnObjecteCubRGB()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	objecte = CUB_RGB;   textura = true;

	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	//Textures skybox
	texturesID[9] = loadIMA_ILUT("./textures/tex1_64x64_c05e3c09362f364a_14.png");
	texturesID[8] = loadIMA_ILUT("./textures/tex1_128x128_0e437d36eaf137df_14.png");
	texturesID[7] = loadIMA_ILUT("./textures/sky-hd-wallpaper-9.jpg");
	texturesID[10] = loadIMA_ILUT("./textures/skybox/right.png");
	texturesID[11] = loadIMA_ILUT("./textures/skybox/left.png");
	texturesID[12] = loadIMA_ILUT("./textures/skybox/top.png");
	texturesID[13] = loadIMA_ILUT("./textures/skybox/bottom.png");
	texturesID[14] = loadIMA_ILUT("./textures/skybox/front.png");
	texturesID[15] = loadIMA_ILUT("./textures/skybox/back.png");

	//shrek
	texturesID[16] = loadIMA_ILUT("./textures/shrek/Shrek.png");
	texturesID[17] = loadIMA_ILUT("./textures/shrek/shrekshirt.png");
	


	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
	//	Canviar l'escala per a centrar la vista (Ortogr�fica)

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateObjecteCubRGB(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (objecte == CUB_RGB) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// OBJECTE Esfera
void CEntornVGIView::OnObjecteEsfera()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	objecte = ESFERA;

	//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
	//	Canviar l'escala per a centrar la vista (Ortogr�fica)

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateObjecteEsfera(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (objecte == ESFERA) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}

// OBJECTE Tetera
void CEntornVGIView::OnObjecteTetera()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	objecte = TETERA;

	//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
	//	Canviar l'escala per a centrar la vista (Ortogr�fica)

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateObjecteTetera(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (objecte == TETERA) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// OBJECTE Truck
void CEntornVGIView::OnObjecteTruck()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	objecte = TRUCK;		textura = true;

	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);	// Activem contexte OpenGL
// Inicialitza vector imatges textura pel Truck.
	//Init_Textures();
	texturesID[1] = loadIMA_ILUT("./textures/vent.bmp");

	texturesID[2] = loadIMA_ILUT("./textures/plat.bmp");

	texturesID[3] = loadIMA_ILUT("./textures/reixeta.bmp");

	texturesID[4] = loadIMA_ILUT("./textures/fars.bmp");

	texturesID[5] = loadIMA_ILUT("./textures/txapa.bmp");

	texturesID[6] = loadIMA_ILUT("./textures/metall.bmp");
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);	// Desactivem contexte OpenGL

//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
//	Canviar l'escala per a centrar la vista (Ortogr�fica)

// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateObjecteTruck(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (objecte == TRUCK) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// OBJECTE Tie
void CEntornVGIView::OnObjecteTie()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	objecte = TIE;

	//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
	//	Canviar l'escala per a centrar la vista (Ortogr�fica)

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateObjecteTie(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (objecte == TIE) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}

// ----------------- OBJECTES CORBES BEZIER, LEMNISCATA i B-SPLINE


// OBJECTE Corba Bezier
void CEntornVGIView::OnObjeteCorbaBezier()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	nom = "";
	objecte = C_BEZIER;

	// Entorn VGI: Obrir di�leg de lectura de fitxer (fitxers (*.crv)
	CFileDialog openSpline(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("SPL Files(*.crv)|*.crv|All Files (*.*)|*.*||"));;

	if (openSpline.DoModal() != IDOK)
		return;                 // stay with old data file
	else nom = openSpline.GetPathName();

	// Entorn VGI: Variable de tipus CString 'nom' cont� el nom del fitxer seleccionat

	// Entorn VGI: Conversi� de la variable CString nom a la variable char *nomfitx, 
	//		compatible amb  les funcions de c�rrega de fitxers fractals
	char* nomfitx = CString2Char(nom);

	npts_T = llegir_ptsC(nomfitx);

	// 	---- Entorn VGI: Modificar R per centrar Vista amb mida de l'objecte

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateObjeteCorbaBezier(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (objecte == C_BEZIER) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// OBJECTE Corba Lemniscata 3D
void CEntornVGIView::OnObjecteCorbaLemniscata()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	objecte = C_LEMNISCATA;

	// 	---- Entorn VGI: Modificar R per centrar Vista amb mida de l'objecte

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateObjecteCorbaLemniscata(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (objecte == C_LEMNISCATA) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// OBJECTE Corba B-Spline
void CEntornVGIView::OnObjecteCorbaBSpline()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	nom = "";
	objecte = C_BSPLINE;

	// Entorn VGI: Obrir di�leg de lectura de fitxer (fitxers (*.crv)
	CFileDialog openSpline(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("SPL Files(*.crv)|*.crv|All Files (*.*)|*.*||"));;

	if (openSpline.DoModal() != IDOK)
		return;                 // stay with old data file
	else nom = openSpline.GetPathName();

	// Entorn VGI: Variable de tipus CString 'nom' cont� el nom del fitxer seleccionat

	// Entorn VGI: Conversi� de la variable CString nom a la variable char *nomfitx, 
	//		compatible amb  les funcions de c�rrega de fitxers fractals
	char* nomfitx = CString2Char(nom);

	npts_T = llegir_ptsC(nomfitx);

	// 	---- Entorn VGI: Modificar R per centrar Vista amb mida de l'objecte

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateObjecteCorbaBSpline(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (objecte == C_BSPLINE) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}




void CEntornVGIView::OnObjectePuntsControl()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	sw_Punts_Control = !sw_Punts_Control;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateObjectePuntsControl(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (sw_Punts_Control) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


/* ------------------------------------------------------------------------- */
/*					6. TRANSFORMA											 */
/* ------------------------------------------------------------------------- */

// TRANSFORMA: TRASLACI�
void CEntornVGIView::OnTransformaTraslacio()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	trasl = !trasl;
	rota = false;
	if (trasl) escal = true;
	transf = trasl || rota || escal;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateTransformaTraslacio(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (trasl) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CEntornVGIView::OnTransformaOrigentraslacio()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if (trasl)
	{
		fact_Tras = 1;
		TG.VTras.x = 0.0;	TG.VTras.y = 0.0;	TG.VTras.z = 0;
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


// TRANSFORMA: ROTACI�
void CEntornVGIView::OnTransformaRotacio()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	rota = !rota;
	trasl = false;
	if (rota) escal = true;
	transf = trasl || rota || escal;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateTransformaRotacio(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (rota) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CEntornVGIView::OnTransformaOrigenrotacio()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if (rota)
	{
		fact_Rota = 90;
		TG.VRota.x = 0;		TG.VRota.y = 0;		TG.VRota.z = 0;
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


// TRANSFORMA: ESCALAT
void CEntornVGIView::OnTransformaEscalat()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if ((!rota) && (!trasl)) escal = !escal;
	transf = trasl || rota || escal;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateTransformaEscalat(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (escal) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


void CEntornVGIView::OnTransformaOrigenescalat()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if (escal) { TG.VScal.x = 1;	TG.VScal.y = 1;	TG.VScal.z = 1; }

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


// TRANSFOMA: M�bil Eix X? (opci� booleana).
void CEntornVGIView::OnTransformaMobilx()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if (transf)
	{
		transX = !transX;
		if (transX) {
			mobil = false;	zzoom = false;
			pan = false;	navega = false;
		}
		else if ((!transY) && (!transZ)) {
			mobil = true;
			zzoom = true;
		}
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateTransformaMobilx(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (transX) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// TRANSFOMA: M�bil Eix Y? (opci� booleana).
void CEntornVGIView::OnTransformaMobily()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if (transf)
	{
		transY = !transY;
		if (transY) {
			mobil = false;	zzoom = false;
			pan = false;	navega = false;
		}
		else if ((!transX) && (!transZ)) {
			mobil = true;
			zzoom = true;
		}
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateTransformaMobily(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (transY) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// TRANSFOMA: M�bil Eix Z? (opci� booleana).
void CEntornVGIView::OnTransformaMobilz()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	if (transf)
	{
		transZ = !transZ;
		if (transZ) {
			mobil = false;	zzoom = false;
			pan = false;	navega = false;
		}
		else if ((!transX) && (!transY)) {
			mobil = true;
			zzoom = true;
		}
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateTransformaMobilz(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (transZ) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


/* ------------------------------------------------------------------------- */
/*					7. OCULTACIONS											 */
/* ------------------------------------------------------------------------- */



void CEntornVGIView::OnOcultacionsFrontFaces()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	front_faces = !front_faces;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateOcultacionsFrontFaces(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (front_faces) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// OCULTACIONS: Test de Visibilitat? (opci� booleana).
void CEntornVGIView::OnOcultacionsTestvis()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	test_vis = !test_vis;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateOcultacionsTestvis(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (test_vis) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// OCULTACIONS: Z-Buffer? (opci� booleana).
void CEntornVGIView::OnOcultacionsZbuffer()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	oculta = !oculta;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateOcultacionsZbuffer(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (oculta) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// OCULTACIONS: Back Line? (opci� booleana).
void CEntornVGIView::OnOcultacionsBackline()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	back_line = !back_line;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateOcultacionsBackline(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (back_line) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


/* ------------------------------------------------------------------------- */
/*					8. IL.LUMINACI�											 */
/* ------------------------------------------------------------------------- */

// IL.LUMINACI� Font de llum fixe? (opci� booleana).
void CEntornVGIView::OnIluminacioLlumfixe()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	ifixe = !ifixe;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateIluminacioLlumfixe(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (ifixe) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// IL.LUMINACI�: Mantenir iluminades les Cares Front i Back
void CEntornVGIView::OnIluminacio2Sides()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	ilum2sides = !ilum2sides;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateIluminacio2Sides(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (ilum2sides) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}



// ILUMINACI� PUNTS
void CEntornVGIView::OnIluminacioPunts()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	ilumina = PUNTS;
	test_vis = false;		oculta = false;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateIluminacioPunts(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (ilumina == PUNTS) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// ILUMINACI� FILFERROS
void CEntornVGIView::OnIluminacioFilferros()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	ilumina = FILFERROS;
	test_vis = false;		oculta = false;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateIluminacioFilferros(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (ilumina == FILFERROS) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// ILUMINACI� PLANA
void CEntornVGIView::OnIluminacioPlana()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	ilumina = PLANA;
	test_vis = false;		oculta = true;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);

}

void CEntornVGIView::OnUpdateIluminacioPlana(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (ilumina == PLANA) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// ILUMINACI� GOURAUD
void CEntornVGIView::OnIluminacioGouraud()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	ilumina = GOURAUD;
	test_vis = false;		oculta = true;

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);

}

void CEntornVGIView::OnUpdateIluminacioGouraud(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (ilumina == GOURAUD) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// ILUMINACI�->REFLECTIVITAT MATERIAL EMISSI�: Activaci� i desactivaci� de la reflectivitat pr�pia del material.
void CEntornVGIView::OnMaterialEmissio()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	sw_material[0] = !sw_material[0];

	if (shader_menu != CAP_SHADER) {
		// Entorn VGI: Activaci� del contexte OpenGL
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
		// Pas m�scara llums
		glUniform1i(glGetUniformLocation(shader_program, "sw_intensity[0]"), sw_material[0]);
		// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
		wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateMaterialEmissio(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (sw_material[0])	pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// ILUMINACI�->REFLECTIVITAT MATERIAL AMBIENT: Activaci� i desactivaci� de la reflectivitat ambient del material.
void CEntornVGIView::OnMaterialAmbient()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	sw_material[1] = !sw_material[1];

	if (shader_menu != CAP_SHADER) {
		// Entorn VGI: Activaci� del contexte OpenGL
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
		// Pas m�scara llums
		glUniform1i(glGetUniformLocation(shader_program, "sw_intensity[1]"), sw_material[1]);
		// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
		wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateMaterialAmbient(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (sw_material[1])	pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// ILUMINACI�->REFLECTIVITAT MATERIAL DIFUSA: Activaci� i desactivaci� de la reflectivitat difusa del materials.
void CEntornVGIView::OnMaterialDifusa()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	sw_material[2] = !sw_material[2];

	if (shader_menu != CAP_SHADER) {
		// Entorn VGI: Activaci� del contexte OpenGL
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
		// Pas m�scara llums
		glUniform1i(glGetUniformLocation(shader_program, "sw_intensity[2]"), sw_material[2]);
		// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
		wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateMaterialDifusa(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (sw_material[2])	pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// ILUMINACI�->REFLECTIVITAT MATERIAL ESPECULAR: Activaci� i desactivaci� de la reflectivitat especular del material.
void CEntornVGIView::OnMaterialEspecular()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	sw_material[3] = !sw_material[3];

	if (shader_menu != CAP_SHADER) {
		// Entorn VGI: Activaci� del contexte OpenGL
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
		// Pas m�scara llums
		glUniform1i(glGetUniformLocation(shader_program, "sw_intensity[3]"), sw_material[3]);
		// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
		wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateMaterialEspecular(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (sw_material[3])	pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// ILUMINACI�: Textures?: Activaci� (TRUE) o desactivaci� (FALSE) de textures.
void CEntornVGIView::OnIluminacioTextures()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	textura = !textura;

	// Entorn VGI: Activaci� del contexte OpenGL
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	//	Pas de textura al shader
	if (shader_menu != CAP_SHADER) glUniform1i(glGetUniformLocation(shader_program, "texture"), textura);

	// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
	wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateIluminacioTextures(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (textura) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// IL.LUMINACI�->TEXTURA TEXTURES PREDEFINIDES
// TEXTURA Fusta
// TEXTURA Marbre
// TEXTURA Metall


void CEntornVGIView::OnIluminacioTexturaFitxerimatge()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	CString nomf;
	t_textura = FITXERIMA;

	// Obrir di�leg de lectura de fitxer
	CFileDialog openTextur(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("JPG Files(*.jpg)|*.jpg|Error Files (*.err)|*err|All Files (*.*)|*.*||"));;

	if (openTextur.DoModal() != IDOK)	return;                 // stay with old data file
	else nomf = openTextur.GetPathName();

	// Conversi� de la variable CString nom a la variable char *nomfitx, 
	//		compatible amb  les funcions de c�rrega de fitxers textura
	char* nomfitx = CString2Char(nomf);

	// Entorn VGI: Activaci� el contexte OpenGL
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	texturesID[0] = loadIMA_SOIL(nomfitx);

	//	Pas de textura al shader
	if (shader_menu != CAP_SHADER) glUniform1i(glGetUniformLocation(shader_program, "texture0"), GLint(0));

	// Desactivaci� contexte OpenGL: Permet la coexistencia d'altres contextes de generaci�
	wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateIluminacioTexturaFitxerimatge(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (t_textura == FITXERIMA) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


/* ------------------------------------------------------------------------- */
/*					9. LLUMS												 */
/* ------------------------------------------------------------------------- */

// LLUMS: Activaci� / Desactivaci� llum ambient 
void CEntornVGIView::OnLlumsLlumambient()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	llum_ambient = !llum_ambient;

	if (shader_menu != CAP_SHADER) {
		// Entorn VGI: Activaci� del contexte OpenGL
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
		// Pas m�scara llums
		glUniform1i(glGetUniformLocation(shader_program, "sw_intensity[1]"), (llum_ambient && sw_material[1]));
		// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
		wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateLlumsLlumambient(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (llum_ambient) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// LLUMS: Activaci� /Desactivaci� llum 0 (GL_LIGHT0)
void CEntornVGIView::OnLlumsLlum0()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	llumGL[0].encesa = !llumGL[0].encesa;

	if (shader_menu != CAP_SHADER) {
		// Entorn VGI: Activaci� del contexte OpenGL
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
		// Pas m�scara llums
		glUniform1i(glGetUniformLocation(shader_program, "sw_lights[0]"), llumGL[0].encesa);
		// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
		wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateLlumsLlum0(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (llumGL[0].encesa) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// LLUMS-->ON/OFF: Activaci� /Desactivaci� llum 1 (GL_LIGHT1)
void CEntornVGIView::OnLlumsLlum1()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	llumGL[1].encesa = !llumGL[1].encesa;

	if (shader_menu != CAP_SHADER) {
		// Entorn VGI: Activaci� del contexte OpenGL
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
		// Pas m�scara llums
		glUniform1i(glGetUniformLocation(shader_program, "sw_lights[1]"), llumGL[1].encesa);
		// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
		wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateLlumsLlum1(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (llumGL[1].encesa) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// LLUMS-->ON/OFF: Activaci� /Desactivaci� llum 2 (GL_LIGHT2)
void CEntornVGIView::OnLlumsLlum2()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	llumGL[2].encesa = !llumGL[2].encesa;

	if (shader_menu != CAP_SHADER) {
		// Entorn VGI: Activaci� del contexte OpenGL
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
		// Pas m�scara llums
		glUniform1i(glGetUniformLocation(shader_program, "sw_lights[2]"), llumGL[2].encesa);
		// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
		wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateLlumsLlum2(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (llumGL[2].encesa) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// LLUMS-->ON/OFF: Activaci� /Desactivaci� llum 3 (GL_LIGHT3)
void CEntornVGIView::OnLlumsLlum3()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	llumGL[3].encesa = !llumGL[3].encesa;
	sw_il = true;

	if (shader_menu != CAP_SHADER) {
		// Entorn VGI: Activaci� del contexte OpenGL
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
		// Pas m�scara llums
		glUniform1i(glGetUniformLocation(shader_program, "sw_lights[3]"), llumGL[3].encesa);
		// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
		wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateLlumsLlum3(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (llumGL[3].encesa) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// LLUMS-->ON/OFF: Activaci� /Desactivaci� llum 4 (GL_LIGHT4)
void CEntornVGIView::OnLlumsLlum4()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	llumGL[4].encesa = !llumGL[4].encesa;
	sw_il = true;

	if (shader_menu != CAP_SHADER) {
		// Entorn VGI: Activaci� del contexte OpenGL
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
		// Pas m�scara llums
		glUniform1i(glGetUniformLocation(shader_program, "sw_lights[4]"), llumGL[4].encesa);
		// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
		wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);
	}

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateLlumsLlum4(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (llumGL[4].encesa) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


/* ------------------------------------------------------------------------- */
/*					10. SHADERS												 */
/* ------------------------------------------------------------------------- */

// SHADERS: Desactivaci� de tots els shaders
void CEntornVGIView::OnShadersSense()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	shader_menu = CAP_SHADER;
	releaseAllShaders();

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}

void CEntornVGIView::OnUpdateShadersSense(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (shader_menu == CAP) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// SHADERS: Iluminaci� Gouraud amb Shaders
void CEntornVGIView::OnShadersGouraud()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	bool apagat = false;
	if (sw_shader) releaseAllShaders();
	else sw_shader = true;
	shader_menu = GOURAUD_SHADER;

	// Entorn VGI: Activaci� del contexte OpenGL
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	shader_program = initializeShaders(_T("./shaders/gouraud_shdrML"));

	glUniform1i(glGetUniformLocation(shader_program, "texture"), textura);
	glUniform1i(glGetUniformLocation(shader_program, "texture0"), GLint(0));
	// Pas m�scara reflectivitat
	glUniform1i(glGetUniformLocation(shader_program, "sw_intensity[0]"), sw_material[0]);
	glUniform1i(glGetUniformLocation(shader_program, "sw_intensity[1]"), sw_material[1]);
	glUniform1i(glGetUniformLocation(shader_program, "sw_intensity[2]"), sw_material[2]);
	glUniform1i(glGetUniformLocation(shader_program, "sw_intensity[3]"), sw_material[3]);
	//Pas m�scara llums
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[0]"), llumGL[0].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[1]"), llumGL[1].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[2]"), llumGL[2].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[3]"), llumGL[3].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[4]"), llumGL[4].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[5]"), llumGL[5].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[6]"), llumGL[6].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[7]"), llumGL[7].encesa);

	// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
	wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateShadersGouraud(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (shader_menu == GOURAUD_SHADER) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// SHADERS: Iluminaci� Phong amb Shaders
void CEntornVGIView::OnShadersPhong()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	bool apagat = false;
	if (sw_shader) releaseAllShaders();		// Eliminar Programs previs
	else sw_shader = true;
	shader_menu = PHONG_SHADER;

	// Entorn VGI: Activaci� del contexte OpenGL
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	// Carregar shaders phong_shdrML.vert i phong_shdrML.frag en Program shader_program
	shader_program = initializeShaders(_T("./shaders/phong_shdrML"));

	// Linkar uniform variables amb variables C++
	glUniform1i(glGetUniformLocation(shader_program, "texture"), textura);
	glUniform1i(glGetUniformLocation(shader_program, "texture0"), GLint(0));
	// Pas m�scara reflectivitat
	glUniform1i(glGetUniformLocation(shader_program, "sw_intensity[0]"), sw_material[0]);
	glUniform1i(glGetUniformLocation(shader_program, "sw_intensity[1]"), sw_material[1]);
	glUniform1i(glGetUniformLocation(shader_program, "sw_intensity[2]"), sw_material[2]);
	glUniform1i(glGetUniformLocation(shader_program, "sw_intensity[3]"), sw_material[3]);
	//Pas m�scara llums
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[0]"), llumGL[0].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[1]"), llumGL[1].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[2]"), llumGL[2].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[3]"), llumGL[3].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[4]"), llumGL[4].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[5]"), llumGL[5].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[6]"), llumGL[6].encesa);
	glUniform1i(glGetUniformLocation(shader_program, "sw_lights[7]"), llumGL[7].encesa);

	// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
	wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateShadersPhong(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (shader_menu == PHONG_SHADER) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}


// SHADERS: C�rrega Fitxers Shader
void CEntornVGIView::OnShaderLoadFiles()
{
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	CString nomVert, nomFrag;

	if (sw_shader) releaseAllShaders();
	else sw_shader = true;
	shader_menu = FILE_SHADER;

	// C�rrega fitxer VERT
	// Entorn VGI: Obrir di�leg de lectura de fitxer (fitxers (*.VERT)
	CFileDialog openVert(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("VERT Files(*.vert)|*.vert|All Files (*.*)|*.*||"));;

	if (openVert.DoModal() != IDOK)
		return;                 // stay with old data file
	else nomVert = openVert.GetPathName();
	// Entorn VGI: Variable de tipus CString 'nomVert' cont� el nom del fitxer seleccionat

	// Entorn VGI: Conversi� de la variable CString nom a la variable char *nomfitx, 
	//		compatible amb  les funcions de c�rrega de fitxers fractals
	//	char *nomfitxV = CString2Char(nomVert);

	// C�rrega fitxer FRAG
	// Entorn VGI: Obrir di�leg de lectura de fitxer (fitxers (*.VERT)
	CFileDialog openFrag(TRUE, NULL, NULL,
		OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_T("FRAG Files(*.frag)|*.frag|All Files (*.*)|*.*||"));;

	if (openFrag.DoModal() != IDOK)
		return;                 // stay with old data file
	else nomFrag = openFrag.GetPathName();
	// Entorn VGI: Variable de tipus CString 'nomFrag' cont� el nom del fitxer seleccionat

// Entorn VGI: Conversi� de la variable CString nom a la variable char *nomfitx, 
//		compatible amb  les funcions de c�rrega de fitxers fractals
//	char *nomfitxF = CString2Char(nomFrag);

// Entorn VGI: Activaci� del contexte OpenGL
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	shader_program = loadFileShaders(nomVert, nomFrag);

	//	shader_program = initializeShaders(_T("./shaders/gouraud_shdrML"));

	glUniform1i(glGetUniformLocation(shader_program, "texture"), textura);
	glUniform1i(glGetUniformLocation(shader_program, "texture0"), GLint(0));

	// Entorn VGI: Desactivaci� del contexte OpenGL. Permet la coexistencia d'altres contextes de generaci�
	wglMakeCurrent(m_pDC->GetSafeHdc(), NULL);

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);

}


void CEntornVGIView::OnUpdateShaderLoadFiles(CCmdUI* pCmdUI)
{
	// TODO: Agregue aqu� su c�digo de controlador de IU para actualizaci�n de comandos
	if (shader_menu == FILE_SHADER) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}



/* ------------------------------------------------------------------------- */
/*   RECURSOS DE BOTONS (ToolBar) DE L'APLICACIO                             */
/* ------------------------------------------------------------------------- */
// Incloure funcions de tractament de botons


// ---------------- Entorn VGI: Funcions locals a EntornVGIView.cpp

// Log2: C�lcul del log base 2 de num
int CEntornVGIView::Log2(int num)
{
	int tlog;

	if (num >= 8192) tlog = 13;
	else if (num >= 4096) tlog = 12;
	else if (num >= 2048) tlog = 11;
	else if (num >= 1024) tlog = 10;
	else if (num >= 512) tlog = 9;
	else if (num >= 256) tlog = 8;
	else if (num >= 128) tlog = 7;
	else if (num >= 64) tlog = 6;
	else if (num >= 32) tlog = 5;
	else if (num >= 16) tlog = 4;
	else if (num >= 8) tlog = 3;
	else if (num >= 4) tlog = 2;
	else if (num >= 2) tlog = 1;
	else tlog = 0;

	return tlog;
}


// CString2char: Funci� de conversi� de variable CString a char * per a noms de fitxers 
char* CEntornVGIView::CString2Char(CString entrada)
{
	//char * par_sortida=" ";
	// Variable de tipus CString 'entrada' cont� un string tipus CString
	//-------------------------------------------------------------------------------------
	// Conversi� de la variable CString entrada a la variable char *sortida, 
	//	compatible amb la funci� Carregar3DS, de c�rrega de fitxers 3DS
	//	char * nomfitx = (char *)(LPCTSTR)nom;

	// Conversi� variable w_char --> char *
	//	char *nomf="  ";
	//	wcstombs(nomf,strFileName.GetBuffer(3),90);
	//	char *nomf = reinterpret_cast<char *> (nom.GetBuffer(3));

	size_t origsize = wcslen(entrada.GetBuffer(3)) + 1;
	size_t convertedChars = 0;

	// Use a multibyte string to append the type of string
	// to the new string before displaying the result.
	char strConcat[] = " (char *)";
	size_t strConcatsize = (strlen(strConcat) + 1) * 2;

	// Allocate two bytes in the multibyte output string for every wide
	// character in the input string (including a wide character
	// null). Because a multibyte character can be one or two bytes,
	// you should allot two bytes for each character. Having extra
	// space for the new string is not an error, but having
	// insufficient space is a potential security problem.
	const size_t newsize = origsize * 2;
	// The new string will contain a converted copy of the original
	// string plus the type of string appended to it.
	//	char *nomfitx = new char[newsize + strConcatsize];
	char* par_sortida = new char[newsize + strConcatsize];

	// Put a copy of the converted string into nstring
	wcstombs_s(&convertedChars, par_sortida, newsize, entrada.GetBuffer(3), _TRUNCATE);
	// append the type of string to the new string.
	//----------------------------------------------------------------------------------

	// Variable de tipus char *nomfitx cont� el nom del fitxer seleccionat
	return par_sortida;
}


// Refl_MaterialOff: Desactivar Reflexi� de Material
void CEntornVGIView::Refl_MaterialOff()
{
	sw_material_old[0] = sw_material[0];	sw_material[0] = false;
	sw_material_old[1] = sw_material[1];	sw_material[1] = false;
	sw_material_old[2] = sw_material[2];	sw_material[2] = false;
	sw_material_old[3] = sw_material[3];	sw_material[3] = false;
}

// Refl_MaterialOn: Activar Reflexi� de Material
void CEntornVGIView::Refl_MaterialOn()
{
	sw_material[0] = sw_material_old[0];
	sw_material[1] = sw_material_old[1];
	sw_material[2] = sw_material_old[2];
	sw_material[3] = sw_material_old[3];
}


// -------------------- FUNCIONS CORBES SPLINE i BEZIER

// llegir_ptsC: Llegir punts de control de corba (spline o Bezier) d'un fitxer .crv. 
//				Retorna el nombre de punts llegits en el fitxer.
//int llegir_pts(CString nomf)
int CEntornVGIView::llegir_ptsC(char* nomf)
{
	int i, j;
	FILE* fd;

	// Inicialitzar vector punts de control de la corba spline
	for (i = 0; i < MAX_PATCH_CORBA; i = i++)
	{
		PC_t[i].x = 0.0;
		PC_t[i].y = 0.0;
		PC_t[i].z = 0.0;
	}

	//	ifstream f("altinicials.dat",ios::in);
	//    f>>i; f>>j;
	if ((fd = fopen(nomf, "rt")) == NULL)
	{
		LPCWSTR texte1 = reinterpret_cast<LPCWSTR> ("ERROR:");
		LPCWSTR texte2 = reinterpret_cast<LPCWSTR> ("File .crv was not opened");
		//MessageBox(NULL, texte1, texte2, MB_OK);
		MessageBox(texte1, texte2, MB_OK);
		//AfxMessageBox("file was not opened");
		return false;
	}
	fscanf(fd, "%d \n", &i);
	if (i == 0) return false;
	else {
		for (j = 0; j < i; j = j++)
		{	//fscanf(fd, "%f", &corbaSpline[j].x);
			//fscanf(fd, "%f", &corbaSpline[j].y);
			//fscanf(fd, "%f \n", &corbaSpline[j].z);
			fscanf(fd, "%f %f %f \n", &PC_t[j].x, &PC_t[j].y, &PC_t[j].z);

		}
	}
	fclose(fd);

	return i;
}

void CEntornVGIView::OnProjeccioortografica()
{
	projeccio = ORTO;
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateProjeccioortografica(CCmdUI* pCmdUI)
{
	if (projeccio == ORTO) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}

void CEntornVGIView::OnObjecteMur()
{
	// TODO: Agregue aquí su código de controlador de comandos
	objecte = MUR;	textura = true;
	//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
	//	Canviar l'escala per a centrar la vista (Ortogràfica)
	// Crida a OnPaint() per redibuixar l'escena
	//InvalidateRect(NULL, false);
	// TODO: Agregue aqu� su c�digo de controlador de comandos
	//objecte = CUB_RGB;   textura = true;

	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	//Textures skybox
	texturesID[9] = loadIMA_ILUT("./textures/tex1_64x64_c05e3c09362f364a_14.png");
	texturesID[8] = loadIMA_ILUT("./textures/tex1_128x128_0e437d36eaf137df_14.png");
	texturesID[7] = loadIMA_ILUT("./textures/sky-hd-wallpaper-9.jpg");
	texturesID[10] = loadIMA_ILUT("./textures/skybox/right.png");
	texturesID[11] = loadIMA_ILUT("./textures/skybox/left.png");
	texturesID[12] = loadIMA_ILUT("./textures/skybox/top.png");
	texturesID[13] = loadIMA_ILUT("./textures/skybox/bottom.png");
	texturesID[14] = loadIMA_ILUT("./textures/skybox/front.png");
	texturesID[15] = loadIMA_ILUT("./textures/skybox/back.png");

	//shrek
	texturesID[16] = loadIMA_ILUT("./textures/shrek/Shrek.png");
	texturesID[17] = loadIMA_ILUT("./textures/shrek/shrekshirt.png");
	loader[0].LoadFile("./objects/shrek/CHARACTER_Shrek.obj");

	//punxes
	loader[1].LoadFile("./objects/punxes/3d-model.obj");

	//taula
	texturesID[18] = loadIMA_ILUT("./objects/taula/light_wood.png");
	loader[2].LoadFile("./objects/taula/simple_table.obj");
	//balloon
	loader[3].LoadFile("./objects/balloon/balloon.obj");
	texturesID[19] = loadIMA_ILUT("./objects/balloon/shrekcolorballoon.png");


	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	//  Modificar R per centrar la Vista a la mida de l'objecte (Perspectiva)
	//	Canviar l'escala per a centrar la vista (Ortogr�fica)

	// Crida a OnPaint() per redibuixar l'escena
	InvalidateRect(NULL, false);
}


void CEntornVGIView::OnUpdateObjecteMur(CCmdUI* pCmdUI)
{
	// TODO: Agregue aquí su código de controlador de IU para actualización de comandos
	// TODO: Agregue aquí su código de controlador de IU para actualización de comandos
	if (objecte == MUR) pCmdUI->SetCheck(1);
	else pCmdUI->SetCheck(0);
}
