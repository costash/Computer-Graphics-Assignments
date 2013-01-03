#include "HeadersAndDefines.h"
#include "WorldDrawer.h"
#include "camera.h"

#include "Point2d.h"
#include "Mesh.h"
#include "CustomObject3D.h"
#include "Cube.h"
#include "Light.h"

bool WorldDrawer::animation = true;
bool WorldDrawer::keyStates[256];
bool WorldDrawer::keySpecialStates[256];

unsigned int WorldDrawer::tick = 0;
Camera WorldDrawer::camera(MODE_TPS);

CustomObject3D *WorldDrawer::aircraft;
Object3D *WorldDrawer::gameBox;
Mesh *WorldDrawer::aircraftMesh;					// Mesh for aircraft
Mesh *WorldDrawer::asteroidMesh;					// Mesh for asteroid
//CustomObject3D *WorldDrawer::asteroids;				// Asteroids objects
//std::vector<CustomObject3D *> WorldDrawer::asteroids;	// Asteroid objects
std::vector<Asteroid *> WorldDrawer::asteroids;		// Asteroid objects
// Omnidirectional light
Light *WorldDrawer::light_o;

//add
void WorldDrawer::init(){

	// Initialize vector arrays
	Vector3D::arr = new float[3];
	Vector4D::arr = new float[4];

	aircraftMesh = new Mesh();
	aircraftMesh->Init("m1365.off");

	asteroidMesh = new Mesh();
	//asteroidMesh->Init("asteroid.off");
	asteroidMesh->Init("asteroid_small.off");

	std::cerr << "Aircraft radius " << aircraftMesh->radius << " center: " << aircraftMesh->center << "\n";
	std::cerr << "Asteroid radius " << asteroidMesh->radius << " center: " << asteroidMesh->center << "\n";

	aircraft = new CustomObject3D(aircraftMesh);
	aircraft->SetScale(new Vector3D(15.f, 15.f, 15.f));
	aircraft->SetColor(new Vector3D(1.f, 0.f, 0.f));
	aircraft->SetRotation(new Vector3D(-90.f, 0.f, 180.f));
	//aircraft->SetPosition(new Vector3D(10.f, 0.f, -30.f));

	// Create display list for aircraft
	glNewList(AIRCRAFT, GL_COMPILE);
	aircraft->Draw();
	glEndList();

	for (int i = 0; i < NUM_ASTEROIDS; ++i)
	{
		if (i == 0)
			asteroids.push_back(new Asteroid(asteroidMesh, ASTEROID, true));
		else
			asteroids.push_back(new Asteroid(asteroidMesh, ASTEROID, false));
		
		float rand_scale = genRandomFloat(0.5f, 2.f);
		asteroids[i]->SetScale(new Vector3D(rand_scale, rand_scale, rand_scale));
		asteroids[i]->SetColor(new Vector3D(0.5f, 0.5f, 0.5f));

		// Move
		Vector3D randPos = WorldDrawer::genRandomPosition(-PLANE_SIZE/2, PLANE_SIZE/2, -PLANE_SIZE/2, PLANE_SIZE/2);
		asteroids[i]->SetPosition(new Vector3D(randPos));
		asteroids[i]->moveStep = genRandomFloat(0.3f, 0.9f);

		asteroids[i]->angleStep = Vector3D(genRandomFloat(0.5f, 1.f), genRandomFloat(0.5f, 1.f), genRandomFloat(0.5f, 1.f));
	}

	/*glNewList(ASTEROID, GL_COMPILE);
	for (int i = 0; i < NUM_ASTEROIDS; ++i)
		asteroids[i]->Draw();
	glEndList();*/
	/*for (unsigned int i = 0; i < asteroids.size(); ++i)
	{
		glNewList(ASTEROID + i, GL_COMPILE);
		asteroids[i]->Draw();
		glEndList();
	}*/

	gameBox = new Object3D(GlutCube);
	gameBox->Wireframe = true;
	gameBox->SetColor(new Vector3D(0.5f, 0.5f, 0.5f));
	gameBox->SetScale(new Vector3D(PLANE_SIZE, PLANE_SIZE, PLANE_SIZE));

	// initializam o noua lumina omnidirectionala
	light_o = new Light();
	// setam pozitia
	light_o->SetPosition(new Vector3D(-2, 0, 3));

	// Set up camera
	camera.init();

	if (camera.mode == MODE_TPS)
	{
		camera.position = Vector3D(0, 0, distanceToTPSTarget);
		camera.rotateTPS_OX(float(M_PI_4 / 2), distanceToTPSTarget);
	}
	else if (camera.mode == MODE_TOP)
	{
		camera.position = Vector3D(0, 0, distanceToTop);
		camera.rotateTPS_OX(float(M_PI), distanceToTop);
	}
	tick = glutGet(GLUT_ELAPSED_TIME);
}

