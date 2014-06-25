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

/* ----- Ship values ---- */
float x = 50, y = -150, z = -100, graus = 0;
int fps = 0, displayList = 0;

//GLfloat lightPosShip[4] = { 50.0, 30.0, 0.0, 0.0 };
GLfloat lightAmbShip[3] = { 0.1, 0.1, 0.1 };
GLfloat lightDiffShip[3] = { 1.0, 1.0, 1.0 };

GLMmodel* spaceship;

/* ----- Lighting values ---- */
GLfloat  whiteLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat  sourceLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
GLfloat	 lightPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };

//a flag that is used to ensure the textures are only loaded once
bool texturesCreated = false;

/* ---- Textures ----- */
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

/* ----- Sun positions and rotation angles ----- */
GLfloat fSunX = 0.0f;
GLfloat fSunY = 0.0f;
GLfloat fSunZ = -500.0f;
GLfloat fCamX = 0.0f;
GLfloat fCamY = 0.0f;
GLfloat fCamZ = 0.0f;
GLfloat fSunRotX = 0.0f;
GLfloat fSunRotY = 0.0f;
GLfloat fSunRotZ = 0.0f;

/* ----- prototypes for the functions ---- */
void keyDown(unsigned char, int, int);
unsigned char *LoadBmp(char *fn, int *wi, int *hi);
void GenerateTextures(char *, int);
void InitialiseTextures(void);

/* ---- Called to draw scene ---- */
void RenderScene(void)
{
	GLUquadricObj* pObj;
	/* ---- angle of revolution ---- */
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

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Save the matrix state and do the rotations
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();


	// Translate the whole scene out and into view	based on the Sun's position
	glTranslatef(fSunX, fSunY, fSunZ);

	/* ----- Sun ----- */
	glDisable(GL_LIGHTING);

	pObj = gluNewQuadric(); //creates new quadric for pObj
	gluQuadricTexture(pObj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sunTexture); //sets texture to the sun texture

	//Rotate the Sun on its centre
	glRotatef(fSunRotX, 1.0f, 0.0f, 0.0f); //rotates Sun along X axis
	glRotatef(fSunRotY, 0.0f, 1.0f, 0.0f); //rotates Sun along Y axis
	glRotatef(fSunRotZ, 0.0f, 0.0f, 1.0f); //rotates Sun along Z axis
	gluSphere(pObj, 25.0f, 30, 17); //draw sphere for the sun
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj); //frees pObj

	glEnable(GL_LIGHTING);

	// Moves the light to the position of the sun
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

