#define _CRT_SECURE_NO_WARNINGS

#include "SolarSystem.h"

#include "windows.h"
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <GL/glu.h>
#include <gl/GL.h>
#include <math.h>

#include "glm.h"

#define PI 3.1416

int window;

/* ----- Spaceship Variablen ---- */
float x = 50, y = -150, z = -100, graus = 0;
int fps = 0, displayList = 0;

GLfloat lightAmbShip[3] = { 0.1, 0.1, 0.1 };
GLfloat lightDiffShip[3] = { 1.0, 1.0, 1.0 };

GLMmodel* spaceship;

/* ----- Spaceship Bewegungsvariablen ----- */
int moving = 0;		// Flag = true, wenn sich die Maus bewegt 
int mouse_x = 0;	// x-Wert der Maus  
int mouse_y = 0;	// x-Wert der Maus 

GLfloat solarShipAngle = 0;
int testShip = 0;

/* ----- Lighting Variablen ---- */
GLfloat  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat  sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

/* ---- Textures Variablen----- */
// Flag, das sicherstellt, dass Texturen nur einmal geladen werden
bool texturesCreated = false;	

GLuint sunTexture;
GLuint mercuryTexture;
GLuint venusTexture;
GLuint earthTexture;
GLuint moonTexture;
GLuint marsTexture;
GLuint jupiterTexture;
GLuint saturnTexture;
GLuint uranusTexture;
GLuint neptuneTexture;
GLuint plutoTexture;
GLuint starsTexture;
GLuint saturnRingsTexture;

/* ----- Sonnenposition und Rotationswinkel ----- */
GLfloat fSunX = 0.0f;
GLfloat fSunY = 0.0f;
GLfloat fSunZ = -500.0f;
GLfloat fCamX = 0.0f;
GLfloat fCamY = 0.0f;
GLfloat fCamZ = 0.0f;
GLfloat fSunRotX = 0.0f;
GLfloat fSunRotY = 0.0f;
GLfloat fSunRotZ = 0.0f;

/* ----- Prototypen für die Funktionen ---- */
void keyDown(unsigned char, int, int);
unsigned char *LoadBmp(char *fn, int *wi, int *hi);
void GenerateTextures(char *, int);
void InitialiseTextures(void);
void mouse(int, int, int, int);
void mouseMotion(int, int);

/* ---- Sonnensystem wird gezeichnet ----- */
void RenderScene(void)
{
	GLUquadricObj* pObj;
	/* ---- Drehwinkel ---- */
	static float fMoonRot = 0.0f;
	static float fEarthRot = 0.0f;
	static float fMercuryRot = 0.0f;
	static float fVenusRot = 0.0f;
	static float fMarsRot = 0.0f;
	static float fJupiterRot = 0.0f;
	static float fSaturnRot = 0.0f;
	static float fUranusRot = 0.0f;
	static float fNeptuneRot = 0.0f;
	static float fPlutoRot = 0.0f;
	static float fSaturnRingRot = 0.0f;

	// Löscht das Window mit der momentanten "Clearing-Color"
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Matrix-Zustand speichern
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// Verschiebt die Szene auf Basis der Sonnenposition
	glTranslatef(fSunX, fSunY, fSunZ);

#pragma region sun
	/* ----- Sonne ----- */
	glDisable(GL_LIGHTING); // Licht ausschalten

	// quadObject erstellen und Texturkoordinaten dafür spezifizieren 
	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	// Sonnen-Textur setzen
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sunTexture);

	// Rotation der Sonne
	glRotatef(fSunRotX, 1.0f, 0.0f, 0.0f); // Sonne rotiert um x-Achse
	glRotatef(fSunRotY, 0.0f, 1.0f, 0.0f); // Sonne rotiert um y-Achse
	glRotatef(fSunRotZ, 0.0f, 0.0f, 1.0f); // Sonne rotiert um z-Achse
	gluSphere(pObj, 172.8f, 30, 17); // Sonnen-Kugel zeichnen (Object, Radius, Slices, Stack) 
	
	glDisable(GL_TEXTURE_2D);

	// quadObject freigeben
	gluDeleteQuadric(pObj);

	glEnable(GL_LIGHTING); // Licht einschalten

	// Lighting-Position auf die Sonnen-Position setzen
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
#pragma endregion

