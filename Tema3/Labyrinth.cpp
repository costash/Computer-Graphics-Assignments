#include "Labyrinth.h"


Labyrinth::Labyrinth(int size)
	: size(size)
{
}


void Labyrinth::init()
{
	if (size > 30)
		size = 30;
	else if (size <= 0)
		size = 1;
	int dim = size * 2 + 1;
	maze = new int[dim * dim];
	
	generateNewMaze();
}

Labyrinth::~Labyrinth()
{
	if (maze != 0)
	{
		delete[] maze;
		maze = 0;
	}
}

void Labyrinth::generateNewMaze()
{
	initMaze();

	int *backX = new int[size * size];
	int *backY = new int[size * size];

	int stepIndex = 0;
	backX[stepIndex] = backY[stepIndex] = 1;
	generateMaze(stepIndex, backX, backY, Point2d(1, 1), 1);
	
	delete[] backX;
	delete[] backY;
}

void Labyrinth::initMaze()
{
	for (int i = 0; i < size * 2 + 1; ++i)
		for (int j = 0; j < size * 2 + 1; ++j)
		{
			if (i % 2 == 0 || j % 2 == 0)
				maze[i * (size * 2 + 1) + j] = WALL;
			else
				maze[i * (size * 2 + 1) + j] = PATH;
		}
}

bool Labyrinth::isMazeClosed(const Point2d p)
{
	if (maze[(p.x - 1) * (size * 2 + 1) + p.y]  == WALL
		&& maze[p.x * (size * 2 + 1) + p.y - 1] == WALL
		&& maze[p.x * (size * 2 + 1) + p.y + 1] == WALL
		&& maze[(p.x + 1) * (size * 2 + 1) + p.y] == WALL)
		return true;

	return false;
}

void Labyrinth::generateMaze(int stepIndex, int *backX, int *backY, Point2d p, int visited)
{
	//std::cerr << "MAZE: \n" << *this << "\n";
    if(visited < size * size)
    {
        int neighbourValid = -1;
        int neighbourX[4];
        int neighbourY[4];
        int step[4];

        int nextX;
        int nextY;

        if(p.x - 2 > 0 && isMazeClosed(Point2d(p.x - 2, p.y)))  // upside
        {
            neighbourValid++;
            neighbourX[neighbourValid] = p.x - 2;
            neighbourY[neighbourValid] = p.y;
            step[neighbourValid] = 1;
        }

        if(p.y - 2 > 0 && isMazeClosed(Point2d(p.x, p.y - 2)))  // leftside
        {
            neighbourValid++;
            neighbourX[neighbourValid] = p.x;
            neighbourY[neighbourValid]= p.y - 2;
            step[neighbourValid] = 2;
        }

        if(p.y + 2 < size * 2 + 1 && isMazeClosed(Point2d(p.x, p.y + 2)))  // rightside
        {
            neighbourValid++;
            neighbourX[neighbourValid] = p.x;
            neighbourY[neighbourValid] = p.y + 2;
            step[neighbourValid] = 3;

        }

		if(p.x + 2 < size * 2 + 1 && isMazeClosed(Point2d(p.x + 2, p.y)))  // downside
        {
            neighbourValid++;
            neighbourX[neighbourValid] = p.x + 2;
            neighbourY[neighbourValid] = p.y;
            step[neighbourValid] = 4;
        }

        if(neighbourValid == -1)
        {
            // backtrack
            nextX = backX[stepIndex];
            nextY = backY[stepIndex];
            stepIndex--;
        }

        if(neighbourValid != -1)
        {
            int randomization = neighbourValid + 1;
            int random = rand() % randomization;
            nextX = neighbourX[random];
            nextY = neighbourY[random];
            stepIndex++;
            backX[stepIndex] = nextX;
            backY[stepIndex] = nextY;

            int rstep = step[random];

            if(rstep == 1)
                maze[(nextX + 1) * (size * 2 + 1) + nextY] = PATH;
            else if(rstep == 2)
                maze[nextX * (size * 2 + 1) + nextY + 1] = PATH;
            else if(rstep == 3)
                maze[nextX * (size * 2 + 1) + nextY - 1] = PATH;
            else if(rstep == 4)
                maze[(nextX - 1) * (size * 2 + 1) + nextY] = PATH;
            visited++;
        }

        generateMaze(stepIndex, backX, backY, Point2d(nextX, nextY), visited);
    }
}

std::ostream& operator<< (std::ostream& os, const Labyrinth &l)
{
	for (int i = 0; i < l.size * 2 + 1; ++i)
		os << "_";
	os << "\n";
	for (int i = 0; i < l.size * 2 + 1; ++i)
	{
		for (int j = 0; j < l.size * 2 + 1; ++j)
		{
			os << ((l.maze[i * (l.size * 2 + 1) + j] == WALL) ? "#" : " ");
		}
		os << "\n";
	}
	for (int i = 0; i < l.size * 2 + 1; ++i)
		os << "_";
	os << "\n";
	return os;
}