#pragma region skybox

	// Store the current matrix
	glPushMatrix();

	// Reset and transform the matrix.

	// Enable/Disable features
	glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);

	// Just in case we set all vertices to white.
	glColor4f(1, 1, 1, 1);
	GLfloat val = 500.0f;

	// Render the front quad
	glBindTexture(GL_TEXTURE_2D, starsTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(val, -val, val);
	glTexCoord2f(1, 0); glVertex3f(-val, -val, val);
	glTexCoord2f(1, 1); glVertex3f(-val, val, val);
	glTexCoord2f(0, 1); glVertex3f(val, val, val);
	glEnd();

	// Render the left quad
	glBindTexture(GL_TEXTURE_2D, starsTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(val, -val, -val);
	glTexCoord2f(1, 0); glVertex3f(val, -val, val);
	glTexCoord2f(1, 1); glVertex3f(val, val, val);
	glTexCoord2f(0, 1); glVertex3f(val, val, -val);
	glEnd();

	// Render the back quad
	glBindTexture(GL_TEXTURE_2D, starsTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-val, -val, -val);
	glTexCoord2f(1, 0); glVertex3f(val, -val, -val);
	glTexCoord2f(1, 1); glVertex3f(val, val, -val);
	glTexCoord2f(0, 1); glVertex3f(-val, val, -val);

	glEnd();

	// Render the right quad
	glBindTexture(GL_TEXTURE_2D, starsTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-val, val, -val);
	glTexCoord2f(1, 0); glVertex3f(-val, val, val);
	glTexCoord2f(1, 1); glVertex3f(-val, -val, val);
	glTexCoord2f(0, 1); glVertex3f(-val, -val, -val);
	glEnd();

	// Render the top quad
	glBindTexture(GL_TEXTURE_2D, starsTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(val, val, -val);
	glTexCoord2f(1, 0); glVertex3f(val, val, val);
	glTexCoord2f(1, 1); glVertex3f(-val, val, val);
	glTexCoord2f(0, 1); glVertex3f(-val, val, -val);
	glEnd();

	// Render the bottom quad
	glBindTexture(GL_TEXTURE_2D, starsTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(-val, -val, -val);
	glTexCoord2f(1, 0); glVertex3f(-val, -val, val);
	glTexCoord2f(1, 1); glVertex3f(val, -val, val);
	glTexCoord2f(0, 1); glVertex3f(val, -val, -val);
	glEnd();

	// Restore enable bits and matrix
	glPopAttrib();
	glPopMatrix();

#pragma endregion

#pragma region mercury 
	/* ----- Mercury ----- */
	glPushMatrix(); //save view matrix

	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, mercuryTexture); //sets it to the mercury texture

	//Rotate coordinate system for Mercury
	glRotatef(fMercuryRot, 1.0f, 2.0f, 0.0f);

	//Draw Mercury
	glTranslatef(45.0f, -15.0f, 0.0f); //moves the position away and out from the sun
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //Rotates mercury on its spot, fixing the texture display
	glRotatef(fMercuryRot * 3, 0.0f, 0.0f, 1.0f); //Rotates Mercury on its spot, simulating the planet spinning
	gluSphere(pObj, 8.0f, 30, 17); //draws the sphere for mercury
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);

	//gets the new rotation position for mercury
	fMercuryRot += 20.0f;
	//resets the rotation of mercury
	if (fMercuryRot >= 360.0f)
		fMercuryRot = 0.0f;

	glPopMatrix(); //restore viewing Matrix

#pragma endregion

#pragma region venus
	/* ----- Venus ----- */
	glPushMatrix(); //stores the view matrix

	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, venusTexture); //sets the texture to the texture for venus

	//Rotate coordinate system for Venus
	glRotatef(fVenusRot, 0.0f, 1.0f, 0.0f);

	//Draw Venus
	glTranslatef(65.0f, 0.0f, 0.0f); //moves the position away and out from the sun
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //Rotates venus on its spot, fixing the texture display
	glRotatef(fVenusRot * 3, 0.0f, 0.0f, 1.0f); //Rotates Venus on its spot, simulating the planet spinning
	gluSphere(pObj, 14.0f, 30, 17); //draws the sphere for venus
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj); //frees pObj

	//gets the new rotation for venus
	fVenusRot += 10.0f;
	//resets the rotation
	if (fVenusRot >= 360.0f)
		fVenusRot = 0.0f;

	//restores the view matrix
	glPopMatrix();

#pragma endregion

#pragma region mars
	/* ----- Mars ----- */
	glPushMatrix();

	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, marsTexture); //sets the texture to mars' texture

	//Rotate coordinate system for Mars
	glRotatef(fMarsRot, 0.0f, 1.0f, 0.3f);

	//Draw Mars
	glTranslatef(130.0f, 0.0f, 0.0f); //positions mars out from the sun
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //Rotates mars on its spot, fixing the texture display
	glRotatef(fMarsRot * 3, 0.0f, 0.0f, 1.0f); //Rotates Mars on its spot, simulating the planet spinning
	gluSphere(pObj, 7.0f, 30, 17); //Draws the sphere
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);

	//gets the next rotation value for mars to orbit around the sun
	fMarsRot += 4.0f;
	//resets the rotation value
	if (fMarsRot >= 360.0f)
		fMarsRot = 0.0f;

	//resets the view matrix to focus on the sun
	glPopMatrix();

#pragma endregion

#pragma region jupiter
	/* ----- Jupiter ----- */
	glPushMatrix(); //stores the view matrix

	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, jupiterTexture); //sets it to jupiter's texture

	//Rotate coordinate system for Jupiter
	glRotatef(fJupiterRot, 0.0f, 1.0f, -0.3f);

	//Draw Jupiter
	glTranslatef(200.0f, 0.0f, 0.0f); //moves the position out from the sun
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //Rotates Jupiter on its spot, fixing the texture display
	glRotatef(fJupiterRot * 3, 0.0f, 0.0f, 1.0f); //Rotates Jupiter on its spot, simulating the planet spinning
	gluSphere(pObj, 22.0f, 30, 17); //draws the sphere
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj); //frees pObj

	//gets the new rotation for jupiter
	fJupiterRot += 2.0f;
	//resets the rotation
	if (fJupiterRot >= 360.0f)
		fJupiterRot = 0.0f;

	//restores the view matrix
	glPopMatrix();

#pragma endregion

