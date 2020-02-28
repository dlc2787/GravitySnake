#include <iostream>
#include "snakeGame.h"
#include "Target.h"
#include <Box2D/Box2D.h>
#include <time.h>
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

bool jumped;

//timestep
float timeStep;

int32 velocityIterations;
int32 positionIterations;

float elapsedTime;
float score;
float levelMod;

Text text;
Font font;

//advances the world, checks if the snake hit the target and keeps track of score, which starts at being worth 20 points and decreases the longer it takes you to get it. returns 0 or 1 depending on whether the snake
//got the target that frame
int update(b2World* world, b2Vec2* snakePos, Target* target)
{
	advance(world);
	elapsedTime += timeStep;
	if (distanceBetween(*snakePos, target->getPositionValue()) <= 1.5) {
		target->setPosition(randomVector(2, 2, 78, 58));
		score += 6000.0f / (levelMod + elapsedTime);
		elapsedTime = 0.0f;
		return 1;
	}
	return 0;
}

//clears and prints the object passed in (snake), target and score to the screen
void display(b2Vec2* snakePos, b2Vec2* target, RenderWindow* window)
{
	system("CLS");
	printf("Snake: %4.2f, %4.2f ---> Target: %4.2f, %4.2f | Score: %0.0f\n", snakePos->x, snakePos->y, target->x, target->y, score);
	//cout << "Snake: " << snakePos->x << ", " << snakePos->y << " ---> Target" << targetPos->x << ", " << targetPos->y << endl;
	//printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	text.setCharacterSize(14);
	text.setStyle(Text::Bold);
	text.setFillColor(Color::White);
	text.setPosition(12, 12);
	text.setString("Move with A and D, jump with space, and trim jump with W and S || Score: " + to_string(getScore()));
	window->draw(text);
}

void setup(Snake* snake, Target* target) {
	if (!font.loadFromFile("arial.ttf")) {
		cout << "Encountered an error loading font" << endl;
	}
	jumped = false;
	timeStep = 1.0 / 60.0;
	velocityIterations = 3;
	positionIterations = 2;
	elapsedTime = 0.0;
	score = 0.0;
	levelMod = 30.0;
	text.setFont(font);
	target->setPosition(randomVector(2, 2, 78, 58));
}

//checks user input and applies force to the onject passed in, in this case the snake
bool applyForces(b2Body* dynBody)
{
	b2Vec2 force = b2Vec2(0.0f, 0.0f);
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		force += b2Vec2(0.0f, -200.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		force += b2Vec2(0.0f, 200.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		force += b2Vec2(-800.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		force += b2Vec2(800.0f, 0.0f);
	}
	if (Keyboard::isKeyPressed(Keyboard::Space) && !jumped) {
		force += b2Vec2(0.0f, -17000.0f);
		jumped = true;
	}
	else if (!Keyboard::isKeyPressed(Keyboard::Space)) jumped = false;
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		return true;
	}
	dynBody->ApplyForceToCenter(force, true);
	return false;
}

//distance between two b2Vec2 objects
float distanceBetween(b2Vec2 one, b2Vec2 two) {
	return sqrtf(powf(one.x - two.x, 2) + powf(one.y - two.y, 2));
}

//returns a random vector within the bounds present
b2Vec2 randomVector(int x1, int y1, int x2, int y2) {
	srand(time(NULL));
	return b2Vec2((rand() % (x2-x1)) + x1, (rand() % (y2-y1)) + y1);
}

//returns score
int getScore() {
	return roundf(score);
}

bool startScreen(RenderWindow* window) {
	text.setCharacterSize(64);
	text.setPosition(202.0f, 200.0f);
	text.setString("Gravity Snake");
	window->draw(text);
	text.setCharacterSize(32);
	text.setPosition(257.0f, 300.0f);
	text.setString("Press Enter to Begin");
	window->draw(text);
	if (Keyboard::isKeyPressed(Keyboard::Enter))
		return true;
	return false;
}

char overScreen( RenderWindow* window) {
	text.setCharacterSize(96);
	text.setPosition(100.0f, 100.0f);
	text.setString("GAME OVER");
	window->draw(text);
	text.setCharacterSize(24);
	float pos = 318.0f;
	double scoreCount = getScore();
	while (scoreCount > 9) {
		scoreCount /= 10;
		pos -= 7;
	}
	text.setPosition(pos, 265.0f);
	text.setString("Final Score: " + to_string(getScore()));
	window->draw(text);
	text.setCharacterSize(32);
	text.setPosition(210.0f, 350.0f);
	text.setString("Press Enter to Play Again");
	window->draw(text);
	text.setCharacterSize(32);
	text.setPosition(245.0f, 400.0f);
	text.setString("Press Escape to Quit");
	window->draw(text);
	if (Keyboard::isKeyPressed(Keyboard::Enter))
		return 'g';
	else if (Keyboard::isKeyPressed(Keyboard::Escape))
		return 'd';
	else return 'o';
}

void advance(b2World* world) {
	world->Step(timeStep, velocityIterations, positionIterations);
}


