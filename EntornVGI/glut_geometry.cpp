//******** PRACTICA VISUALITZACIÓ GRÀFICA INTERACTIVA (Escola Enginyeria - UAB)
//******** Entorn bàsic VS2019 MULTIFINESTRA amb interfície MFC, Status Bar i primitives GLUT en codi font
//******** Ferran Poveda, Marc Vivet, Carme Julià, Débora Gil, Enric Martí (Setembre 2019)
// glut_geometry.cpp : Codi font de les primitives gràfiques freeglut i GLU adaptades a VS2019.
// FUNCIONS:		- Primitives sòlides (glutSolid<primitiva>)
//					- Primitives filferros (glutWire<primitiva>)
//					- Primitives punts (glutPoint<primitiva>)
//					- Interficie de primitives (glet<primitiva>)
//					- Primitives sòlides (gluCilindre, gluDisc, GluParcialDisc, GluEsfera)

/*
* glut_geometry.cpp
 *
 * Codi adaptat de Freeglut geometry rendering methods.
 *
 * Copyright (c) 2017 Nosferatu Software. All Rights Reserved.
 * Adaptat per Enric Martí Gòdia, <enric.marti@uab.cat>
 * Creation date: Dimarts 9 Maig 2017
 * Update date: Dimarts 28 Novembre 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "stdafx.h"
#include "glut_geometry.h"

/*
 * TODO BEFORE THE STABLE RELEASE:
 *
 * Following functions have been contributed by Andreas Umbach.
 *
 *      glutWireCube()          -- looks OK
 *      glutSolidCube()         -- OK
 *
 * Those functions have been implemented by John Fay.
 *
 *      glutWireTorus()         -- looks OK
 *      glutSolidTorus()        -- looks OK
 *      glutWireDodecahedron()  -- looks OK
 *      glutSolidDodecahedron() -- looks OK
 *      glutWireOctahedron()    -- looks OK
 *      glutSolidOctahedron()   -- looks OK
 *      glutWireTetrahedron()   -- looks OK
 *      glutSolidTetrahedron()  -- looks OK
 *      glutWireIcosahedron()   -- looks OK
 *      glutSolidIcosahedron()  -- looks OK
 *
 *  The Following functions have been updated by Nigel Stewart, based
 *  on FreeGLUT 2.0.0 implementations:
 *
 *      glutWireSphere()        -- looks OK
 *      glutSolidSphere()       -- looks OK
 *      glutWireCone()          -- looks OK
 *      glutSolidCone()         -- looks OK

 *  The Following functions have been updated by Enric Martí, based
 *  on GLU 9.0.0 implementations (include texture coordinates):
 *
 *      gluCilindre()			-- looks OK
 *      gluDisc()				-- looks OK
 *      gluParcialDisc()       -- looks OK
 *      gluEsfera()			-- looks OK
 */


/* -- INTERFACE FUNCTIONS -------------------------------------------------- */
/* ----------CUBE -----------------------------------------------------------*/

/*
 * Draws a solid cube. Code contributed by Andreas Umbach <marvin@dataway.ch>
 */