#pragma region saturn
	/* ----- Saturn ----- */
	glPushMatrix(); //saves the view matrix

	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, saturnTexture); //sets it to saturn's texture

	//Rotate coordinate system for Saturn
	glRotatef(fSaturnRot, 0.0f, 0.8f, -0.2f);

	//Draw Saturn
	glTranslatef(250.0f, 0.0f, 0.0f); //moves away from the sun
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //Rotates Saturn on its spot, fixing the texture display
	glRotatef(fSaturnRot * 3, 0.0f, 0.0f, 1.0f); //Rotates Saturn on its spot, simulating the planet spinning
	gluSphere(pObj, 20.0f, 30, 17); //draws the sphere
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj); //frees pObj

	//gets the new rotation value for saturn
	fSaturnRot += 1.5f;
	//resets the rotation
	if (fSaturnRot >= 360.0f)
		fSaturnRot = 0.0f;


	/* ----- SaturnRings ----- */

	pObj = gluNewQuadric();
	gluQuadricNormals(pObj, GLU_SMOOTH);
	gluQuadricTexture(pObj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, saturnRingsTexture);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glRotatef(fSaturnRingRot, 0.0f, 0.0f, 1.0f);
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glScalef(1, 1, .02);
	glRotatef(fSaturnRingRot * 3, 0.0f, 0.0f, 1.0f);
	gluSphere(pObj, 20.0f * 2, 48, 48);


	fSaturnRingRot += 1.0;
	//resets the rotation
	if (fSaturnRingRot >= 360.0f)
		fSaturnRingRot = 0.0f;

	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);
	//restores the view matrix
	glPopMatrix();

#pragma endregion

#pragma region uranus
	/* ----- Uranus ------ */
	glPushMatrix();

	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, uranusTexture); //sets texture to uranus' texture

	//Rotate coordinate system for Uranus
	glRotatef(fUranusRot, 0.0f, 0.8f, 0.2f);

	//Draw Uranus
	glTranslatef(285.0f, 0.0f, 0.0f); //moves away and out from the sun
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //Rotates Uranus on its spot, fixing the texture display
	glRotatef(fUranusRot * 3, 0.0f, 0.0f, 1.0f); //Rotates Uranus on its spot, simulating the planet spinning
	gluSphere(pObj, 10.0f, 30, 17); //draws the sphere
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj); //frees pObj

	//gets the new rotation for uranus
	fUranusRot += 1.0f;
	//resets the rotation
	if (fUranusRot >= 360.0f)
		fUranusRot = 0.0f;

	//restores the view matrix
	glPopMatrix();

#pragma endregion

#pragma region neptune
	/* ----- Neptune ----- */
	glPushMatrix();

	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, neptuneTexture); //sets it to neptune's texture

	//Rotate coordinate system for Neptune
	glRotatef(fNeptuneRot, 0.0f, 0.8f, 0.2f);

	//Draw Neptune
	glTranslatef(300.0f, 0.0f, 0.0f); //moves the position out from the sun
	glRotatef(300.0f, 1.0f, 0.0f, 0.0f); //Rotates Neptune on its spot, fixing the texture display
	glRotatef(fNeptuneRot * 3, 0.0f, 0.0f, 1.0f); //Rotates Neptune on its spot, simulating the planet spinning
	gluSphere(pObj, 12.0f, 30, 17); //draw the sphere for neptune
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj); //frees pObj

	//gets the new rotation value for neptune
	fNeptuneRot += 0.6f;
	//resets the rotation
	if (fNeptuneRot >= 360.0f)
		fNeptuneRot = 0.0f;

	//restores the view matrix
	glPopMatrix();

#pragma endregion

#pragma region pluto
	/* ----- Pluto ----- */
	glPushMatrix(); //stores the view matrix

	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, plutoTexture); //sets it to plutos texture

	//Rotate coordinate system for Pluto
	glRotatef(fPlutoRot, 0.0f, 0.8f, 0.2f);

	//Draw Pluto
	glTranslatef(325.0f, 0.0f, 0.0f); //moves away and out from the sun
	glRotatef(300.0f, 1.0f, 0.0f, 0.0f); //Rotates Pluto on its spot, fixing the texture display
	glRotatef(fPlutoRot * 3, 0.0f, 0.0f, 1.0f); //Rotates the Pluto on its spot, simulating the planet spinning
	gluSphere(pObj, 12.0f, 30, 17); //draws the sphere
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj); //frees pObj

	//gets the new rotation for pluto
	fPlutoRot += 0.2f;
	//resets the rotation
	if (fPlutoRot >= 360.0f)
		fPlutoRot = 0.0f;

	//restores the view matrix
	glPopMatrix();

#pragma endregion

