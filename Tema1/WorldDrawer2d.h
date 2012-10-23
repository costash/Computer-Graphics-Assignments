#pragma once
#include "HeadersAndDefines.h"
#include "Support2d.h"
#include "Ball.h"


//-----------------------------------------------------------------------------------------------------
//	WorldDrawer2d
//	ca un obiect sa fie desenat trebuie sa fie atasat ori la cs_basis ori la un sistem de coordonate
//	din lista cs_used.
//-----------------------------------------------------------------------------------------------------
class WorldDrawer2d{
	public:
		//implemented in worldDrawer2d_gl .. not for lab1
		WorldDrawer2d(int argc, char **argv, int windowWidth, int windowHeight, int windowStartX, int windowStartY, std::string windowName);
		~WorldDrawer2d();
		static void run();	
		static void displayCallbackFunction();
		static void reshapeCallbackFunction(int width, int height);
		static void idleCallbackFunction();
		static void keyboardCallbackFunction(unsigned char key, int x, int y);


		//implemented in worldDrawer2d_logic
		static void init();
		static void onIdle();
		static void onKey(unsigned char key);

	private:
		//helpers for the game implemented in main
		static void initBall();
		static void initGoalKeepers();
		static void initBoard();
		static void initTeams();
		static void moveBallToRandomPlayer(Ball *ball);
		static void moveBallRandomAngle(Ball *ball);
		static bool isCircleOnBoard(Circle2d *ball);
		static bool isBallPlayerColision();
		static bool isBallPlayerColision(Point2d point);
		static Point2d wallColisionDirection();
		static Point2d getRandomPoint(float lowx, float highx, float lowy, float highy);

		static bool isWallColision();
		static void rotateBallWithPlayer(float radius);

	public:
		static bool animation;
		static CoordinateSystem2d cs_basis;
		static std::vector<CoordinateSystem2d*> cs_used;
};