static const GLubyte Fixed8x13_Character_000[] = { 8,  0,  0,  0,170,  0,130,  0,130,  0,130,  0,170,  0,  0 };
static const GLubyte Fixed8x13_Character_001[] = { 8,  0,  0,  0,  0, 16, 56,124,254,124, 56, 16,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_002[] = { 8,  0,170, 85,170, 85,170, 85,170, 85,170, 85,170, 85,170 };
static const GLubyte Fixed8x13_Character_003[] = { 8,  0,  0,  0,  4,  4,  4,  4,174,160,224,160,160,  0,  0 };
static const GLubyte Fixed8x13_Character_004[] = { 8,  0,  0,  0,  8,  8, 12,  8,142,128,192,128,224,  0,  0 };
static const GLubyte Fixed8x13_Character_005[] = { 8,  0,  0,  0, 10, 10, 12, 10,108,128,128,128, 96,  0,  0 };
static const GLubyte Fixed8x13_Character_006[] = { 8,  0,  0,  0,  8,  8, 12,  8,238,128,128,128,128,  0,  0 };
static const GLubyte Fixed8x13_Character_007[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0, 24, 36, 36, 24,  0,  0 };
static const GLubyte Fixed8x13_Character_008[] = { 8,  0,  0,  0,  0,124,  0, 16, 16,124, 16, 16,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_009[] = { 8,  0,  0,  0, 14,  8,  8,  8,168,160,160,160,192,  0,  0 };
static const GLubyte Fixed8x13_Character_010[] = { 8,  0,  0,  0,  4,  4,  4,  4, 46, 80, 80,136,136,  0,  0 };
static const GLubyte Fixed8x13_Character_011[] = { 8,  0,  0,  0,  0,  0,  0,  0,240, 16, 16, 16, 16, 16, 16 };
static const GLubyte Fixed8x13_Character_012[] = { 8,  0, 16, 16, 16, 16, 16, 16,240,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_013[] = { 8,  0, 16, 16, 16, 16, 16, 16, 31,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_014[] = { 8,  0,  0,  0,  0,  0,  0,  0, 31, 16, 16, 16, 16, 16, 16 };
static const GLubyte Fixed8x13_Character_015[] = { 8,  0, 16, 16, 16, 16, 16, 16,255, 16, 16, 16, 16, 16, 16 };
static const GLubyte Fixed8x13_Character_016[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255 };
static const GLubyte Fixed8x13_Character_017[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_018[] = { 8,  0,  0,  0,  0,  0,  0,  0,255,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_019[] = { 8,  0,  0,  0,  0,255,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_020[] = { 8,  0,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_021[] = { 8,  0, 16, 16, 16, 16, 16, 16, 31, 16, 16, 16, 16, 16, 16 };
static const GLubyte Fixed8x13_Character_022[] = { 8,  0, 16, 16, 16, 16, 16, 16,240, 16, 16, 16, 16, 16, 16 };
static const GLubyte Fixed8x13_Character_023[] = { 8,  0,  0,  0,  0,  0,  0,  0,255, 16, 16, 16, 16, 16, 16 };
static const GLubyte Fixed8x13_Character_024[] = { 8,  0, 16, 16, 16, 16, 16, 16,255,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_025[] = { 8,  0, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16 };
static const GLubyte Fixed8x13_Character_026[] = { 8,  0,  0,  0,254,  0, 14, 48,192, 48, 14,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_027[] = { 8,  0,  0,  0,254,  0,224, 24,  6, 24,224,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_028[] = { 8,  0,  0,  0, 68, 68, 68, 68, 68,254,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_029[] = { 8,  0,  0,  0, 32, 32,126, 16,  8,126,  4,  4,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_030[] = { 8,  0,  0,  0,220, 98, 32, 32, 32,112, 32, 34, 28,  0,  0 };
static const GLubyte Fixed8x13_Character_031[] = { 8,  0,  0,  0,  0,  0,  0,  0, 24,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_032[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_033[] = { 8,  0,  0,  0, 16,  0, 16, 16, 16, 16, 16, 16, 16,  0,  0 };
static const GLubyte Fixed8x13_Character_034[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0,  0, 36, 36, 36,  0,  0 };
static const GLubyte Fixed8x13_Character_035[] = { 8,  0,  0,  0,  0, 36, 36,126, 36,126, 36, 36,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_036[] = { 8,  0,  0,  0, 16,120, 20, 20, 56, 80, 80, 60, 16,  0,  0 };
static const GLubyte Fixed8x13_Character_037[] = { 8,  0,  0,  0, 68, 42, 36, 16,  8,  8, 36, 82, 34,  0,  0 };
static const GLubyte Fixed8x13_Character_038[] = { 8,  0,  0,  0, 58, 68, 74, 48, 72, 72, 48,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_039[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 48, 56,  0,  0 };
static const GLubyte Fixed8x13_Character_040[] = { 8,  0,  0,  0,  4,  8,  8, 16, 16, 16,  8,  8,  4,  0,  0 };
static const GLubyte Fixed8x13_Character_041[] = { 8,  0,  0,  0, 32, 16, 16,  8,  8,  8, 16, 16, 32,  0,  0 };
static const GLubyte Fixed8x13_Character_042[] = { 8,  0,  0,  0,  0,  0, 36, 24,126, 24, 36,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_043[] = { 8,  0,  0,  0,  0,  0, 16, 16,124, 16, 16,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_044[] = { 8,  0,  0, 64, 48, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_045[] = { 8,  0,  0,  0,  0,  0,  0,  0,126,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_046[] = { 8,  0,  0, 16, 56, 16,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_047[] = { 8,  0,  0,  0,128,128, 64, 32, 16,  8,  4,  2,  2,  0,  0 };
static const GLubyte Fixed8x13_Character_048[] = { 8,  0,  0,  0, 24, 36, 66, 66, 66, 66, 66, 36, 24,  0,  0 };
static const GLubyte Fixed8x13_Character_049[] = { 8,  0,  0,  0,124, 16, 16, 16, 16, 16, 80, 48, 16,  0,  0 };
static const GLubyte Fixed8x13_Character_050[] = { 8,  0,  0,  0,126, 64, 32, 24,  4,  2, 66, 66, 60,  0,  0 };
static const GLubyte Fixed8x13_Character_051[] = { 8,  0,  0,  0, 60, 66,  2,  2, 28,  8,  4,  2,126,  0,  0 };
static const GLubyte Fixed8x13_Character_052[] = { 8,  0,  0,  0,  4,  4,126, 68, 68, 36, 20, 12,  4,  0,  0 };
static const GLubyte Fixed8x13_Character_053[] = { 8,  0,  0,  0, 60, 66,  2,  2, 98, 92, 64, 64,126,  0,  0 };
static const GLubyte Fixed8x13_Character_054[] = { 8,  0,  0,  0, 60, 66, 66, 98, 92, 64, 64, 32, 28,  0,  0 };
static const GLubyte Fixed8x13_Character_055[] = { 8,  0,  0,  0, 32, 32, 16, 16,  8,  8,  4,  2,126,  0,  0 };
static const GLubyte Fixed8x13_Character_056[] = { 8,  0,  0,  0, 60, 66, 66, 66, 60, 66, 66, 66, 60,  0,  0 };
static const GLubyte Fixed8x13_Character_057[] = { 8,  0,  0,  0, 56,  4,  2,  2, 58, 70, 66, 66, 60,  0,  0 };
static const GLubyte Fixed8x13_Character_058[] = { 8,  0,  0, 16, 56, 16,  0,  0, 16, 56, 16,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_059[] = { 8,  0,  0, 64, 48, 56,  0,  0, 16, 56, 16,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_060[] = { 8,  0,  0,  0,  2,  4,  8, 16, 32, 16,  8,  4,  2,  0,  0 };
static const GLubyte Fixed8x13_Character_061[] = { 8,  0,  0,  0,  0,  0,126,  0,  0,126,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_062[] = { 8,  0,  0,  0, 64, 32, 16,  8,  4,  8, 16, 32, 64,  0,  0 };
static const GLubyte Fixed8x13_Character_063[] = { 8,  0,  0,  0,  8,  0,  8,  8,  4,  2, 66, 66, 60,  0,  0 };
static const GLubyte Fixed8x13_Character_064[] = { 8,  0,  0,  0, 60, 64, 74, 86, 82, 78, 66, 66, 60,  0,  0 };
static const GLubyte Fixed8x13_Character_065[] = { 8,  0,  0,  0, 66, 66, 66,126, 66, 66, 66, 36, 24,  0,  0 };
static const GLubyte Fixed8x13_Character_066[] = { 8,  0,  0,  0,252, 66, 66, 66,124, 66, 66, 66,252,  0,  0 };
static const GLubyte Fixed8x13_Character_067[] = { 8,  0,  0,  0, 60, 66, 64, 64, 64, 64, 64, 66, 60,  0,  0 };
static const GLubyte Fixed8x13_Character_068[] = { 8,  0,  0,  0,252, 66, 66, 66, 66, 66, 66, 66,252,  0,  0 };
static const GLubyte Fixed8x13_Character_069[] = { 8,  0,  0,  0,126, 64, 64, 64,120, 64, 64, 64,126,  0,  0 };
static const GLubyte Fixed8x13_Character_070[] = { 8,  0,  0,  0, 64, 64, 64, 64,120, 64, 64, 64,126,  0,  0 };
static const GLubyte Fixed8x13_Character_071[] = { 8,  0,  0,  0, 58, 70, 66, 78, 64, 64, 64, 66, 60,  0,  0 };
static const GLubyte Fixed8x13_Character_072[] = { 8,  0,  0,  0, 66, 66, 66, 66,126, 66, 66, 66, 66,  0,  0 };
static const GLubyte Fixed8x13_Character_073[] = { 8,  0,  0,  0,124, 16, 16, 16, 16, 16, 16, 16,124,  0,  0 };
static const GLubyte Fixed8x13_Character_074[] = { 8,  0,  0,  0, 56, 68,  4,  4,  4,  4,  4,  4, 31,  0,  0 };
static const GLubyte Fixed8x13_Character_075[] = { 8,  0,  0,  0, 66, 68, 72, 80, 96, 80, 72, 68, 66,  0,  0 };
static const GLubyte Fixed8x13_Character_076[] = { 8,  0,  0,  0,126, 64, 64, 64, 64, 64, 64, 64, 64,  0,  0 };
static const GLubyte Fixed8x13_Character_077[] = { 8,  0,  0,  0,130,130,130,146,146,170,198,130,130,  0,  0 };
static const GLubyte Fixed8x13_Character_078[] = { 8,  0,  0,  0, 66, 66, 66, 70, 74, 82, 98, 66, 66,  0,  0 };
static const GLubyte Fixed8x13_Character_079[] = { 8,  0,  0,  0, 60, 66, 66, 66, 66, 66, 66, 66, 60,  0,  0 };
static const GLubyte Fixed8x13_Character_080[] = { 8,  0,  0,  0, 64, 64, 64, 64,124, 66, 66, 66,124,  0,  0 };
static const GLubyte Fixed8x13_Character_081[] = { 8,  0,  0,  2, 60, 74, 82, 66, 66, 66, 66, 66, 60,  0,  0 };
static const GLubyte Fixed8x13_Character_082[] = { 8,  0,  0,  0, 66, 68, 72, 80,124, 66, 66, 66,124,  0,  0 };
static const GLubyte Fixed8x13_Character_083[] = { 8,  0,  0,  0, 60, 66,  2,  2, 60, 64, 64, 66, 60,  0,  0 };
static const GLubyte Fixed8x13_Character_084[] = { 8,  0,  0,  0, 16, 16, 16, 16, 16, 16, 16, 16,254,  0,  0 };
static const GLubyte Fixed8x13_Character_085[] = { 8,  0,  0,  0, 60, 66, 66, 66, 66, 66, 66, 66, 66,  0,  0 };
static const GLubyte Fixed8x13_Character_086[] = { 8,  0,  0,  0, 16, 40, 40, 40, 68, 68, 68,130,130,  0,  0 };
static const GLubyte Fixed8x13_Character_087[] = { 8,  0,  0,  0, 68,170,146,146,146,130,130,130,130,  0,  0 };
static const GLubyte Fixed8x13_Character_088[] = { 8,  0,  0,  0,130,130, 68, 40, 16, 40, 68,130,130,  0,  0 };
static const GLubyte Fixed8x13_Character_089[] = { 8,  0,  0,  0, 16, 16, 16, 16, 16, 40, 68,130,130,  0,  0 };
static const GLubyte Fixed8x13_Character_090[] = { 8,  0,  0,  0,126, 64, 64, 32, 16,  8,  4,  2,126,  0,  0 };
static const GLubyte Fixed8x13_Character_091[] = { 8,  0,  0,  0, 60, 32, 32, 32, 32, 32, 32, 32, 60,  0,  0 };
static const GLubyte Fixed8x13_Character_092[] = { 8,  0,  0,  0,  2,  2,  4,  8, 16, 32, 64,128,128,  0,  0 };
static const GLubyte Fixed8x13_Character_093[] = { 8,  0,  0,  0,120,  8,  8,  8,  8,  8,  8,  8,120,  0,  0 };
static const GLubyte Fixed8x13_Character_094[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0,  0, 68, 40, 16,  0,  0 };
static const GLubyte Fixed8x13_Character_095[] = { 8,  0,  0,254,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_096[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4, 24, 56,  0,  0 };
static const GLubyte Fixed8x13_Character_097[] = { 8,  0,  0,  0, 58, 70, 66, 62,  2, 60,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_098[] = { 8,  0,  0,  0, 92, 98, 66, 66, 98, 92, 64, 64, 64,  0,  0 };
static const GLubyte Fixed8x13_Character_099[] = { 8,  0,  0,  0, 60, 66, 64, 64, 66, 60,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_100[] = { 8,  0,  0,  0, 58, 70, 66, 66, 70, 58,  2,  2,  2,  0,  0 };
static const GLubyte Fixed8x13_Character_101[] = { 8,  0,  0,  0, 60, 66, 64,126, 66, 60,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_102[] = { 8,  0,  0,  0, 32, 32, 32, 32,124, 32, 32, 34, 28,  0,  0 };
static const GLubyte Fixed8x13_Character_103[] = { 8,  0, 60, 66, 60, 64, 56, 68, 68, 58,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_104[] = { 8,  0,  0,  0, 66, 66, 66, 66, 98, 92, 64, 64, 64,  0,  0 };
static const GLubyte Fixed8x13_Character_105[] = { 8,  0,  0,  0,124, 16, 16, 16, 16, 48,  0, 16,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_106[] = { 8,  0, 56, 68, 68,  4,  4,  4,  4, 12,  0,  4,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_107[] = { 8,  0,  0,  0, 66, 68, 72,112, 72, 68, 64, 64, 64,  0,  0 };
static const GLubyte Fixed8x13_Character_108[] = { 8,  0,  0,  0,124, 16, 16, 16, 16, 16, 16, 16, 48,  0,  0 };
static const GLubyte Fixed8x13_Character_109[] = { 8,  0,  0,  0,130,146,146,146,146,236,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_110[] = { 8,  0,  0,  0, 66, 66, 66, 66, 98, 92,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_111[] = { 8,  0,  0,  0, 60, 66, 66, 66, 66, 60,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_112[] = { 8,  0, 64, 64, 64, 92, 98, 66, 98, 92,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_113[] = { 8,  0,  2,  2,  2, 58, 70, 66, 70, 58,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_114[] = { 8,  0,  0,  0, 32, 32, 32, 32, 34, 92,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_115[] = { 8,  0,  0,  0, 60, 66, 12, 48, 66, 60,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_116[] = { 8,  0,  0,  0, 28, 34, 32, 32, 32,124, 32, 32,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_117[] = { 8,  0,  0,  0, 58, 68, 68, 68, 68, 68,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_118[] = { 8,  0,  0,  0, 16, 40, 40, 68, 68, 68,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_119[] = { 8,  0,  0,  0, 68,170,146,146,130,130,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_120[] = { 8,  0,  0,  0, 66, 36, 24, 24, 36, 66,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_121[] = { 8,  0, 60, 66,  2, 58, 70, 66, 66, 66,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_122[] = { 8,  0,  0,  0,126, 32, 16,  8,  4,126,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_123[] = { 8,  0,  0,  0, 14, 16, 16,  8, 48,  8, 16, 16, 14,  0,  0 };
static const GLubyte Fixed8x13_Character_124[] = { 8,  0,  0,  0, 16, 16, 16, 16, 16, 16, 16, 16, 16,  0,  0 };
static const GLubyte Fixed8x13_Character_125[] = { 8,  0,  0,  0,112,  8,  8, 16, 12, 16,  8,  8,112,  0,  0 };
static const GLubyte Fixed8x13_Character_126[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0,  0, 72, 84, 36,  0,  0 };
static const GLubyte Fixed8x13_Character_127[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_128[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_129[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_130[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_131[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_132[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_133[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_134[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_135[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_136[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_137[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_138[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_139[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_140[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_141[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_142[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_143[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_144[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_145[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_146[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_147[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_148[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_149[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_150[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_151[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_152[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_153[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_154[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_155[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_156[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_157[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_158[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_159[] = { 9,  0,  0,  0,  0,  0,  0,170,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,130,  0,  0,  0,170,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_160[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_161[] = { 8,  0,  0,  0, 16, 16, 16, 16, 16, 16, 16,  0, 16,  0,  0 };
static const GLubyte Fixed8x13_Character_162[] = { 8,  0,  0,  0,  0, 16, 56, 84, 80, 80, 84, 56, 16,  0,  0 };
static const GLubyte Fixed8x13_Character_163[] = { 8,  0,  0,  0,220, 98, 32, 32, 32,112, 32, 34, 28,  0,  0 };
static const GLubyte Fixed8x13_Character_164[] = { 8,  0,  0,  0,  0, 66, 60, 36, 36, 60, 66,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_165[] = { 8,  0,  0,  0, 16, 16,124, 16,124, 40, 68,130,130,  0,  0 };
static const GLubyte Fixed8x13_Character_166[] = { 8,  0,  0,  0, 16, 16, 16, 16,  0, 16, 16, 16, 16,  0,  0 };
static const GLubyte Fixed8x13_Character_167[] = { 8,  0,  0,  0, 24, 36,  4, 24, 36, 36, 24, 32, 36, 24,  0 };
static const GLubyte Fixed8x13_Character_168[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,108,  0,  0 };
static const GLubyte Fixed8x13_Character_169[] = { 8,  0,  0,  0,  0, 56, 68,146,170,162,170,146, 68, 56,  0 };
static const GLubyte Fixed8x13_Character_170[] = { 8,  0,  0,  0,  0,  0,124,  0, 60, 68, 60,  4, 56,  0,  0 };
static const GLubyte Fixed8x13_Character_171[] = { 8,  0,  0,  0,  0, 18, 36, 72,144, 72, 36, 18,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_172[] = { 8,  0,  0,  0,  0,  2,  2,  2,126,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_173[] = { 8,  0,  0,  0,  0,  0,  0,  0, 60,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_174[] = { 8,  0,  0,  0,  0, 56, 68,170,178,170,170,146, 68, 56,  0 };
static const GLubyte Fixed8x13_Character_175[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,126,  0,  0 };
static const GLubyte Fixed8x13_Character_176[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0, 24, 36, 36, 24,  0,  0 };
static const GLubyte Fixed8x13_Character_177[] = { 8,  0,  0,  0,  0,124,  0, 16, 16,124, 16, 16,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_178[] = { 8,  0,  0,  0,  0,  0,  0,  0,120, 64, 48,  8, 72, 48,  0 };
static const GLubyte Fixed8x13_Character_179[] = { 8,  0,  0,  0,  0,  0,  0,  0, 48, 72,  8, 16, 72, 48,  0 };
static const GLubyte Fixed8x13_Character_180[] = { 8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  8,  0 };
static const GLubyte Fixed8x13_Character_181[] = { 8,  0,  0, 64, 90,102, 66, 66, 66, 66,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_182[] = { 8,  0,  0,  0, 20, 20, 20, 20, 52,116,116,116, 62,  0,  0 };
static const GLubyte Fixed8x13_Character_183[] = { 8,  0,  0,  0,  0,  0,  0,  0, 24,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_184[] = { 8,  0, 24,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_185[] = { 8,  0,  0,  0,  0,  0,  0,  0,112, 32, 32, 32, 96, 32,  0 };
static const GLubyte Fixed8x13_Character_186[] = { 8,  0,  0,  0,  0,  0,  0,120,  0, 48, 72, 72, 48,  0,  0 };
static const GLubyte Fixed8x13_Character_187[] = { 8,  0,  0,  0,  0,144, 72, 36, 18, 36, 72,144,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_188[] = { 8,  0,  0,  0,  6, 26, 18, 10,230, 66, 64, 64,192, 64,  0 };
static const GLubyte Fixed8x13_Character_189[] = { 8,  0,  0,  0, 30, 16, 12,  2,242, 76, 64, 64,192, 64,  0 };
static const GLubyte Fixed8x13_Character_190[] = { 8,  0,  0,  0,  6, 26, 18, 10,102,146, 16, 32,144, 96,  0 };
static const GLubyte Fixed8x13_Character_191[] = { 8,  0,  0,  0, 60, 66, 66, 64, 32, 16, 16,  0, 16,  0,  0 };
static const GLubyte Fixed8x13_Character_192[] = { 8,  0,  0,  0, 66, 66,126, 66, 66, 36, 24,  0,  8, 16,  0 };
static const GLubyte Fixed8x13_Character_193[] = { 8,  0,  0,  0, 66, 66,126, 66, 66, 36, 24,  0, 16,  8,  0 };
static const GLubyte Fixed8x13_Character_194[] = { 8,  0,  0,  0, 66, 66,126, 66, 66, 36, 24,  0, 36, 24,  0 };
static const GLubyte Fixed8x13_Character_195[] = { 8,  0,  0,  0, 66, 66,126, 66, 66, 36, 24,  0, 76, 50,  0 };
static const GLubyte Fixed8x13_Character_196[] = { 8,  0,  0,  0, 66, 66,126, 66, 66, 36, 24,  0, 36, 36,  0 };
static const GLubyte Fixed8x13_Character_197[] = { 8,  0,  0,  0, 66, 66,126, 66, 66, 36, 24, 24, 36, 24,  0 };
static const GLubyte Fixed8x13_Character_198[] = { 8,  0,  0,  0,158,144,144,240,156,144,144,144,110,  0,  0 };
static const GLubyte Fixed8x13_Character_199[] = { 8,  0, 16,  8, 60, 66, 64, 64, 64, 64, 64, 66, 60,  0,  0 };
static const GLubyte Fixed8x13_Character_200[] = { 8,  0,  0,  0,126, 64, 64,120, 64, 64,126,  0,  8, 16,  0 };
static const GLubyte Fixed8x13_Character_201[] = { 8,  0,  0,  0,126, 64, 64,120, 64, 64,126,  0, 16,  8,  0 };
static const GLubyte Fixed8x13_Character_202[] = { 8,  0,  0,  0,126, 64, 64,120, 64, 64,126,  0, 36, 24,  0 };
static const GLubyte Fixed8x13_Character_203[] = { 8,  0,  0,  0,126, 64, 64,120, 64, 64,126,  0, 36, 36,  0 };
static const GLubyte Fixed8x13_Character_204[] = { 8,  0,  0,  0,124, 16, 16, 16, 16, 16,124,  0, 16, 32,  0 };
static const GLubyte Fixed8x13_Character_205[] = { 8,  0,  0,  0,124, 16, 16, 16, 16, 16,124,  0, 16,  8,  0 };
static const GLubyte Fixed8x13_Character_206[] = { 8,  0,  0,  0,124, 16, 16, 16, 16, 16,124,  0, 36, 24,  0 };
static const GLubyte Fixed8x13_Character_207[] = { 8,  0,  0,  0,124, 16, 16, 16, 16, 16,124,  0, 40, 40,  0 };
static const GLubyte Fixed8x13_Character_208[] = { 8,  0,  0,  0,120, 68, 66, 66,226, 66, 66, 68,120,  0,  0 };
static const GLubyte Fixed8x13_Character_209[] = { 8,  0,  0,  0,130,134,138,146,162,194,130,  0,152,100,  0 };
static const GLubyte Fixed8x13_Character_210[] = { 8,  0,  0,  0,124,130,130,130,130,130,124,  0, 16, 32,  0 };
static const GLubyte Fixed8x13_Character_211[] = { 8,  0,  0,  0,124,130,130,130,130,130,124,  0, 16,  8,  0 };
static const GLubyte Fixed8x13_Character_212[] = { 8,  0,  0,  0,124,130,130,130,130,130,124,  0, 36, 24,  0 };
static const GLubyte Fixed8x13_Character_213[] = { 8,  0,  0,  0,124,130,130,130,130,130,124,  0,152,100,  0 };
static const GLubyte Fixed8x13_Character_214[] = { 8,  0,  0,  0,124,130,130,130,130,130,124,  0, 40, 40,  0 };
static const GLubyte Fixed8x13_Character_215[] = { 8,  0,  0,  0,  0, 66, 36, 24, 24, 36, 66,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_216[] = { 8,  0,  0, 64, 60, 98, 82, 82, 82, 74, 74, 70, 60,  2,  0 };
static const GLubyte Fixed8x13_Character_217[] = { 8,  0,  0,  0, 60, 66, 66, 66, 66, 66, 66,  0,  8, 16,  0 };
static const GLubyte Fixed8x13_Character_218[] = { 8,  0,  0,  0, 60, 66, 66, 66, 66, 66, 66,  0, 16,  8,  0 };
static const GLubyte Fixed8x13_Character_219[] = { 8,  0,  0,  0, 60, 66, 66, 66, 66, 66, 66,  0, 36, 24,  0 };
static const GLubyte Fixed8x13_Character_220[] = { 8,  0,  0,  0, 60, 66, 66, 66, 66, 66, 66,  0, 36, 36,  0 };
static const GLubyte Fixed8x13_Character_221[] = { 8,  0,  0,  0, 16, 16, 16, 16, 40, 68, 68,  0, 16,  8,  0 };
static const GLubyte Fixed8x13_Character_222[] = { 8,  0,  0,  0, 64, 64, 64,124, 66, 66, 66,124, 64,  0,  0 };
static const GLubyte Fixed8x13_Character_223[] = { 8,  0,  0,  0, 92, 66, 66, 76, 80, 72, 68, 68, 56,  0,  0 };
static const GLubyte Fixed8x13_Character_224[] = { 8,  0,  0,  0, 58, 70, 66, 62,  2, 60,  0,  0,  8, 16,  0 };
static const GLubyte Fixed8x13_Character_225[] = { 8,  0,  0,  0, 58, 70, 66, 62,  2, 60,  0,  0,  8,  4,  0 };
static const GLubyte Fixed8x13_Character_226[] = { 8,  0,  0,  0, 58, 70, 66, 62,  2, 60,  0,  0, 36, 24,  0 };
static const GLubyte Fixed8x13_Character_227[] = { 8,  0,  0,  0, 58, 70, 66, 62,  2, 60,  0,  0, 76, 50,  0 };
static const GLubyte Fixed8x13_Character_228[] = { 8,  0,  0,  0, 58, 70, 66, 62,  2, 60,  0,  0, 36, 36,  0 };
static const GLubyte Fixed8x13_Character_229[] = { 8,  0,  0,  0, 58, 70, 66, 62,  2, 60,  0, 24, 36, 24,  0 };
static const GLubyte Fixed8x13_Character_230[] = { 8,  0,  0,  0,108,146,144,124, 18,108,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_231[] = { 8,  0, 16,  8, 60, 66, 64, 64, 66, 60,  0,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_232[] = { 8,  0,  0,  0, 60, 66, 64,126, 66, 60,  0,  0,  8, 16,  0 };
static const GLubyte Fixed8x13_Character_233[] = { 8,  0,  0,  0, 60, 66, 64,126, 66, 60,  0,  0, 16,  8,  0 };
static const GLubyte Fixed8x13_Character_234[] = { 8,  0,  0,  0, 60, 66, 64,126, 66, 60,  0,  0, 36, 24,  0 };
static const GLubyte Fixed8x13_Character_235[] = { 8,  0,  0,  0, 60, 66, 64,126, 66, 60,  0,  0, 36, 36,  0 };
static const GLubyte Fixed8x13_Character_236[] = { 8,  0,  0,  0,124, 16, 16, 16, 16, 48,  0,  0, 16, 32,  0 };
static const GLubyte Fixed8x13_Character_237[] = { 8,  0,  0,  0,124, 16, 16, 16, 16, 48,  0,  0, 32, 16,  0 };
static const GLubyte Fixed8x13_Character_238[] = { 8,  0,  0,  0,124, 16, 16, 16, 16, 48,  0,  0, 72, 48,  0 };
static const GLubyte Fixed8x13_Character_239[] = { 8,  0,  0,  0,124, 16, 16, 16, 16, 48,  0,  0, 40, 40,  0 };
static const GLubyte Fixed8x13_Character_240[] = { 8,  0,  0,  0, 60, 66, 66, 66, 66, 60,  4, 40, 24, 36,  0 };
static const GLubyte Fixed8x13_Character_241[] = { 8,  0,  0,  0, 66, 66, 66, 66, 98, 92,  0,  0, 76, 50,  0 };
static const GLubyte Fixed8x13_Character_242[] = { 8,  0,  0,  0, 60, 66, 66, 66, 66, 60,  0,  0, 16, 32,  0 };
static const GLubyte Fixed8x13_Character_243[] = { 8,  0,  0,  0, 60, 66, 66, 66, 66, 60,  0,  0, 16,  8,  0 };
static const GLubyte Fixed8x13_Character_244[] = { 8,  0,  0,  0, 60, 66, 66, 66, 66, 60,  0,  0, 36, 24,  0 };
static const GLubyte Fixed8x13_Character_245[] = { 8,  0,  0,  0, 60, 66, 66, 66, 66, 60,  0,  0, 76, 50,  0 };
static const GLubyte Fixed8x13_Character_246[] = { 8,  0,  0,  0, 60, 66, 66, 66, 66, 60,  0,  0, 36, 36,  0 };
static const GLubyte Fixed8x13_Character_247[] = { 8,  0,  0,  0,  0, 16, 16,  0,124,  0, 16, 16,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_248[] = { 8,  0,  0, 64, 60, 98, 82, 74, 70, 60,  2,  0,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_249[] = { 8,  0,  0,  0, 58, 68, 68, 68, 68, 68,  0,  0, 16, 32,  0 };
static const GLubyte Fixed8x13_Character_250[] = { 8,  0,  0,  0, 58, 68, 68, 68, 68, 68,  0,  0, 16,  8,  0 };
static const GLubyte Fixed8x13_Character_251[] = { 8,  0,  0,  0, 58, 68, 68, 68, 68, 68,  0,  0, 36, 24,  0 };
static const GLubyte Fixed8x13_Character_252[] = { 8,  0,  0,  0, 58, 68, 68, 68, 68, 68,  0,  0, 40, 40,  0 };
static const GLubyte Fixed8x13_Character_253[] = { 8,  0, 60, 66,  2, 58, 70, 66, 66, 66,  0,  0, 16,  8,  0 };
static const GLubyte Fixed8x13_Character_254[] = { 8,  0, 64, 64, 92, 98, 66, 66, 98, 92, 64, 64,  0,  0,  0 };
static const GLubyte Fixed8x13_Character_255[] = { 8,  0, 60, 66,  2, 58, 70, 66, 66, 66,  0,  0, 36, 36,  0 };

/* The font characters mapping: */
static const GLubyte* Fixed8x13_Character_Map[] = { Fixed8x13_Character_000,Fixed8x13_Character_001,Fixed8x13_Character_002,Fixed8x13_Character_003,Fixed8x13_Character_004,Fixed8x13_Character_005,Fixed8x13_Character_006,Fixed8x13_Character_007,Fixed8x13_Character_008,Fixed8x13_Character_009,Fixed8x13_Character_010,Fixed8x13_Character_011,Fixed8x13_Character_012,Fixed8x13_Character_013,Fixed8x13_Character_014,Fixed8x13_Character_015,
												   Fixed8x13_Character_016,Fixed8x13_Character_017,Fixed8x13_Character_018,Fixed8x13_Character_019,Fixed8x13_Character_020,Fixed8x13_Character_021,Fixed8x13_Character_022,Fixed8x13_Character_023,Fixed8x13_Character_024,Fixed8x13_Character_025,Fixed8x13_Character_026,Fixed8x13_Character_027,Fixed8x13_Character_028,Fixed8x13_Character_029,Fixed8x13_Character_030,Fixed8x13_Character_031,
												   Fixed8x13_Character_032,Fixed8x13_Character_033,Fixed8x13_Character_034,Fixed8x13_Character_035,Fixed8x13_Character_036,Fixed8x13_Character_037,Fixed8x13_Character_038,Fixed8x13_Character_039,Fixed8x13_Character_040,Fixed8x13_Character_041,Fixed8x13_Character_042,Fixed8x13_Character_043,Fixed8x13_Character_044,Fixed8x13_Character_045,Fixed8x13_Character_046,Fixed8x13_Character_047,
												   Fixed8x13_Character_048,Fixed8x13_Character_049,Fixed8x13_Character_050,Fixed8x13_Character_051,Fixed8x13_Character_052,Fixed8x13_Character_053,Fixed8x13_Character_054,Fixed8x13_Character_055,Fixed8x13_Character_056,Fixed8x13_Character_057,Fixed8x13_Character_058,Fixed8x13_Character_059,Fixed8x13_Character_060,Fixed8x13_Character_061,Fixed8x13_Character_062,Fixed8x13_Character_063,
												   Fixed8x13_Character_064,Fixed8x13_Character_065,Fixed8x13_Character_066,Fixed8x13_Character_067,Fixed8x13_Character_068,Fixed8x13_Character_069,Fixed8x13_Character_070,Fixed8x13_Character_071,Fixed8x13_Character_072,Fixed8x13_Character_073,Fixed8x13_Character_074,Fixed8x13_Character_075,Fixed8x13_Character_076,Fixed8x13_Character_077,Fixed8x13_Character_078,Fixed8x13_Character_079,
												   Fixed8x13_Character_080,Fixed8x13_Character_081,Fixed8x13_Character_082,Fixed8x13_Character_083,Fixed8x13_Character_084,Fixed8x13_Character_085,Fixed8x13_Character_086,Fixed8x13_Character_087,Fixed8x13_Character_088,Fixed8x13_Character_089,Fixed8x13_Character_090,Fixed8x13_Character_091,Fixed8x13_Character_092,Fixed8x13_Character_093,Fixed8x13_Character_094,Fixed8x13_Character_095,
												   Fixed8x13_Character_096,Fixed8x13_Character_097,Fixed8x13_Character_098,Fixed8x13_Character_099,Fixed8x13_Character_100,Fixed8x13_Character_101,Fixed8x13_Character_102,Fixed8x13_Character_103,Fixed8x13_Character_104,Fixed8x13_Character_105,Fixed8x13_Character_106,Fixed8x13_Character_107,Fixed8x13_Character_108,Fixed8x13_Character_109,Fixed8x13_Character_110,Fixed8x13_Character_111,
												   Fixed8x13_Character_112,Fixed8x13_Character_113,Fixed8x13_Character_114,Fixed8x13_Character_115,Fixed8x13_Character_116,Fixed8x13_Character_117,Fixed8x13_Character_118,Fixed8x13_Character_119,Fixed8x13_Character_120,Fixed8x13_Character_121,Fixed8x13_Character_122,Fixed8x13_Character_123,Fixed8x13_Character_124,Fixed8x13_Character_125,Fixed8x13_Character_126,Fixed8x13_Character_032,
												   Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,
												   Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,Fixed8x13_Character_032,
												   Fixed8x13_Character_160,Fixed8x13_Character_161,Fixed8x13_Character_162,Fixed8x13_Character_163,Fixed8x13_Character_164,Fixed8x13_Character_165,Fixed8x13_Character_166,Fixed8x13_Character_167,Fixed8x13_Character_168,Fixed8x13_Character_169,Fixed8x13_Character_170,Fixed8x13_Character_171,Fixed8x13_Character_172,Fixed8x13_Character_173,Fixed8x13_Character_174,Fixed8x13_Character_175,
												   Fixed8x13_Character_176,Fixed8x13_Character_177,Fixed8x13_Character_178,Fixed8x13_Character_179,Fixed8x13_Character_180,Fixed8x13_Character_181,Fixed8x13_Character_182,Fixed8x13_Character_183,Fixed8x13_Character_184,Fixed8x13_Character_185,Fixed8x13_Character_186,Fixed8x13_Character_187,Fixed8x13_Character_188,Fixed8x13_Character_189,Fixed8x13_Character_190,Fixed8x13_Character_191,
												   Fixed8x13_Character_192,Fixed8x13_Character_193,Fixed8x13_Character_194,Fixed8x13_Character_195,Fixed8x13_Character_196,Fixed8x13_Character_197,Fixed8x13_Character_198,Fixed8x13_Character_199,Fixed8x13_Character_200,Fixed8x13_Character_201,Fixed8x13_Character_202,Fixed8x13_Character_203,Fixed8x13_Character_204,Fixed8x13_Character_205,Fixed8x13_Character_206,Fixed8x13_Character_207,
												   Fixed8x13_Character_208,Fixed8x13_Character_209,Fixed8x13_Character_210,Fixed8x13_Character_211,Fixed8x13_Character_212,Fixed8x13_Character_213,Fixed8x13_Character_214,Fixed8x13_Character_215,Fixed8x13_Character_216,Fixed8x13_Character_217,Fixed8x13_Character_218,Fixed8x13_Character_219,Fixed8x13_Character_220,Fixed8x13_Character_221,Fixed8x13_Character_222,Fixed8x13_Character_223,
												   Fixed8x13_Character_224,Fixed8x13_Character_225,Fixed8x13_Character_226,Fixed8x13_Character_227,Fixed8x13_Character_228,Fixed8x13_Character_229,Fixed8x13_Character_230,Fixed8x13_Character_231,Fixed8x13_Character_232,Fixed8x13_Character_233,Fixed8x13_Character_234,Fixed8x13_Character_235,Fixed8x13_Character_236,Fixed8x13_Character_237,Fixed8x13_Character_238,Fixed8x13_Character_239,
												   Fixed8x13_Character_240,Fixed8x13_Character_241,Fixed8x13_Character_242,Fixed8x13_Character_243,Fixed8x13_Character_244,Fixed8x13_Character_245,Fixed8x13_Character_246,Fixed8x13_Character_247,Fixed8x13_Character_248,Fixed8x13_Character_249,Fixed8x13_Character_250,Fixed8x13_Character_251,Fixed8x13_Character_252,Fixed8x13_Character_253,Fixed8x13_Character_254,Fixed8x13_Character_255,NULL };

/* The font structure: */
SFG_Font fgFontFixed8x13 = { "-misc-fixed-medium-r-normal--13-120-75-75-C-80-iso8859-1", 256, 14, Fixed8x13_Character_Map, 0, 3 };



SFG_Font* fghFontByID(void* font)
{
	if (font == GLUT_BITMAP_8_BY_13)
		return &fgFontFixed8x13;
	/*
	if (font == GLUT_BITMAP_9_BY_15)
		return &fgFontFixed9x15;
	if (font == GLUT_BITMAP_HELVETICA_10)
		return &fgFontHelvetica10;
	if (font == GLUT_BITMAP_HELVETICA_12)
		return &fgFontHelvetica12;
	if (font == GLUT_BITMAP_HELVETICA_18)
		return &fgFontHelvetica18;
	if (font == GLUT_BITMAP_TIMES_ROMAN_10)
		return &fgFontTimesRoman10;
	if (font == GLUT_BITMAP_TIMES_ROMAN_24)
		return &fgFontTimesRoman24;
		*/

	return 0;
}



void glutBitmapCharacter(void* fontID, int character)
{
	const GLubyte* face;
	SFG_Font* font;
	font = fghFontByID(fontID);
	/*
	FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutBitmapCharacter" );
	font = fghFontByID( fontID );
	if (!font)
	{
		fgWarning("glutBitmapCharacter: bitmap font 0x%08x not found. Make sure you're not passing a stroke font.\n",fontID);
		return;
	}
	freeglut_return_if_fail( ( character >= 1 )&&( character < 256 ) );
	*/
	/*
	 * Find the character we want to draw (???)
	 */
	face = font->Characters[character];

	glPushClientAttrib(GL_CLIENT_PIXEL_STORE_BIT);
	glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
	glPixelStorei(GL_UNPACK_LSB_FIRST, GL_FALSE);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBitmap(
		face[0], font->Height,      /* The bitmap's width and height  */
		font->xorig, font->yorig,     /* The origin in the font glyph   */
		(float)(face[0]), 0.0,  /* The raster advance -- inc. x,y */
		(face + 1)                  /* The packed bitmap data...      */
	);
	glPopClientAttrib();
}

void glutSolidCube( GLdouble dSize )
{
    GLfloat size = dSize * 0.5f;
	GLuint vboId = 0;

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidCube" );

#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

	// cube ///////////////////////////////////////////////////////////////////////
	//    v6----- v5
	//   /|      /|
	//  v1------v0|
	//  | |     | |
	//  | |v7---|-|v4
	//  |/      |/
	//  v2------v3

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

// Vertex coords array for glDrawArrays() =====================================
// A cube has 6 sides and each side has 1 square, therefore, a cube consists
// of 24 vertices (6 sides * 1 square * 4 vertices = 24 vertices). And, each
// vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
// array is 72 floats (24 * 3 = 72). The size of each float is 4 bytes (72 * 4 = 288 bytes)
	GLfloat vertices[] = { size, size, size, -size, size, size, -size, -size,  size,  size, -size, size,     // v0-v1-v2-v3 (front)
		 size, -size,  size,  size, -size, -size,  size,  size, -size,  size,  size,  size,				// v3-v4-v5-v0 (right)
		 size,  size,  size,  size,  size, -size, -size,  size, -size, -size,  size,  size,				// v0-v5-v6-v1 (top)
		-size,  size,  size, -size,  size, -size, -size, -size, -size, -size, -size,  size,				// v1-v6-v7-v2 (left)
		-size, -size,  size, -size, -size, -size,  size, -size, -size,  size, -size,  size,				// v2-v7-v4-v3 (bottom)
		-size, -size, -size, -size,  size, -size,  size,  size, -size,  size, -size, -size };			// v7-v6-v5-v4 (back)

// Normal array
	GLfloat normals[] = { 0,  0, 1,  0,  0,  1,  0,  0,  1,  0,  0,  1,		// v0-v1-v2-v3 (front)
						  1,  0, 0,  1,  0,  0,  1,  0,  0,  1,  0,  0,		// v3-v4-v5-v0 (right)
						  0,  1, 0,  0,  1,  0,  0,  1,  0,  0,  1,  0,		// v0-v5-v6-v1 (top)
						 -1,  0, 0, -1,  0,  0, -1,  0,  0, -1,  0,  0,		// v1-v6-v7-v2 (left)
						  0, -1, 0,  0, -1,  0,  0, -1,  0,  0, -1,  0,		// v2-v7-v4-v3 (bottom)
						  0, 0, -1,  0,  0, -1,  0,  0, -1,  0,  0, -1 };	// v7-v6-v5-v4 (back)

// Color array
	GLfloat colors[] = {
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2],  // v0-v1-v2-v3 (front)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2],  // v3-v4-v5-v0 (right)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2],  // v0-v5-v6-v1 (top)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2],  // v1-v6-v7-v2 (left)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2],  // v2-v7-v4-v3 (bottom)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2]};// v7-v6-v5-v4 (back)

// Texture Array
	GLfloat textures[] = { 0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0,		// v0-v1-v2-v3 (front)
						   0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0,		// v3-v4-v5-v0 (right)
						   0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0,		// v0-v5-v6-v1 (top)
						   0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0,		// v1-v6-v7-v2 (left)
						   0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0,		// v2-v7-v4-v3 (bottom)
						   0.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 1.0 };	// v7-v6-v5-v4 (back)

// Create vertex buffer objects, you need to delete them when program exits
// Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
// glBufferDataARB with NULL pointer reserves only memory space.
// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
	glGenBuffersARB(1, &vboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals) + sizeof(colors) + sizeof(textures), 0, GL_STATIC_DRAW_ARB);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(vertices), vertices);									// copy vertices starting from 0 offest
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices), sizeof(normals), normals);					// copy normals after vertices
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals), sizeof(colors), colors);	// copy colours after normals
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals) + sizeof(colors), sizeof(textures), textures);  // copy textures after colours

// Bind VBOs with IDs and set the buffer offsets of the bound VBOs
// When buffer object is bound with its ID, all pointers in gl*Pointer()
//		are treated as offset instead of real pointer.
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

// Enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

// Before draw, specify vertex and index arrays with their offsets
	glTexCoordPointer(2, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals) + sizeof(colors)));
	glColorPointer(3, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals)));
	glNormalPointer(GL_FLOAT, 0, (void*)sizeof(vertices));
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_QUADS, 0, 24);

	glDisableClientState(GL_VERTEX_ARRAY);  // Disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

// It is good idea to release VBOs with ID 0 after use.
// Once bound with 0, all pointers in gl*Pointer() behave as real
// pointer, so, normal vertex array operations are re-activated
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glDeleteBuffersARB(1, &vboId);
#   undef V
#   undef N
}


/*
* Draws a solid cube with RGB color model. Code contributed by Andreas Umbach <marvin@dataway.ch>
*/
void glutSolidCubeRGB(GLdouble dSize)
{
	GLfloat size = dSize * 0.5f;
	GLuint vboId = 0;

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidCube" );

// cube ///////////////////////////////////////////////////////////////////////
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3

// vertex coords array for glDrawArrays() =====================================
// A cube has 6 sides and each side has 2 triangles, therefore, a cube consists
// of 36 vertices (6 sides * 2 tris * 3 vertices = 36 vertices). And, each
// vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
// array is 108 floats (36 * 3 = 108).
	GLfloat vertices[] = { size, size, size, -size, size, size, -size, -size, size,      // v0-v1-v2 (front)
		-size, -size,  size,  size, -size,  size,  size,  size,  size,      // v2-v3-v0
		 size,  size,  size,  size, -size,  size,  size, -size, -size,      // v0-v3-v4 (right)
		 size, -size, -size,  size,  size, -size,  size,  size,  size,      // v4-v5-v0
		 size,  size,  size,  size,  size, -size, -size,  size, -size,      // v0-v5-v6 (top)
		-size,  size, -size, -size,  size,  size,  size,  size,  size,      // v6-v1-v0
		-size,  size,  size, -size,  size, -size, -size, -size, -size,      // v1-v6-v7 (left)
		-size, -size, -size, -size, -size,  size, -size,  size,  size,      // v7-v2-v1
		-size, -size, -size,  size, -size, -size,  size, -size,  size,      // v7-v4-v3 (bottom)
		 size, -size,  size, -size, -size,  size, -size, -size, -size,      // v3-v2-v7
		 size, -size, -size, -size, -size, -size, -size,  size, -size,      // v4-v7-v6 (back)
		-size,  size, -size,  size,  size, -size,  size, -size, -size };	// v6-v5-v4

// Normal array
	GLfloat normals[] = {  0,  0,  1,  0,  0,  1,  0,  0,  1,   // v0-v1-v2 (front)
						   0,  0,  1,  0,  0,  1,  0,  0,  1,   // v2-v3-v0
						   1,  0,  0,  1,  0,  0,  1,  0,  0,   // v0-v3-v4 (right)
						   1,  0,  0,  1,  0,  0,  1,  0,  0,   // v4-v5-v0
						   0,  1,  0,  0,  1,  0,  0,  1,  0,   // v0-v5-v6 (top)
						   0,  1,  0,  0,  1,  0,  0,  1,  0,   // v6-v1-v0
						  -1,  0,  0, -1,  0,  0, -1,  0,  0,   // v1-v6-v7 (left)
						  -1,  0,  0, -1,  0,  0, -1,  0,  0,   // v7-v2-v1
						   0, -1,  0,  0, -1,  0,  0, -1,  0,   // v7-v4-v3 (bottom)
						   0, -1,  0,  0, -1,  0,  0, -1,  0,   // v3-v2-v7
						   0,  0, -1,  0,  0, -1,  0,  0, -1,   // v4-v7-v6 (back)
					   	   0,  0, -1,  0,  0, -1,  0,  0, -1 }; // v6-v5-v4

// Color array
	GLfloat colors[] = { 1, 1, 1, 0, 1, 1, 0, 0, 1,      // v0-v1-v2 (front)
		0, 0, 1, 1, 0, 1, 1, 1, 1,      // v2-v3-v0
		1, 1, 1, 1, 0, 1, 1, 0, 0,      // v0-v3-v4 (right)
		1, 0, 0, 1, 1, 0, 1, 1, 1,      // v4-v5-v0
		1, 1, 1, 1, 1, 0, 0, 1, 0,      // v0-v5-v6 (top)
		0, 1, 0, 0, 1, 1, 1, 1, 1,      // v6-v1-v0
		0, 1, 1, 0, 1, 0, 0, 0, 0,      // v1-v6-v7 (left)
		0, 0, 0, 0, 0, 1, 0, 1, 1,      // v7-v2-v1
		0, 0, 0, 1, 0, 0, 1, 0, 1,      // v7-v4-v3 (bottom)
		1, 0, 1, 0, 0, 1, 0, 0, 0,      // v3-v2-v7
		1, 0, 0, 0, 0, 0, 0, 1, 0,      // v4-v7-v6 (back)
		0, 1, 0, 1, 1, 0, 1, 0, 0 };    // v6-v5-v4

// Texture Array
	GLfloat textures[] = { 1, 1, 1, 0, 0, 0,      // v0-v1-v2 (front)
		1, 0, 0, 1, 1, 1,      // v2-v3-v0
		1, 1, 0, 1, 0, 0,      // v0-v3-v4 (right)
		0, 0, 1, 0, 1, 1,      // v4-v5-v0
		1, 1, 1, 0, 0, 1,      // v0-v5-v6 (top)
		0, 1, 1, 0, 1, 1,      // v6-v1-v0
		1, 1, 0, 0, 1, 0,      // v1-v6-v7 (left)
		0, 0, 0, 1, 1, 1,      // v7-v2-v1
		0, 0, 0, 1, 1, 0,      // v7-v4-v3 (bottom)
		1, 0, 1, 1, 0, 0,      // v3-v2-v7
		0, 0, 1, 0, 1, 0,      // v4-v7-v6 (back)
		0, 1, 0, 0, 1, 1 };    // v6-v5-v4

// Create vertex buffer objects, you need to delete them when program exits
// Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
// glBufferDataARB with NULL pointer reserves only memory space.
// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
// target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
	glGenBuffersARB(1, &vboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals) + sizeof(colors) + sizeof(textures), 0, GL_STATIC_DRAW_ARB);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(vertices), vertices);									// copy vertices starting from 0 offest
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices), sizeof(normals), normals);					// copy normals after vertices
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals), sizeof(colors), colors);	// copy colours after normals
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals) + sizeof(colors), sizeof(textures), textures);  // copy textures after colours

// bind VBOs with IDs and set the buffer offsets of the bound VBOs
// When buffer object is bound with its ID, all pointers in gl*Pointer()
// are treated as offset instead of real pointer.
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

// Enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

// Before draw, specify vertex and index arrays with their offsets
	glTexCoordPointer(2, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals) + sizeof(colors)));
	glColorPointer(3, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals)));
	glNormalPointer(GL_FLOAT, 0, (void*)sizeof(vertices));
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableClientState(GL_VERTEX_ARRAY);  // Disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

// it is good idea to release VBOs with ID 0 after use.
// Once bound with 0, all pointers in gl*Pointer() behave as real
// pointer, so, normal vertex array operations are re-activated
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glDeleteBuffersARB(1, &vboId);
}


/*
* Draws a solid cube without VBO and texture coordinates generated by equation (GEN_S, GEN_T). For Truck object
Code contributed by Andreas Umbach <marvin@dataway.ch>
*/
void glutSolidCubeT(GLdouble dSize)
{
	GLfloat size = dSize * 0.5f;

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidCube" );
#   define V(a,b,c) glVertex3d( a size, b size, c size );
#   define N(a,b,c) glNormal3d( a, b, c );

//---- DEFINICIÓ COORDENADES TEXTURA
//	Activa_Coordenades_Textura();

// PWO: Again, I dared to convert the code to use macros... 
	glBegin(GL_QUADS);
// Cub SENSE Textura incrustada glTexCoord2f() -> Activar Coordenades Textura
		N(1.0, 0.0, 0.0); V(+, -, +); V(+, -, -); V(+, +, -); V(+, +, +);
		N(0.0, 1.0, 0.0);  V(+, +, +); V(+, +, -); V(-, +, -); V(-, +, +);
		N(0.0, 0.0, 1.0); V(+, +, +); V(-, +, +); V(-, -, +); V(+, -, +);
		N(-1.0, 0.0, 0.0); V(-, -, +); V(-, +, +); V(-, +, -); V(-, -, -);
		N(0.0, -1.0, 0.0); V(-, -, +); V(-, -, -); V(+, -, -); V(+, -, +);
		N(0.0, 0.0, -1.0); V(-, -, -); V(-, +, -); V(+, +, -); V(+, -, -);
	glEnd();

//---- DEFINICIÓ COORDENADES TEXTURA
//	Desactiva_Coordenades_Textura();
#   undef V
#   undef N
}



/* ---------- SPHERE -----------------------------------------------------*/
/*
 * Compute lookup table of cos and sin values forming a cirle
 *
 * Notes:
 *    It is the responsibility of the caller to free these tables
 *    The size of the table is (n+1) to form a connected loop
 *    The last entry is exactly the same as the first
 *    The sign of n can be flipped to get the reverse loop
 */

/*
 * Draws a solid sphere
 */
void glutSolidSphere(GLdouble radius, GLint slices, GLint stacks)
{
    int i,j;

/* Adjust z and radius as stacks are drawn. */
    double z0,z1;
    double r0,r1;

/* Pre-computed circle */
    double *sint1,*cost1;
    double *sint2,*cost2;

// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, normals, colors, textures;	// Definició vectors dinàmics per a vertexs, normals i textures 
	vertices.resize(0);		normals.resize(0);		colors.resize(0);		textures.resize(0);		// Reinicialitzar vectors

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidSphere" );

//---- DEFINICIÓ COORDENADES TEXTURA
	//Activa_Coordenades_Textura();

    fghCircleTable(&sint1,&cost1,-slices);
    fghCircleTable(&sint2,&cost2,stacks*2);

/* The top stack is covered with a triangle fan */
    z0 = 1.0;
    z1 = cost2[(stacks>0)?1:0];
    r0 = 0.0;
    r1 = sint2[(stacks>0)?1:0];

    //glBegin(GL_TRIANGLE_FAN);
    //glNormal3d(0,0,1);
    //glVertex3d(0,0,radius);
	colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);	// Vector Colors
	normals.push_back(0.0);			normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
	vertices.push_back(0.0);		vertices.push_back(0.0);		vertices.push_back(radius);		// Vector Vertices
	textures.push_back(0.0);		textures.push_back(radius);										// Vector Textures

    for (j=slices; j>=0; j--)
        {   
			//glNormal3d(cost1[j]*r1,        sint1[j]*r1,        z1       );
            //glVertex3d(cost1[j]*r1*radius, sint1[j]*r1*radius, z1*radius);
			colors.push_back(cColor[0]);				colors.push_back(cColor[1]);				colors.push_back(cColor[2]);	// Vector Colors
			normals.push_back(cost1[j] * r1);			normals.push_back(sint1[j] * r1);			normals.push_back(z1);	// Vector Normals
			vertices.push_back(cost1[j] * r1*radius);	vertices.push_back(sint1[j] * r1*radius);	vertices.push_back(z1*radius);	// Vector Vertices
			textures.push_back(-(cost1[j] * r1*radius) + (sint1[j] * r1*radius));	textures.push_back(-(cost1[j] * r1*radius) + z1*radius);// Vector Textures

        }
    //glEnd();

	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

	draw_GL_TRIANGLE_FAN_VBO(vertices, normals, colors, textures, nv / 3);

	vertices.resize(0);		normals.resize(0);		colors.resize(0);		textures.resize(0);		// Reinicialitzar vectors

/* Cover each stack with a quad strip, except the top and bottom stacks */
    for( i=1; i<stacks-1; i++ )
    {
        z0 = z1; z1 = cost2[i+1];
        r0 = r1; r1 = sint2[i+1];
       // glBegin(GL_QUAD_STRIP);
            for(j=0; j<=slices; j++)
            {   
				//glNormal3d(cost1[j]*r1,        sint1[j]*r1,        z1       );
                //glVertex3d(cost1[j]*r1*radius, sint1[j]*r1*radius, z1*radius);
				colors.push_back(cColor[0]);				colors.push_back(cColor[1]);				colors.push_back(cColor[2]);	// Vector Colors
				normals.push_back(cost1[j] * r1);			normals.push_back(sint1[j] * r1);			normals.push_back(z1);	// Vector Normals
				textures.push_back(-(cost1[j] * r1*radius) + (sint1[j] * r1*radius));	textures.push_back(-(cost1[j] * r1*radius) + z1*radius);// Vector Textures
				vertices.push_back(cost1[j] * r1*radius);	vertices.push_back(sint1[j] * r1*radius);	vertices.push_back(z1*radius);	// Vector Vertices
				
				//glNormal3d(cost1[j]*r0,        sint1[j]*r0,        z0       );
                //glVertex3d(cost1[j]*r0*radius, sint1[j]*r0*radius, z0*radius);
				colors.push_back(cColor[0]);				colors.push_back(cColor[1]);				colors.push_back(cColor[2]);	// Vector Colors
				normals.push_back(cost1[j] * r0);			normals.push_back(sint1[j] * r0);			normals.push_back(z0);	// Vector Normals
				textures.push_back(-(cost1[j] * r0*radius) + (sint1[j] * r0*radius));	textures.push_back(-(cost1[j] * r0*radius) + z0*radius);// Vector Textures
				vertices.push_back(cost1[j] * r0*radius);	vertices.push_back(sint1[j] * r0*radius);	vertices.push_back(z0*radius);	// Vector Vertices
				
            }
        //glEnd();

		nv = vertices.size();	// Tamany del vector vertices en elements.
		nn = normals.size();	// Tamany del vector normals en elements.
		nc = colors.size();		// Tamany del vector colors en elements.
		nt = textures.size();	// Tamany del vector textures en elements.

		draw_GL_QUAD_STRIP_VBO(vertices, normals, colors, textures, nv / 3);

		vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors
    }

/* The bottom stack is covered with a triangle fan */
    z0 = z1;
    r0 = r1;

    //glBegin(GL_TRIANGLE_FAN);
    //    glNormal3d(0,0,-1);
    //    glVertex3d(0,0,-radius);
	colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);	// Vector Colors
	normals.push_back(0.0);			normals.push_back(0.0);			normals.push_back(-1.0);	// Vector Normals
	textures.push_back(0.0);		textures.push_back(-radius);								// Vector Textures
	vertices.push_back(0.0);		vertices.push_back(0.0);		vertices.push_back(-radius);// Vector Vertices

    for (j=0; j<=slices; j++)
        {   
			//glNormal3d(cost1[j]*r0,        sint1[j]*r0,        z0       );
            //glVertex3d(cost1[j]*r0*radius, sint1[j]*r0*radius, z0*radius);
			colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);	// Vector Colors
			normals.push_back(cost1[j] * r0);			normals.push_back(sint1[j] * r0);			normals.push_back(z0);	// Vector Normals
			textures.push_back(-(cost1[j] * r0*radius) + (sint1[j] * r0*radius));	textures.push_back(-(cost1[j] * r0*radius) + z0*radius);// Vector Textures
			vertices.push_back(cost1[j] * r0*radius);	vertices.push_back(sint1[j] * r0*radius);	vertices.push_back(z0*radius);	// Vector Vertices
        }
    //glEnd();

// ----------------------- VBO
	nv = vertices.size();	// Tamany del vector vertices en elements.
	nn = normals.size();	// Tamany del vector normals en elements.
	nc = colors.size();		// Tamany del vector colors en elements.
	nt = textures.size();	// Tamany del vector textures en elements.

	draw_GL_TRIANGLE_FAN_VBO(vertices, normals, colors, textures, nv / 3);

//---- DEFINICIÓ COORDENADES TEXTURA
	//Desactiva_Coordenades_Textura();

// Release sin and cos tables
    free(sint1);
    free(cost1);
    free(sint2);
    free(cost2);
}


void fghCircleTable(double **sint,double **cost,const int n)
{
    int i;

/* Table size, the sign of n flips the circle direction */
    const int size = abs(n);

/* Determine the angle between samples */
    const double angle = 2*pi/(double)( ( n == 0 ) ? 1 : n );

/* Allocate memory for n samples, plus duplicate of first entry at the end */
    *sint = (double *) calloc(sizeof(double), size+1);
    *cost = (double *) calloc(sizeof(double), size+1);

/* Bail out if memory allocation fails, fgError never returns */
    if (!(*sint) || !(*cost))
    {   free(*sint);
        free(*cost);
		AfxMessageBox(_T("Failed to allocate memory in fghCircleTable"));
    }

/* Compute cos and sin around the circle */
    (*sint)[0] = 0.0;
    (*cost)[0] = 1.0;

    for (i=1; i<size; i++)
    {
        (*sint)[i] = sin(angle*i);
        (*cost)[i] = cos(angle*i);
    }

/* Last sample is duplicate of the first */
    (*sint)[size] = (*sint)[0];
    (*cost)[size] = (*cost)[0];
}


/* ---------- CONE -----------------------------------------------------*/
/*
 * Draws a solid cone
 */
void glutSolidCone( GLdouble base, GLdouble height, GLint slices, GLint stacks )
{
    int i,j;

/* Step in z and radius as stacks are drawn. */
    double z0,z1;
    double r0,r1;

    const double zStep = height / ( ( stacks > 0 ) ? stacks : 1 );
    const double rStep = base / ( ( stacks > 0 ) ? stacks : 1 );

/* Scaling factors for vertex normals */
    const double cosn = ( height / sqrt ( height * height + base * base ));
    const double sinn = ( base   / sqrt ( height * height + base * base ));

/* Pre-computed circle */
    double *sint,*cost;

// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, normals, colors, textures;	// Definició vectors dinàmics per a vertexs, normals i textures 
	vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidCone" );

//---- DEFINICIÓ COORDENADES TEXTURA
	//Activa_Coordenades_Textura();

    fghCircleTable(&sint,&cost,-slices);

/* Cover the circular base with a triangle fan... */
    z0 = 0.0;
    z1 = zStep;

    r0 = base;
    r1 = r0 - rStep;

    //glBegin(GL_TRIANGLE_FAN);
	    //glNormal3d(0.0,0.0,-1.0);
        //glVertex3d(0.0,0.0, z0 );
	colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);// Vector Colors
	normals.push_back(0.0);			normals.push_back(0.0);			normals.push_back(-1.0);	// Vector Normals
	textures.push_back(0.0);		textures.push_back(z0);										// Vector Textures
	vertices.push_back(0.0);		vertices.push_back(0.0);		vertices.push_back(z0);		// Vector Vertices
        for (j=0; j<=slices; j++)
			{	//glVertex3d(cost[j]*r0, sint[j]*r0, z0);
				colors.push_back(cColor[0]);		colors.push_back(cColor[1]);		colors.push_back(cColor[2]);// Vector Colors
				normals.push_back(0.0);				normals.push_back(0.0);				normals.push_back(-1.0);	// Vector Normals
				textures.push_back(-(cost[j] * r0) + (sint[j] * r0));			textures.push_back(-(cost[j] * r0) + z0);	// Vector Textures
				vertices.push_back(cost[j] * r0);	vertices.push_back(sint[j] * r0);	vertices.push_back(z0);		// Vector Vertices
			}
    //glEnd();

	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

/* Cover each stack with a quad strip, except the top stack */
    for( i=0; i<stacks-1; i++ )
    {	//glBegin(GL_QUAD_STRIP);
            for(j=0; j<=slices; j++)
            {   //glNormal3d(cost[j]*cosn, sint[j]*cosn, sinn);
                //glVertex3d(cost[j]*r0,   sint[j]*r0,   z0  );
				colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);	// Vector Colors
				normals.push_back(cost[j] * cosn);	normals.push_back(sint[j] * cosn);	normals.push_back(sinn);// Vector Normals
				textures.push_back(-(cost[j] * r0) + (sint[j] * r0));			textures.push_back(-(cost[j] * r0) + z0);	// Vector Textures
				vertices.push_back(cost[j] * r0);	vertices.push_back(sint[j] * r0);	vertices.push_back(z0);	// Vector Vertices

                //glVertex3d(cost[j]*r1,   sint[j]*r1,   z1  );
				colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);	// Vector Colors
				normals.push_back(cost[j] * cosn);	normals.push_back(sint[j] * cosn);	normals.push_back(sinn);// Vector Normals
				textures.push_back(-(cost[j] * r1) + (sint[j] * r1));			textures.push_back(-(cost[j] * r1) + z1);	// Vector Textures
				vertices.push_back(cost[j] * r1);	vertices.push_back(sint[j] * r1);	vertices.push_back(z1);	// Vector Vertices
            }
            z0 = z1; z1 += zStep;
            r0 = r1; r1 -= rStep;
        //glEnd();
    }

	nv = vertices.size();	// Tamany del vector vertices en elements.
	nn = normals.size();	// Tamany del vector normals en elements.
	nc = colors.size();		// Tamany del vector colors en elements.
	nt = textures.size();	// Tamany del vector textures en elements.

	draw_GL_QUAD_STRIP_VBO(vertices, normals, colors, textures, nv / 3);
	vertices.resize(0);		textures.resize(0);		colors.resize(0);	 normals.resize(0);	// Reinicialitzar vectors

/* The top stack is covered with individual triangles */
    //glBegin(GL_TRIANGLES);
    //  glNormal3d(cost[0]*sinn, sint[0]*sinn, cosn);

        for (j=0; j<slices; j++)
        {   //glVertex3d(cost[j+0]*r0,   sint[j+0]*r0,   z0    );
			colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);	// Vector Colors
			normals.push_back(cost[0] * sinn);	normals.push_back(sint[0] * sinn);	normals.push_back(cosn);	// Vector Normals
			vertices.push_back(cost[j + 0] * r0);	vertices.push_back(sint[j + 0] * r0);	vertices.push_back(z0);		// Vector Vertices
			textures.push_back(-(cost[j + 0] * r0) + (sint[j + 0] * r0));			textures.push_back(-(cost[j + 0] * r0) + z0);	// Vector Textures
            //glVertex3d(0,              0,              height);

			colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
			normals.push_back(cost[0] * sinn);	normals.push_back(sint[0] * sinn);	normals.push_back(cosn);	// Vector Normals
			textures.push_back(0.0);			textures.push_back(height);										// Vector Textures
			vertices.push_back(0.0);			vertices.push_back(0.0);			vertices.push_back(height);	// Vector Vertices

            //glNormal3d(cost[j+1]*sinn, sint[j+1]*sinn, cosn  );
            //glVertex3d(cost[j+1]*r0,   sint[j+1]*r0,   z0    );
			colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
			normals.push_back(cost[j + 1] * sinn);	normals.push_back(sint[j + 1] * sinn);	normals.push_back(cosn);// Vector Normals
			textures.push_back(-(cost[j + 1] * r0) + (sint[j + 1] * r0));		textures.push_back(-(cost[j + 1] * r0) + z0);	// Vector Textures
			vertices.push_back(cost[j + 1] * r0);	vertices.push_back(sint[j + 1] * r0);	vertices.push_back(z0);	// Vector Vertices

        }
    //glEnd();

// ----------------------- VBO
	nv = vertices.size();	// Tamany del vector vertices en elements.
	nn = normals.size();	// Tamany del vector normals en elements.
	nc = colors.size();	// Tamany del vector colors en elements.
	nt = textures.size();	// Tamany del vector textures en elements.

	draw_GL_TRIANGLES_VBO(vertices, normals, colors, textures, nv / 3);

//---- DEFINICIÓ COORDENADES TEXTURA
	//Desactiva_Coordenades_Textura();

/* Release sin and cos tables */
    free(sint);
    free(cost);
}


/* ---------- CYLINDER --------------------------------------------------*/
/*
 * Draws a solid cylinder
 */
void glutSolidCylinder(GLdouble radius, GLdouble height, GLint slices, GLint stacks)
{
    int i,j;

/* Step in z and radius as stacks are drawn. */
    double z0,z1;
    const double zStep = height / ( ( stacks > 0 ) ? stacks : 1 );

/* Pre-computed circle */
    double *sint,*cost;

// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, normals, colors, textures;	// Definició vectors dinàmics per a vertexs, normals i textures 
	vertices.resize(0);		normals.resize(0);		colors.resize(0);	textures.resize(0);			// Reinicialitzar vectors

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

//    FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidCylinder" );

//---- DEFINICIÓ COORDENADES TEXTURA
	//Activa_Coordenades_Textura();

    fghCircleTable(&sint,&cost,-slices);

/* Cover the base and top */

    //glBegin(GL_TRIANGLE_FAN);
    //  glNormal3d(0.0, 0.0, -1.0 );
    //  glVertex3d(0.0, 0.0,  0.0 );
	colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);	// Vector Colors
	normals.push_back(0.0);		normals.push_back(0.0);		normals.push_back(-1.0);				// Vector Normals
	textures.push_back(0.0);	textures.push_back(0.0);											// Vector Textures
	vertices.push_back(0.0);	vertices.push_back(0.0);	vertices.push_back(0.0);				// Vector Vertices


	for (j = 0; j <= slices; j++)
		{	//glVertex3d(cost[j]*radius, sint[j]*radius, 0.0);
			colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);				// Vector Colors
			normals.push_back(0.0);			normals.push_back(0.0);			normals.push_back(-1.0);					// Vector Normals
			textures.push_back(-(cost[j] * radius) + (sint[j] * radius)); textures.push_back(-(cost[j] * radius));		// Vector Textures
			vertices.push_back(cost[j] * radius);	vertices.push_back(sint[j] * radius);	vertices.push_back(0.0);	// Vector Vertices

		}
    //glEnd();

// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.	

	draw_GL_TRIANGLE_FAN_VBO(vertices, normals, colors, textures, nv / 3);

	vertices.resize(0);		textures.resize(0);		normals.resize(0);	// Reinicialitzar vectors

    //glBegin(GL_TRIANGLE_FAN);
    //  glNormal3d(0.0, 0.0, 1.0);
    //  glVertex3d(0.0, 0.0, height);
	colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);// Vector Colors
	normals.push_back(0.0);		normals.push_back(0.0);		normals.push_back(1.0);				// Vector Normals
	textures.push_back(0.0);	textures.push_back(0.0);										// Vector Textures
	vertices.push_back(0.0);	vertices.push_back(0.0);	vertices.push_back(height);			// Vector Vertices


	for (j = slices; j >= 0; j--)
		{	//glVertex3d(cost[j]*radius, sint[j]*radius, height);
			colors.push_back(cColor[0]);			colors.push_back(cColor[1]);			colors.push_back(cColor[2]);// Vector Colors
			normals.push_back(0.0);					normals.push_back(0.0);					normals.push_back(-1.0);	// Vector Normals
			textures.push_back(-(cost[j] * radius) + (sint[j] * radius)); textures.push_back(-(cost[j] * radius) + height);// Vector Textures
			vertices.push_back(cost[j] * radius);	vertices.push_back(sint[j] * radius);	vertices.push_back(height);	// Vector Vertices
		}
    //glEnd();

// ----------------------- VBO
	nv = vertices.size();	// Tamany del vector vertices en elements.
	nn = normals.size();	// Tamany del vector normals en elements.
	nc = colors.size();	// Tamany del vector colors en elements.
	nt = textures.size();	// Tamany del vector textures en elements.

	draw_GL_TRIANGLE_FAN_VBO(vertices, normals, colors, textures, nv / 3);

	vertices.resize(0);		textures.resize(0);		normals.resize(0);	// Reinicialitzar vectors

/* Do the stacks */
    z0 = 0.0;
    z1 = zStep;

    for (i=1; i<=stacks; i++)
    {   if (i==stacks) z1 = height;
	    //glBegin(GL_QUAD_STRIP);
            for (j=0; j<=slices; j++ )
            {   //glNormal3d(cost[j],        sint[j],        0.0 );
                //glVertex3d(cost[j]*radius, sint[j]*radius, z0  );
				colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);				// Vector Colors
				normals.push_back(cost[j]);				normals.push_back(sint[j]);				normals.push_back(0.0);		// Vector Normals
				textures.push_back(-(cost[j] * radius) + (sint[j] * radius)); textures.push_back(-(cost[j] * radius) + z0);	// Vector Textures
				vertices.push_back(cost[j] * radius);	vertices.push_back(sint[j] * radius);	vertices.push_back(z0);		// Vector Vertices
                
				//glVertex3d(cost[j]*radius, sint[j]*radius, z1  );
				colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);				// Vector Colors
				normals.push_back(cost[j]);				normals.push_back(sint[j]);				normals.push_back(0.0);		// Vector Normals
				textures.push_back(-(cost[j] * radius) + (sint[j] * radius)); textures.push_back(-(cost[j] * radius) + z1);	// Vector Textures
				vertices.push_back(cost[j] * radius);	vertices.push_back(sint[j] * radius);	vertices.push_back(z1);		// Vector Vertices


            }
        //glEnd();
        z0 = z1; z1 += zStep;
    }

// ---------------------- - VBO
	nv = vertices.size();	// Tamany del vector vertices en elements.
	nn = normals.size();	// Tamany del vector normals en elements.
	nc = colors.size();	// Tamany del vector colors en elements.
	nt = textures.size();	// Tamany del vector textures en elements.

	draw_GL_QUAD_STRIP_VBO(vertices, normals, colors, textures, nv / 3);

//---- DEFINICIÓ COORDENADES TEXTURA
	//Desactiva_Coordenades_Textura();

/* Release sin and cos tables */
    free(sint);
    free(cost);
}


/* ---------- TORUS -----------------------------------------------------*/
/*
 * Draws a solid torus
 */
void glutSolidTorus( GLdouble dInnerRadius, GLdouble dOuterRadius, GLint nSides, GLint nRings )
{
  double  iradius = dInnerRadius, oradius = dOuterRadius, phi, psi, dpsi, dphi;
  double *vertex, *normal;
  int    i, j;
  double spsi, cpsi, sphi, cphi ;
  //float modul = 0.0;
  CPunt3D val;

 // VBO
  GLuint vboId = 0;
  std::vector <float> vertices, normals, colors, textures;	// Definició vectors dinàmics per a vertexs, normals i textures 
  vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors

// Obtenir color actual definit en OpenGL amb glColor();
  GLfloat cColor[4];
  glGetFloatv(GL_CURRENT_COLOR, cColor);

//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidTorus" );

//---- DEFINICIÓ COORDENADES TEXTURA
  //Activa_Coordenades_Textura();

  if ( nSides < 1 ) nSides = 1;
  if ( nRings < 1 ) nRings = 1;

/* Increment the number of sides and rings to allow for one more point than surface */
  nSides ++ ;
  nRings ++ ;

/* Allocate the vertices array */
  vertex = (double *)calloc( sizeof(double), 3 * nSides * nRings );
  normal = (double *)calloc( sizeof(double), 3 * nSides * nRings );

  dpsi =  2.0 * pi / (double)(nRings - 1) ;
  dphi = -2.0 * pi / (double)(nSides - 1) ;
  psi  = 0.0;

  for( j=0; j<nRings; j++ )
  { cpsi = cos ( psi ) ;
    spsi = sin ( psi ) ;
    phi = 0.0;

    for( i=0; i<nSides; i++ )
    { int offset = 3 * ( j * nSides + i ) ;
      cphi = cos ( phi ) ;
      sphi = sin ( phi ) ;
      *(vertex + offset + 0) = cpsi * ( oradius + cphi * iradius ) ;
      *(vertex + offset + 1) = spsi * ( oradius + cphi * iradius ) ;
      *(vertex + offset + 2) =                    sphi * iradius  ;
      *(normal + offset + 0) = cpsi * cphi ;
      *(normal + offset + 1) = spsi * cphi ;
      *(normal + offset + 2) =        sphi ;
      phi += dphi;
    }
    psi += dpsi;
  }

  //glBegin( GL_QUADS );
    for( i=0; i<nSides-1; i++ )
    { for( j=0; j<nRings-1; j++ )
      { int offset = 3 * ( j * nSides + i ) ;

		colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);	// Vector Colors
		val.x = *(vertex + offset + 0);	val.y = *(vertex + offset + 1);	val.z = *(vertex + offset + 2);
		//modul = sqrt(val.x * val.x + val.y * val.y + val.z * val.z);	val.x = val.x / modul;	val.y = val.y / modul;	val.z = val.z / modul;
		textures.push_back(-val.x + val.y); textures.push_back(-val.x + val.z);							// Vector Textures
		//glNormal3dv(normal + offset);
		normals.push_back(*(normal + offset + 0));	normals.push_back(*(normal + offset + 1));	normals.push_back(*(normal + offset + 2)); // Vector Normals
		//glVertex3dv(vertex + offset);
		vertices.push_back(*(vertex + offset + 0));	vertices.push_back(*(vertex + offset + 1)); vertices.push_back(*(vertex + offset + 2)); // Vector Vertices

		colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);	// Vector Colors
		val.x = *(vertex + offset + 3);	val.y = *((vertex + offset + 3) + 1);	val.z = *((vertex + offset + 3) + 2);
		//modul = sqrt(val.x * val.x + val.y * val.y + val.z * val.z);	val.x = val.x / modul;	val.y = val.y / modul;	val.z = val.z / modul;
		textures.push_back(-val.x + val.y); textures.push_back(-val.x + val.z);							// Vector Textures
		//glNormal3dv(normal + offset + 3);
		normals.push_back(*(normal + offset + 3)); normals.push_back(*((normal + offset + 3) + 1));	normals.push_back(*((normal + offset + 3) + 2)); // Vector Normals
		//glVertex3dv(vertex + offset + 3);
		vertices.push_back(*(vertex + offset + 3));	vertices.push_back(*((vertex + offset + 3) + 1));	vertices.push_back(*((vertex + offset + 3) + 2)); // Vector Vertices

		colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);	// Vector Colors
		val.x = *((vertex + offset + 3 * nSides + 3) + 0);	val.y = *((vertex + offset + 3 * nSides + 3) + 1);	val.z = *((vertex + offset + 3 * nSides + 3) + 2);
		//modul = sqrt(val.x * val.x + val.y * val.y + val.z * val.z);	val.x = val.x / modul;	val.y = val.y / modul;	val.z = val.z / modul;
		textures.push_back(-val.x + val.y); textures.push_back(-val.x + val.z);							// Vector Textures
		//glNormal3dv(normal + offset + 3 * nSides + 3);
		normals.push_back(*((normal + offset + 3 * nSides + 3) + 0));	normals.push_back(*((normal + offset + 3 * nSides + 3) + 1)); normals.push_back(*((normal + offset + 3 * nSides + 3) + 2));	// Vector Normals
		//glVertex3dv(vertex + offset + 3 * nSides + 3);
		vertices.push_back(*((vertex + offset + 3 * nSides + 3) + 0));	vertices.push_back(*((vertex + offset + 3 * nSides + 3) + 1));	vertices.push_back(*((vertex + offset + 3 * nSides + 3) + 2)); // Vector Vertices

		colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);	// Vector Colors
		val.x = *((vertex + offset + 3 * nSides) + 0);	val.y = *((vertex + offset + 3 * nSides) + 1);	val.z = *((vertex + offset + 3 * nSides) + 2);
		//modul = sqrt(val.x * val.x + val.y * val.y + val.z * val.z);	val.x = val.x / modul;	val.y = val.y / modul;	val.z = val.z / modul;
		textures.push_back(-val.x + val.y); textures.push_back(-val.x + val.z);							// Vector Textures
		//glNormal3dv(normal + offset + 3 * nSides);
		normals.push_back(*((normal + offset + 3 * nSides) + 0));	normals.push_back(*((normal + offset + 3 * nSides) + 1)); normals.push_back(*((normal + offset + 3 * nSides) + 2));	// Vector Normals
		//glVertex3dv(vertex + offset + 3 * nSides);
		vertices.push_back(*((vertex + offset + 3 * nSides) + 0));	vertices.push_back(*((vertex + offset + 3 * nSides) + 1));	vertices.push_back(*((vertex + offset + 3 * nSides) + 2)); // Vector Vertices
      }
    }
  //glEnd();

  std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
  std::vector <int>::size_type nn = normals.size();		// Tamany del vector normals en elements.
  std::vector <int>::size_type nc = colors.size();		// Tamany del vector colors en elements.
  std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

  draw_GL_QUADS_VBO(vertices, normals, colors, textures, nv / 3);

  free ( vertex ) ;
  free ( normal ) ;

//---- DEFINICIÓ COORDENADES TEXTURA
  //Desactiva_Coordenades_Textura();
}


/* ---------- DODECAHEDRON -----------------------------------------------------*/
/*
 * Draws a solid dodecahedron
 */
void glutSolidDodecahedron( void )
{
// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, normals, colors, textures;	// Definició vectors dinàmics per a vertexs, normals i textures 

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidDodecahedron" );

//---- DEFINICIÓ COORDENADES TEXTURA
	Activa_Coordenades_Textura();

  /* Magic Numbers:  It is possible to create a dodecahedron by attaching two pentagons to each face of
   * of a cube.  The coordinates of the points are:
   *   (+-x,0, z); (+-1, 1, 1); (0, z, x )
   * where x = (-1 + sqrt(5))/2, z = (1 + sqrt(5))/2 or
   *       x = 0.61803398875 and z = 1.61803398875.
   */
  //glBegin ( GL_POLYGON ) ; // CARA 1
  //  glNormal3d (  0.0,  0.525731112119,  0.850650808354 ) ; glVertex3d (  0.0,  1.61803398875,  0.61803398875 ) ; glVertex3d ( -1.0,  1.0,  1.0 ) ; glVertex3d ( -0.61803398875, 0.0,  1.61803398875 ) ; glVertex3d (  0.61803398875, 0.0,  1.61803398875 ) ; glVertex3d (  1.0,  1.0,  1.0 ) ;
  //glEnd () ;

	vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors
// VBO CARA 1
  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(0.525731112119);	normals.push_back(0.850650808354);	// Vector Normals
  textures.push_back(1.61803398875); textures.push_back(0.61803398875);									// Vector Textures
  vertices.push_back(0.0);	vertices.push_back(1.61803398875);	vertices.push_back(0.61803398875);		// Vector Vertices

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(0.525731112119);	normals.push_back(0.850650808354);	// Vector Normals
  textures.push_back(2.0); textures.push_back(2.0);														// Vector Textures
  vertices.push_back(-1.0);	vertices.push_back(1.0);	vertices.push_back(1.0);						// Vector Vertices

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(0.525731112119);	normals.push_back(0.850650808354);	// Vector Normals
  textures.push_back(0.61803398875); textures.push_back(0.61803398875 + 1.61803398875);					// Vector Textures
  vertices.push_back(-0.61803398875);	vertices.push_back(0.0);	vertices.push_back(1.61803398875);	// Vector Vertices

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(0.525731112119);	normals.push_back(0.850650808354);	// Vector Normals
  textures.push_back(-0.61803398875); textures.push_back(-0.61803398875 + 1.61803398875);				// Vector Textures
  vertices.push_back(0.61803398875);	vertices.push_back(0.0);	vertices.push_back(1.61803398875);	// Vector Vertices
 
  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(0.525731112119);	normals.push_back(0.850650808354);	// Vector Normals
  textures.push_back(0.0); textures.push_back(0.0);														// Vector textures
  vertices.push_back(1.0);	vertices.push_back(1.0);			vertices.push_back(1.0);				// Vector Vertices

  std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
  std::vector <int>::size_type nn = normals.size();		// Tamany del vector normals en elements.
  std::vector <int>::size_type nc = colors.size();		// Tamany del vector colors en elements.
  std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

  draw_GL_POLYGON_VBO(vertices, normals, colors, textures, nv / 3);

/*
  glBegin ( GL_POLYGON ) ; // CARA 2
    glNormal3d (  0.0,  0.525731112119, -0.850650808354 ) ; glVertex3d (  0.0,  1.61803398875, -0.61803398875 ) ; glVertex3d (  1.0,  1.0, -1.0 ) ; glVertex3d (  0.61803398875, 0.0, -1.61803398875 ) ; glVertex3d ( -0.61803398875, 0.0, -1.61803398875 ) ; glVertex3d ( -1.0,  1.0, -1.0 ) ;
  glEnd () ;
*/

  vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors
// VBO CARA 2
  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(0.525731112119);	normals.push_back(-0.850650808354);	// Vector Normals
  vertices.push_back(0.0);	vertices.push_back(1.61803398875);	vertices.push_back(-0.61803398875);		// Vector Vertices
  textures.push_back(1.61803398875); textures.push_back(-0.61803398875);								// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(0.525731112119);	normals.push_back(-0.850650808354);	// Vector Normals
  vertices.push_back(1.0);	vertices.push_back(1.0);			vertices.push_back(-1.0);				// Vector Vertices
  textures.push_back(0.0);	textures.push_back(-2.0);													// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(0.525731112119);	normals.push_back(-0.850650808354);	// Vector Normals
  vertices.push_back(0.61803398875);	vertices.push_back(0.0);	vertices.push_back(-1.61803398875);	// Vector Vertices
  textures.push_back(-0.61803398875); textures.push_back(-0.61803398875 - 1.61803398875);				// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(0.525731112119);	normals.push_back(-0.850650808354);	// Vector Normals
  vertices.push_back(-0.61803398875);	vertices.push_back(0.0);	vertices.push_back(-1.61803398875);	// Vector Vertices
  textures.push_back(0.61803398875); textures.push_back(0.61803398875 - 1.61803398875);					// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(0.525731112119);	normals.push_back(-0.850650808354);	// Vector Normals
  vertices.push_back(-1.0);	vertices.push_back(1.0);			vertices.push_back(-1.0);				// Vector Vertices
  textures.push_back(2.0);	textures.push_back(0.0);													// Vector textures

  nv = vertices.size();	// Tamany del vector vertices en elements.
  nn = normals.size();	// Tamany del vector normals en elements.
  nc = colors.size();	// Tamany del vector colors en elements.
  nt = textures.size();	// Tamany del vector textures en elements.

  draw_GL_POLYGON_VBO(vertices, normals, colors, textures, nv / 3);

/*
  glBegin ( GL_POLYGON ) ;	// CARA 3
    glNormal3d (  0.0, -0.525731112119,  0.850650808354 ) ; glVertex3d (  0.0, -1.61803398875,  0.61803398875 ) ; glVertex3d (  1.0, -1.0,  1.0 ) ; glVertex3d (  0.61803398875, 0.0,  1.61803398875 ) ; glVertex3d ( -0.61803398875, 0.0,  1.61803398875 ) ; glVertex3d ( -1.0, -1.0,  1.0 ) ;
  glEnd () ;
*/

  vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors
// VBO CARA 3
  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(-0.525731112119);	normals.push_back(0.850650808354);	// Vector Normals
  vertices.push_back(0.0);	vertices.push_back(-1.61803398875);	vertices.push_back(0.61803398875);		// Vector Vertices
  textures.push_back(-1.61803398875); textures.push_back(0.61803398875);								// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(-0.525731112119);	normals.push_back(0.850650808354);	// Vector Normals
  vertices.push_back(1.0);	vertices.push_back(-1.0);	vertices.push_back(1.0);						// Vector Vertices
  textures.push_back(-2.0);	textures.push_back(0.0);													// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(-0.525731112119);	normals.push_back(0.850650808354);	// Vector Normals
  vertices.push_back(0.61803398875);	vertices.push_back(0.0);	vertices.push_back(1.61803398875);	// Vector Vertices
  textures.push_back(-0.61803398875); textures.push_back(-0.61803398875 + 1.61803398875);				// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(-0.525731112119);	normals.push_back(0.850650808354);	// Vector Normals
  vertices.push_back(-0.61803398875);	vertices.push_back(0.0);	vertices.push_back(1.61803398875);	// Vector Vertices
  textures.push_back(0.61803398875); textures.push_back(0.61803398875 + 1.61803398875);					// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(-0.525731112119);	normals.push_back(0.850650808354);	// Vector Normals
  vertices.push_back(-1.0);	vertices.push_back(-1.0);			vertices.push_back(1.0);				// Vector Vertices
  textures.push_back(0.0);	textures.push_back(2.0);													// Vector textures

  nv = vertices.size();	// Tamany del vector vertices en elements.
  nn = normals.size();	// Tamany del vector normals en elements.
  nc = colors.size();		// Tamany del vector colors en elements.
  nt = textures.size();	// Tamany del vector textures en elements.

  draw_GL_POLYGON_VBO(vertices, normals, textures, colors, nv / 3);
/*
  glBegin ( GL_POLYGON ) ;	// CARA 4
    glNormal3d (  0.0, -0.525731112119, -0.850650808354 ) ; glVertex3d (  0.0, -1.61803398875, -0.61803398875 ) ; glVertex3d ( -1.0, -1.0, -1.0 ) ; glVertex3d ( -0.61803398875, 0.0, -1.61803398875 ) ; glVertex3d (  0.61803398875, 0.0, -1.61803398875 ) ; glVertex3d (  1.0, -1.0, -1.0 ) ;
  glEnd () ;
*/

  vertices.resize(0);		normals.resize(0);	colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors
// VBO CARA 4
  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(-0.525731112119);	normals.push_back(-0.850650808354);	// Vector Normals
  vertices.push_back(0.0);	vertices.push_back(-1.61803398875);	vertices.push_back(-0.61803398875);		// Vector Vertices
  textures.push_back(-1.61803398875); textures.push_back(-0.61803398875);								// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(-0.525731112119);	normals.push_back(-0.850650808354);	// Vector Normals
  vertices.push_back(-1.0);	vertices.push_back(-1.0);	vertices.push_back(-1.0);						// Vector Vertices
  textures.push_back(0.0);	textures.push_back(0.0);													// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(-0.525731112119);	normals.push_back(-0.850650808354);	// Vector Normals
  vertices.push_back(-0.61803398875);	vertices.push_back(0.0);	vertices.push_back(-1.61803398875);	// Vector Vertices
  textures.push_back(0.61803398875); textures.push_back(0.61803398875 - 1.61803398875);					// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(-0.525731112119);	normals.push_back(-0.850650808354);	// Vector Normals
  vertices.push_back(0.61803398875);	vertices.push_back(0.0);	vertices.push_back(-1.61803398875);	// Vector Vertices
  textures.push_back(-0.61803398875); textures.push_back(-0.61803398875 - 1.61803398875);				// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.0);		normals.push_back(-0.525731112119);	normals.push_back(-0.850650808354);	// Vector Normals
  vertices.push_back(1.0);	vertices.push_back(-1.0);			vertices.push_back(-1.0);				// Vector Vertices
  textures.push_back(-2.0);	textures.push_back(-2.0);													// Vector textures

  nv = vertices.size();	// Tamany del vector vertices en elements.
  nn = normals.size();	// Tamany del vector normals en elements.
  nc = colors.size();	// Tamany del vector colors en elements.
  nt = textures.size();	// Tamany del vector textures en elements.

  draw_GL_POLYGON_VBO(vertices, normals, colors, textures, nv / 3);

/*
  glBegin ( GL_POLYGON ) ;	// CARA 5
    glNormal3d (  0.850650808354,  0.0,  0.525731112119 ) ; glVertex3d (  0.61803398875,  0.0,  1.61803398875 ) ; glVertex3d (  1.0, -1.0,  1.0 ) ; glVertex3d (  1.61803398875, -0.61803398875, 0.0 ) ; glVertex3d (  1.61803398875,  0.61803398875, 0.0 ) ; glVertex3d (  1.0,  1.0,  1.0 ) ;
  glEnd () ;
*/

  vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors
// VBO CARA 5
  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.850650808354);	normals.push_back(0.0);	normals.push_back(0.525731112119);	// Vector Normals
  vertices.push_back(0.61803398875);	vertices.push_back(0.0); vertices.push_back(1.61803398875);	// Vector Vertices
  textures.push_back(-0.61803398875);	textures.push_back(-0.61803398875 + 1.61803398875);			// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.850650808354);	normals.push_back(0.0);	 normals.push_back(0.525731112119);	// Vector Normals
  vertices.push_back(1.0);			vertices.push_back(-1.0); vertices.push_back(1.0);				// Vector Vertices
  textures.push_back(-2.0);			textures.push_back(0.0);										// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.850650808354);	normals.push_back(0.0);	normals.push_back(0.525731112119);	// Vector Normals
  vertices.push_back(1.61803398875);	vertices.push_back(-0.61803398875); vertices.push_back(0.0);// Vector Vertices
  textures.push_back(-1.61803398875 - 0.61803398875);  textures.push_back(-1.61803398875);			// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.850650808354);	normals.push_back(0.0);	normals.push_back(0.525731112119);	// Vector Normals
  vertices.push_back(1.61803398875);	vertices.push_back(0.61803398875); vertices.push_back(0.0);	// Vector Vertices
  textures.push_back(-1.61803398875 + 0.61803398875); textures.push_back(-1.61803398875);			// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.850650808354);	normals.push_back(0.0);	normals.push_back(0.525731112119);	// Vector Normals
  vertices.push_back(1.0);			vertices.push_back(1.0); vertices.push_back(1.0);				// Vector Vertices
  textures.push_back(0.0);			textures.push_back(0.0);										// Vector textures

  nv = vertices.size();	// Tamany del vector vertices en elements.
  nn = normals.size();	// Tamany del vector normals en elements.
  nc = colors.size();	// Tamany del vector colors en elements.
  nt = textures.size();	// Tamany del vector textures en elements.

  draw_GL_POLYGON_VBO(vertices, normals, colors, textures, nv / 3);

 /*
  glBegin ( GL_POLYGON ) ;	// CARA 6
    glNormal3d ( -0.850650808354,  0.0,  0.525731112119 ) ; glVertex3d ( -0.61803398875,  0.0,  1.61803398875 ) ; glVertex3d ( -1.0,  1.0,  1.0 ) ; glVertex3d ( -1.61803398875,  0.61803398875, 0.0 ) ; glVertex3d ( -1.61803398875, -0.61803398875, 0.0 ) ; glVertex3d ( -1.0, -1.0,  1.0 ) ;
  glEnd () ;
 */

  vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);		// Reinicialitzar vectors
// VBO CARA 6
  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.850650808354);	normals.push_back(0.0);	normals.push_back(0.525731112119);	// Vector Normals
  vertices.push_back(-0.61803398875);	vertices.push_back(0.0); vertices.push_back(1.61803398875);	// Vector Vertices
  textures.push_back(0.61803398875);	textures.push_back(0.61803398875 + 1.61803398875);			// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(-0.850650808354);	normals.push_back(0.0);	normals.push_back(0.525731112119);	// Vector Normals
  vertices.push_back(-1.0);			vertices.push_back(1.0); vertices.push_back(1.0);				// Vector Vertices
  textures.push_back(2.0);			textures.push_back(2.0);										// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(-0.850650808354);	normals.push_back(0.0);	normals.push_back(0.525731112119);	// Vector Normals
  vertices.push_back(-1.61803398875);	vertices.push_back(0.61803398875); vertices.push_back(0.0);	// Vector Vertices
  textures.push_back(1.61803398875 + 0.61803398875); textures.push_back(1.61803398875);				// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(-0.850650808354);	normals.push_back(0.0);	normals.push_back(0.525731112119);	// Vector Normals
  vertices.push_back(-1.61803398875);	vertices.push_back(-0.61803398875); vertices.push_back(0.0);// Vector Vertices
  textures.push_back(1.61803398875 - 0.61803398875); textures.push_back(1.61803398875);				// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.850650808354);	normals.push_back(0.0);	normals.push_back(0.525731112119);	// Vector Normals
  vertices.push_back(-1.0);			vertices.push_back(-1.0); vertices.push_back(1.0);				// Vector Vertices
  textures.push_back(0.0);			textures.push_back(2.0);										// Vector textures

  nv = vertices.size();	// Tamany del vector vertices en elements.
  nn = normals.size();	// Tamany del vector normals en elements.
  nc = colors.size();	// Tamany del vector colors en elements.
  nt = textures.size();	// Tamany del vector textures en elements.

  draw_GL_POLYGON_VBO(vertices, normals, colors, textures, nv / 3);
 /*
  glBegin ( GL_POLYGON ) ;	// CARA 7
    glNormal3d (  0.850650808354,  0.0, -0.525731112119 ) ; glVertex3d (  0.61803398875,  0.0, -1.61803398875 ) ; glVertex3d (  1.0,  1.0, -1.0 ) ; glVertex3d (  1.61803398875,  0.61803398875, 0.0 ) ; glVertex3d (  1.61803398875, -0.61803398875, 0.0 ) ; glVertex3d (  1.0, -1.0, -1.0 ) ;
  glEnd () ;
 */

  vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors
 // VBO CARA 7
  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.850650808354);	normals.push_back(0.0);	normals.push_back(-0.850650808354);		// Vector Normals
  vertices.push_back(0.61803398875);	vertices.push_back(0.0); vertices.push_back(-1.61803398875);	// Vector Vertices
  textures.push_back(-0.61803398875); textures.push_back(-0.61803398875 - 1.61803398875);				// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.850650808354);	normals.push_back(0.0);	normals.push_back(-0.850650808354);		// Vector Normals
  vertices.push_back(1.0);			vertices.push_back(1.0); vertices.push_back(-1.0);					// Vector Vertices
  textures.push_back(0.0); textures.push_back(-2.0);													// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.850650808354);	normals.push_back(0.0);	normals.push_back(-0.850650808354);		// Vector Normals
  vertices.push_back(1.61803398875);	vertices.push_back(0.61803398875);	vertices.push_back(0.0);	// Vector Vertices
  textures.push_back(-1.61803398875 + 0.61803398875); textures.push_back(-1.61803398875);				// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.850650808354);	normals.push_back(0.0);	normals.push_back(-0.850650808354);		// Vector Normals
  vertices.push_back(1.61803398875);	vertices.push_back(-0.61803398875);	vertices.push_back(0.0);	// Vector Vertices
  textures.push_back(-1.61803398875 - 0.61803398875); textures.push_back(-1.61803398875);				// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
  normals.push_back(0.850650808354);	normals.push_back(0.0);	normals.push_back(-0.850650808354);		// Vector Normals
  vertices.push_back(1.0);			vertices.push_back(-1.0); vertices.push_back(-1.0);					// Vector Vertices
  textures.push_back(-2.0); textures.push_back(-2.0);													// Vector textures

  nv = vertices.size();	// Tamany del vector vertices en elements.
  nn = normals.size();	// Tamany del vector normals en elements.
  nc = colors.size();	// Tamany del vector colors en elements.
  nt = textures.size();	// Tamany del vector textures en elements.

  draw_GL_POLYGON_VBO(vertices, normals, colors, textures, nv / 3);

/*
  glBegin ( GL_POLYGON ) ;	// CARA 8
    glNormal3d ( -0.850650808354,  0.0, -0.525731112119 ) ; glVertex3d ( -0.61803398875,  0.0, -1.61803398875 ) ; glVertex3d ( -1.0, -1.0, -1.0 ) ; glVertex3d ( -1.61803398875, -0.61803398875, 0.0 ) ; glVertex3d ( -1.61803398875,  0.61803398875, 0.0 ) ; glVertex3d ( -1.0,  1.0, -1.0 ) ;
  glEnd () ;
*/

  vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);		// Reinicialitzar vectors
// VBO CARA 8
  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.850650808354);	normals.push_back(0.0);	normals.push_back(-0.525731112119);	// Vector Normals
  vertices.push_back(-0.61803398875);	vertices.push_back(0.0); vertices.push_back(-1.61803398875);// Vector Vertices
  textures.push_back(0.61803398875);  textures.push_back(0.61803398875 - 1.61803398875);			// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.850650808354);	normals.push_back(0.0);	normals.push_back(-0.525731112119);	// Vector Normals
  vertices.push_back(-1.0);	vertices.push_back(-1.0);	vertices.push_back(-1.0);					// Vector Vertices
  textures.push_back(0.0); textures.push_back(0.0);													// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.850650808354);	normals.push_back(0.0);	normals.push_back(-0.525731112119);	// Vector Normals
  vertices.push_back(-1.61803398875);	vertices.push_back(-0.61803398875);	vertices.push_back(0.0);// Vector Vertices
  textures.push_back(1.61803398875 - 0.61803398875); textures.push_back(1.61803398875);				// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.850650808354);	normals.push_back(0.0);	normals.push_back(-0.525731112119);	// Vector Normals
  vertices.push_back(-1.61803398875);	vertices.push_back(0.61803398875);	vertices.push_back(0.0);// Vector Vertices
  textures.push_back(1.61803398875 + 0.61803398875); textures.push_back(1.61803398875);				// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.850650808354);	normals.push_back(0.0);	normals.push_back(-0.525731112119);	// Vector Normals
  vertices.push_back(-1.0);			vertices.push_back(1.0); vertices.push_back(-1.0);				// Vector Vertices
  textures.push_back(2.0);			textures.push_back(0.0);										// Vector textures

  nv = vertices.size();	// Tamany del vector vertices en elements.
  nn = normals.size();	// Tamany del vector normals en elements.
  nc = colors.size();	// Tamany del vector colors en elements.
  nt = textures.size();	// Tamany del vector textures en elements.

  draw_GL_POLYGON_VBO(vertices, normals, colors, textures, nv / 3);

/*
  glBegin ( GL_POLYGON ) ;	// CARA 9
    glNormal3d (  0.525731112119,  0.850650808354,  0.0 ) ; glVertex3d (  1.61803398875,  0.61803398875,  0.0 ) ; glVertex3d (  1.0,  1.0, -1.0 ) ; glVertex3d ( 0.0,  1.61803398875, -0.61803398875 ) ; glVertex3d ( 0.0,  1.61803398875,  0.61803398875 ) ; glVertex3d (  1.0,  1.0,  1.0 ) ;
  glEnd () ;
*/

  vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors
// VBO CARA 9
  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.525731112119);	normals.push_back(0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(1.61803398875);	vertices.push_back(0.61803398875);	vertices.push_back(0.0);// Vector Vertices
  textures.push_back(-1.61803398875 + 0.61803398875); textures.push_back(-1.61803398875);			// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.525731112119);	normals.push_back(0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(1.0);			vertices.push_back(1.0);			vertices.push_back(-1.0);	// Vector Vertices
  textures.push_back(0.0);			textures.push_back(-2.0);										// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.525731112119);	normals.push_back(0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(0.0); vertices.push_back(1.61803398875);	vertices.push_back(-0.61803398875);	// Vector Vertices
  textures.push_back(1.61803398875); textures.push_back(-0.61803398875);							// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.525731112119);	normals.push_back(0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(0.0);	vertices.push_back(1.61803398875);	vertices.push_back(0.61803398875);	// Vector Vertices
  textures.push_back(1.61803398875);	textures.push_back(0.61803398875);							// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.525731112119);	normals.push_back(0.850650808354);	normals.push_back(-0.850650808354);	// Vector Normals
  vertices.push_back(1.0);			vertices.push_back(1.0);			vertices.push_back(1.0);	// Vector Vertices
  textures.push_back(0.0);			textures.push_back(0.0);										// Vector textures

  nv = vertices.size();	// Tamany del vector vertices en elements.
  nn = normals.size();	// Tamany del vector normals en elements.
  nc = colors.size();	// Tamany del vector colors en elements.
  nt = textures.size();	// Tamany del vector textures en elements.

  draw_GL_POLYGON_VBO(vertices, normals, colors, textures, nv / 3);

//  glBegin ( GL_POLYGON ) ;	// CARA 10
//    glNormal3d (  0.525731112119, -0.850650808354,  0.0 ) ; glVertex3d (  1.61803398875, -0.61803398875,  0.0 ) ; glVertex3d (  1.0, -1.0,  1.0 ) ; glVertex3d ( 0.0, -1.61803398875,  0.61803398875 ) ; glVertex3d ( 0.0, -1.61803398875, -0.61803398875 ) ; glVertex3d (  1.0, -1.0, -1.0 ) ;
//  glEnd () ;
  
  vertices.resize(0);		textures.resize(0);		normals.resize(0);	// Reinicialitzar vectors
// VBO CARA 10
  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.525731112119);	normals.push_back(-0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(1.61803398875);	vertices.push_back(-0.61803398875);	vertices.push_back(0.0);// Vector Vertices
  textures.push_back(-1.61803398875 - 0.61803398875); textures.push_back(-1.61803398875);			// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.525731112119);	normals.push_back(-0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(1.0);			vertices.push_back(-1.0);	vertices.push_back(1.0);			// Vector Vertices
  textures.push_back(-2.0);			textures.push_back(0.0);										// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.525731112119);	normals.push_back(-0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(0.0);	vertices.push_back(-1.61803398875);	vertices.push_back(0.61803398875);	// Vector Vertices
  textures.push_back(-1.61803398875); textures.push_back(0.61803398875);							// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.525731112119);	normals.push_back(-0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(0.0);	vertices.push_back(-1.61803398875);	vertices.push_back(-0.61803398875);	// Vector Vertices
  textures.push_back(-1.61803398875); textures.push_back(-0.61803398875);							// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(0.525731112119);	normals.push_back(-0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(1.0);			vertices.push_back(-1.0);			vertices.push_back(-1.0);	// Vector Vertices
  textures.push_back(-2.0);			textures.push_back(-2.0);										// Vector textures

  nv = vertices.size();	// Tamany del vector vertices en elements.
  nn = normals.size();	// Tamany del vector normals en elements.
  nc = colors.size();	// Tamany del vector colors en elements.
  nt = textures.size();	// Tamany del vector textures en elements.

  draw_GL_POLYGON_VBO(vertices, normals, colors, textures, nv / 3);
 
/*
  glBegin ( GL_POLYGON ) ;	// CARA 11
    glNormal3d ( -0.525731112119,  0.850650808354,  0.0 ) ; glVertex3d ( -1.61803398875,  0.61803398875,  0.0 ) ; glVertex3d ( -1.0,  1.0,  1.0 ) ; glVertex3d ( 0.0,  1.61803398875,  0.61803398875 ) ; glVertex3d ( 0.0,  1.61803398875, -0.61803398875 ) ; glVertex3d ( -1.0,  1.0, -1.0 ) ;
  glEnd () ;
*/

  vertices.resize(0);		textures.resize(0);		normals.resize(0);	// Reinicialitzar vectors
// VBO CARA 11
  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.525731112119);	normals.push_back(0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(-1.61803398875);	vertices.push_back(0.61803398875);	vertices.push_back(0.0);// Vector Vertices
  textures.push_back(1.61803398875 + 0.61803398875); textures.push_back(1.61803398875);				// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.525731112119);	normals.push_back(0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(-1.0);			vertices.push_back(1.0);			vertices.push_back(1.0);	// Vector Vertices
  textures.push_back(2.0);			textures.push_back(2.0);										// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.525731112119);	normals.push_back(0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(0.0);	vertices.push_back(1.61803398875);	vertices.push_back(0.61803398875);	// Vector Vertices
  textures.push_back(1.61803398875); textures.push_back(0.61803398875);								// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.525731112119);	normals.push_back(0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(0.0);	vertices.push_back(1.61803398875);	vertices.push_back(-0.61803398875);	// Vector Vertices
  textures.push_back(1.61803398875); textures.push_back(-0.61803398875);							// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.525731112119);	normals.push_back(0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(-1.0);			vertices.push_back(1.0);			vertices.push_back(-1.0);	// Vector Vertices
  textures.push_back(2.0);			textures.push_back(0.0);										// Vector textures

  nv = vertices.size();	// Tamany del vector vertices en elements.
  nn = normals.size();	// Tamany del vector normals en elements.
  nc = colors.size();	// Tamany del vector colors en elements.
  nt = textures.size();	// Tamany del vector textures en elements.

  draw_GL_POLYGON_VBO(vertices, normals, colors, textures, nv / 3);
  
/*
  glBegin ( GL_POLYGON ) ;	// CARA 12
    glNormal3d ( -0.525731112119, -0.850650808354,  0.0 ) ; glVertex3d ( -1.61803398875, -0.61803398875,  0.0 ) ; glVertex3d ( -1.0, -1.0, -1.0 ) ; glVertex3d ( 0.0, -1.61803398875, -0.61803398875 ) ; glVertex3d ( 0.0, -1.61803398875,  0.61803398875 ) ; glVertex3d ( -1.0, -1.0,  1.0 ) ;
  glEnd () ;
*/

  vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);		// Reinicialitzar vectors
// VBO CARA 12
  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.525731112119);	normals.push_back(-0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(-1.61803398875);	vertices.push_back(-0.61803398875);	vertices.push_back(0.0);// Vector Vertices
  textures.push_back(1.61803398875 - 0.61803398875); textures.push_back(1.61803398875);				// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.525731112119);	normals.push_back(-0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(-1.0);			vertices.push_back(-1.0);			vertices.push_back(-1.0);	// Vector Vertices
  textures.push_back(0.0);			textures.push_back(0.0);										// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.525731112119);	normals.push_back(-0.850650808354);	normals.push_back(0.00);// Vector Normals
  vertices.push_back(0.0);	vertices.push_back(-1.61803398875);	vertices.push_back(-0.61803398875);	// Vector Vertices
  textures.push_back(-1.61803398875); textures.push_back(-0.61803398875);							// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.525731112119);	normals.push_back(-0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(0.0);	vertices.push_back(-1.61803398875);	vertices.push_back(0.61803398875);	// Vector Vertices
  textures.push_back(-1.61803398875); textures.push_back(0.61803398875);							// Vector Textures

  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
  normals.push_back(-0.525731112119);	normals.push_back(-0.850650808354);	normals.push_back(0.0);	// Vector Normals
  vertices.push_back(-1.0);			vertices.push_back(-1.0);			vertices.push_back(1.0);	// Vector Vertices
  textures.push_back(0.0);			textures.push_back(2.0);										// Vector textures

  nv = vertices.size();	// Tamany del vector vertices en elements.
  nn = normals.size();	// Tamany del vector normals en elements.
  nc = colors.size();	// Tamany del vector colors en elements.
  nt = textures.size();	// Tamany del vector textures en elements.

  draw_GL_POLYGON_VBO(vertices, normals, colors, textures, nv / 3);

 //---- DEFINICIÓ COORDENADES TEXTURA
  //Desactiva_Coordenades_Textura();
}


/* ---------- OCTAHEDRON -----------------------------------------------------*/

/*
* Draws a solid octahedron
 */
void glutSolidOctahedron( void )
{
//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidOctahedron" );

// VBO
	GLuint vboId = 0;

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

//---- DEFINICIÓ COORDENADES TEXTURA
	//Activa_Coordenades_Textura();

#define RADIUS    1.0f
// vertex coords array for glDrawArrays() =====================================
// A octahedron has 8 sides and each side has 1 triangle, therefore, a octahedron consists
// of 24 vertices (8 sides * 1 triangle * 3 vertices = 24 vertices). And, each
// vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
// array is 72 floats (24 * 3 = 72).
	GLfloat vertices[] = { RADIUS, 0.0, 0.0, 0.0, RADIUS, 0.0, 0.0, 0.0, RADIUS,   // v0-v1-v2 (front)
		RADIUS, 0.0, 0.0, 0.0, 0.0, -RADIUS, 0.0, RADIUS, 0.0, 		// v3-v4-v5 (right)
		RADIUS, 0.0, 0.0, 0.0, 0.0, RADIUS, 0.0, -RADIUS, 0.0,		// v0-v5-v6 (top)
		RADIUS, 0.0, 0.0, 0.0, -RADIUS, 0.0, 0.0, 0.0, -RADIUS,     // v1-v6-v7 (left)
		-RADIUS, 0.0, 0.0, 0.0, 0.0, RADIUS, 0.0, RADIUS, 0.0,      // v2-v7-v4 (bottom)
		-RADIUS, 0.0, 0.0, 0.0, RADIUS, 0.0, 0.0, 0.0, -RADIUS,      // v2-v7-v4 (bottom)
		-RADIUS, 0.0, 0.0, 0.0, -RADIUS, 0.0, 0.0, 0.0, RADIUS,      // v2-v7-v4 (bottom)
		-RADIUS, 0.0, 0.0, 0.0, 0.0, -RADIUS, 0.0, -RADIUS, 0.0 };   // v7-v6-v5 (back)

// Normal array
	GLfloat normals[] = { 0.577350269189, 0.577350269189, 0.577350269189, 0.577350269189, 0.577350269189, 0.577350269189, 0.577350269189, 0.577350269189, 0.577350269189,   // v0-v1-v2 
		0.577350269189, 0.577350269189, -0.577350269189, 0.577350269189, 0.577350269189, -0.577350269189, 0.577350269189, 0.577350269189, -0.577350269189, 		// v3-v4-v5-v0 (right)
		0.577350269189, -0.577350269189, 0.577350269189, 0.577350269189, -0.577350269189, 0.577350269189, 0.577350269189, -0.577350269189, 0.577350269189,		// v0-v5-v6-v1 (top)
		0.577350269189, -0.577350269189, -0.577350269189, 0.577350269189, -0.577350269189, -0.577350269189, 0.577350269189, -0.577350269189, -0.577350269189, 	// v1-v6-v7-v2 (left)
		-0.577350269189, 0.577350269189, 0.577350269189, -0.577350269189, 0.577350269189, 0.577350269189, -0.577350269189, 0.577350269189, 0.577350269189, 		// v2-v7-v4-v3 (bottom)
		-0.577350269189, 0.577350269189, -0.577350269189, -0.577350269189, 0.577350269189, -0.577350269189, -0.577350269189, 0.577350269189, -0.577350269189, 	// v2-v7-v4-v3 (bottom)
		-0.577350269189, -0.577350269189, 0.577350269189, -0.577350269189, -0.577350269189, 0.577350269189, -0.577350269189, -0.577350269189, 0.577350269189, 	// v2-v7-v4-v3 (bottom)
		-0.577350269189, -0.577350269189, -0.577350269189, -0.577350269189, -0.577350269189, -0.577350269189, -0.577350269189, -0.577350269189, -0.577350269189 };	// v7-v6-v5-v4 (back)

// Color array
	GLfloat colors[] = { cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2],   // v0-v1-v2 
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], 		// v3-v4-v5-v0 (right)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2],		// v0-v5-v6-v1 (top)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2],  	// v1-v6-v7-v2 (left)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], 		// v2-v7-v4-v3 (bottom)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2],  	// v2-v7-v4-v3 (bottom)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2],  	// v2-v7-v4-v3 (bottom)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2] };	// v7-v6-v5-v4 (back)

// Texture Array
	GLfloat textures[] = { -RADIUS, -RADIUS, RADIUS, 0.0, 0.0, RADIUS,    // v0-v1-v2 (front)
		-RADIUS, -RADIUS, 0.0, -RADIUS, RADIUS, 0.0,   // v3-v4-v5 (right)
		-RADIUS, -RADIUS, 0.0, RADIUS, -RADIUS, 0.0,    // v0-v5-v6 (top)
		-RADIUS, -RADIUS, -RADIUS, 0.0, 0.0, -RADIUS,   // v1-v6-v7 (left)
		RADIUS, RADIUS, 0.0, RADIUS, RADIUS, 0.0,		// v2-v7-v4 (bottom)
		RADIUS, RADIUS, RADIUS, 0.0, 0.0, -RADIUS,		// v2-v7-v4 (bottom)
		RADIUS, RADIUS, -RADIUS, 0.0, 0.0, RADIUS,		// v2-v7-v4 (bottom)
		RADIUS, RADIUS, 0.0, -RADIUS, -RADIUS, 0.0 };  // v7-v6-v5 (back)
#undef RADIUS

/*
  glBegin( GL_TRIANGLES );
    glNormal3d( 0.577350269189, 0.577350269189, 0.577350269189); glVertex3d( RADIUS, 0.0, 0.0 ); glVertex3d( 0.0, RADIUS, 0.0 ); glVertex3d( 0.0, 0.0, RADIUS );
    glNormal3d( 0.577350269189, 0.577350269189,-0.577350269189); glVertex3d( RADIUS, 0.0, 0.0 ); glVertex3d( 0.0, 0.0,-RADIUS ); glVertex3d( 0.0, RADIUS, 0.0 );
    glNormal3d( 0.577350269189,-0.577350269189, 0.577350269189); glVertex3d( RADIUS, 0.0, 0.0 ); glVertex3d( 0.0, 0.0, RADIUS ); glVertex3d( 0.0,-RADIUS, 0.0 );
    glNormal3d( 0.577350269189,-0.577350269189,-0.577350269189); glVertex3d( RADIUS, 0.0, 0.0 ); glVertex3d( 0.0,-RADIUS, 0.0 ); glVertex3d( 0.0, 0.0,-RADIUS );
    glNormal3d(-0.577350269189, 0.577350269189, 0.577350269189); glVertex3d(-RADIUS, 0.0, 0.0 ); glVertex3d( 0.0, 0.0, RADIUS ); glVertex3d( 0.0, RADIUS, 0.0 );
    glNormal3d(-0.577350269189, 0.577350269189,-0.577350269189); glVertex3d(-RADIUS, 0.0, 0.0 ); glVertex3d( 0.0, RADIUS, 0.0 ); glVertex3d( 0.0, 0.0,-RADIUS );
    glNormal3d(-0.577350269189,-0.577350269189, 0.577350269189); glVertex3d(-RADIUS, 0.0, 0.0 ); glVertex3d( 0.0,-RADIUS, 0.0 ); glVertex3d( 0.0, 0.0, RADIUS );
    glNormal3d(-0.577350269189,-0.577350269189,-0.577350269189); glVertex3d(-RADIUS, 0.0, 0.0 ); glVertex3d( 0.0, 0.0,-RADIUS ); glVertex3d( 0.0,-RADIUS, 0.0 );
  glEnd();
*/

// Create vertex buffer objects, you need to delete them when program exits
// Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
// glBufferDataARB with NULL pointer reserves only memory space.
// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
// target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
  glGenBuffersARB(1, &vboId);
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
  glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals) + +sizeof(colors) + sizeof(textures), 0, GL_STATIC_DRAW_ARB);
  glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(vertices), vertices);                             // copy vertices starting from 0 offest
  glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices), sizeof(normals), normals);                // copy normals after vertices
  glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals), sizeof(colors), colors);  // copy colours after normals
  glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals) + sizeof(colors), sizeof(textures), textures);  // copy textures after colours

// Bind VBOs with IDs and set the buffer offsets of the bound VBOs
// When buffer object is bound with its ID, all pointers in gl*Pointer()
// are treated as offset instead of real pointer.
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

// Enable vertex arrays
  glEnableClientState(GL_TEXTURE_COORD_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnableClientState(GL_VERTEX_ARRAY);

// Before draw, specify vertex and index arrays with their offsets
  glTexCoordPointer(2, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals) + sizeof(colors)));
  glColorPointer(3, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals)));
  glNormalPointer(GL_FLOAT, 0, (void*)sizeof(vertices));
  glVertexPointer(3, GL_FLOAT, 0, 0);

  glDrawArrays(GL_TRIANGLES, 0, 24);

  glDisableClientState(GL_VERTEX_ARRAY);  // Disable vertex arrays
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_TEXTURE_COORD_ARRAY);

// It is good idea to release VBOs with ID 0 after use.
// Once bound with 0, all pointers in gl*Pointer() behave as real
// pointer, so, normal vertex array operations are re-activated
  glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

  glDeleteBuffersARB(1, &vboId);

 //---- DEFINICIÓ COORDENADES TEXTURA
  //Desactiva_Coordenades_Textura();
}

/* ---------- TETRAHEDRON -----------------------------------------------------*/
/*
* Draws a solid tetrahedron
 */
void glutSolidTetrahedron( void )
{
	GLuint vboId = 0;

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidTetrahedron" );

//---- DEFINICIÓ COORDENADES TEXTURA
  //Activa_Coordenades_Textura();

/*
  glBegin( GL_TRIANGLES ) ;
	glNormal3d ( -tet_r[0][0], -tet_r[0][1], -tet_r[0][2] ) ; glVertex3dv ( tet_r[1] ) ; glVertex3dv ( tet_r[3] ) ; glVertex3dv ( tet_r[2] ) ;
	glNormal3d ( -tet_r[1][0], -tet_r[1][1], -tet_r[1][2] ) ; glVertex3dv ( tet_r[0] ) ; glVertex3dv ( tet_r[2] ) ; glVertex3dv ( tet_r[3] ) ;
	glNormal3d ( -tet_r[2][0], -tet_r[2][1], -tet_r[2][2] ) ; glVertex3dv ( tet_r[0] ) ; glVertex3dv ( tet_r[3] ) ; glVertex3dv ( tet_r[1] ) ;
	glNormal3d ( -tet_r[3][0], -tet_r[3][1], -tet_r[3][2] ) ; glVertex3dv ( tet_r[0] ) ; glVertex3dv ( tet_r[1] ) ; glVertex3dv ( tet_r[2] ) ;
  glEnd() ;
*/

// vertex coords array for glDrawArrays() =====================================
// A tetrahedron has 4 sides and each side has 1 triangle, therefore, a tetraahedron consists
// of 12 vertices (4 sides * 1 triangle * 3 vertices = 12 vertices). And, each
// vertex is 3 components (x,y,z) of floats, therefore, the size of vertex
// array is 36 floats (12 * 3 = 36).
	GLfloat vertices[] = { tet_r[1][0], tet_r[1][1], tet_r[1][2], tet_r[3][0], tet_r[3][1], tet_r[3][2], tet_r[2][0], tet_r[2][1], tet_r[2][2],   // v1-v3-v2 (front)
		tet_r[0][0], tet_r[0][1], tet_r[0][2], tet_r[2][0], tet_r[2][1], tet_r[2][2], tet_r[3][0], tet_r[3][1], tet_r[3][2],      // v0-v2-v3 (bottom)
		tet_r[0][0], tet_r[0][1], tet_r[0][2], tet_r[3][0], tet_r[3][1], tet_r[3][2], tet_r[1][0], tet_r[1][1], tet_r[1][2],      // v0-v3-v1 (bottom)
		tet_r[0][0], tet_r[0][1], tet_r[0][2], tet_r[1][0], tet_r[1][1], tet_r[1][2], tet_r[2][0], tet_r[2][1], tet_r[2][2] };   // v0-v1-v2 (back)


// Normal array
	GLfloat normals[] = { -tet_r[0][0], -tet_r[0][1], -tet_r[0][2], -tet_r[0][0], -tet_r[0][1], -tet_r[0][2], -tet_r[0][0], -tet_r[0][1], -tet_r[0][2],   // v1-v3-v2 (front)
		tet_r[1][0], -tet_r[1][1], -tet_r[1][2], tet_r[1][0], -tet_r[1][1], -tet_r[1][2], tet_r[1][0], -tet_r[1][1], -tet_r[1][2], 		// v0-v2-v3 (bottom)
		-tet_r[2][0], -tet_r[2][1], -tet_r[2][2], -tet_r[2][0], -tet_r[2][1], -tet_r[2][2], -tet_r[2][0], -tet_r[2][1], -tet_r[2][2],	// v0-v3-v1 (bottom)
		-tet_r[3][0], -tet_r[3][1], -tet_r[3][2], -tet_r[3][0], -tet_r[3][1], -tet_r[3][2], -tet_r[3][0], -tet_r[3][1], -tet_r[3][2] };	// v0-v1-v2 (back)

// Color array
	GLfloat colors[] = { cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2],   // v1-v3-v2 (front)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], 		// v0-v2-v3 (bottom)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2],		// v0-v3-v1 (bottom)
		cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], cColor[0], cColor[1], cColor[2], };	// v0-v1-v2 (back)

// Texture Array
	GLfloat textures[] = { -tet_r[1][0] + tet_r[1][1], -tet_r[1][0] + tet_r[1][2], -tet_r[3][0] + tet_r[3][1], -tet_r[3][0] + tet_r[3][2], -tet_r[2][0] + tet_r[2][1], -tet_r[2][0] + tet_r[2][2],    // v1-v3-v2 (front)
		-tet_r[0][0] + tet_r[0][1], -tet_r[0][0] + tet_r[0][2], -tet_r[2][0] + tet_r[2][1], -tet_r[2][0] + tet_r[2][2], -tet_r[3][0] + tet_r[3][1], -tet_r[3][0] + tet_r[3][2],   // v0-v2-v3 (right)
		-tet_r[0][0] + tet_r[0][1], -tet_r[0][0] + tet_r[0][2], -tet_r[3][0] + tet_r[3][1], -tet_r[3][0] + tet_r[3][2], -tet_r[1][0] + tet_r[1][1], -tet_r[1][0] + tet_r[1][2],    // v0-v3-v1 (top)
		-tet_r[0][0] + tet_r[0][1], -tet_r[0][0] + tet_r[0][2], -tet_r[1][0] + tet_r[1][1], -tet_r[1][0] + tet_r[1][2], -tet_r[2][0] + tet_r[2][1], -tet_r[2][0] + tet_r[2][2] };  // v0-v1-v2 (back)

// Create vertex buffer objects, you need to delete them when program exits
// Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
// glBufferDataARB with NULL pointer reserves only memory space.
// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
// target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
	glGenBuffersARB(1, &vboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals) + sizeof(colors) + sizeof(textures), 0, GL_STATIC_DRAW_ARB);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, sizeof(vertices), vertices);                             // copy vertices starting from 0 offest
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices), sizeof(normals), normals);                // copy normals after vertices
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals), sizeof(colors), colors);  // copy colours after normals
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, sizeof(vertices) + sizeof(normals) + sizeof(colors), sizeof(textures), textures);  // copy textures after colours

// Bind VBOs with IDs and set the buffer offsets of the bound VBOs
// When buffer object is bound with its ID, all pointers in gl*Pointer()
// are treated as offset instead of real pointer.
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

// Enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	// Before draw, specify vertex and index arrays with their offsets
	glTexCoordPointer(2, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals) + sizeof(colors)));
	glColorPointer(3, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals)));
	glNormalPointer(GL_FLOAT, 0, (void*)sizeof(vertices));
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 12);

	glDisableClientState(GL_VERTEX_ARRAY);  // Disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

// It is good idea to release VBOs with ID 0 after use.
// Once bound with 0, all pointers in gl*Pointer() behave as real
// pointer, so, normal vertex array operations are re-activated
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glDeleteBuffersARB(1, &vboId);

//---- DEFINICIÓ COORDENADES TEXTURA
  //Desactiva_Coordenades_Textura();
}


/* ---------- ICOSAHEDRON -----------------------------------------------------*/
/*
* Draws a solid Icosahedron
 */
void glutSolidIcosahedron( void )
{
  int i ;
  double normal[3];

 // VBO
  GLuint vboId = 0;
  std::vector <float> vertices, normals, colors, textures;	// Definició vectors dinàmics per a vertexs, normals i textures 
  vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors

 // Obtenir color actual definit en OpenGL amb glColor();
  GLfloat cColor[4];
  glGetFloatv(GL_CURRENT_COLOR, cColor);

//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidIcosahedron" );

//---- DEFINICIÓ COORDENADES TEXTURA
//  Activa_Coordenades_Textura();

  //glBegin ( GL_TRIANGLES ) ;
    for ( i = 0; i < 20; i++ )
	{ //double normal[3];
      normal[0] = ( icos_r[icos_v[i][1]][1] - icos_r[icos_v[i][0]][1] ) * ( icos_r[icos_v[i][2]][2] - icos_r[icos_v[i][0]][2] ) - ( icos_r[icos_v[i][1]][2] - icos_r[icos_v[i][0]][2] ) * ( icos_r[icos_v[i][2]][1] - icos_r[icos_v[i][0]][1] ) ;
      normal[1] = ( icos_r[icos_v[i][1]][2] - icos_r[icos_v[i][0]][2] ) * ( icos_r[icos_v[i][2]][0] - icos_r[icos_v[i][0]][0] ) - ( icos_r[icos_v[i][1]][0] - icos_r[icos_v[i][0]][0] ) * ( icos_r[icos_v[i][2]][2] - icos_r[icos_v[i][0]][2] ) ;
      normal[2] = ( icos_r[icos_v[i][1]][0] - icos_r[icos_v[i][0]][0] ) * ( icos_r[icos_v[i][2]][1] - icos_r[icos_v[i][0]][1] ) - ( icos_r[icos_v[i][1]][1] - icos_r[icos_v[i][0]][1] ) * ( icos_r[icos_v[i][2]][0] - icos_r[icos_v[i][0]][0] ) ;
      //glNormal3dv ( normal );
      //glVertex3dv ( icos_r[icos_v[i][0]] );
	  colors.push_back(cColor[0]);					colors.push_back(cColor[1]);					colors.push_back(cColor[2]);						// Vector Colors
	  normals.push_back(normal[0]);					normals.push_back(normal[1]);					normals.push_back(normal[2]);						// Vector Normals
	  vertices.push_back(icos_r[icos_v[i][0]][0]);	vertices.push_back(icos_r[icos_v[i][0]][1]);	vertices.push_back(icos_r[icos_v[i][0]][2]);		// Vector Vertices
	  textures.push_back(-icos_r[icos_v[i][0]][0] + icos_r[icos_v[i][0]][1]); textures.push_back(-icos_r[icos_v[i][0]][0] + icos_r[icos_v[i][0]][2]);	// Vector Textures

      //glVertex3dv ( icos_r[icos_v[i][1]] );
	  colors.push_back(cColor[0]);					colors.push_back(cColor[1]);					colors.push_back(cColor[2]);						// Vector Colors
	  normals.push_back(normal[0]);					normals.push_back(normal[1]);					normals.push_back(normal[2]);						// Vector Normals
	  vertices.push_back(icos_r[icos_v[i][1]][0]);	vertices.push_back(icos_r[icos_v[i][1]][1]);	vertices.push_back(icos_r[icos_v[i][1]][2]);		// Vector Vertices
	  textures.push_back(-icos_r[icos_v[i][1]][0] + icos_r[icos_v[i][1]][1]); textures.push_back(-icos_r[icos_v[i][1]][0] + icos_r[icos_v[i][1]][2]);	// Vector Textures
	  
	  //glVertex3dv ( icos_r[icos_v[i][2]] );
	  colors.push_back(cColor[0]);					colors.push_back(cColor[1]);					colors.push_back(cColor[2]);						// Vector Colors
	  normals.push_back(normal[0]);					normals.push_back(normal[1]);					normals.push_back(normal[2]);						// Vector Normals
	  vertices.push_back(icos_r[icos_v[i][2]][0]);	vertices.push_back(icos_r[icos_v[i][2]][1]);	vertices.push_back(icos_r[icos_v[i][2]][2]);		// Vector Vertices
	  textures.push_back(-icos_r[icos_v[i][2]][0] + icos_r[icos_v[i][2]][1]); textures.push_back(-icos_r[icos_v[i][2]][0] + icos_r[icos_v[i][2]][2]);	// Vector Textures
    }
  //glEnd () ;

// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

	draw_GL_TRIANGLES_VBO(vertices, normals, colors, textures, nv / 3);

//---- DEFINICIÓ COORDENADES TEXTURA
  //Desactiva_Coordenades_Textura();
}


/* ---------- ROMBIC DODECAHEDRON -----------------------------------------------------*/

/*
* Draws a solid Rhombic Dodecahedron
 */
void glutSolidRhombicDodecahedron( void )
{
  int i ;

// VBO
  GLuint vboId = 0;
  std::vector <float> vertices, normals, colors, textures;	// Definició vectors dinàmics per a vertexs, normals i textures 
  vertices.resize(0);		normals.resize(0);	colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors

// Obtenir color actual definit en OpenGL amb glColor();
  GLfloat cColor[4];
  glGetFloatv(GL_CURRENT_COLOR, cColor);

 //  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidRhombicDodecahedron" );

//---- DEFINICIÓ COORDENADES TEXTURA
 // Activa_Coordenades_Textura();

  //glBegin ( GL_QUADS ) ;
    for ( i = 0; i < 12; i++ )
    {   //glNormal3dv ( rdod_n[i] ) ;
        //glVertex3dv ( rdod_r[rdod_v[i][0]] );
		colors.push_back(cColor[0]);					colors.push_back(cColor[1]);					colors.push_back(cColor[2]);					// Vector Colors
		normals.push_back(rdod_n[i][0]);				normals.push_back(rdod_n[i][1]);				normals.push_back(rdod_n[i][2]);				// Vector Normals
		vertices.push_back(rdod_r[rdod_v[i][0]][0]);	vertices.push_back(rdod_r[rdod_v[i][0]][1]);	vertices.push_back(rdod_r[rdod_v[i][0]][2]);	// Vector Vertices
		textures.push_back(-rdod_r[rdod_v[i][0]][0] + rdod_r[rdod_v[i][0]][1]); textures.push_back(-rdod_r[rdod_v[i][0]][0] + rdod_r[rdod_v[i][0]][2]);	// Vector Textures

		//glVertex3dv ( rdod_r[rdod_v[i][1]] );
		colors.push_back(cColor[0]);					colors.push_back(cColor[1]);					colors.push_back(cColor[2]);					// Vector Colors
		normals.push_back(rdod_n[i][0]);				normals.push_back(rdod_n[i][1]);				normals.push_back(rdod_n[i][2]);				// Vector Normals
		vertices.push_back(rdod_r[rdod_v[i][1]][0]);	vertices.push_back(rdod_r[rdod_v[i][1]][1]);	vertices.push_back(rdod_r[rdod_v[i][1]][2]);	// Vector Vertices
		textures.push_back(-rdod_r[rdod_v[i][1]][0] + rdod_r[rdod_v[i][1]][1]); textures.push_back(-rdod_r[rdod_v[i][1]][0] + rdod_r[rdod_v[i][1]][2]);	// Vector Textures

		//glVertex3dv ( rdod_r[rdod_v[i][2]] );
		colors.push_back(cColor[0]);					colors.push_back(cColor[1]);					colors.push_back(cColor[2]);					// Vector Colors
		normals.push_back(rdod_n[i][0]);				normals.push_back(rdod_n[i][1]);				normals.push_back(rdod_n[i][2]);				// Vector Normals
		vertices.push_back(rdod_r[rdod_v[i][2]][0]);	vertices.push_back(rdod_r[rdod_v[i][2]][1]);	vertices.push_back(rdod_r[rdod_v[i][2]][2]);	// Vector Vertices
		textures.push_back(-rdod_r[rdod_v[i][2]][0] + rdod_r[rdod_v[i][2]][1]); textures.push_back(-rdod_r[rdod_v[i][2]][0] + rdod_r[rdod_v[i][2]][2]);	// Vector Textures

		//glVertex3dv ( rdod_r[rdod_v[i][3]] );
		colors.push_back(cColor[0]);					colors.push_back(cColor[1]);					colors.push_back(cColor[2]);					// Vector Colors
		normals.push_back(rdod_n[i][0]);				normals.push_back(rdod_n[i][1]);				normals.push_back(rdod_n[i][2]);				// Vector Normals
		vertices.push_back(rdod_r[rdod_v[i][3]][0]);	vertices.push_back(rdod_r[rdod_v[i][3]][1]);	vertices.push_back(rdod_r[rdod_v[i][3]][2]);	// Vector Vertices
		textures.push_back(-rdod_r[rdod_v[i][3]][0] + rdod_r[rdod_v[i][3]][1]); textures.push_back(-rdod_r[rdod_v[i][3]][0] + rdod_r[rdod_v[i][3]][2]);	// Vector Textures
    }
  //glEnd () ;

// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

	draw_GL_QUADS_VBO(vertices, normals, colors, textures, nv / 3);

//---- DEFINICIÓ COORDENADES TEXTURA
  //Desactiva_Coordenades_Textura();
}


/* ---------- SIERPPINSKI SPONGE ------------------------------------------------*/
/*
* Draws a solid Sierpinski Sponge
*/
void glutSolidSierpinskiSponge ( int num_levels, GLdouble offset[3], GLdouble scale )
{
  int i, j ;

// VBO
  GLuint vboId = 0;
  std::vector <float> vertices, normals, colors, textures;	// Definició vectors dinàmics per a vertexs, normals i textures 
  vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors

// Obtenir color actual definit en OpenGL amb glColor();
  GLfloat cColor[4];
  glGetFloatv(GL_CURRENT_COLOR, cColor);
  
//  FREEGLUT_EXIT_IF_NOT_INITIALISED ( "glutSolidSierpinskiSponge" );

//---- DEFINICIÓ COORDENADES TEXTURA
  //Activa_Coordenades_Textura();

  if ( num_levels == 0 )
  { //glBegin ( GL_TRIANGLES ) ;
    for ( i = 0 ; i < NUM_TETR_FACES ; i++ )
    {
      //glNormal3d ( -tet_r[i][0], -tet_r[i][1], -tet_r[i][2] ) ;
      for ( j = 0; j < 3; j++ )
      {
        double x = offset[0] + scale * tet_r[tet_i[i][j]][0] ;
        double y = offset[1] + scale * tet_r[tet_i[i][j]][1] ;
        double z = offset[2] + scale * tet_r[tet_i[i][j]][2] ;
        //glVertex3d ( x, y, z ) ;
		colors.push_back(cColor[0]);		colors.push_back(cColor[1]);		colors.push_back(cColor[2]);	// Vector Colors
		normals.push_back(-tet_r[i][0]);	normals.push_back(-tet_r[i][1]);	normals.push_back(-tet_r[i][2]);// Vector Normals
		vertices.push_back(x);				vertices.push_back(y);				vertices.push_back(z);			// Vector Vertices
		textures.push_back(-x + y);			textures.push_back(-x + z);											// Vector Textures
      }
    }
    //glEnd ();

// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

	draw_GL_TRIANGLES_VBO(vertices, normals, colors, textures, nv / 3);
  }
  else if ( num_levels > 0 )
  { GLdouble local_offset[3] ;  /* Use a local variable to avoid buildup of roundoff errors */
    num_levels -- ;
    scale /= 2.0 ;
    for ( i = 0 ; i < NUM_TETR_FACES ; i++ )
    { local_offset[0] = offset[0] + scale * tet_r[i][0] ;
      local_offset[1] = offset[1] + scale * tet_r[i][1] ;
      local_offset[2] = offset[2] + scale * tet_r[i][2] ;
      glutSolidSierpinskiSponge ( num_levels, local_offset, scale ) ;
    }
  }

//---- DEFINICIÓ COORDENADES TEXTURA
  //Desactiva_Coordenades_Textura();
}

/* ---------- TEAPOT -----------------------------------------------------*/

static void fghTeapot(GLint grid, GLdouble scale, GLenum type)
{
	//#if defined(_WIN32_WCE)
	int i, numV = sizeof(strip_vertices) / 4, numI = sizeof(strip_normals) / 4;
	/*#else
	double p[4][4][3], q[4][4][3], r[4][4][3], s[4][4][3];
	long i, j, k, l;
	#endif*/

	// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, normals, colors, textures;	// Definició vectors dinàmics per a vertexs, normals i textures 
	std::vector <int>::size_type nv;
	//	std::vector <int>::size_type nn;
	//	std::vector <int>::size_type nc;
	//	std::vector <int>::size_type nt;

	vertices.resize(0);		normals.resize(0);		colors.resize(0);	textures.resize(0);	// Reinicialitzar vectors

	// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

	//	glPushAttrib(GL_ENABLE_BIT | GL_EVAL_BIT);
	//	glEnable(GL_AUTO_NORMAL);
	//	glEnable(GL_NORMALIZE);
	//	glEnable(GL_MAP2_VERTEX_3);
	//	glEnable(GL_MAP2_TEXTURE_COORD_2);

	//	glPushMatrix();
	//	glRotated(270.0, 1.0, 0.0, 0.0);
	//	glScaled(0.5 * scale, 0.5 * scale, 0.5 * scale);
	//	glTranslated(0.0, 0.0, -1.5);

	//#if defined(_WIN32_WCE)
	//	glRotated(90.0, 1.0, 0.0, 0.0);
	//glBegin(GL_TRIANGLE_STRIP);

	for (i = 0; i < numV - 1; i++)
	{
		int vidx = strip_vertices[i],
			nidx = strip_normals[i];

		if (vidx != -1)
		{	//glNormal3fv(Normals[nidx]);
			//glVertex3fv(Vertices[vidx]);
			colors.push_back(cColor[0]);			colors.push_back(cColor[1]);			colors.push_back(cColor[2]);	colors.push_back(cColor[3]);// Vector Colors
			normals.push_back(Normals[nidx][0]);	normals.push_back(Normals[nidx][1]);	normals.push_back(Normals[nidx][2]);	// Vector Normals
			vertices.push_back(Vertices[vidx][0]);	vertices.push_back(Vertices[vidx][1]);	vertices.push_back(Vertices[vidx][2]);	// Vector Vertices
			textures.push_back(-Vertices[vidx][0] + Vertices[vidx][1]); textures.push_back(-Vertices[vidx][0] + Vertices[vidx][2]);	// Vector Textures
		}
		else {
			//glEnd();

			// ----------------------- VBO
			nv = vertices.size();	// Tamany del vector vertices en elements.
			//			nn = normals.size();	// Tamany del vector normals en elements.
			//			nt = textures.size();	// Tamany del vector textures en elements.

			draw_GL_TRIANGLE_STRIP_VBO(vertices, normals, colors, textures, nv / 3);

			vertices.resize(0);		normals.resize(0);	 colors.resize(0);		textures.resize(0);	// Reinicialitzar vectors

			//glBegin(GL_TRIANGLE_STRIP);
		}
	}
	//glEnd();

	// ----------------------- VBO
	nv = vertices.size();	// Tamany del vector vertices en elements.
	//	nn = normals.size();	// Tamany del vector normals en elements.
	//	nt = textures.size();	// Tamany del vector textures en elements.

	draw_GL_TRIANGLE_STRIP_VBO(vertices, normals, colors, textures, nv / 3);
	//	glPopMatrix();
	//	glPopAttrib();
}


/* -- TEAPOT INTERFACE FUNCTIONS -------------------------------------------------- */

/*
* Renders a beautiful filled teapot...
*/
void glutSolidTeapot(GLdouble size)
{
//	FREEGLUT_EXIT_IF_NOT_INITIALISED("glutSolidTeapot");

//---- DEFINICIÓ COORDENADES TEXTURA
	//Activa_Coordenades_Textura();

/* We will use the general teapot rendering code */
	fghTeapot(10, size, GL_FILL);

//---- DEFINICIÓ COORDENADES TEXTURA
	//Desactiva_Coordenades_Textura();
}


// ------------------- PRIMITIVES GLU (CYLINDER, DISC, SPHERE) -------------------------
/* Make it not a power of two to avoid cache thrashing on the chip */
#define CACHE_SIZE	240
#define PI	      3.14159265358979323846

// --- CILINDRE
void gluCylinder(GLdouble baseRadius, GLdouble topRadius, GLdouble height, GLint slices, GLint stacks)
{
	GLint i, j;
	GLfloat sinCache[CACHE_SIZE];
	GLfloat cosCache[CACHE_SIZE];
	GLfloat sinCache2[CACHE_SIZE];
	GLfloat cosCache2[CACHE_SIZE];
	GLfloat angle;
	GLfloat zLow, zHigh;
	GLfloat length;
	GLfloat deltaRadius;
	GLfloat zNormal;
	GLfloat xyNormalRatio;
	GLfloat radiusLow, radiusHigh;
	int needCache2, needCache3;

// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, normals, colors, textures;	// Definició vectors dinàmics per a vertexs, normals i textures 
	vertices.resize(0);		normals.resize(0);	colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

	if (slices >= CACHE_SIZE) slices = CACHE_SIZE - 1;

	if (slices < 2 || stacks < 1 || baseRadius < 0.0 || topRadius < 0.0 ||
		height < 0.0)	return;

/* Compute length (needed for normal calculations) */
	deltaRadius = baseRadius - topRadius;
	length = sqrt(deltaRadius*deltaRadius + height*height);
	if (length == 0.0) return;

/* Cache2 is the various normals at the vertices themselves */
	needCache2 = needCache3 = 0;
	needCache2 = 1;
	zNormal = deltaRadius / length;
	xyNormalRatio = height / length;

	for (i = 0; i < slices; i++) {
		angle = 2 * PI * i / slices;
		sinCache2[i] = xyNormalRatio * sin(angle);
		cosCache2[i] = xyNormalRatio * cos(angle);
		sinCache[i] = sin(angle);
		cosCache[i] = cos(angle);
	}

	sinCache[slices] = sinCache[0];
	cosCache[slices] = cosCache[0];
	sinCache2[slices] = sinCache2[0];
	cosCache2[slices] = cosCache2[0];
	for (j = 0; j < stacks; j++) {
		zLow = j * height / stacks;
		zHigh = (j + 1) * height / stacks;
		radiusLow = baseRadius - deltaRadius * ((float)j / stacks);
		radiusHigh = baseRadius - deltaRadius * ((float)(j + 1) / stacks);

//		glBegin(GL_QUAD_STRIP);
		for (i = 0; i <= slices; i++) {
			colors.push_back(cColor[0]);		colors.push_back(cColor[1]);		colors.push_back(cColor[2]);	// Vector Colors
			//glNormal3f(sinCache2[i], cosCache2[i], zNormal);
			normals.push_back(sinCache2[i]);	normals.push_back(cosCache2[i]);	normals.push_back(zNormal);		// Vector Normals
			//glTexCoord2f(1 - (float)i / slices, (float)j / stacks);
			textures.push_back(1 - (float)i / slices);	textures.push_back((float)j / stacks);						// Vector Textures
			//glVertex3f(radiusLow * sinCache[i], radiusLow * cosCache[i], zLow);
			vertices.push_back(radiusLow * sinCache[i]);	vertices.push_back(radiusLow * cosCache[i]);	vertices.push_back(zLow); // Vector Vertexs

			colors.push_back(cColor[0]);		colors.push_back(cColor[1]);		colors.push_back(cColor[2]);	// Vector Colors
			normals.push_back(sinCache2[i]);	normals.push_back(cosCache2[i]);	normals.push_back(zNormal);		// Vector Normals
			//glTexCoord2f(1 - (float)i / slices, (float)(j + 1) / stacks);
			textures.push_back(1 - (float)i / slices);	textures.push_back((float)(j + 1) / stacks);				// Vector Textures
			//glVertex3f(radiusHigh * sinCache[i], radiusHigh * cosCache[i], zHigh);
			vertices.push_back(radiusHigh * sinCache[i]);	vertices.push_back(radiusHigh * cosCache[i]);	vertices.push_back(zHigh); // Vector Vertexs
		}
	   //glEnd();
	}

// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

	draw_GL_QUAD_STRIP_VBO(vertices, normals, colors, textures, nv / 3);
}

// --- DISC
void gluDisk(GLdouble innerRadius, GLdouble outerRadius,
	GLint slices, GLint loops)
{
	gluPartialDisk(innerRadius, outerRadius, slices, loops, 0.0, 360.0);
}


// --- PARCIAL DISC
void gluPartialDisk(GLdouble innerRadius, GLdouble outerRadius, GLint slices, GLint loops, GLdouble startAngle, GLdouble sweepAngle)
{
	GLint i, j;
	GLfloat sinCache[CACHE_SIZE];
	GLfloat cosCache[CACHE_SIZE];
	GLfloat angle;
	GLfloat deltaRadius;
	GLfloat radiusLow, radiusHigh;
	GLfloat texLow = 0.0, texHigh = 0.0;
	GLfloat angleOffset;
	GLint slices2;
	GLint finish;

// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, normals, colors, textures;	// Definició vectors dinàmics per a vertexs, normals i textures 
	vertices.resize(0);		normals.resize(0);	colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

	if (slices >= CACHE_SIZE) slices = CACHE_SIZE - 1;
	if (slices < 2 || loops < 1 || outerRadius <= 0.0 || innerRadius < 0.0 ||
		innerRadius > outerRadius) {
		return;
	}
	if (sweepAngle < -360.0) sweepAngle = 360.0;
	if (sweepAngle > 360.0) sweepAngle = 360.0;
	if (sweepAngle < 0) {	startAngle += sweepAngle;
							sweepAngle = -sweepAngle;
						}

	if (sweepAngle == 360.0)	slices2 = slices;
		else slices2 = slices + 1;

/* Compute length (needed for normal calculations) */
	deltaRadius = outerRadius - innerRadius;

/* Cache is the vertex locations cache */
	angleOffset = startAngle / 180.0 * PI;
	for (i = 0; i <= slices; i++) {
		angle = angleOffset + ((PI * sweepAngle) / 180.0) * i / slices;
		sinCache[i] = sin(angle);
		cosCache[i] = cos(angle);
		}

	if (sweepAngle == 360.0) {
		sinCache[slices] = sinCache[0];
		cosCache[slices] = cosCache[0];
		}

	//glNormal3f(0.0, 0.0, 1.0);


	if (innerRadius == 0.0) {
		finish = loops - 1;

/* Triangle strip for inner polygons */
		//glBegin(GL_TRIANGLE_FAN);
		  //glTexCoord2f(0.5, 0.5);
		  //glVertex3f(0.0, 0.0, 0.0);
		  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);	// Vector Colors
		  normals.push_back(0.0);		normals.push_back(0.0);			normals.push_back(1.0);			// Vector Normals
		  textures.push_back(0.5);		textures.push_back(0.5);										// Vector Textures
		  vertices.push_back(0.0);		vertices.push_back(0.0);		vertices.push_back(0.0);		// Vector Vertexs

		  radiusLow = outerRadius - deltaRadius * ((float)(loops - 1) / loops);
		  texLow = radiusLow / outerRadius / 2;
		  for (i = slices; i >= 0; i--) {
			  //glTexCoord2f(texLow * sinCache[i] + 0.5, texLow * cosCache[i] + 0.5);
			  //glVertex3f(radiusLow * sinCache[i], radiusLow * cosCache[i], 0.0);
			  colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);					// Vector Colors
			  normals.push_back(0.0);		normals.push_back(0.0);			normals.push_back(1.0);							// Vector Normals
			  textures.push_back(texLow * sinCache[i] + 0.5);				textures.push_back(texLow * cosCache[i] + 0.5);	// Vector Textures
			  vertices.push_back(radiusLow * sinCache[i]);		vertices.push_back(radiusLow * cosCache[i]);		vertices.push_back(0.0);		// Vector Vertexs

			  }
		//glEnd();

// ----------------------- VBO
		  std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
		  std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
		  std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.
		  std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

		  draw_GL_TRIANGLE_FAN_VBO(vertices, normals, colors, textures, nv / 3);
	}
	else finish = loops;
	for (j = 0; j < finish; j++) {
		radiusLow = outerRadius - deltaRadius * ((float)j / loops);
		radiusHigh = outerRadius - deltaRadius * ((float)(j + 1) / loops);
		texLow = radiusLow / outerRadius / 2;
		texHigh = radiusHigh / outerRadius / 2;
		//glBegin(GL_QUAD_STRIP);
		for (i = 0; i <= slices; i++) {
			//glTexCoord2f(texLow * sinCache[i] + 0.5, texLow * cosCache[i] + 0.5);
			//glVertex3f(radiusLow * sinCache[i], radiusLow * cosCache[i], 0.0);
			colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);		// Vector Colors
			normals.push_back(0.0);		normals.push_back(0.0);			normals.push_back(1.0);					// Vector Normals
			textures.push_back(texLow * sinCache[i] + 0.5);		textures.push_back(texLow * cosCache[i] + 0.5);	// Vector Textures
			vertices.push_back(radiusLow * sinCache[i]);		vertices.push_back(radiusLow * cosCache[i]);		vertices.push_back(0.0);	// Vector Vèrtexs

			//glTexCoord2f(texHigh * sinCache[i] + 0.5, texHigh * cosCache[i] + 0.5);
			//glVertex3f(radiusHigh * sinCache[i], radiusHigh * cosCache[i], 0.0);
			colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);				// Vector Colors
			normals.push_back(0.0);			normals.push_back(0.0);			normals.push_back(1.0);						// Vector Normals
			textures.push_back(texHigh * sinCache[i] + 0.5);		textures.push_back(texHigh * cosCache[i] + 0.5);	// Vector Textures
			vertices.push_back(radiusHigh * sinCache[i]);			vertices.push_back(radiusHigh * cosCache[i]);		vertices.push_back(0.0);// Vector Vèrtexs
		}
		//glEnd();
	}

// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

	draw_GL_QUAD_STRIP_VBO(vertices, normals, colors, textures, nv / 3);
}


// --- ESFERA : Texturització compatible amb superficie planetes
void gluSphere(GLdouble radius, GLint slices, GLint stacks)
{
	GLint i, j;
	GLfloat sinCache1a[CACHE_SIZE];
	GLfloat cosCache1a[CACHE_SIZE];
	GLfloat sinCache2a[CACHE_SIZE];
	GLfloat cosCache2a[CACHE_SIZE];
	GLfloat sinCache1b[CACHE_SIZE];
	GLfloat cosCache1b[CACHE_SIZE];
	GLfloat sinCache2b[CACHE_SIZE];
	GLfloat cosCache2b[CACHE_SIZE];
	GLfloat angle;
	GLfloat zLow, zHigh;
	GLfloat sintemp1 = 0.0, sintemp2 = 0.0, sintemp3 = 0.0, sintemp4 = 0.0;
	GLfloat costemp1 = 0.0, costemp2 = 0.0, costemp3 = 0.0, costemp4 = 0.0;
	GLboolean needCache2;
	GLint start, finish;

// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, normals, colors, textures;	// Definició vectors dinàmics per a vertexs, normals i textures 
	vertices.resize(0);		normals.resize(0);		colors.resize(0);	 textures.resize(0);			// Reinicialitzar vectors

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

	if (slices >= CACHE_SIZE) slices = CACHE_SIZE - 1;
	if (stacks >= CACHE_SIZE) stacks = CACHE_SIZE - 1;
	if (slices < 2 || stacks < 1 || radius < 0.0) return;

// Cache2 is the various normals at the vertices themselves 
	needCache2 = GL_TRUE;

	for (i = 0; i < slices; i++) {
		angle = 2 * PI * i / slices;
		sinCache1a[i] = sin(angle);
		cosCache1a[i] = cos(angle);
		sinCache2a[i] = sinCache1a[i];
		cosCache2a[i] = cosCache1a[i];
	}

	for (j = 0; j <= stacks; j++) {
		angle = PI * j / stacks;
		sinCache2b[j] = sin(angle);
		cosCache2b[j] = cos(angle);
		sinCache1b[j] = radius * sin(angle);
		cosCache1b[j] = radius * cos(angle);
	}

// Make sure it comes to a point 
	sinCache1b[0] = 0;
	sinCache1b[stacks] = 0;

	sinCache1a[slices] = sinCache1a[0];
	cosCache1a[slices] = cosCache1a[0];

	sinCache2a[slices] = sinCache2a[0];
	cosCache2a[slices] = cosCache2a[0];

//	** When texturing we need to respecify the
//	** texture coordinates of the apex for every adjacent vertex (because
//	** it isn't a constant for that point)
	start = 0;
	finish = stacks;

	for (j = start; j < finish; j++) {
		zLow = cosCache1b[j];
		zHigh = cosCache1b[j + 1];
		sintemp1 = sinCache1b[j];
		sintemp2 = sinCache1b[j + 1];
		sintemp3 = sinCache2b[j + 1];
		costemp3 = cosCache2b[j + 1];
		sintemp4 = sinCache2b[j];
		costemp4 = cosCache2b[j];

		//glBegin(GL_QUAD_STRIP);
		for (i = 0; i <= slices; i++) {
			//glNormal3f(sinCache2a[i] * sintemp3, cosCache2a[i] * sintemp3, costemp3);
			//glTexCoord2f(1 - (float)i / slices,	1 - (float)(j + 1) / stacks);
			//glVertex3f(sintemp2 * sinCache1a[i], sintemp2 * cosCache1a[i], zHigh);
			colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
			normals.push_back(sinCache2a[i] * sintemp3);	normals.push_back(cosCache2a[i] * sintemp3);		normals.push_back(costemp3);// Vector Normals
			textures.push_back(1 - (float)i / slices);		textures.push_back(1 - (float)(j + 1) / stacks);		// Vector Textures
			vertices.push_back(sintemp2 * sinCache1a[i]);	vertices.push_back(sintemp2 * cosCache1a[i]);		vertices.push_back(zHigh);	// Vector Vèrtexs


			//glNormal3f(sinCache2a[i] * sintemp4, cosCache2a[i] * sintemp4, costemp4);
			//glTexCoord2f(1 - (float)i / slices,	1 - (float)j / stacks);
			//glVertex3f(sintemp1 * sinCache1a[i], sintemp1 * cosCache1a[i], zLow);
			colors.push_back(cColor[0]);	colors.push_back(cColor[1]);	colors.push_back(cColor[2]);			// Vector Colors
			normals.push_back(sinCache2a[i] * sintemp4);		normals.push_back(cosCache2a[i] * sintemp4);		normals.push_back(costemp4);// Vector Normals
			textures.push_back(1 - (float)i / slices);			textures.push_back(1 - (float)j / stacks);	// Vector Textures
			vertices.push_back(sintemp1 * sinCache1a[i]);		vertices.push_back(sintemp1 * cosCache1a[i]);		vertices.push_back(zLow);// Vector Vèrtexs
		}
		//glEnd();
	}
	// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

	draw_GL_QUAD_STRIP_VBO(vertices, normals, colors, textures, nv / 3);
}
// ------------------- FI PRIMITIVES GLU (CYLINDER, DISC, SPHERE) -------------------------


//------------------------------- DIBUIX DE CORBES i SUPERFICIES --------------------------------

// Vnormal: Càlcul del producte vectorial normalitzat de dos vectors v1,v2.
//         Resultat a la variable n.
CPunt3D VNormal(CPunt3D v1, CPunt3D v2)
{
	float longitud;
	CPunt3D vn;

	vn.x = v1.y * v2.z - v2.y * v1.z;	//	n[0] = v1[1] * v2[2] - v2[1] * v1[2];
	vn.y = v1.z * v2.x - v2.z * v1.x;	//	n[1] = v1[2] * v2[0] - v2[2] * v1[0];
	vn.z = v1.x * v2.y - v1.y * v2.x;	//	n[2] = v1[0] * v2[1] - v1[1] * v2[0];

// Convertim el vector en vector unitat
	longitud = sqrt(vn.x * vn.x + vn.y * vn.y + vn.z * vn.z);
	vn.x = vn.x / longitud;
	vn.y = vn.y / longitud;
	vn.z = vn.z / longitud;

	return vn;
}

//----------------------------  CORBA LEMNISCATA 3D
void draw_Lemniscata(float escala, float pas)
{
// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, colors;		// Definició vectors dinàmics per a vertexs, normals i textures 
	vertices.resize(0);		colors.resize(0);	// Reinicialitzar vectors

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

	float t = 0;
	CPunt3D vertexL1, vertexL2;
	if (pas == 0) return;
	else {
		vertexL1 = Punt_Lemniscata3D(t, escala);
		t = t + pas;
		//glBegin(GL_LINES);
		while (t <= 360) {
			vertexL2 = Punt_Lemniscata3D(t, escala);
			//glVertex3f(vertexL1.x, vertexL1.y, vertexL1.z);
			colors.push_back(cColor[0]);		colors.push_back(cColor[1]);		colors.push_back(cColor[2]);	// Vector Colors
			vertices.push_back(vertexL1.x);		vertices.push_back(vertexL1.y);		vertices.push_back(vertexL1.z);	// Vector Vèrtexs

			//glVertex3f(vertexL2.x, vertexL2.y, vertexL2.z);
			colors.push_back(cColor[0]);		colors.push_back(cColor[1]);		colors.push_back(cColor[2]);	// Vector Colors
			vertices.push_back(vertexL2.x);		vertices.push_back(vertexL2.y);		vertices.push_back(vertexL2.z);	// Vector Vèrtexs

			vertexL1 = vertexL2;
			t = t + pas;
		}
		//glEnd();
		// ----------------------- VBO
		std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
		std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.

		draw_GL_LINES_VBO(vertices, colors, nv / 2);
	}

}

// Punt_Lemniscata3D: Calcul de la posició (x,y,z) segons lemniscata 3D (CPunt3D)
CPunt3D Punt_Lemniscata3D(float t, float scale)
{
	CPunt3D p = { (0, 0, 0) };
	const double a = 1.0*scale*(0.6); // paràmetre lemniscata

	float bet = sqrtf(2.0) / 2;
	//float aeli=0.95*512/2;
	//float beli=0.8*512/2;
	float x1 = a*cos(2 * t*pi / 180)*cos(t*pi / 180);
	float y1 = a*cos(2 * t*pi / 180)*sin(t*pi / 180);
	float z1 = a*(sin(t*pi / 180) + cos(t*pi / 180));	// Trajectòria 1
	//float z1=a*sin(t*pi/180);							// Trajectòria 2

// Càlcul de la Posició
	p.x = bet*x1 + bet*y1;
	p.y = -bet*x1 + bet*y1;

	//p.z=bet*z1+256;		// Elevació 1 (la més alta)
	//p.z=(bet/2)*z1+158;	// Elevació 2 
	p.z = (bet / 4)*z1 + 82;	// Elevació 3
	//p.z=(bet/8)*z1+43;	// Elevació 4
	return p;
}


//----------------------------  CORBA LEMNISCATA 2D
void draw_Lemniscata2D(float escala, float pas)
{
// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, colors;		// Definició vectors dinàmics per a vertexs, normals i textures 
	vertices.resize(0);		colors.resize(0);	// Reinicialitzar vectors

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

	float t = 0;
	CPunt3D vertexL1, vertexL2;
	if (pas == 0) return;
	else {
		vertexL1 = Punt_Lemniscata2D(t, escala);
		t = t + pas;
		//glBegin(GL_LINES);
		while (t <= 360) {
			vertexL2 = Punt_Lemniscata2D(t, escala);
			//glVertex3f(vertexL1.x, vertexL1.y, vertexL1.z);
			colors.push_back(cColor[0]);		colors.push_back(cColor[1]);		colors.push_back(cColor[2]);	// Vector Colors
			vertices.push_back(vertexL1.x);		vertices.push_back(vertexL1.y);		vertices.push_back(vertexL1.z);	// Vector Vèrtexs
			
			//glVertex3f(vertexL2.x, vertexL2.y, vertexL2.z);
			colors.push_back(cColor[0]);		colors.push_back(cColor[1]);		colors.push_back(cColor[2]);	// Vector Colors
			vertices.push_back(vertexL2.x);		vertices.push_back(vertexL2.y);		vertices.push_back(vertexL2.z);	// Vector Vèrtexs

			vertexL1 = vertexL2;
			t = t + pas;
		}
		//glEnd();
// ----------------------- VBO
		std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
		std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.

		draw_GL_LINES_VBO(vertices, colors, nv / 2);
	}
}


// Punt_Lemniscata2D: Calcul de la posició (x,y,z) segons lemniscata 2D (CPoint3D)
CPunt3D Punt_Lemniscata2D(float t, float scale)
{
	CPunt3D p = { (0, 0, 0) };
	const double a = 1.0*scale*(0.6); // paràmetre lemniscata

	float bet = sqrtf(2.0) / 2;

	float x1 = a*cos(2 * t*pi / 180)*cos(t*pi / 180);
	float y1 = a*cos(2 * t*pi / 180)*sin(t*pi / 180);

// Càlcul de la Posició
	p.x = bet*x1 + bet*y1;
	p.y = -bet*x1 + bet*y1;
	p.z = 0;
	return p;

}


//----------------------------  CORBA SPLINE

void draw_BSpline_Curve(CPunt3D ctr_points[MAX_PATCH_CORBA], int nptsCorba, float pas)
{
	CPunt3D vertexL1, vertexL2;
	CPunt3D ctr[4];		// Punts control del patch de l'spline.
	int patch = 0;			// Patch actual.
	GLfloat t = 0;

// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, colors;		// Definició vectors dinàmics per a vertexs, normals i textures 
	vertices.resize(0);		colors.resize(0);	// Reinicialitzar vectors

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

	//t = t - pas;
	// Càrrega primers punts de control.
	for (int i = 0; i<4; i++)
	{
		ctr[i].x = ctr_points[i].x;
		ctr[i].y = ctr_points[i].y;
		ctr[i].z = ctr_points[i].z;
	}
	//glBegin(GL_LINES);
	vertexL1 = Punt_Corba_BSpline(t, ctr);
	t = t + pas;
	while (patch <= nptsCorba - 4){
		if (t > 1.0 + 2 * pas)	{
			t -= 1.0;
			patch++;
			if (patch <= nptsCorba - 4)
			{
				for (int i = 0; i < 4; i++)
				{
					ctr[i].x = ctr_points[patch + i].x;
					ctr[i].y = ctr_points[patch + i].y;
					ctr[i].z = ctr_points[patch + i].z;
				}
			}
		}
		if (patch <= nptsCorba - 4) {
			if (t>1.0) vertexL2 = Punt_Corba_BSpline(1.0, ctr);
			else vertexL2 = Punt_Corba_BSpline(t, ctr);
			vertexL2 = Punt_Corba_BSpline(t, ctr);
			//glVertex3f(vertexL1.x, vertexL1.y, vertexL1.z);	// Vertex 1 de la línia
			colors.push_back(cColor[0]);		colors.push_back(cColor[1]);		colors.push_back(cColor[2]);	// Vector Colors
			vertices.push_back(vertexL1.x);		vertices.push_back(vertexL1.y);		vertices.push_back(vertexL1.z);	// Vector Vèrtexs
			
			//glVertex3f(vertexL2.x, vertexL2.y, vertexL2.z);	// Vertex 2 de la línia
			colors.push_back(cColor[0]);		colors.push_back(cColor[1]);		colors.push_back(cColor[2]);	// Vector Colors
			vertices.push_back(vertexL2.x);		vertices.push_back(vertexL2.y);		vertices.push_back(vertexL2.z);	// Vector Vèrtexs
			vertexL1 = vertexL2;
			t = t + pas;
		}
	}
	//glEnd();
	// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.

	draw_GL_LINES_VBO(vertices, colors, nv / 2);
}

// Punt_Corba_Spline: Calcul del punt del spline en coordenades 3D (CPunt3D) segons el 
//             paràmetre i i els punts de control ctr 
CPunt3D Punt_Corba_BSpline(float t, CPunt3D * ctr)
{
	CPunt3D p = { (0, 0, 0) };
	float coef[4];
	int i, j;

	// Polinomis que multipliquen els punts de control del patch
	for (i = 0; i<4; i++)
	{
		coef[i] = 0;
		for (j = 0; j<4; j++)
			coef[i] = coef[i] * t + AS[i][j];
	}

	// Càlcul de la Posició
	for (i = 0; i<4; i++)
	{
		p.x += coef[i] * ctr[i].x;
		p.y += coef[i] * ctr[i].y;
		p.z += coef[i] * ctr[i].z;
	}
	return p;

}

//----------------------------  CORBA BEZIER

void draw_Bezier_Curve(CPunt3D ctr_points[MAX_PATCH_CORBA], int nptsCorba, float pas, bool tancat)
{
// VBO
	GLuint vboId = 0;
	std::vector <float> vertices, colors;		// Definició vectors dinàmics per a vertexs, normals i textures 
	vertices.resize(0);		colors.resize(0);	// Reinicialitzar vectors

// Obtenir color actual definit en OpenGL amb glColor();
	GLfloat cColor[4];
	glGetFloatv(GL_CURRENT_COLOR, cColor);

	CPunt3D vertexL1, vertexL2;
	CPunt3D ctr[4];		// Punts control del patch de l'spline.
	int patch = 0;			// Patch actual.
	GLfloat t = 0;

	//t = t - pas;
	// Càrrega primers punts de control.
	for (int i = 0; i<4; i++)
	{
		ctr[i].x = ctr_points[i].x;
		ctr[i].y = ctr_points[i].y;
		ctr[i].z = ctr_points[i].z;
	}
	//glBegin(GL_LINES);
	vertexL1 = Punt_Corba_Bezier(t, ctr);
	t = t + pas;
	while (patch <= nptsCorba - 4){
		if (t > 1.0 + 2 * pas)	{
			t -= 1.0;
			//patch++;
			patch = patch + 3;
			if ((patch < nptsCorba - 1) && (patch + 4 > nptsCorba)) patch = nptsCorba - 4;
			if (patch <= nptsCorba - 4)
			{
				for (int i = 0; i < 4; i++)
				{
					ctr[i].x = ctr_points[patch + i].x;
					ctr[i].y = ctr_points[patch + i].y;
					ctr[i].z = ctr_points[patch + i].z;
				}
			}
		}
		if (patch <= nptsCorba - 4) {
			if (t>1.0) vertexL2 = Punt_Corba_Bezier(1.0, ctr);
			else vertexL2 = Punt_Corba_Bezier(t, ctr);
			//glVertex3f(vertexL1.x, vertexL1.y, vertexL1.z);	// Vértex 1 de la línia
			colors.push_back(cColor[0]);		colors.push_back(cColor[1]);		colors.push_back(cColor[2]);	// Vector Colors
			vertices.push_back(vertexL1.x);		vertices.push_back(vertexL1.y);		vertices.push_back(vertexL1.z);	// Vector Vèrtexs
			
			//glVertex3f(vertexL2.x, vertexL2.y, vertexL2.z);	// Vèrtex 2 de la línia
			colors.push_back(cColor[0]);		colors.push_back(cColor[1]);		colors.push_back(cColor[2]);	// Vector Colors
			vertices.push_back(vertexL2.x);		vertices.push_back(vertexL2.y);		vertices.push_back(vertexL2.z);	// Vector Vèrtexs
			
			vertexL1 = vertexL2;
			t = t + pas;
		}
	}
	//glEnd();
// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.

	draw_GL_LINES_VBO(vertices, colors, nv / 2);

}

// Punt_Corba_Bezier: Calcul del punt de Bezier en coordenades 3D (CPunt3D) segons el 
//             paràmetre i i els punts de control ctr 
CPunt3D Punt_Corba_Bezier(float t, CPunt3D * ctr)
{
	CPunt3D p = { (0, 0, 0) };
	float coef[4];
	int i, j;

	// Polinomis que multipliquen els punts de control del patch
	for (i = 0; i<4; i++)
	{
		coef[i] = 0;
		for (j = 0; j<4; j++)
			coef[i] = coef[i] * t + AB[i][j];
	}

	// Càlcul de la Posició
	for (i = 0; i<4; i++)
	{
		p.x += coef[i] * ctr[i].x;
		p.y += coef[i] * ctr[i].y;
		p.z += coef[i] * ctr[i].z;
	}
	return p;
}


// ------------------------- ACTIVACIÓ VERTEX ARRAY DE CADA FORMA GL_* PER A VBO ------------------------------------------
// --------------------(GL_LINES, GL_POLYGON, GL_TRIANGLES, GL_TRIANGLES_STRIP, GL_QUADS, GL_QUADSTRIP) -------------------------

// ACTIVACIÓ VERTEX ARRAY DE GL_LINES PER A VBO
void draw_GL_LINES_VBO(std::vector <float> vertices, std::vector <float> colors, int num_lines)
{
	GLuint vboId = 0;
// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.

// Create vertex buffer objects, you need to delete them when program exits
// Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
// glBufferDataARB with NULL pointer reserves only memory space.
// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
// target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
	glGenBuffersARB(1, &vboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (nv + nc) * 4, 0, GL_STATIC_DRAW_ARB);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, nv * 4, &vertices[0]);					// copy vertices starting from 0 offest
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, nv * 4, nc * 4, &colors[0]);                // copy colors  after vertices

// Bind VBOs with IDs and set the buffer offsets of the bound VBOs
// When buffer object is bound with its ID, all pointers in gl*Pointer()
// are treated as offset instead of real pointer.
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

// Enable vertex arrays
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

// Before draw, specify vertex and index arrays with their offsets
	glColorPointer(3, GL_FLOAT, 0, (void*)(nv * 4));
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_LINES, 0, num_lines);

	glDisableClientState(GL_VERTEX_ARRAY);  // Disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);

// It is good idea to release VBOs with ID 0 after use.
// Once bound with 0, all pointers in gl*Pointer() behave as real
// pointer, so, normal vertex array operations are re-activated
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glDeleteBuffersARB(1, &vboId);
}

// ACTIVACIÓ VERTEX ARRAY DE GL_POLYGON PER A VBO
void draw_GL_POLYGON_VBO(std::vector <float> vertices, std::vector <float> normals, std::vector <float> colors, std::vector <float> textures, int num_cares)
{
	GLuint vboId = 0;
// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

// Create vertex buffer objects, you need to delete them when program exits
// Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
// glBufferDataARB with NULL pointer reserves only memory space.
// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
// target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
	glGenBuffersARB(1, &vboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn + nc + nt) * 4, 0, GL_STATIC_DRAW_ARB);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, nv * 4, &vertices[0]);				// copy vertices starting from 0 offest
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, nv * 4, nn * 4, &normals[0]);           // copy normals after vertices
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn) * 4, nc + 4, &colors[0]);		// copy colours after normals
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn + nc) * 4, nt * 4, &textures[0]);  // copy textures after normals

// Bind VBOs with IDs and set the buffer offsets of the bound VBOs
// When buffer object is bound with its ID, all pointers in gl*Pointer()
// are treated as offset instead of real pointer.
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

// Enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

// Before draw, specify vertex and index arrays with their offsets
	//glTexCoordPointer(2, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals)));
	glTexCoordPointer(2, GL_FLOAT, 0, (void*)((nv + nn + nc) * 4));
	glColorPointer(3, GL_FLOAT, 0, (void*)((nv + nn) * 4));
	glNormalPointer(GL_FLOAT, 0, (void*)(nv * 4));
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_POLYGON, 0, num_cares);

	glDisableClientState(GL_VERTEX_ARRAY);  // Disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

// It is good idea to release VBOs with ID 0 after use.
// Once bound with 0, all pointers in gl*Pointer() behave as real
// pointer, so, normal vertex array operations are re-activated
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glDeleteBuffersARB(1, &vboId);
}

// ACTIVACIÓ VERTEX ARRAY DE GL_QUADS PER A VBO
void draw_GL_QUADS_VBO(std::vector <float> vertices, std::vector <float> normals, std::vector <float> colors, std::vector <float> textures, int num_cares)
{
	GLuint vboId = 0;
// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

// Create vertex buffer objects, you need to delete them when program exits
// Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
// glBufferDataARB with NULL pointer reserves only memory space.
// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
// target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
	glGenBuffersARB(1, &vboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn + nc + nt) * 4, 0, GL_STATIC_DRAW_ARB);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, nv * 4, &vertices[0]);					// copy vertices starting from 0 offest
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, nv * 4, nn * 4, &normals[0]);				// copy normals after vertices
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn) * 4, nc * 4, &colors[0]);			// copy colours after normals
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn + nc) * 4, nt * 4, &textures[0]);  // copy textures after normals