#pragma region skybox
	/* ----- Weltraum-Himmel ----- */
	// Speichert die aktuelle Matrix
	glPushMatrix();

	// Matrix wird nun transformiert

	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1, 1, 1, 1);
	GLfloat val = 6000.0f; // Größe der skybox

	// Texturen für das fordere Quadrat
	glBindTexture(GL_TEXTURE_2D, starsTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(val, -val, val);
	glTexCoord2f(1, 0); glVertex3f(-val, -val, val);
	glTexCoord2f(1, 1); glVertex3f(-val, val, val);
	glTexCoord2f(0, 1); glVertex3f(val, val, val);
	glEnd();

	// Texturen für das linke Quadrat
	glBindTexture(GL_TEXTURE_2D, starsTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(val, -val, -val);
	glTexCoord2f(1, 0); glVertex3f(val, -val, val);
	glTexCoord2f(1, 1); glVertex3f(val, val, val);
	glTexCoord2f(0, 1); glVertex3f(val, val, -val);
	glEnd();

	// Texturen für das hintere Quadrat
	glBindTexture(GL_TEXTURE_2D, starsTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-val, -val, -val);
	glTexCoord2f(1, 0); glVertex3f(val, -val, -val);
	glTexCoord2f(1, 1); glVertex3f(val, val, -val);
	glTexCoord2f(0, 1); glVertex3f(-val, val, -val);

	glEnd();

	// Texturen für das rechte Quadrat
	glBindTexture(GL_TEXTURE_2D, starsTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-val, val, -val);
	glTexCoord2f(1, 0); glVertex3f(-val, val, val);
	glTexCoord2f(1, 1); glVertex3f(-val, -val, val);
	glTexCoord2f(0, 1); glVertex3f(-val, -val, -val);
	glEnd();

	// Texturen für das obere Quadrat
	glBindTexture(GL_TEXTURE_2D, starsTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(val, val, -val);
	glTexCoord2f(1, 0); glVertex3f(val, val, val);
	glTexCoord2f(1, 1); glVertex3f(-val, val, val);
	glTexCoord2f(0, 1); glVertex3f(-val, val, -val);
	glEnd();

	// Texturen für das untere Quadrat
	glBindTexture(GL_TEXTURE_2D, starsTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-val, -val, -val);
	glTexCoord2f(1, 0); glVertex3f(-val, -val, val);
	glTexCoord2f(1, 1); glVertex3f(val, -val, val);
	glTexCoord2f(0, 1); glVertex3f(val, -val, -val);
	glEnd();

	glPopAttrib();
	glPopMatrix();
#pragma endregion

#pragma region mercury 
	/* ----- Merkur ----- */
	glPushMatrix();

	// quadObject erstellen und Texturkoordinaten dafür spezifizieren 
	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	// Merkur-Textur setzen
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mercuryTexture);

	// Rotationskoordinaten für Merkur
	glRotatef(fMercuryRot, 1.0f, 2.0f, 0.0f);

	// Merkur zeichnen
	glTranslatef(200.0f, -15.0f, 0.0f); // Merkur von der Sonne wegverschieben
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); // dreht die Textur
	glRotatef(fMercuryRot * 3, 0.0f, 0.0f, 1.0f); // Merkur-Rotation um sich selber - simuliert Eigenrotation
	gluSphere(pObj, 6.4f, 30, 17); // Merkur - Kugel zeichnen(Object, Radius, Slices, Stack)
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);

	// neue Rotationsposition von Merkur (Rotationsgeschwindigkeit um die Sonne)
	fMercuryRot += 20.0f;
	// Rotation zurücksetzen bei 360 Grad
	if (fMercuryRot >= 360.0f)
		fMercuryRot = 0.0f;

	glPopMatrix();
#pragma endregion

#pragma region venus
	/* ----- Venus ----- */
	glPushMatrix();

	// quadObject erstellen und Texturkoordinaten dafür spezifizieren 
	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	// Venus-Textur setzen
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, venusTexture);

	// Rotationskoordinaten für Venus
	glRotatef(fVenusRot, 0.0f, 1.0f, 0.0f);

	// Venus zeichnen
	glTranslatef(350.0f, 0.0f, 0.0f); // Venus von der Sonne wegverschieben
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); // dreht die Textur
	glRotatef(fVenusRot * 3, 0.0f, 0.0f, 1.0f); // Venus-Rotation um sich selber - simuliert Eigenrotation
	gluSphere(pObj, 16.0f, 30, 17); // Venus - Kugel zeichnen(Object, Radius, Slices, Stack)
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);

	// neue Rotationsposition von Venus (Rotationsgeschwindigkeit um die Sonne)
	fVenusRot += 10.0f;
	// Rotation zurücksetzen bei 360 Grad
	if (fVenusRot >= 360.0f)
		fVenusRot = 0.0f;

	glPopMatrix();
