//-----------------------------------------------------------------------------------------------
//					Tema1
//
//	Fisiere de interes: Transform2d.cpp main.cpp
//
//	Functii WorldDrawer2d:
//	-init e apelat o singura data, la inceput.
//	-idle e apelat per cadru de desenare
//	-onKey la apasarea unei taste.
//
//	Obiecte:
//	- un obiect este reprezentat prin punct si topologia punctelor (cum sunt legate pctele)
//	- obiectele sunt compuse din triunghiuri! de exemplu cu 4 puncte si 6 indici de topologie
//	pot crea 2 triunghiuri adiacente ce impreuna formeaza un dreptunghi.
//
//	Sisteme de coordonate:
//	- sunt 2 tipuri de sisteme de coordonate (fix - bleu&magenta) si dinamic(rosu&albastru)
//	- ca un obiect sa fie desenat trebuie sa fie atasat unui sistem de coordonate
//	- cand un obiect e atasat la un sistem de coordonate urmeaza transformarile sistemului.
//
//	Control obiecte:
//	- daca translatez/rotesc un obiect/punct direct (ex: o->translate(1,1)) o fac in coordonate globale
//	- daca translatez/rotesc un obiect printr-un sistem de coordonate o fac in coordonate locale
//	- pentru simplitate toate coordonatele mentinute in obiecte(de c++) sunt globale.
//
//	Happy coding.
//----------------------------------------------------------------------------------------------

#define  _USE_MATH_DEFINES		// enables M_PI macro
#include <cmath>
#include "WorldDrawer2d.h"
#include "Circle2d.h"
#include "Rectangle2d.h"
#include "Ball.h"
#include <iostream>

#include <ctime>
#include <climits>

#include <random>
std::random_device random_device;
std::mt19937 generator(random_device());

bool WorldDrawer2d::animation=false;
int WorldDrawer2d::score_blue = 0, WorldDrawer2d::score_green = 0;		// Game score


//used global vars
CoordinateSystem2d *cs1, *cs2,*cs3;
Object2d *o1, *o2, *o3;
Circle2d *circle1, *circle2;
Object2d *out_border, *in_border;
Object2d *out_net1, *in_net1, *out_net2, *in_net2;
Object2d *net_line1, *net_line2, *board_center_line;

Object2d *score_up;
Object2d *score_down;

std::vector<Object2d *> score_lines_up;
std::vector<Object2d *> score_lines_down;
std::vector<Object2d *> scores;
Ball *ball;
Object2d *goal_keeper;
std::vector<Object2d *> team1, team2, players;

// Constants
static const float TWICE_PI = (float)(2.0f * M_PI);	// Math constant 2 * pi
const int num_players = 6;

const float out_length = 22.5f;
const float out_height = 28.f;
const float out_small_length = 22.f;
const float out_small_heigth = 27.5f;
const float net_outer_length = 8.f;
const float net_outer_heigth = 5.f;
const float net_inner_length = 7.5f;
const float net_inner_height = 4.5f;
const float net_translate_y = 14.f;
const float net_line_length = 7.5f;
const float net_line_height = 0.25f;
const float net_line_translate_y = 13.875f;
const float center_line_height = 0.25f;
const float center_line_length = 22.f;

const float score_line_length = .4f;
const float score_line_height = 4.5f;
const float score_line_translate_y = 4.f;
const float score_line_translate_x1 = out_length / 2 + 2.f;
const float score_line_step_x = 2 * score_line_length;

const float ball_radius = 0.7f;
const float ball_delta_x = out_small_length / 2 - ball_radius - .1;
const float ball_delta_y = net_line_translate_y - ball_radius - .1;
const float player_radius = 1.f;
const float min_dist_between_player_center = 3.f;
const float min_player_x = -9.7f;
const float max_player_x = 9.7f;
const float min_player_y = -12.7f;
const float max_player_y = 12.7f;

const float speed = 0.1f;
const float rotate_speed = 0.1f;
const float rotation_step = 1.f;


// Func declaration
static float getRandomFloat(float low, float high);
static int getRandomInt(int low, int high);

//add
void WorldDrawer2d::init(){
	//creeaza 2 sistem de coordonate client
	cs1 = new CoordinateSystem2d();
	cs2 = new CoordinateSystem2d();	
	cs_used.push_back(cs1);
	cs_used.push_back(cs2);
	
	

	initBoard();

	// Game score
	score_blue = 0;
	score_green = 0;		
	animation = false;

	initTeams();
	initBall();
	
}

// Initializes the ball on the board
void WorldDrawer2d::initBall()
{
	if (ball != NULL)
		delete ball;
	ball = new Ball(ball_radius);
	ball->setcolor(1, 0, 0);	//red ball
	cs1->objectAddFront(ball);

	moveBallToRandomPlayer(ball);
}

