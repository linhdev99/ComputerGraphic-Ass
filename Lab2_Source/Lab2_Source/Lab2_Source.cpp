#include <math.h>
#include <iostream>
#include "supportClass.h"
#include "Mesh.h"

#define DEG2RAD (3.14159 / 180.0)

using namespace std;

int		screenWidth = 600;
int		screenHeight= 300;

Mesh	tetrahedron;
Mesh	cube;
Mesh	cylinder;
Mesh	cylinderEmpty;
Mesh	shape1;
Mesh	shape2;
Mesh	shape3;
Mesh	shape4;
Mesh	shape5;

int		nChoice = 1;

float radius = 4.5;
float camera[] = { radius, 2, radius - 2 };
GLfloat angle = 0.0;


float* vectorNewell(float iVector[10][3], int n)
{
	float vectorResult[] = { 0,0,0 };
	for (int i = 0; i < n; i++)
	{
		vectorResult[0] += (iVector[i][1] - iVector[(i + 1) % n][1]) * (iVector[i][2] + iVector[(i + 1) % n][2]);
		vectorResult[1] += (iVector[i][2] - iVector[(i + 1) % n][2]) * (iVector[i][0] + iVector[(i + 1) % n][0]);
		vectorResult[2] += (iVector[i][0] - iVector[(i + 1) % n][0]) * (iVector[i][1] + iVector[(i + 1) % n][1]);
	}
	return vectorResult;
}

void rotateCamera(int value)
{
	angle += (GLfloat)value;
	if (angle > 360) angle = angle - 360.0f;
	camera[0] = radius * cos(DEG2RAD * angle);
	camera[2] = radius * sin(DEG2RAD * angle);
	glutTimerFunc(10, rotateCamera, 1);
	glutPostRedisplay();
}

void drawAxis()
{
	// Truc toa do Oxyz
	glColor3f(0, 0, 1);
	glBegin(GL_LINES);
		glColor3f(0, 0, 1); //Ox, blue
		glVertex3f(0, 0, 0);
		glVertex3f(10, 0, 0);

		glColor3f(0, 1, 0); //Oy, green 
		glVertex3f(0, 0, 0);
		glVertex3f(0, 10, 0);

		glColor3f(1, 0, 0); //Oz, red
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 10);
	glEnd();
}
void myDisplay()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camera[0], camera[1], camera[2], 0, 0, 0, 0, 1, 0);
	/*
	{eye_x, eye_y, eye_z} --> Toạ độ điểm của Camera
	{center_z, center_y,n center_z} --> Điểm Camera hướng tới
	{up_x, up_y, up_z} --> Chọn trục hướng lên, thường trục Y hướng lên trên
	*/

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glViewport(0, 0, screenWidth/2, screenHeight);
	
	drawAxis();

	glColor3f(0, 0, 0);
	if (nChoice == 1)
		tetrahedron.DrawWireframe();
	else if (nChoice == 2)
		cube.DrawWireframe();
	else if (nChoice == 3)
		cylinder.DrawWireframe();
	else if (nChoice == 4)
		cylinderEmpty.DrawWireframe();
	else if (nChoice == 5)
		shape1.DrawWireframe();
	else if (nChoice == 6)
		shape2.DrawWireframe();
	else if (nChoice == 7)
		shape3.DrawWireframe();

	glViewport(screenWidth/2, 0, screenWidth/2, screenHeight);

	drawAxis();
	if(nChoice == 1)
		tetrahedron.DrawColor();
	else if(nChoice == 2)
		cube.DrawColor();
	else if (nChoice == 3)
		cylinder.DrawColor();
	else if (nChoice == 4)
		cylinderEmpty.DrawColor();
	else if (nChoice == 5)
		shape1.DrawColor();
	else if (nChoice == 6)
		shape2.DrawColor();
	else if (nChoice == 7)
		shape3.DrawColor();

	/*glColor3f(0, 0, 1);
	RealRect temp;
	temp.set(2,-2,2,-2);
	temp.draw();*/

	glFlush();
    glutSwapBuffers();
}

void myInit()
{
	float	fHalfSize = 4;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-fHalfSize, fHalfSize, -fHalfSize, fHalfSize, -1000, 1000);
}

int main(int argc, char* argv[])
{
	/*float p[][3] = {
		{0,2,0},
		{1,0,0},
		{0,0,3}
	};
	float * result = vectorNewell(p, 3);
	cout << result[0] << ";" << result[1] << ";" << result[2] << endl;
	float q[][3] = {
		{0,0,0},
		{1,0,0},
		{0,0,1},
		{1,5,1}
	};
	result = vectorNewell(q, 4);
	cout << result[0] << ";" << result[1] << ";" << result[2] << endl*/;
	//return 0;
	cout << "1. Tetrahedron" << endl;
	cout << "2. Cube" << endl;
	cout << "3. Hinh tru" << endl;
	cout << "4. Hinh tru rong" << endl;
	cout << "5. Shape1" << endl;
	cout << "6. Shape2" << endl;
	cout << "7. Shape3" << endl;
	cout << "8. Shape4" << endl;
	cout << "Input the choice: " << endl;
	cin  >> nChoice;


	glutInit(&argc, (char**)argv); //initialize the tool kit
	glutInitDisplayMode(GLUT_DOUBLE |GLUT_RGB | GLUT_DEPTH);//set the display mode
	glutInitWindowSize(screenWidth, screenHeight); //set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Lab 2"); // open the screen window

	tetrahedron.CreateTetrahedron();
	cube.CreateCube(1);
	cylinder.CreateCylinder(5, 4, 2);
	cylinderEmpty.CreateCylinderEmpty(36, 4, 1, 0.5);
	shape1.CreateShape1(3, 1, 0.3, 0.8);
	shape2.CreateShape2(5, 0.5, 1.2, 0.25, 0.7);
	shape3.CreateShape3(6, 4, 1, 1, 0.5);

	myInit();
    glutDisplayFunc(myDisplay);
	glutTimerFunc(100, rotateCamera, 1);
	glutMainLoop();
	return 0;
}