#pragma region earth
	/* ----- Earth ----- */
	glPushMatrix();

	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, earthTexture);

	// Rotate coordinate system for Earth
	glRotatef(fEarthRot, 0.0f, 1.0f, 0.0f); //rotate earth around the Sun

	// Draw the Earth
	glTranslatef(100.0f, 0.0f, 0.0f); //moves the position out from the sun
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //Rotates the Earth on its spot, fixing the texture display
	glRotatef(fEarthRot * 3, 0.0f, 0.0f, 1.0f); //Rotates the Earth on its spot, simulating the planet spinning
	gluSphere(pObj, 16.0f, 30, 17); //draws the sphere for the earth
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj); //frees pObj

#pragma region earthMoon
	/* ----- Moon ----- */
	// Rotate from Earth based coordinates and draw Moon
	pObj = gluNewQuadric();
	gluQuadricTexture(pObj, GL_TRUE);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, moonTexture); //sets the texture to the moon
	glRotatef(fMoonRot, 0.0f, 1.0f, 0.0f); //rotates the moon around the earth
	glTranslatef(25.0f, 0.0f, 0.0f); //moves away and out from the earth
	glRotatef(270.0f, 1.0f, 0.0f, 0.0f); //Rotates the moon on its spot, fixing the texture display
	glRotatef(fMoonRot * 3, 0.0f, 0.0f, 1.0f); //Rotates the moon on its spot, simulating the planet spinning

	//gets the new rotation for the moon
	fMoonRot = 2.4f;
	//resets the rotation
	if (fMoonRot >= 360.0f)
		fMoonRot = 0.0f;

	gluSphere(pObj, 4.0f, 30, 17); //draws the sphere for the moon
	glDisable(GL_TEXTURE_2D);

	gluDeleteQuadric(pObj);
	// Restore the matrix state
	glPopMatrix();	// Modelview matrix

#pragma endregion


	// Step earth orbit 5 degrees
	fEarthRot += 5.0f;
	//resets the rotation value
	if (fEarthRot >= 360.0f)
		fEarthRot = 0.0f;
	// Restore the matrix state
	glPopMatrix();	// Modelview matrix

#pragma endregion

#pragma region ship
	/* ----- Ship ----- */
	glLoadIdentity();

	gluLookAt(200.0, 200.0, 200.0,	// Gibt die Position des Betrachters an. 
		100.0, 0.0, -150.0,			// Gibt die Position des Refernenzpunktes an, auf den "geblickt" wird.
		0.0f, 1.0f, 0.0f);			// Gibt die Richtung des Vektors an, der nach oben zeigt. 

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbShip);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffShip);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef(x, y, z);
	glRotatef(graus, 1.0, 0.0, 0.0);

	glCallList(displayList);
#pragma endregion

	// Show the image
	glutSwapBuffers();

}

// This function does any needed initialization on the rendering
// context. 

void SetupRC()
{
	// Light values and coordinates
	glEnable(GL_DEPTH_TEST);	// Hidden surface removal
	glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
	glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

	// Enable lighting
	glEnable(GL_LIGHTING);

	// Setup and enable light 0
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, whiteLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sourceLight);
	//glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
	glEnable(GL_LIGHT0);

	// Enable color tracking
	glEnable(GL_COLOR_MATERIAL);

	// Set Material properties to follow glColor values
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	// Black blue background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void TimerFunc(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunc, 1);
}

//allows the window size to be changed by the user
void ChangeSize(int w, int h)
{
	GLfloat fAspect;

	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Calculate aspect ratio of the window
	fAspect = (GLfloat)w / (GLfloat)h;

	// Set the perspective coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// field of view of 45 degrees, near and far planes 1.0 and 800
	gluPerspective(45.0f, fAspect, 1.0, 1600.0);

	// Modelview matrix reset
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 600);
	window = glutCreateWindow("SolarSystem"); //names the window

	glutReshapeFunc(ChangeSize);
	glutDisplayFunc(RenderScene);
	glutKeyboardFunc(keyDown); //calls this procedure everytime a key is pressed	
	glutTimerFunc(250, TimerFunc, 1);
	SetupRC();

	/* ----- Ship ----- */
	spaceship = (GLMmodel*)malloc(sizeof(GLMmodel));
	spaceship = glmReadOBJ("ship.obj");

	displayList = glGenLists(1);
	glNewList(displayList, GL_COMPILE);
	glmDraw(spaceship, GLM_SMOOTH);
	glEndList();

	//a flag check to make sur ethe textures are only loaded in once
	if (texturesCreated == false)
	{
		InitialiseTextures();
		texturesCreated = true; //sets the flag to true so this if statement doesn't execute again
	}

	glutMainLoop();

	return 0;
}