// Bind VBOs with IDs and set the buffer offsets of the bound VBOs
// When buffer object is bound with its ID, all pointers in gl*Pointer()
// are treated as offset instead of real pointer.
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

// Enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);	
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

// Before draw, specify vertex and index arrays with their offsets
	glTexCoordPointer(2, GL_FLOAT, 0, (void*)((nv + nn + nc) * 4));
	glColorPointer(3, GL_FLOAT, 0, (void*)((nv + nn) * 4));
	glNormalPointer(GL_FLOAT, 0, (void*)(nv * 4));
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_QUADS, 0, num_cares);
	//glDrawArrays(GL_QUAD_STRIP, 0, nv / 3);

	glDisableClientState(GL_VERTEX_ARRAY);  // Disable vertex arrays
	glDisableClientState(GL_NORMAL_ARRAY);	
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

// It is good idea to release VBOs with ID 0 after use.
// Once bound with 0, all pointers in gl*Pointer() behave as real
// pointer, so, normal vertex array operations are re-activated
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glDeleteBuffersARB(1, &vboId);
}

// ACTIVACIÓ VERTEX ARRAY DE QUAD_STRIP PER A VBO
void draw_GL_QUAD_STRIP_VBO(std::vector <float> vertices, std::vector <float> normals, std::vector <float> colors, std::vector <float> textures, int num_cares)
{
	GLuint vboId = 0;
// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

// Create vertex buffer objects, you need to delete them when program exits
// Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
// glBufferDataARB with NULL pointer reserves only memory space.
// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
// target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
	glGenBuffersARB(1, &vboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn + nc + nt) * 4, 0, GL_STATIC_DRAW_ARB);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, nv * 4, &vertices[0]);					// copy vertices starting from 0 offest
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, nv * 4, nn * 4, &normals[0]);               // copy normals after vertices
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn) * 4, nc * 4, &colors[0]);			// copy colours after normals
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn + nc) * 4, nt * 4, &textures[0]);  // copy textures after normals

