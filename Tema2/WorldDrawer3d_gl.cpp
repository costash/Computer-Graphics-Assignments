#include "WorldDrawer3d.h"

using namespace WorldDrawer3dNamespace;

CoordinateSystem3d WorldDrawer3d::cs_basis;
std::vector<CoordinateSystem3d*> WorldDrawer3d::cs_used;

void WorldDrawer3d::idleCallbackFunction(){
	//call client function
	onIdle();
	//redisplay
	glutPostRedisplay();
}

void WorldDrawer3d::reshapeCallbackFunction(int w, int h){
	glViewport(0,0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = (float)w/(float)h;
	gluPerspective(90.0f, aspect, 0.1f, 3000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(20.0, 20.0, 20.0,0.0, 0.0, 0.0, 0.0, 1.0, 0.0);  //looking at xoy
}

void WorldDrawer3d::displayCallbackFunction(){
	//Render objects
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	cs_basis.draw(2);

	//draw objects in cs_basis
	for(unsigned int j=0;j<cs_basis.objects.size();j++){
		cs_basis.objects[j]->draw();
	}

	//draw each used coord system
	for(unsigned int i = 0; i < cs_used.size(); ++i)
	{
		//draw used coord system
		cs_used[i]->draw(1);

		//draw objects
		for(unsigned int j = 0; j < cs_used[i]->objects.size(); ++j)
		{
			cs_used[i]->objects[j]->draw();
		}
	}

	//swap buffers
	glutSwapBuffers();
}

void WorldDrawer3d::keyDownCallbackFunction(unsigned char key, int posx, int posy)
{
	if (key == KEY_SPACE)
		animation = !animation;
	keyStates[key] = true;
}

void WorldDrawer3d::keyUpCallbackFunction(unsigned char key, int posx, int posy)
{
	keyStates[key] = false;
}

void WorldDrawer3d::specialKeyDownCallbackFunction(int key, int posx, int posy)
{
	keySpecialStates[key] = true;
	//std::cerr << "Mouse (" << posx << "," << posy << ") ";
}

void WorldDrawer3d::specialKeyUpCallbackFunction(int key, int posx, int posy)
{
	keySpecialStates[key] = false;
}

WorldDrawer3d::WorldDrawer3d(int argc, char **argv, int windowWidth, int windowHeight, int windowStartX, int windowStartY, std::string windowName){
	//init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(windowStartX,windowStartY);
	glutCreateWindow(windowName.c_str());
	
	//bind funcs
	glutDisplayFunc(displayCallbackFunction);
	glutReshapeFunc(reshapeCallbackFunction);
	glutIdleFunc(idleCallbackFunction);

	//Keyboard callbacks
	glutKeyboardFunc(keyDownCallbackFunction);
	glutKeyboardUpFunc(keyUpCallbackFunction);
	glutSpecialFunc(specialKeyDownCallbackFunction);
	glutSpecialUpFunc(specialKeyUpCallbackFunction);

	glClearColor(0.4f,0.5f,1,1);

	//zbuff
	glEnable(GL_DEPTH_TEST);
}
void WorldDrawer3d::run(){
	glutMainLoop();
}
WorldDrawer3d::~WorldDrawer3d(){
}