#pragma endregion

#pragma region mars
	/* ----- Mars ----- */
	glPushMatrix();

	// quadObject erstellen und Texturkoordinaten dafür spezifizieren 
	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	// Mars-Textur setzen
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, marsTexture);

	// Rotationskoordinaten für Mars
	glRotatef(fMarsRot, 0.0f, 1.0f, 0.3f);

	// Mars zeichnen
	glTranslatef(700.0f, 0.0f, 0.0f); // Mars von der Sonne wegverschieben
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); // dreht die Textur
	glRotatef(fMarsRot * 3, 0.0f, 0.0f, 1.0f); // Mars - Rotation um sich selber - simuliert Eigenrotation
	gluSphere(pObj, 8.0f, 30, 17); // Mars - Kugel zeichnen(Object, Radius, Slices, Stack)
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);

	// neue Rotationsposition von Mars (Rotationsgeschwindigkeit um die Sonne)
	fMarsRot += 4.0f;
	// Rotation zurücksetzen bei 360 Grad
	if (fMarsRot >= 360.0f)
		fMarsRot = 0.0f;

	glPopMatrix();

#pragma endregion

#pragma region jupiter
	/* ----- Jupiter ----- */
	glPushMatrix();

	// quadObject erstellen und Texturkoordinaten dafür spezifizieren
	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	// Jupiter-Textur setzen
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jupiterTexture); //sets it to jupiter's texture

	// Rotationskoordinaten für Jupiter
	glRotatef(fJupiterRot, 0.0f, 1.0f, -0.3f);

	// Jupiter zeichnen
	glTranslatef(1300.0f, 0.0f, 0.0f); // Jupiter von der Sonne wegverschieben
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); // dreht die Textur
	glRotatef(fJupiterRot * 3, 0.0f, 0.0f, 1.0f); // Jupiter - Rotation um sich selber - simuliert Eigenrotation
	gluSphere(pObj, 88.0f, 30, 17); // Jupiter - Kugel zeichnen(Object, Radius, Slices, Stack)
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);

	// neue Rotationsposition von Jupiter (Rotationsgeschwindigkeit um die Sonne)
	fJupiterRot += 2.0f;
	// Rotation zurücksetzen bei 360 Grad
	if (fJupiterRot >= 360.0f)
		fJupiterRot = 0.0f;

	glPopMatrix();
#pragma endregion

#pragma region saturn
	/* ----- Saturn ----- */
	glPushMatrix(); //saves the view matrix

	// quadObject erstellen und Texturkoordinaten dafür spezifizieren
	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	// Saturn-Textur setzen
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, saturnTexture); //sets it to saturn's texture

	// Rotationskoordinaten für Saturn
	glRotatef(fSaturnRot, 0.0f, 0.8f, -0.2f);

	// Saturn zeichnen
	glTranslatef(2375.0f, 0.0f, 0.0f); // Saturn von der Sonne wegverschieben
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); // dreht die Textur
	glRotatef(fSaturnRot * 3, 0.0f, 0.0f, 1.0f); // Saturn - Rotation um sich selber - simuliert Eigenrotation
	gluSphere(pObj, 72.0f, 30, 17); // Saturn - Kugel zeichnen(Object, Radius, Slices, Stack)
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);

	// neue Rotationsposition von Saturn (Rotationsgeschwindigkeit um die Sonne)
	fSaturnRot += 1.5f;
	// Rotation zurücksetzen bei 360 Grad
	if (fSaturnRot >= 360.0f)
		fSaturnRot = 0.0f;
#pragma endregion

#pragma region saturnrings
	/* ----- Saturnringe ----- */

	// quadObject erstellen und Texturkoordinaten dafür spezifizieren
	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	gluQuadricTexture(pObj, GL_TRUE);

	// Saturnring-Textur setzen
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, saturnRingsTexture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Rotationskoordinaten für Saturnringe
	glRotatef(fSaturnRingRot, 0.0f, 0.0f, 1.0f);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glScalef(1, 1, .02);
	glRotatef(fSaturnRingRot * 3, 0.0f, 0.0f, 1.0f);
	gluSphere(pObj, 72.0f * 2, 48, 48); // Saturnringe zeichnen

	// neue Rotationsposition vom Saturnring
	fSaturnRingRot += 1.0;
	// Rotation zurücksetzen bei 360 Grad
	if (fSaturnRingRot >= 360.0f)
		fSaturnRingRot = 0.0f;

	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);
	glPopMatrix();