// Bind VBOs with IDs and set the buffer offsets of the bound VBOs
// When buffer object is bound with its ID, all pointers in gl*Pointer()
// are treated as offset instead of real pointer.
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

// Enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

// Before draw, specify vertex and index arrays with their offsets
	//glTexCoordPointer(2, GL_FLOAT, 0, (void*)(sizeof(vertices) + sizeof(normals)));
	glTexCoordPointer(2, GL_FLOAT, 0, (void*)((nv + nn + nc) * 4));
	glColorPointer(3, GL_FLOAT, 0, (void*)((nv + nn) * 4));
	glNormalPointer(GL_FLOAT, 0, (void*)(nv * 4));
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_QUAD_STRIP, 0, num_cares);
	//glDrawArrays(GL_QUAD_STRIP, 0, nv / 3);

	glDisableClientState(GL_VERTEX_ARRAY);  // Disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

// It is good idea to release VBOs with ID 0 after use.
// Once bound with 0, all pointers in gl*Pointer() behave as real
// pointer, so, normal vertex array operations are re-activated
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glDeleteBuffersARB(1, &vboId);
}

// ACTIVACIÓ VERTEX ARRAY DE GL_TRIANGLES PER A VBO
void draw_GL_TRIANGLES_VBO(std::vector <float> vertices, std::vector <float> normals, std::vector <float> colors, std::vector <float> textures, int num_cares)
{
	GLuint vboId = 0;
// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

// Create vertex buffer objects, you need to delete them when program exits
// Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
// glBufferDataARB with NULL pointer reserves only memory space.
// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
// target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
	glGenBuffersARB(1, &vboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn + nc + nt) * 4, 0, GL_STATIC_DRAW_ARB);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, nv * 4, &vertices[0]);							// copy vertices starting from 0 offest
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, nv * 4, nn * 4, &normals[0]);           // copy normals after vertices
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn) * 4, nc + 4, &colors[0]);		// copy colours after normals
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn + nc) * 4, nt * 4, &textures[0]);  // copy textures after normals

