#include <GL/glut.h>
#include "terrain.h"
#include "world.h"
#include "camera.h"
#include "particlehandler.h"
#include "water.h"
#include "math.h"
#include <stdlib.h>
#include <time.h>
#include "sph.h"

#define wWidth 800
#define wHeight 600
#define MAX_PARTICLES 1000;
#define SLOW_SPEED 0.2f;
#define fullscreen false
// TODO: Add terrain parameters via #define's

world w(64,64);
terrain t(w);
camera c;
particlehandler p(3000, 0.2f, w);
water wAwesome;

// Initialize EVERYTHING
// Called at program start
void init(){
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	if(fullscreen) glutFullScreen();
	// TODO: initialize the constructor for enviornment with its parameters
	
	// initialize the random seed
	srand((unsigned)time(0));
}

// Draws everything to the screen when glutPostRedisplay() is called
// TODO:
//	Check if only images in the view frustrum are being drawn
void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	// TODO: Call drawing functions from different objects	
	t.display();
	p.display(1);
	w.drawNormals();
	glutSwapBuffers();
}

// Adjusts the camera for when the user modifies the window size
// called when window is adjusted and when program launches
void reshape(int w, int h){
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// The update cycle is called every frame
void update(){
	// TODO: figure some update logic
	// redraw everything	
	glutPostRedisplay();
}

// Call this before you exit so you can clean up all of your data
void unload(){
	// TODO: Clean up attributes in the main
	// TODO: Clean up objects

	// Clean up all the environment objects
	t.~terrain();
}

void keyboard(unsigned char key, int x, int y){
	sph s;
	switch(key){
		// quit the program and clean up data
		case 'q': case 'Q': case 27:
			unload();
			exit(0);
			break;
		// change to full screen
		case 'f': case 'F':
			glutFullScreen();
			break;
		// perform the terrain generation
		case 't': case 'T':
			t.generate(1000, w.getWidth(), w.getLength(), 1.0);
			break;
		case 'y': case 'Y':
			t.smooth(1, w.getWidth(), w.getLength(), 0.9);
			break;
		case 'p':
			p.generate(0);
			break;
		case 'o':
			p.init(0);
			break;
		case 'k':
			p.init(1);
			break;
		case 'l':
			p.generate(1);
			break;
		case 'n':
			p.init(2);
			break;
		case 'm':
			p.generate(2);
			break;
		case ',':
			p.init(4);
			break;
		case'.':
			p.generate(4);
			break;
		case 'j':
			// toggle normals
			t.toggleNormals();
			break;
		case 'u':
			p.init(3);
			break;
		case 'i':
			// draw me water
			p.updateParticles4(&t);
			break;
		case 'w':
			c.translateCam(0,0,1);
			break;
		case 's':
			c.translateCam(0,0,-1);
			break;
		case 'd':
			c.translateCam(1,0,0);
			break;
		case 'a':
			c.translateCam(-1,0,0);
			break;
		case 'z':
			c.translateCam(0,1,0);
			break;
		case 'x':
			c.translateCam(0,-1,0);
			break;
		case 'v':
			c.rotateCam(1, 0,1,0);
			break;
		case 'c':
			c.rotateCam(-1,0,1,0);
			break;

	}
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (wWidth, wHeight); 
	glutInitWindowPosition (0, 0);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(update);
	glutMainLoop();
}