#pragma endregion

#pragma region uranus
	/* ----- Uranus ------ */
	glPushMatrix();

	// quadObject erstellen und Texturkoordinaten dafür spezifizieren
	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	// Uranus-Textur setzen
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, uranusTexture); //sets texture to uranus' texture

	// Rotationskoordinaten für Uranus
	glRotatef(fUranusRot, 0.0f, 0.8f, 0.2f);

	// Uranus zeichnen
	glTranslatef(3167.0f, 0.0f, 0.0f); // Uranus von der Sonne wegverschieben
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); // dreht die Textur
	glRotatef(fUranusRot * 3, 0.0f, 0.0f, 1.0f); // Uranus - Rotation um sich selber - simuliert Eigenrotation
	gluSphere(pObj, 32.0f, 30, 17); // Uranus - Kugel zeichnen(Object, Radius, Slices, Stack)
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);

	// neue Rotationsposition von Uranus (Rotationsgeschwindigkeit um die Sonne)
	fUranusRot += 1.0f;
	// Rotation zurücksetzen bei 360 Grad
	if (fUranusRot >= 360.0f)
		fUranusRot = 0.0f;

	glPopMatrix();
#pragma endregion

#pragma region neptune
	/* ----- Neptun ----- */
	glPushMatrix();

	// quadObject erstellen und Texturkoordinaten dafür spezifizieren
	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	// Neptun-Textur setzen
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, neptuneTexture); //sets it to neptune's texture

	// Rotationskoordinaten für Neptun
	glRotatef(fNeptuneRot, 0.0f, 0.8f, 0.2f);

	// Neptun zeichnen
	glTranslatef(4166.0f, 0.0f, 0.0f); // Neptun von der Sonne wegverschieben
	glRotatef(300.0f, 1.0f, 0.0f, 0.0f); // dreht die Textur
	glRotatef(fNeptuneRot * 3, 0.0f, 0.0f, 1.0f); // Neptun - Rotation um sich selber - simuliert Eigenrotation
	gluSphere(pObj, 32.0f, 30, 17); // Neptun - Kugel zeichnen(Object, Radius, Slices, Stack)
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);

	// neue Rotationsposition von Neptun (Rotationsgeschwindigkeit um die Sonne)
	fNeptuneRot += 0.6f;
	// Rotation zurücksetzen bei 360 Grad
	if (fNeptuneRot >= 360.0f)
		fNeptuneRot = 0.0f;

	glPopMatrix();
#pragma endregion

#pragma region pluto
	/* ----- Pluto ----- */
	glPushMatrix();

	// quadObject erstellen und Texturkoordinaten dafür spezifizieren
	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	// Pluto-Textur setzen
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, plutoTexture); //sets it to plutos texture

	// Rotationskoordinaten für Pluto
	glRotatef(fPlutoRot, 0.0f, 0.8f, 0.2f);

	// Pluto zeichnen
	glTranslatef(5000.0f, 0.0f, 0.0f); // Pluto von der Sonne wegverschieben
	glRotatef(300.0f, 1.0f, 0.0f, 0.0f); // dreht die Textur
	glRotatef(fPlutoRot * 3, 0.0f, 0.0f, 1.0f); // Pluto - Rotation um sich selber - simuliert Eigenrotation
	gluSphere(pObj, 3.2f, 30, 17); // Pluto - Kugel zeichnen(Object, Radius, Slices, Stack)
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);

	// neue Rotationsposition von Pluto (Rotationsgeschwindigkeit um die Sonne)
	fPlutoRot += 0.2f;
	// Rotation zurücksetzen bei 360 Grad
	if (fPlutoRot >= 360.0f)
		fPlutoRot = 0.0f;

	glPopMatrix();
#pragma endregion

