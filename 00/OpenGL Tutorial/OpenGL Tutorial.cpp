// OpenGL Tutorial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL/freeglut.h>

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Empty Window");

	glutMainLoop();
}