void WorldDrawer2d::moveBallToRandomPlayer(Ball *ball)
{
	int random_player = getRandomInt(0, players.size() - 1);
	ball->translate(players[random_player]->getCenter().x, players[random_player]->getCenter().y);
	
	ball->translate(player_radius + .2, 0);
	bool position_is_good = false;
	while (!position_is_good)
	{
		float random_angle = getRandomFloat(0, TWICE_PI);
		ball->rotateRelativeToPoint(players[random_player]->getCenter(), random_angle);
		if (isCircleOnBoard(ball))
		{
			position_is_good = true;
			ball->at_player = players[random_player];
			ball->posessed = true;
		}
	}
}

void WorldDrawer2d::resetBallAfterGoal()
{
	//move back to origin
	ball->translate(-ball->getCenter().x, -ball->getCenter().y);
	moveBallToRandomPlayer(ball);
}

void WorldDrawer2d::resetGame()
{
	for (int i = 0; i < 4; ++i)
	{
		invertColors();
		displayCallbackFunction();
		Sleep(500);
	}

	initTeams();
	initBall();
	score_blue = 0;
	score_green = 0;
	for (unsigned int i = 0; i < scores.size(); ++i)
	{
		cs1->objectRemove(scores[i]);
		delete scores[i];
	}
	scores.clear();
	score_lines_down.clear();
	score_lines_up.clear();
}

void WorldDrawer2d::invertColors()
{
	for (unsigned int i = 0; i < cs1->objects.size(); ++i)
	{
		Object2d *o = cs1->objects[i];
		o->setcolor(1 - o->colorx, 1 - o->colory, 1 - o->colorz);
	}
}

// Checks if a Circle object is on board
bool WorldDrawer2d::isCircleOnBoard(Circle2d *ball)
{
	Point2d center = ball->getCenter();
	if ( abs(center.x) + ball->radius >= out_small_length / 2 - .1 ||
		abs(center.y) + ball_radius >= net_line_translate_y - .1)
		return false;
	return true;
}

// Initializes the teams on the board. Team1 is green attacking down. Team 2
// is blue, attacking up.
void WorldDrawer2d::initTeams()
{
	// Clean up players
	team1.clear();
	team2.clear();
	for (unsigned int i = 0; i < players.size(); ++i)
	{
		cs1->objectRemove(players[i]);
		delete players[i];
	}
	players.clear();

	initGoalKeepers();

	for (unsigned int i = 0; i < num_players * 2; ++i)
	{
		// Generate random position for players to be separated by a minimum distance
		bool good = false;
		while (!good)
		{
			Point2d random_point = getRandomPoint(min_player_x, max_player_x, min_player_y, max_player_y);
			Object2d *player = new Circle2d(player_radius);
			player->translate(random_point.x, random_point.y);

			bool bad_position = false;
			for (unsigned int j = 0; j < players.size(); ++j)
			{
				if ( abs(player->getCenter().x - players[j]->getCenter().x) < min_dist_between_player_center &&
					abs(player->getCenter().y - players[j]->getCenter().y) < min_dist_between_player_center)
				{
					bad_position = true;
					delete player;
					break;
				}
			}
			
			// Generated position is good
			if (!bad_position)
			{
				if (i < num_players)
				{
					player->setcolor(0, 1, 0);	//green
					team1.push_back(player);
				}
				else
				{
					player->setcolor(0, 0, 1);	//blue
					team2.push_back(player);
				}
				players.push_back(player);
				cs1->objectAddFront(player);
				good = true;
			}
		}
	}
}

// Initialize goal keepers
void WorldDrawer2d::initGoalKeepers()
{
	// Goal keeper for team 1
	goal_keeper = new Circle2d(player_radius);
	goal_keeper->translate(0, net_line_translate_y - 1);
	goal_keeper->setcolor(0, 1, 0);		//green
	cs1->objectAddFront(goal_keeper);
	players.push_back(goal_keeper);
	team1.push_back(goal_keeper);

	// Goal keeper for team 2
	goal_keeper = new Circle2d(player_radius);
	goal_keeper->translate(0, -net_line_translate_y + 1);
	goal_keeper->setcolor(0, 0, 1);		//blue
	cs1->objectAddFront(goal_keeper);
	players.push_back(goal_keeper);
	team2.push_back(goal_keeper);
}

// Generate random Point2d in range
Point2d WorldDrawer2d::getRandomPoint(float lowx, float highx, float lowy, float highy)
{
	Point2d point(getRandomFloat(lowx, highx), getRandomFloat(lowy, highy));
	return point;
}

