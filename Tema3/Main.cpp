//include librarii de opengl, glut si glu
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glut32.lib")

//includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>

//glut and glew
#include "glut.h"

//ground
#include "ground.h"

//camera
#include "camera.h"



//cam
Camera camera;

//cuburi
float angle=0;

//functie afisare
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//setup view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.render();


	//ground
	glColor3f(0.5,0.5,0.5);
	draw_ground(20,16,2,2,-2);

	//rest scena
	for(int i=0;i<4;i++){
		for(int j=0;j<4;j++){
			glPushMatrix();

			if((i+j)%5==0) glColor3f( 1,0,0);
			if((i+j)%5==1) glColor3f( 0,1,0);
			if((i+j)%5==2) glColor3f( 0,0,1);
			if((i+j)%5==3) glColor3f( 1,0,1);
			if((i+j)%5==4) glColor3f( 1,1,0);
			glTranslatef((i-1.5)*3, j*3, -25);

			glRotatef(angle*(i+1)*(j+1)/(i+2+j),0,1,0);
			glutSolidCube(2);
			glPopMatrix();
		}
	}

	// Cub la punctul de interes
	glPushMatrix();


	Vector3D pos(camera.position + camera.forward * 10);
	glTranslatef(pos.x, pos.y, pos.z);
	glutSolidCube(2);
	glPopMatrix();

	//swap buffers
	glutSwapBuffers();
}

void reshape(int width, int height){
	//set viewport
	glViewport(0,0,width,height);

	//set proiectie
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,(float)width/(float)height,0.2,100);
}

void idle();

void keyboard(unsigned char ch, int x, int y){
	switch(ch){
	case 27:	//esc
		exit(0);
		break;

	case 'w':
		camera.translate_Forward(0.5);
		break;
	case 'a':
		camera.rotateFPS_OY(-0.1);
		break;
	case 's':
		camera.translate_Forward(-0.5);
		break;
	case 'r':
		camera.translate_Right(0.5);
		break;
	case 'f':
		camera.translate_Right(-0.5);
		break;
	case 't':
		camera.translate_Up(0.5);
		break;
	case 'g':
		camera.translate_Up(-0.5);
		break;
	case 'd':
		camera.rotateFPS_OY(0.1);
		break;
	case 'z':
		camera.rotateFPS_OX(0.1);
		break;
	case 'x':
		camera.rotateFPS_OX(-0.1);
		break;
	case 'v':
		camera.rotateFPS_OZ(0.1);
		break;
	case 'b':
		camera.rotateFPS_OZ(-0.1);
		break;

	case 'q':
		camera.rotateTPS_OY(-0.1,10);
		break;
	case 'e':
		camera.rotateTPS_OY(0.1,10);
		break;

	case 'n':
		camera.rotateTPS_OX(-0.1, 10);
		break;
	case 'm':
		camera.rotateTPS_OX(0.1, 10);
		break;

	case 'k':
		camera.rotateTPS_OZ(-0.1, 10);
		break;
	case 'l':
		camera.rotateTPS_OZ(0.1, 10);
		break;



	default:
		break;
	}

}


//idle
void idle(){
	angle = angle+0.01;
	if(angle >360) angle = angle-360;
	glutPostRedisplay();
}



int main(int argc, char *argv[]){

	//init glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	//init window
	glutInitWindowSize(800,600);
	glutInitWindowPosition(200,200);
	glutCreateWindow("lab transformari si camera");

	//callbacks
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);


	//z test on
	glEnable(GL_DEPTH_TEST);

	//set background
	glClearColor(0.2,0.2,0.2,1.0);

	//init camera
	camera.init();

	//loop
	glutMainLoop();

	return 0;
}