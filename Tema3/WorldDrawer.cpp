#include "WorldDrawer.h"
#include "ground.h"

bool WorldDrawer::mouseLeftState = false;		// Left click not pressed
bool WorldDrawer::mouseRightState = false;	// Right click not pressed
float WorldDrawer::mousePosX = 0.f;			// Mouse position X coordinate
float WorldDrawer::mousePosY = 0.f;			// Mouse position Y coordinate
float WorldDrawer::viewAngleX = 0.f;			// ViewAngle on OX
float WorldDrawer::viewAngleY = 0.f;			// ViewAngle on OY
float WorldDrawer::eyeDistance = 0.f;			// Distance from viewer

int WorldDrawer::mainWindow = 0;				// Main window ID
float WorldDrawer::angle = 0;
//Camera WorldDrawer::camera;

WorldDrawer::WorldDrawer
	(int argc, char **argv, int windowWidth, int windowHeight,
	int windowStartX, int windowStartY, std::string windowName)
{
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
	glClearColor(0.2,0.2,0.2,1.0);

	//zbuff
	glEnable(GL_DEPTH_TEST);
}


WorldDrawer::~WorldDrawer()
{
}

void WorldDrawer::idleCallbackFunction(){
	
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
unsigned int WorldDrawer::getTimeDifference()
{
	unsigned int newTick = getTime();
	return newTick - tick;
}

// Gets current time
unsigned int WorldDrawer::getTime()
{
	return glutGet(GLUT_ELAPSED_TIME);
}

void WorldDrawer::reshapeCallbackFunction(int w, int h){
	glViewport(0,0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspect = (float)w/(float)h;
	gluPerspective(45.0f, aspect, 0.2f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//gluLookAt(0.0, 0.0, 30.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0);	// Looking at (0, 0, 0) from (0, 0, 30)
}

void WorldDrawer::displayCallbackFunction(){
	//Render objects
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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

// Buffer keys on press
void WorldDrawer::keyDownCallbackFunction(unsigned char key, int posx, int posy)
{
	if (key == KEY_SPACE)
		animation = !animation;
	keyStates[key] = true;
}

// Unbuffer keys on release
void WorldDrawer::keyUpCallbackFunction(unsigned char key, int posx, int posy)
{
	keyStates[key] = false;
}

// Buffer special keys on press
void WorldDrawer::specialKeyDownCallbackFunction(int key, int posx, int posy)
{
	keySpecialStates[key] = true;
}

// Unbuffer special keys on release
void WorldDrawer::specialKeyUpCallbackFunction(int key, int posx, int posy)
{
	keySpecialStates[key] = false;
}

void WorldDrawer::run(){
	glutMainLoop();
}