#pragma region keyfunction
void keyDown(unsigned char key, int x, int y)
{
	//Moves the camera to the left
	if (key == 'A' || key == 'a')
	{
		fSunX += 3.0f;
		fCamX += -3.0f;
	}
	//Moves the camera to the right
	if (key == 'D' || key == 'd')
	{
		fSunX += -3.0f;
		fCamX += 3.0f;
	}
	//Moves the camera up
	if (key == 'W' || key == 'w')
	{
		fSunY += -3.0f;
		fCamY += 3.0f;
	}
	//Moves the camera down
	if (key == 'S' || key == 's')
	{
		fSunY += 3.0f;
		fCamY += -3.0f;
	}
	//Zooms the camera out
	if (key == 'X' || key == 'x')
	{
		fSunZ += -3.0f;
		fCamZ += 3.0f;
	}
	//Zooms the camera in
	if (key == 'Z' || key == 'z')
	{
		fSunZ += 3.0f;
		fCamZ += -3.0f;
	}
	//Rotates the camera along the positive X axis
	if (key == 'J' || key == 'j')
	{
		fSunRotY += 3.0f;
	}
	//Rotates the camera along the negative X axis
	if (key == 'L' || key == 'l')
	{
		fSunRotY += -3.0f;
	}
	//Rotates the camera along the negative Y axis
	if (key == 'I' || key == 'i')
	{
		fSunRotX += 3.0f;
	}
	//Rotates the camera along the positive Y axis
	if (key == 'K' || key == 'k')
	{
		fSunRotX += -3.0f;
	}
	//Rotates the camera along the positive Z axis
	if (key == 'M' || key == 'm')
	{
		fSunRotZ += -3.0f;
	}
	//Rotates the camera along the positive Z axis
	if (key == 'N' || key == 'n')
	{
		fSunRotZ += 3.0f;
	}

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

	// read the bitmap
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
	//calls the procedure to load and store every texture
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


//the char* is used to store the name of the texture file to be loaded, the number is used to determine which variable the texture is stored in
void GenerateTextures(char *name, int i)
{
	unsigned char *pix;
	int w, h;
	glEnable(GL_TEXTURE_2D);
	//assigns pix to a texture
	pix = LoadBmp(name, &w, &h);
	if (i == 1) //gets & sets texture for the earth
	{
		glGenTextures(1, &earthTexture);
		glBindTexture(GL_TEXTURE_2D, earthTexture);
	}
	if (i == 2) //gets & sets texture for the sun
	{
		glGenTextures(1, &sunTexture);
		glBindTexture(GL_TEXTURE_2D, sunTexture);
	}
	if (i == 3) //gets & sets texture for mercury
	{
		glGenTextures(1, &mercuryTexture);
		glBindTexture(GL_TEXTURE_2D, mercuryTexture);
	}
	if (i == 4) //gets & sets texture for venus
	{
		glGenTextures(1, &venusTexture);
		glBindTexture(GL_TEXTURE_2D, venusTexture);
	}
	if (i == 5) //gets & sets texture for the moon
	{
		glGenTextures(1, &moonTexture);
		glBindTexture(GL_TEXTURE_2D, moonTexture);
	}
	if (i == 6) //gets & sets texture for the mars
	{
		glGenTextures(1, &marsTexture);
		glBindTexture(GL_TEXTURE_2D, marsTexture);
	}
	if (i == 7) //gets & sets texture for the jupiter
	{
		glGenTextures(1, &jupiterTexture);
		glBindTexture(GL_TEXTURE_2D, jupiterTexture);
	}
	if (i == 8) //gets & sets texture for the saturn
	{
		glGenTextures(1, &saturnTexture);
		glBindTexture(GL_TEXTURE_2D, saturnTexture);
	}
	if (i == 9) //gets & sets texture for the uranus
	{
		glGenTextures(1, &uranusTexture);
		glBindTexture(GL_TEXTURE_2D, uranusTexture);
	}
	if (i == 10) //gets & sets texture for the neptune
	{
		glGenTextures(1, &neptuneTexture);
		glBindTexture(GL_TEXTURE_2D, neptuneTexture);
	}
	if (i == 11) //gets & sets texture for the pluto
	{
		glGenTextures(1, &plutoTexture);
		glBindTexture(GL_TEXTURE_2D, plutoTexture);
	}
	if (i == 12) //gets & sets texture for the stars
	{
		glGenTextures(1, &starsTexture);
		glBindTexture(GL_TEXTURE_2D, starsTexture);
	}
	if (i == 13)
	{
		glGenTextures(1, &saturnRingsTexture);
		glBindTexture(GL_TEXTURE_2D, saturnRingsTexture);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
		0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pix);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	free(pix); //deletes the data held by pix
	glDisable(GL_TEXTURE_2D);
}