// Generate random float number in range
static float getRandomFloat(float low, float high)
{
	//return low + (float)(std::rand() / ( (float)RAND_MAX / (high - low) ));
	std::uniform_real_distribution<> distribution(low, high);
	return (float)distribution(generator);
}

// Generate random int number in range
static int getRandomInt(int low, int high)
{
	std::uniform_int_distribution<> disrtibution(low, high);
	return (int)disrtibution(generator);
}

// Inits the game board
void WorldDrawer2d::initBoard()
{
	// Dreptunghi alb la mijlocul terenului
	board_center_line = new Rectangle2d(center_line_length, center_line_height);
	board_center_line->setcolor(1, 1, 1);
	cs1->objectAdd(board_center_line);

	// Dreptunghi alb linia portii de sus
	net_line1 = new Rectangle2d(net_line_length, net_line_height);
	net_line1->setcolor(1, 1, 1);
	net_line1->translate(0, net_line_translate_y);
	cs1->objectAdd(net_line1);

	// Dreptunghi alb linia portii de jos
	net_line2 = new Rectangle2d(net_line_length, net_line_height);
	net_line2->setcolor(1, 1, 1);
	net_line2->translate(0, -net_line_translate_y);
	cs1->objectAdd(net_line2);

	// Dreptunghi portocaliu la interior, teren de joc
	in_border = new Rectangle2d(out_small_length, out_small_heigth);
	in_border->setcolor(1, 0.5, 0);
	cs1->objectAdd(in_border);

	// Dreptunghi portocaliu interiorul portii de sus
	in_net1 = new Rectangle2d(net_inner_length, net_inner_height);
	in_net1->setcolor(1, 0.5, 0);
	in_net1->translate(0, net_translate_y);
	cs1->objectAdd(in_net1);

	// Dreptunghi rosu exterior portii de sus
	out_net1 = new Rectangle2d(net_outer_length, net_outer_heigth);
	out_net1->setcolor(1, 0, 0);
	out_net1->translate(0, net_translate_y);
	cs1->objectAdd(out_net1);

	// Dreptunghi portocaliu interiorul portii de jos
	in_net2 = new Rectangle2d(net_inner_length, net_inner_height);
	in_net2->setcolor(1, 0.5, 0);
	in_net2->translate(0, -net_translate_y);
	cs1->objectAdd(in_net2);

	// Dreptunghi rosu exterior portii de sus
	out_net2 = new Rectangle2d(net_outer_length, net_outer_heigth);
	out_net2->setcolor(1, 0, 0);
	out_net2->translate(0, -net_translate_y);
	cs1->objectAdd(out_net2);

	// Dreptunghi rosu la exterior, manta
	out_border = new Rectangle2d(out_length, out_height);
	out_border->setcolor(1, 0, 0);
	cs1->objectAdd(out_border);
}

void WorldDrawer2d::onIdle(){	//per frame
	Sleep(20);
	static int iteration=1;
	static int dir = 1;
	if(animation){
		if (iteration%30 == 0)
			dir *= -1;

		// ball is at player
		if (ball->posessed)
		{
			ball->translate(speed * (ball->current_center.x - ball->at_player->getCenter().x),
				speed * (ball->current_center.y - ball->at_player->getCenter().y));
			ball->at_player  = NULL;
			ball->posessed = false;
		}

		// Possible colision with walls
		else
		{
			Point2d nextPosition(2 * ball->current_center.x - ball->previews_center.x,
				2 * ball->current_center.y - ball->previews_center.y);
			if (isGoal(nextPosition))
			{
				ball->translate(ball->current_center.x - ball->previews_center.x,
					ball->current_center.y - ball->previews_center.y);
				animation = false;

				// Goal up, so Blue team increases score (team2)
				if (ball->current_center.y > 0)
				{
					++score_blue;
					score_down = new Rectangle2d(score_line_length, score_line_height);
					score_down->setcolor(0.5, 0.3, 0);
					score_down->translate(score_line_translate_x1 + (score_blue - 1) * score_line_step_x,
						score_line_translate_y);
					cs1->objectAddFront(score_down);
					score_lines_down.push_back(score_down);
					scores.push_back(score_down);

					if (score_blue == 3)
					{
						printf("Blue team wins!\n");
						resetGame();
						return;
					}
					else
					{
						printf("Score for blue team: %d\n", score_blue);
						resetBallAfterGoal();
						return;
					}
				}

				// Goal up, so Green team increases score (team1)
				if (ball->current_center.y < 0)
				{
					++score_green;
					score_up = new Rectangle2d(score_line_length, score_line_height);
					score_up->setcolor(0.5, 0.3, 0);
					score_up->translate(score_line_translate_x1 + (score_green - 1) * score_line_step_x,
						-score_line_translate_y);
					cs1->objectAddFront(score_up);
					score_lines_up.push_back(score_up);
					scores.push_back(score_up);

					if (score_green == 3)
					{
						printf("Green team wins!\n");
						resetGame();
						return;
					}
					else
					{
						printf("Score for green team: %d\n", score_green);
						resetBallAfterGoal();
						return;
					}
				}

			}

			Point2d wallDirection = wallColisionDirection();

			ball->translate(ball->current_center.x - ball->previews_center.x,
				ball->current_center.y - ball->previews_center.y);

			ball->translate(wallDirection.x, wallDirection.y);
		}
		if (isBallPlayerColision())
			animation = false;

		iteration++;
	}
}

