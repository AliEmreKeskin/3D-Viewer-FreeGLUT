// OpenGL Tutorial.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <GL/freeglut.h>
#include <windows.h>
#include <atlstr.h>

//cisim hareketi için değişkenler
float WorldAngle_x = 0.0f;
float WorldAngle_y = 0.0f;

float deltaWorldAngle_x = 0.0f;
float deltaWorldAngle_y = 0.0f;

float xOrigin = 0;
float yOrigin = 0;

//görsel için değişkenler
int width, height;
long size;
BYTE* resim;

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(0, 0, 1000, 0, 0, 0, 0, 1, 0);

	WorldAngle_x += deltaWorldAngle_x;
	WorldAngle_y += deltaWorldAngle_y;
	glRotatef(WorldAngle_x, 1, 0, 0);
	glRotatef(WorldAngle_y, 0, 1, 0);

	glBegin(GL_POINTS);
	float red;
	float green;
	float blue;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			//RGB
			blue = resim[y * width * 3 + x * 3];
			green = resim[y * width * 3 + x * 3 + 1];
			red = resim[y * width * 3 + x * 3 + 2];
			glColor3f(red / 255.0, green / 255.0, blue / 255.0);

			//Coordinates
			glVertex3f(x - width / 2, y - height / 2, 0);
		}
	}
	glEnd();

	glutSwapBuffers();
}

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

void PressKey(int key, int x, int y) {
	int mod = glutGetModifiers();
	switch (key) {
	case GLUT_KEY_LEFT:	if (mod == GLUT_ACTIVE_CTRL) { deltaWorldAngle_y = 0.1f; }break;
	case GLUT_KEY_RIGHT:if (mod == GLUT_ACTIVE_CTRL) { deltaWorldAngle_y = -0.1f; }break;
	case GLUT_KEY_UP:	if (mod == GLUT_ACTIVE_CTRL) { deltaWorldAngle_x = 0.1f; }break;
	case GLUT_KEY_DOWN:	if (mod == GLUT_ACTIVE_CTRL) { deltaWorldAngle_x = -0.1f; }break;
	}
}

void ReleaseKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
	case GLUT_KEY_RIGHT:deltaWorldAngle_y = 0.0f; break;
	case GLUT_KEY_UP:
	case GLUT_KEY_DOWN:	deltaWorldAngle_x = 0.0f; break;
	}
}

void MouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			xOrigin = x;
			yOrigin = y;
		}
	}
}

void MouseMove(int x, int y) {
	WorldAngle_y += (x - xOrigin)*0.01f;
	WorldAngle_x += (y - yOrigin)*0.01f;
}

BYTE* LoadBMP(int* width, int* height, long* size, LPCTSTR bmpfile)
{
	// declare bitmap structures
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;
	// value to be used in ReadFile funcs
	DWORD bytesread;
	// open file to read from
	HANDLE file = CreateFile(bmpfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (NULL == file)
		return NULL; // coudn't open file

					 // read file header
	if (ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	//read bitmap info
	if (ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	// check if file is actually a bmp
	if (bmpheader.bfType != 'MB') {
		CloseHandle(file);
		return NULL;
	}
	// get image measurements
	*width = bmpinfo.biWidth;
	*height = abs(bmpinfo.biHeight);

	// check if bmp is uncompressed
	if (bmpinfo.biCompression != BI_RGB) {
		CloseHandle(file);
		return NULL;
	}
	// check if we have 24 bit bmp
	if (bmpinfo.biBitCount != 24) {
		CloseHandle(file);
		return NULL;
	}

	// create buffer to hold the data
	*size = bmpheader.bfSize - bmpheader.bfOffBits;
	BYTE* Buffer = new BYTE[*size];
	// move file pointer to start of bitmap data
	SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
	// read bmp data
	if (ReadFile(file, Buffer, *size, &bytesread, NULL) == false) {
		delete[] Buffer;
		CloseHandle(file);
		return NULL;
	}
	// everything successful here: close file and return buffer
	CloseHandle(file);

	return Buffer;
}//LOADPMB

void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Empty Window");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutIdleFunc(RenderScene);
	glutSpecialFunc(PressKey);
	glutSpecialUpFunc(ReleaseKey);
	glutMouseFunc(MouseButton);
	glutMotionFunc(MouseMove);

	CString str = "resim.bmp";
	LPCTSTR input;
	input = (LPCTSTR)str;
	resim = LoadBMP(&width, &height, &size, input);

	glutMainLoop();
}