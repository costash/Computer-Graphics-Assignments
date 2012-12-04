#pragma once
#include "HeadersAndDefines.h"
#include "Point2d.h"
#include <ctime>
#include "Vector3D.h"
#include <vector>

class Labyrinth
{
public:
	Labyrinth(int size);
	~Labyrinth();
	void init();			// Init Labyrinth with a new maze of current size

	void generateNewMaze();	// Generates a new Maze with current size
	void drawLabyrinth();	// Draws Labyrinth on scene

	Point2d generateRandomPosition();	// Generates a random position on labyrinth not on wall
	void setPortal(const Point2d p);
	void setPlayerPos(const Point2d p);

	bool isColision(const Point2d cell, const Vector3D pos);
	bool isChangingCell(const Point2d cell, const Vector3D pos);
	std::vector<Point2d> getNeighbours(const Point2d cell);
	bool updateCell(std::vector<Point2d> cells, const Vector3D pos);

	friend std::ostream& operator<< (std::ostream& os, const Labyrinth &l);

public:
	int size;				// Size of maze. Actual size is size * 2 + 1
	int *maze;				// Matrix for maze
	Point2d portalPos;		// Position of the portal
	Point2d playerPos;		// Position of the player

private:
	void initMaze();
	bool isMazeClosed(const Point2d p);
	void generateMaze(int stepIndex, int *backX, int *backY, Point2d p, int visited);
	bool isOnWall(const Point2d p);	// Wether a point is wall or not
};