#pragma region earth
	/* ----- Erde ----- */
	glPushMatrix();

	// quadObject erstellen und Texturkoordinaten dafür spezifizieren
	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	// Erden-Textur setzen
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, earthTexture);

	// Rotationskoordinaten für Erde (Rotation um die Sonne)
	glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f);

	// Erde zeichnen
	glTranslatef(500.0f, 0.0f, 0.0f); // Erde von der Sonne wegverschieben
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); // dreht die Textur
	glRotatef(fEarthRot * 3, 0.0f, 0.0f, 1.0f); // Erde - Rotation um sich selber - simuliert Eigenrotation
	gluSphere(pObj, 16.0f, 30, 17); // Erde - Kugel zeichnen(Object, Radius, Slices, Stack)
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);
#pragma endregion

#pragma region earthMoon
	/* ----- Mond ----- */

	// quadObject erstellen und Texturkoordinaten dafür spezifizieren
	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	// Mond-Textur setzen
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, moonTexture);

	glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f); // Mond-Rotation um die Erde
	glTranslatef(25.0f, 0.0f, 0.0f); // Mond von der Erde wegverschieben
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); // dreht die Textur
	glRotatef(fMoonRot * 3, 0.0f, 0.0f, 1.0f); // Mond - Rotation um sich selber - simuliert Eigenrotation

	// neue Rotationsposition vom Mond
	fMoonRot = 2.4f;
	// Rotation zurücksetzen bei 360 Grad
	if (fMoonRot >= 360.0f)
		fMoonRot = 0.0f;

	// Mond zeichnen
	gluSphere(pObj, 4.3f, 30, 17); // Mond - Kugel zeichnen(Object, Radius, Slices, Stack)
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);
	glPopMatrix();

	// neue Rotationsposition von der Erde
	fEarthRot += 5.0f;
	// Rotation zurücksetzen bei 360 Grad
	if (fEarthRot >= 360.0f)
		fEarthRot = 0.0f;
	
	glPopMatrix();
#pragma endregion

#pragma region ship
	/* ----- Ship ----- */
	glLoadIdentity();

	gluLookAt(200.0, 200.0, 200.0,	// Gibt die Position des Betrachters an
		100.0, 0.0, -150.0,			// Gibt die Position des Refernenzpunktes an, auf den "geblickt" wird
		0.0f, 1.0f, 0.0f);			// Gibt die Richtung des Vektors an, der nach oben zeigt 

	// Ligting für das Spaceship
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbShip);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffShip);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef(x, y, z); // Position des Raumschiffes in der Skybox
	//glRotatef(graus, 1.0, 0.0, 0.0);

	// Spaceship-Rotation mit der Maus steuern
	glRotatef(solarShipAngle, 0.0, 0.0, 1.0);
	//glRotatef(solarShipAngle, 0.0, 1.0, 0.0);
	//glRotatef(solarShipAngle, 1.0, 0.0, 0.0);

	glCallList(displayList);
#pragma endregion

	// Sonnensystem anzeigen
	glutSwapBuffers();

}

/* ----- Initialisierung der Funktion für Ligthing, etc. ----- */
void SetupRC()
{
	// Licht-Werte und Koordinaten
	glEnable(GL_DEPTH_TEST); // Tiefenbuffer aktivieren
	glFrontFace(GL_CCW);	
	glEnable(GL_CULL_FACE);

	// Lighting aktivieren
	glEnable(GL_LIGHTING);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	// Colortracking aktivieren (mehrere Materialparameter benutzen die aktuelle Farbeinstellung)
	glEnable(GL_COLOR_MATERIAL);

	// Materialeigenschaften festsetzen
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Hintergrundfarbe
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}

/* ----- Ermöglich die Windows-Größe zu verändert ----- */
void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	// Division durch Null vermeiden
	if (h == 0)	h = 1;

	// Viewport auf Windows-Dimensionen festlegen
	glViewport(0, 0, w, h);

	// Window-Verhältnis berechnen
	fAspect = (GLfloat)w / (GLfloat)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Ansicht hat 45 Grad und liegt zwischen 1 und 6000
	gluPerspective(45.0f, fAspect, 1.0, 6000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 600); // Window-Größe
	window = glutCreateWindow("SolarSystem"); // Window-Name

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(keyDown); // wird aufgerufen, wenn eine Taste gedrückt wird	
	glutTimerFunc(250, TimerFunc, 1);
	SetupRC();

	// Mausfunktionen
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	
	/* ----- Ship ----- */
	spaceship = (GLMmodel*)malloc(sizeof(GLMmodel));
	spaceship = glmReadOBJ("ship.obj"); // Laden des Ship-Modell

	displayList = glGenLists(1);
		glNewList(displayList, GL_COMPILE);
		glmFacetNormals(spaceship);
		glmVertexNormals(spaceship, 90.0);
		glmLinearTexture(spaceship);
		glmDraw(spaceship, GLM_SMOOTH);
	glEndList();

	// Flag, welches sicherstellt, dass die Texturen nur einmal geladen werden
	if (texturesCreated == false)
	{
		InitialiseTextures();
		texturesCreated = true;
	}

	glutMainLoop();

	return 0;
}

