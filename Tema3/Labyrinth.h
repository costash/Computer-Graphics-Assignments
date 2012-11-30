#pragma once
#include "HeadersAndDefines.h"
#include "Point2d.h"
#include <ctime>

class Labyrinth
{
public:
	Labyrinth(int size);
	~Labyrinth();
	void init();

	void generateNewMaze();

	friend std::ostream& operator<< (std::ostream& os, const Labyrinth &p);

public:
	int size;
	int *maze;

private:
	void initMaze();
	bool isMazeClosed(const Point2d p);
	void generateMaze(int stepIndex, int *backX, int *backY, Point2d p, int visited);
};

