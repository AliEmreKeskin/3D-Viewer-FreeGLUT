// OpenGL Tutorial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL/freeglut.h>

void ChangeSize(int w, int h) {
	if (h == 0) {
		h = 1;
	}
	float ratio = 1.0*w / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45, ratio, 1, 10000);
	glMatrixMode(GL_MODELVIEW);
}

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	glBegin(GL_TRIANGLES);
	glVertex3f(-1, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glColor3f(1, 0, 0);
	glEnd();

	glutSwapBuffers();
}

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Empty Window");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);


	glutMainLoop();
}