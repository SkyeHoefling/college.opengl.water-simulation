#include "camera.h"
#include <GL/glut.h>

/*camera::camera(void)
{
	view.setW(1);
	view.setX(1);
	view.setY(1);
	view.setZ(1);
	angle = 0.0f;
	position.setX(0);
	position.setY(0);
	position.setZ(5);
}*/
//http://www.flipcode.com/archives/OpenGL_Camera.shtml
camera::camera(float x, float y, float z){
	// memset?
	t[0] = t[5] = t[15] = 1.0f;
	t[10] = -1.0f;
	t[12] = x; t[13] = y; t[14] = z;
	r = &t[0];
	u = &t[8];
	p = &t[12];
}
camera::~camera(){}
void camera::setView(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	float viewM[16] = {//Remove the three - for non-inverted z-axis
						  t[0], t[4], -t[8], 0,
						  t[1], t[5], -t[9], 0,
						  t[2], t[6], -t[10], 0,

						  -(t[0]*t[12] +
						  t[1]*t[13] +
						  t[2]*t[14]),

						  -(t[4]*t[12] +
						  t[5]*t[13] +
						  t[6]*t[14]),

						  //add a - like above for non-inverted z-axis
						  (t[8]*t[12] +
						  t[9]*t[13] +
						  t[10]*t[14]), 1};
	glLoadMatrixf(viewM);
}
void camera::rotateCam(float angle, float x, float y, float z){
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(t);
	glRotatef(angle, x,y,z);
	glGetFloatv(GL_MODELVIEW_MATRIX, t);
	glPopMatrix();
	setView();
}
void camera::rotateWorld(float angle, float x, float y, float z){
	float dx=x*t[0] + y*t[1] + z*t[2];
	float dy=x*t[4] + y*t[5] + z*t[6];
	float dz=x*t[8] + y*t[9] + z*t[10];
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf(t);
	glRotatef(angle, dx,dy,dz);
	glGetFloatv(GL_MODELVIEW_MATRIX, t);
	glPopMatrix();
}

void camera::translateCam(float x, float y, float z, float d){
	float dx=x*t[0] + y*t[4] + z*t[8];
	float dy=x*t[1] + y*t[5] + z*t[9];
	float dz=x*t[2] + y*t[6] + z*t[10];
	t[12] += dx * d;
	t[13] += dy * d;
	t[14] += dz * d;
	setView();
}

void camera::translateWorld(float x, float y, float z, float d){
	t[12] += x * d;
	t[13] += y * d;
	t[14] += z * d;
}























/*void camera::init(){
	init(800,600);
}
void camera::init(int w, int h){
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 300.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt (0.0, 0.0, 5.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.0);
}
void camera::rotate(float theta, float x, float y, float z){

}
void camera::translate(float x, float y, float z){
	position.addX(x);position.addY(y);position.addZ(z);
	update();
}
void camera::update(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.getX(), position.getY(), position.getZ(),
		view.getX(), view.getY(), view.getZ(), 0,1, 0);
}
void camera::translate(float x, float y, float z){
	glTranslatef(x,y,z);
	position.addX(x);
	position.addY(y);
	position.addZ(z);
	/*view.setX(view.getX() + x);
	view.setY(view.getY() + y);
	view.setZ(view.getZ() + z);
	//update();
}
void camera::rotate(float theta, float x, float y, float z){
	angle += theta;
	quaternion r, v, f;
	r.setX(x * sin(angle / 2));
	r.setY(y * sin(angle / 2));
	r.setZ(z * sin(angle / 2));
	r.setW(cos(angle / 2));

	v = view;
	v.setW(0);

	f = r * v * r.conjugate();

	view.setX(f.getX());
	view.setY(f.getY());
	view.setZ(f.getZ());

	// calc up
	up = calcUp(
	update();
	//glMatrixMode(GL_PROJECTION);
	////glLoadIdentity();
	//glMultMatrixf(f.normalize().toMatrix(true));
}*/