// Bind VBOs with IDs and set the buffer offsets of the bound VBOs
// When buffer object is bound with its ID, all pointers in gl*Pointer()
// are treated as offset instead of real pointer.
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

// Enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

// Before draw, specify vertex and index arrays with their offsets
	glTexCoordPointer(2, GL_FLOAT, 0, (void*)((nv + nn + nc) * 4));
	glColorPointer(3, GL_FLOAT, 0, (void*)((nv + nn) * 4));
	glNormalPointer(GL_FLOAT, 0, (void*)(nv * 4));
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, num_cares);

	glDisableClientState(GL_VERTEX_ARRAY);  // Disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

// It is good idea to release VBOs with ID 0 after use.
// Once bound with 0, all pointers in gl*Pointer() behave as real
// pointer, so, normal vertex array operations are re-activated
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glDeleteBuffersARB(1, &vboId);
}

// ACTIVACIÓ VERTEX ARRAY DE GL_TRIANGLE_FAN PER A VBO
void draw_GL_TRIANGLE_FAN_VBO(std::vector <float> vertices, std::vector <float> normals, std::vector <float> colors, std::vector <float> textures, int num_cares)
{
	GLuint vboId = 0;
// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector colors en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

// Create vertex buffer objects, you need to delete them when program exits
// Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
// glBufferDataARB with NULL pointer reserves only memory space.
// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
// target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
	glGenBuffersARB(1, &vboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn + nc + nt) * 4, 0, GL_STATIC_DRAW_ARB);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, nv * 4, &vertices[0]);					// copy vertices starting from 0 offest
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, nv * 4, nn * 4, &normals[0]);				// copy normals after vertices
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn) * 4, nc * 4, &colors[0]);			// copy colours after normals
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn + nc) * 4, nt * 4, &textures[0]);  // copy textures after normals