// Is called in glut main loop by the system on idle
void WorldDrawer::onIdle(){	//per frame
	keyOperations();			// Operations for buffered keys
	mouseRotations();

	if(animation){
		// Do nothing here
		angle = angle+1;

		if(angle > 360) angle = angle-360;

		for (unsigned int i = 0; i < asteroids.size(); ++i)
		{
			Vector3D pos = asteroids[i]->GetPosition();
			pos.x += asteroids[i]->moveStep;

			if (pos.x >= PLANE_SIZE / 2)
			{
				pos = genRandomPosition(-PLANE_SIZE / 2, PLANE_SIZE / 2, -PLANE_SIZE / 2, PLANE_SIZE / 2);
			}
			asteroids[i]->SetPosition(new Vector3D(pos));
			
			Vector3D rot = asteroids[i]->GetRotation();
			rot += asteroids[i]->angleStep;
			asteroids[i]->SetRotation(new Vector3D(rot));
		}

	}
}

// All key events are processed here
void WorldDrawer::keyOperations()
{
	if (keyStates[KEY_ESC])			// On Escape, program exits
		glutExit();

	float rotateStep = 0.04f;
	float moveStep = 0.25f;

	if (camera.mode == MODE_FPS)
	{
		if (keySpecialStates[KEY_UP])			// Rotate FPS up
		{
			camera.rotateFPS_OX(-rotateStep);
		}
		if (keySpecialStates[KEY_DOWN])			// Rotate FPS down
		{
			camera.rotateFPS_OX(rotateStep);
		}
		if (keySpecialStates[KEY_LEFT])			// Rotate FPS left
		{
			camera.rotateFPS_OY(-rotateStep);
		}
		if (keySpecialStates[KEY_RIGHT])		// Rotate FPS right
		{
			camera.rotateFPS_OY(rotateStep);
		}
	}
	else if (camera.mode == MODE_TPS)
	{
		if (keySpecialStates[KEY_UP])					// Rotate TPS up
		{
			camera.rotateTPS_OX(-rotateStep, distanceToTPSTarget);
		}
		if (keySpecialStates[KEY_DOWN])					// Rotate TPS down
		{
			camera.rotateTPS_OX(rotateStep, distanceToTPSTarget);
		}
		if (keySpecialStates[KEY_LEFT])					// Rotate TPS left
		{
			camera.rotateTPS_OY(-rotateStep, distanceToTPSTarget);
		}
		if (keySpecialStates[KEY_RIGHT])				// Rotate TPS right
		{
			camera.rotateTPS_OY(rotateStep, distanceToTPSTarget);
		}
	}
	else if (camera.mode == MODE_TOP)
	{
		if (keySpecialStates[KEY_LEFT])					// Rotate left
		{
			camera.rotateTPS_OY(-rotateStep, distanceToTop);
		}
		if (keySpecialStates[KEY_RIGHT])				// Rotate right
		{
			camera.rotateTPS_OY(rotateStep, distanceToTop);
		}
	}

	float eyeDistanceStep = 1.f;

	// Zoom closer
	if (keyStates['['])
	{
		eyeDistance -= eyeDistanceStep;		// Move closer to the viewer
		if (camera.mode == MODE_TPS && distanceToTPSTarget - zoomSensivity > 0)
		{
			distanceToTPSTarget -= zoomSensivity;
			camera.translate_ForwardFree(zoomSensivity);
		}
		else if (camera.mode == MODE_TOP && distanceToTop - zoomSensivity * 20 > 0)
		{
			distanceToTop -= zoomSensivity * 20;
			camera.translate_ForwardFree(zoomSensivity * 20);
		}
	}
	if (keyStates[']'])
	{
		eyeDistance += eyeDistanceStep;		// Move farther from the viewer
		if (camera.mode == MODE_TPS)
		{
			distanceToTPSTarget += zoomSensivity;
			camera.translate_ForwardFree(-zoomSensivity);
		}
		else if (camera.mode == MODE_TOP)
		{
			distanceToTop += zoomSensivity * 20;
			camera.translate_ForwardFree(-zoomSensivity * 20);
		}
	}

	if (keyStates['w'])						// Move forward
	{
		camera.translate_Forward(moveStep);

		// Check colision
	}
	if (keyStates['s'])						// Move backwards
	{
		camera.translate_Forward(-moveStep);

		// Check colision
	}
	if (keyStates['a'])						// Move left
	{
		camera.translate_Right(-moveStep);

		// Check colision
	}
	if (keyStates['d'])						// Move right
	{
		camera.translate_Right(moveStep);

		// Check colision
	}
}

