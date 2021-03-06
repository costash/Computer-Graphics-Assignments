#include "WorldDrawer3d.h"

CoordinateSystem3d WorldDrawer3d::cs_basis;
std::vector<CoordinateSystem3d*> WorldDrawer3d::cs_used;
bool WorldDrawer3d::mouseLeftState = false;		// Left click not pressed
bool WorldDrawer3d::mouseRightState = false;	// Right click not pressed
float WorldDrawer3d::mousePosX = 0.f;			// Mouse position X coordinate
float WorldDrawer3d::mousePosY = 0.f;			// Mouse position Y coordinate
float WorldDrawer3d::viewAngleX = 0.f;			// ViewAngle on OX
float WorldDrawer3d::viewAngleY = 0.f;			// ViewAngle on OY
float WorldDrawer3d::eyeDistance = 0.f;			// Distance from viewer

int WorldDrawer3d::mainWindow = 0;				// Main window ID

void WorldDrawer3d::idleCallbackFunction(){
	
	unsigned int diff = getTimeDifference();
	// Limit to 50 frames per second
	if (diff >= 20)
	{
		tick += diff;

		onIdle();

		//redisplay
		glutPostRedisplay();
	}
}

// Returns difference of time since last update
unsigned int WorldDrawer3d::getTimeDifference()
{
	unsigned int newTick = getTime();
	return newTick - tick;
}

// Gets current time
unsigned int WorldDrawer3d::getTime()
{
	return glutGet(GLUT_ELAPSED_TIME);
}

void WorldDrawer3d::reshapeCallbackFunction(int w, int h){
	glViewport(0,0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = (float)w/(float)h;
	gluPerspective(90.0f, aspect, 0.1f, 3000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, 30.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0);	// Looking at (0, 0, 0) from (0, 0, 30)
}

void WorldDrawer3d::displayCallbackFunction(){
	//Render objects
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Save the initial ModelView matrix before modifying ModelView matrix
	glPushMatrix();

	// Tramsform view
	glTranslatef(1.5f, 0, -eyeDistance);
	glRotatef(viewAngleY, 1, 0, 0);   // Rotate left or right
	glRotatef(viewAngleX, 0, 1, 0);   // Rotate up or down

	// Draw cs_basis coord system
	cs_basis.draw(2);

	// Draw objects in cs_basis
	for(unsigned int j=0;j<cs_basis.objects.size();j++){
		cs_basis.objects[j]->draw();
	}

	// Draw each used coord system
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

	// Restore the ModelView matrix after drawing objects
	glPopMatrix();


	// Draw text here
	drawScore(-25, 22, 3, Color(0.961f, 0.871f, 0.702f));
	drawWin(-25, 20, 3, Color(0.961f, 0.871f, 0.702f));

	//swap buffers
	glutSwapBuffers();
}

// Buffer keys on press
void WorldDrawer3d::keyDownCallbackFunction(unsigned char key, int posx, int posy)
{
	if (key == KEY_SPACE)
		animation = !animation;
	keyStates[key] = true;
}

// Unbuffer keys on release
void WorldDrawer3d::keyUpCallbackFunction(unsigned char key, int posx, int posy)
{
	keyStates[key] = false;
}

// Buffer special keys on press
void WorldDrawer3d::specialKeyDownCallbackFunction(int key, int posx, int posy)
{
	keySpecialStates[key] = true;
}

// Unbuffer special keys on release
void WorldDrawer3d::specialKeyUpCallbackFunction(int key, int posx, int posy)
{
	keySpecialStates[key] = false;
}

WorldDrawer3d::WorldDrawer3d(int argc, char **argv, int windowWidth, int windowHeight, int windowStartX, int windowStartY, std::string windowName){
	//init
	glutInit(&argc, argv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);	// This will not close the program for multiWindowClose

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GLUT_MULTISAMPLE);							// Enable multisampling
	glutInitWindowSize(windowWidth,windowHeight);		// Window size
	glutInitWindowPosition(windowStartX,windowStartY);	// Window position
	mainWindow = glutCreateWindow(windowName.c_str());

	// Display, reshape and idle callbacks
	glutDisplayFunc(displayCallbackFunction);
	glutReshapeFunc(reshapeCallbackFunction);
	glutIdleFunc(idleCallbackFunction);

	// Keyboard callbacks
	glutKeyboardFunc(keyDownCallbackFunction);
	glutKeyboardUpFunc(keyUpCallbackFunction);
	glutSpecialFunc(specialKeyDownCallbackFunction);
	glutSpecialUpFunc(specialKeyUpCallbackFunction);

	// Mouse callbacks
	glutMouseFunc(mouseCallbackFunction);
	glutMotionFunc(mouseMotionCallbackFunction);
	glutMouseWheelFunc(mouseWheelCallbackFunction);

	// Background color
	glClearColor(0.4f,0.5f,1,1);

	//zbuff
	glEnable(GL_DEPTH_TEST);
}
void WorldDrawer3d::run(){
	glutMainLoop();
}
WorldDrawer3d::~WorldDrawer3d(){
}