bool WorldDrawer2d::isGoal(Point2d point)
{
	if (abs(point.y) >= ball_delta_y && 
		abs(point.x) <= net_line_length / 2)
		return true;
	return false;
}

Point2d WorldDrawer2d::wallColisionDirection()
{
	Point2d current = ball->current_center;
	Point2d previous = ball->previews_center;
	Point2d direction(current.x - previous.x, current.y - previous.y);

	if ( abs(current.x + direction.x) <= ball_delta_x
		&& abs(current.y + direction.y) > ball_delta_y )
	{
		return Point2d(direction.x, -direction.y);
	}
	else if ( abs(current.x + direction.x) > ball_delta_x
		&& abs(current.y + direction.y) <= ball_delta_y )
	{
		return Point2d(-direction.x, direction.y);
	}
	else if ( abs(current.x + direction.x) > ball_delta_x
		&& abs(current.y + direction.y) > ball_delta_y )
	{
		return Point2d(-direction.x, -direction.y);
	}

	return Point2d(direction.x, direction.y);
}

bool WorldDrawer2d::isWallColision()
{
	Point2d current = ball->current_center;
	Point2d previous = ball->previews_center;
	Point2d direction(current.x - previous.x, current.y - previous.y);

	if ( abs(current.x + direction.x) > ball_delta_x
		|| abs(current.y + direction.y) > ball_delta_y )
		return true;
	return false;
}

bool WorldDrawer2d::isBallPlayerColision(Point2d point)
{
	for (unsigned int i = 0; i < players.size(); ++i)
	{
		if (players[i]->getCenter().x != ball->at_player->getCenter().x &&
			players[i]->getCenter().y != ball->at_player->getCenter().y)
		{
			float deltax = point.x - players[i]->getCenter().x;
			float deltay = point.y - players[i]->getCenter().y;
			if ( deltax * deltax + deltay * deltay <= ball_radius + player_radius + .2f )
			{
				return true;
			}
		}
	}
	return false;
}

bool WorldDrawer2d::isBallPlayerColision()
{
	for (unsigned int i = 0; i < players.size(); ++i)
	{
		float deltax = ball->getCenter().x - players[i]->getCenter().x;
		float deltay = ball->getCenter().y - players[i]->getCenter().y;
		if ( deltax * deltax + deltay * deltay <= ball_radius + player_radius + .2f )
		{
			ball->at_player = players[i];
			ball->posessed = true;
			return true;
		}
	}
	return false;
}

void WorldDrawer2d::onKey(unsigned char key){
	switch(key){
		case KEY_SPACE:
				animation=!animation;
			break;
		case 'w':
				// move up

			break;
		case 'a':
				// move left

			break;
		case 's':
				// move down
				
			break;
		case 'd':
				// move right

			break;
		case 'q':
				// rotate counterclockwise
				rotateBallWithPlayer(rotate_speed * rotation_step);
			break;
		case 'e':
				// rotate clockwise
				rotateBallWithPlayer(-rotate_speed * rotation_step);
			break;
		case 'r':
				// Game reset
				resetGame();
		default:
			break;
	}
}

void WorldDrawer2d::rotateBallWithPlayer(float radius)
{
	if(ball->posessed)
	{
		Point2d center = ball->current_center;
		center.rotateRelativeToPoint(ball->at_player->getCenter(), radius);

		if (abs(center.x) > ball_delta_x || abs(center.y) > ball_delta_y)
			return;

		if (isBallPlayerColision(center))
			return;

		ball->rotateRelativeToPoint(ball->at_player->getCenter(), radius);
	}
}


int main(int argc, char** argv){

	

	std::srand((unsigned int)std::time(0));

	WorldDrawer2d wd2d(argc,argv,600,600,200,100,std::string("Tema 1"));
	wd2d.init();
	wd2d.run();
	return 0;
}