// Callback function for mouse actions
void WorldDrawer::mouseCallbackFunction(int button, int state, int x, int y)
{
	mousePosX = float (x);
	mousePosY = float (y);
	if (button == MOUSE_LEFT)			// Buffer left clicks
	{
		if (state == GLUT_DOWN)
			mouseLeftState = true;
		else if (state == GLUT_UP)
			mouseLeftState = false;
	}
	else if (button == MOUSE_RIGHT)		// Buffer right clicks
	{
		if (state == GLUT_DOWN)
			mouseRightState = true;
		else if (state == GLUT_UP)
			mouseRightState = false;
	}
}

// Callback for mouse movement
void WorldDrawer::mouseMotionCallbackFunction(int x, int y)
{
	float eyeDistanceStep = 0.2f;
	if (mouseLeftState == true)			// Make rotation if left is clicked and moved mouse
	{
		viewAngleX += (y - mousePosY) / mouseSensivity;
		viewAngleY += (x - mousePosX) / mouseSensivity;
		mousePosX = float(x);
		mousePosY = float(y);
	}
	if (mouseRightState == true)		// Make zoom in/out if right is clicked and moved
	{
		eyeDistance -= (y - mousePosY) * eyeDistanceStep;
		mousePosY = float (y);
	}
}

// Execute mouse rotations
void WorldDrawer::mouseRotations()
{
	if (camera.mode == MODE_FPS)
	{
		camera.rotateFPS_OX(viewAngleX);
		camera.rotateFPS_OY(viewAngleY);
		viewAngleX = viewAngleY = 0.f;
	}
	else if (camera.mode == MODE_TPS)
	{
		camera.rotateTPS_OX(viewAngleX, distanceToTPSTarget);
		camera.rotateTPS_OY(viewAngleY, distanceToTPSTarget);
		viewAngleX = viewAngleY = 0.f;
	}
}