// Bind VBOs with IDs and set the buffer offsets of the bound VBOs
// When buffer object is bound with its ID, all pointers in gl*Pointer()
// are treated as offset instead of real pointer.
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

// Enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

// Before draw, specify vertex and index arrays with their offsets
	glTexCoordPointer(2, GL_FLOAT, 0, (void*)((nv + nn + nc) * 4));
	glColorPointer(3, GL_FLOAT, 0, (void*)((nv + nn) * 4));
	glNormalPointer(GL_FLOAT, 0, (void*)(nv * 4));
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLE_FAN, 0, num_cares);

	glDisableClientState(GL_VERTEX_ARRAY);  // Disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

// It is good idea to release VBOs with ID 0 after use.
// Once bound with 0, all pointers in gl*Pointer() behave as real
// pointer, so, normal vertex array operations are re-activated
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glDeleteBuffersARB(1, &vboId);
}


// ACTIVACIÓ VERTEX ARRAY DE GL_TRIANGLE_STRIP PER A VBO
void draw_GL_TRIANGLE_STRIP_VBO(std::vector <float> vertices, std::vector <float> normals, std::vector <float> colors, std::vector <float> textures, int num_cares)
{
	GLuint vboId = 0;
// ----------------------- VBO
	std::vector <int>::size_type nv = vertices.size();	// Tamany del vector vertices en elements.
	std::vector <int>::size_type nn = normals.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nc = colors.size();	// Tamany del vector normals en elements.
	std::vector <int>::size_type nt = textures.size();	// Tamany del vector textures en elements.

// Create vertex buffer objects, you need to delete them when program exits
// Try to put both vertex coords array, vertex normal array and vertex color in the same buffer object.
// glBufferDataARB with NULL pointer reserves only memory space.
// Copy actual data with 2 calls of glBufferSubDataARB, one for vertex coords and one for normals.
// target flag is GL_ARRAY_BUFFER_ARB, and usage flag is GL_STATIC_DRAW_ARB
	glGenBuffersARB(1, &vboId);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn + nc + nt) * 4, 0, GL_STATIC_DRAW_ARB);
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, nv * 4, &vertices[0]);							// copy vertices starting from 0 offest
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, nv * 4, nn * 4, &normals[0]);						// copy normals after vertices
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn) *4, nc * 4, &colors[0]);  // copy colours after normals
	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, (nv + nn + nc) * 4, nt * 4, &textures[0]);  // copy textures after normals

