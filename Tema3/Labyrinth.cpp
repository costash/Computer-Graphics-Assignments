#include "Labyrinth.h"

//-----------------------------------------------------------------------------------------------------
//	Labyrinth class holding information of maze
//-----------------------------------------------------------------------------------------------------


Labyrinth::Labyrinth(int size)
	: size(size)
{
}

// Init Labyrinth with a new maze of current size
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

// Generates a new Maze with current size
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

void Labyrinth::drawLabyrinth()
{
	int dim = size * 2 + 1;
	for (int i = 0; i < dim; ++i)
		for (int j = 0; j < dim; ++j)
		{
			glPushMatrix();

			if (maze[i * dim + j] == WALL)
			{
				glColor3f(0.f, 0.f, 1.f);
				//glScalef(1.f, 2.f, 1.f);
				glTranslatef((j - dim / 2) * 3.f, 0.f, (i - dim / 2) * 3.f);
				glutSolidCube(2.5f);
			}
			else if (maze[i * dim + j] == PORTAL)
			{
				glColor3f(1.f, 0.f, 0.f);
				
				glTranslatef((j - dim / 2) * 3.f, 0.f, (i - dim / 2) * 3.f);
				// Rotate portal coresponding to the walls
				if (maze[i * dim + j - 1] == WALL && maze[(i - 1) * dim + j] == WALL)	// left, up walls
					glRotatef(-45, 0.f, 1.f, 0.f);
				else if (maze[i * dim + j - 1] == WALL && maze[(i + 1) * dim + j] == WALL) // left, down walls
					glRotatef(45, 0.f, 1.f, 0.f);
				else if (maze[i * dim + j + 1] == WALL && maze[(i + 1) * dim + j] == WALL) // right, down walls
					glRotatef(-45, 0.f, 1.f, 0.f);
				else if (maze[i * dim + j + 1] == WALL && maze[(i - 1) * dim + j] == WALL) // right, up walls
					glRotatef(45, 0.f, 1.f, 0.f);
				else if (maze[(i - 1) * dim + j] == WALL && maze[(i - 1) * dim + j] == WALL) // up, down walls
					glRotatef(90, 0.f, 1.f, 0.f);
				
				glutSolidTorus(0.5, 1, 100, 100);
				//glutSolidCube(3);
			}
			glPopMatrix();
		}
}

// Generates a random position for portal
void Labyrinth::generatePortalPosition()
{
	int x, y, dim = size * 2 + 1;
	bool wall = true;

	do
	{
		x = rand() % dim;
		y = rand() % dim;
		wall = isOnWall(Point2d(x, y));
		std::cerr << "(x,y): " << Point2d(x, y) << " " << maze[x * dim + y] << "\n";
	} while (wall == true);
	
	portalPos = Point2d(x, y);
	maze[x * dim + y] = PORTAL;
	std::cerr << "(x,y): " << Point2d(x, y) << " " << maze[x * dim + y] << "\n";
}

bool Labyrinth::isOnWall(const Point2d p)
{
	int dim = size * 2 + 1;
	if (maze[p.x * dim + p.y] == WALL)
		return true;
	return false;
}

void Labyrinth::initMaze()
{
	int dim = size * 2 + 1;
	for (int i = 0; i < dim; ++i)
		for (int j = 0; j < dim; ++j)
		{
			if (i % 2 == 0 || j % 2 == 0)
				maze[i * (dim) + j] = WALL;
			else
				maze[i * (dim) + j] = PATH;
		}
}

bool Labyrinth::isMazeClosed(const Point2d p)
{
	int dim = size * 2 + 1;
	if (maze[(p.x - 1) * (dim) + p.y]  == WALL
		&& maze[p.x * (dim) + p.y - 1] == WALL
		&& maze[p.x * (dim) + p.y + 1] == WALL
		&& maze[(p.x + 1) * (dim) + p.y] == WALL)
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

		int dim = size * 2 + 1;

        if(p.x - 2 > 0 && isMazeClosed(Point2d(p.x - 2, p.y)))  // up side of point
        {
            neighbourValid++;
            neighbourX[neighbourValid] = p.x - 2;
            neighbourY[neighbourValid] = p.y;
            step[neighbourValid] = 1;
        }

        if(p.y - 2 > 0 && isMazeClosed(Point2d(p.x, p.y - 2)))  // left side of point
        {
            neighbourValid++;
            neighbourX[neighbourValid] = p.x;
            neighbourY[neighbourValid]= p.y - 2;
            step[neighbourValid] = 2;
        }

        if(p.y + 2 < dim && isMazeClosed(Point2d(p.x, p.y + 2)))  // right side of point
        {
            neighbourValid++;
            neighbourX[neighbourValid] = p.x;
            neighbourY[neighbourValid] = p.y + 2;
            step[neighbourValid] = 3;

        }

		if(p.x + 2 < dim && isMazeClosed(Point2d(p.x + 2, p.y)))  // down side of point
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
                maze[(nextX + 1) * (dim) + nextY] = PATH;
            else if(rstep == 2)
                maze[nextX * (dim) + nextY + 1] = PATH;
            else if(rstep == 3)
                maze[nextX * (dim) + nextY - 1] = PATH;
            else if(rstep == 4)
                maze[(nextX - 1) * (dim) + nextY] = PATH;
            visited++;
        }

        generateMaze(stepIndex, backX, backY, Point2d(nextX, nextY), visited);
    }
}

std::ostream& operator<< (std::ostream& os, const Labyrinth &l)
{
	int dim = l.size * 2 + 1;
	for (int i = 0; i < dim; ++i)
		os << "_";
	os << "\n";
	for (int i = 0; i < dim; ++i)
	{
		for (int j = 0; j < dim; ++j)
		{
			os << ((l.maze[i * (dim) + j] == WALL) ? "#" : " ");
		}
		os << "\n";
	}
	for (int i = 0; i < dim; ++i)
		os << "_";
	os << "\n";
	return os;
}