#pragma region keyfunction
void keyDown(unsigned char key, int x, int y)
{
	// bewegt Kamera nach links
	if (key == 'A' || key == 'a')
	{
		fSunX += 30.0f;
		//fCamX += -30.0f;
		/*
		if (testShip == 0) {
			solarShipAngle += 30.0f;
			testShip = 1;
		}
		else {
			solarShipAngle -= 30.0f;
			testShip = 0;
		}
		*/
	}
	// bewegt Kamera nach rechts
	if (key == 'D' || key == 'd')
	{
		fSunX += -30.0f;
		//fCamX += 30.0f;
	}
	// bewegt Kamera nach oben
	if (key == 'W' || key == 'w')
	{
		fSunY += -30.0f;
		//fCamY += 30.0f;
	}
	// Bewegt Kamera nach unten
	if (key == 'S' || key == 's')
	{
		fSunY += 30.0f;
		//fCamY += -30.0f;
	}
	// zoomt die Kamera raus
	if (key == 'X' || key == 'x')
	{
		fSunZ += -30.0f;
		//fCamZ += 30.0f;
	}
	// zoomt die Kamera rein
	if (key == 'Z' || key == 'z')
	{
		fSunZ += 30.0f;
		//fCamZ += -30.0f;
	}
	// rotiert die Kamera um die positive x-Achse 
	if (key == 'J' || key == 'j')
	{
		fSunRotY += 3.0f;
	}
	// rotiert die Kamera um die negative x-Achse 
	if (key == 'L' || key == 'l')
	{
		fSunRotY += -3.0f;
	}
	// rotiert die Kamera um die negative y-Achse 
	if (key == 'I' || key == 'i')
	{
		fSunRotX += 3.0f;
	}
	// rotiert die Kamera um die positive y-Achse 
	if (key == 'K' || key == 'k')
	{
		fSunRotX += -3.0f;
	}
	// rotiert die Kamera um die negative z-Achse
	if (key == 'M' || key == 'm')
	{
		fSunRotZ += -3.0f;
	}
	// rotiert die Kamera um die positive z-Achse
	if (key == 'N' || key == 'n')
	{
		fSunRotZ += 3.0f;
	}

	// schließt das Programm mit ESC
	if (key == 27)
	{
		glutDestroyWindow(window);
		exit(0);
	}

}
#pragma endregion

unsigned char *LoadBmp(char *fn, int *wi, int *hi)
{
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER bmih;
	WORD bits;
	FILE *t24;
	unsigned char *lpBitmapBits;
	long imagesize, nc;

	// liest das .bmp File
	t24 = fopen((char *)fn, "rb");
	if (t24 == NULL){ printf("Could not open input file\n"); exit(0); }
	fread((char *)&bmfh, sizeof(BITMAPFILEHEADER), 1, t24);
	fread((char *)&bmih, sizeof(BITMAPINFOHEADER), 1, t24);
	if (bmih.biClrUsed != 0)nc = bmih.biClrUsed;
	else{
		bits = bmih.biBitCount;
		switch (bits){
		case 1:    nc = 2;   break;
		case 4:    nc = 16;  break;
		case 8:    nc = 256; break;
		default:   nc = 0;   break;
		}
	}
	if (nc > 0){ printf("Cannot handle paletted image\n"); exit(0); }
	imagesize = bmfh.bfSize - bmfh.bfOffBits;
	if ((lpBitmapBits = (unsigned char *)malloc(imagesize)) == NULL){ fclose(t24); exit(0); }
	fread((char *)lpBitmapBits, imagesize, 1, t24);
	fclose(t24);
	*wi = bmih.biWidth; *hi = bmih.biHeight;
	return lpBitmapBits;
}