// Callback for mouse scroll (wheel)
void WorldDrawer::mouseWheelCallbackFunction(int wheel, int direction, int x, int y)
{
	float eyeDistanceStep = 2.f;
	eyeDistance += eyeDistanceStep * (-direction);
	if (camera.mode == MODE_TPS && distanceToTPSTarget + zoomSensivity * 20 * (-direction) > 0)
	{
		distanceToTPSTarget += zoomSensivity * 20 * (-direction);
		camera.translate_ForwardFree(-zoomSensivity * 20 * (-direction));
	}
	else if (camera.mode == MODE_TOP && distanceToTop + zoomSensivity * 50 * (-direction) > 0)
	{
		distanceToTop += zoomSensivity * 50 * (-direction);
		camera.translate_ForwardFree(-zoomSensivity * 50 * (-direction));
	}
}

// Switches the camera mode
void WorldDrawer::switchCameraMode(int mode)
{
	if (camera.mode == MODE_FPS && mode == MODE_TPS)
	{
		camera.rotateFPS_OX(float(ANGLE_LIMIT * 2));
		camera.rotateFPS_OX(float(-ANGLE_LIMIT + camera.angleTpsX));
		camera.translate_ForwardFree(-distanceToTPSTarget);
	}
	else if (camera.mode == MODE_FPS && mode == MODE_TOP)
	{
		camera.rotateFPS_OX(float(ANGLE_LIMIT * 2));
		camera.translate_ForwardFree(-distanceToTop);
	}
	else if (camera.mode == MODE_TPS && mode == MODE_FPS)
	{
		camera.angleTpsX = camera.getAngleX();
		camera.translate_ForwardFree(distanceToTPSTarget);
		camera.rotateFPS_OX(float(ANGLE_LIMIT * 2));
		camera.rotateFPS_OX(float(-ANGLE_LIMIT));
	}
	else if (camera.mode == MODE_TPS && mode == MODE_TOP)
	{
		camera.angleTpsX = camera.getAngleX();
		camera.translate_ForwardFree(distanceToTPSTarget);
		camera.rotateFPS_OX(float(ANGLE_LIMIT * 2));
		camera.translate_ForwardFree(-distanceToTop);
	}
	else if (camera.mode == MODE_TOP && mode == MODE_FPS)
	{
		camera.translate_ForwardFree(distanceToTop);
		camera.rotateFPS_OX(float(-ANGLE_LIMIT));
	}
	else if (camera.mode == MODE_TOP && mode == MODE_TPS)
	{
		camera.translate_ForwardFree(distanceToTop);
		camera.rotateFPS_OX(float(-ANGLE_LIMIT + camera.angleTpsX));
		camera.translate_ForwardFree(-distanceToTPSTarget);
	}
	camera.mode = mode;
}

// Gets the position of the player in world space
Vector3D WorldDrawer::getPlayerPosition()
{
	if (camera.mode == MODE_FPS)
		return camera.position;
	else
	{
		int mode = camera.mode;
		switchCameraMode(MODE_FPS);
		Vector3D temp(camera.position);
		switchCameraMode(mode);
		return temp;
	}
}

// Random helper
float WorldDrawer::genRandomFloat(float min, float max)
{
	return ((float(rand()) / float(RAND_MAX)) * (max - min)) + min;
}

// Random Asteroid position
Vector3D WorldDrawer::genRandomPosition(float minY, float maxY, float minZ, float maxZ)
{
	float x = genRandomFloat(-PLANE_SIZE /2, 0.f);
	float y = genRandomFloat(minY, maxY);
	float z = genRandomFloat(minZ, maxZ);
	return Vector3D(-PLANE_SIZE /2, y, z);
}

void WorldDrawer::drawAxis()
{
	float size = 100;

	glLineWidth(5);

	glBegin(GL_LINES);
	// Draw X
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(size, 0, 0);

	// Draw Y
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, size, 0);

	// Draw Z
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, size);
	glEnd();
}

int main(int argc, char *argv[]){
	srand((unsigned int)time(0));

	WorldDrawer wd(argc, argv, 800, 600, 200, 200, std::string("Tema 4: SpaceEscape 2012"));
	wd.init();
	wd.run();

	return 0;
}