// Bind VBOs with IDs and set the buffer offsets of the bound VBOs
// When buffer object is bound with its ID, all pointers in gl*Pointer()
// are treated as offset instead of real pointer.
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vboId);

// Enable vertex arrays
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

// Before draw, specify vertex and index arrays with their offsets
	glTexCoordPointer(2, GL_FLOAT, 0, (void*)((nv + nn + nc) * 4));
	glColorPointer(3, GL_FLOAT, 0, (void*) ((nv + nn) * 4));
	glNormalPointer(GL_FLOAT, 0, (void*)(nv * 4));
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, num_cares);

	glDisableClientState(GL_VERTEX_ARRAY);  // Disable vertex arrays
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

// It is good idea to release VBOs with ID 0 after use.
// Once bound with 0, all pointers in gl*Pointer() behave as real
// pointer, so, normal vertex array operations are re-activated
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);

	glDeleteBuffersARB(1, &vboId);
}

// --- ACTIVACIÓ DEFINICIÓ COORDENADES TEXTURA PER A OBJECTES GLUT ------------------------ 
void Activa_Coordenades_Textura()
{
//---- DEFINICIÓ COORDENADES TEXTURA
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);

// Generació coordenades textura.
	GLfloat sPlane[4] = { -1.0f, 1.0f, 0.0f, 1.0f };
	GLfloat tPlane[4] = { -1.0f, 0.0f, 1.0f, 1.0f };

	glTexGenfv(GL_S, GL_OBJECT_PLANE, sPlane);
	glTexGenfv(GL_T, GL_OBJECT_PLANE, tPlane);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
//--- FI DEFINICIÓ COORDENADES TEXTURA
}

void Desactiva_Coordenades_Textura()
{
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
}
// --- FI ACTIVACIÓ I DESACTIVACIÓ DE LA DEFINICIÓ COORDENADES TEXTURA PER A OBJECTES GLUT ------

/*** END OF FILE ***/