void InitialiseTextures()
{
	// ruft die Funktion "GenerateTextures" auf um jede Textur zu laden mit Hilfe eines Index
	GenerateTextures("earthmap1k.bmp", 1);
	GenerateTextures("sunmap.bmp", 2);
	GenerateTextures("mercurymap.bmp", 3);
	GenerateTextures("venusmap.bmp", 4);
	GenerateTextures("moon.bmp", 5);
	GenerateTextures("marsmap1k.bmp", 6);
	GenerateTextures("jupitermap.bmp", 7);
	GenerateTextures("saturnmap.bmp", 8);
	GenerateTextures("uranusmap.bmp", 9);
	GenerateTextures("neptunemap.bmp", 10);
	GenerateTextures("plutomap2k.bmp", 11);
	GenerateTextures("stars.bmp", 12);
	GenerateTextures("saturnringmap.bmp", 13);
}

// name: steht für den Filenamen der Texture
// i: steht für den index-number, damit die Textur dem richtigen Planeten zugeordnet werden kann
void GenerateTextures(char *name, int i)
{
	unsigned char *pix;
	int w, h;
	glEnable(GL_TEXTURE_2D);
	
	// Textur aus Datei laden
	pix = LoadBmp(name, &w, &h);
	if (i == 1) // zuordnen der Textur für die Erde
	{
		glGenTextures(1, &earthTexture);
		glBindTexture(GL_TEXTURE_2D, earthTexture);
	}
	if (i == 2) // zuordnen der Textur für die Sonne
	{
		glGenTextures(1, &sunTexture);
		glBindTexture(GL_TEXTURE_2D, sunTexture);
	}
	if (i == 3) // zuordnen der Textur für den Merkur
	{
		glGenTextures(1, &mercuryTexture);
		glBindTexture(GL_TEXTURE_2D, mercuryTexture);
	}
	if (i == 4) // zuordnen der Textur für die Venus
	{
		glGenTextures(1, &venusTexture);
		glBindTexture(GL_TEXTURE_2D, venusTexture);
	}
	if (i == 5) // zuordnen der Textur für den Mond
	{
		glGenTextures(1, &moonTexture);
		glBindTexture(GL_TEXTURE_2D, moonTexture);
	}
	if (i == 6) // zuordnen der Textur für den Mars
	{
		glGenTextures(1, &marsTexture);
		glBindTexture(GL_TEXTURE_2D, marsTexture);
	}
	if (i == 7) // zuordnen der Textur für den Jupiter
	{
		glGenTextures(1, &jupiterTexture);
		glBindTexture(GL_TEXTURE_2D, jupiterTexture);
	}
	if (i == 8) // zuordnen der Textur für den Saturn
	{
		glGenTextures(1, &saturnTexture);
		glBindTexture(GL_TEXTURE_2D, saturnTexture);
	}
	if (i == 9) // zuordnen der Textur für den Uranus
	{
		glGenTextures(1, &uranusTexture);
		glBindTexture(GL_TEXTURE_2D, uranusTexture);
	}
	if (i == 10) // zuordnen der Textur für den Neptun
	{
		glGenTextures(1, &neptuneTexture);
		glBindTexture(GL_TEXTURE_2D, neptuneTexture);
	}
	if (i == 11) // zuordnen der Textur für den Pluto
	{
		glGenTextures(1, &plutoTexture);
		glBindTexture(GL_TEXTURE_2D, plutoTexture);
	}
	if (i == 12) // zuordnen der Textur für den Sternen-Hintergrund
	{
		glGenTextures(1, &starsTexture);
		glBindTexture(GL_TEXTURE_2D, starsTexture);
	}
	if (i == 13) // zuordnen der Textur für die Saturnringe
	{
		glGenTextures(1, &saturnRingsTexture);
		glBindTexture(GL_TEXTURE_2D, saturnRingsTexture);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pix);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	free(pix);
	glDisable(GL_TEXTURE_2D);
}

#pragma region mousefunction
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON: 
		if (state == GLUT_DOWN){ // Maustaste gedrückt
			moving = 1;
			// Maus-Koordinaten
			mouse_x = x;
			mouse_y = y;

		}
		else if (state == GLUT_UP){ // Maustaste nicht gedrückt
			moving = 0;
		}
		break;

	default:
		break;
	}

	glutPostRedisplay();
}

void mouseMotion(int x, int y) {

	if (moving) { // Maustaste ist gedrückt

		solarShipAngle = solarShipAngle + (x - mouse_x);

		mouse_x = x;
		mouse_y = y;
		glutPostRedisplay();
	}
}
#pragma endregion