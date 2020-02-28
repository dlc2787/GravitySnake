#pragma once
#include <Box2D/Box2D.h>
#include "Target.h"
#include "Snake.h"

int update(b2World*, b2Vec2* snakePos, Target* target);
void display(b2Vec2* snakePos, b2Vec2* target, RenderWindow* window);
bool applyForces(b2Body* target);
float distanceBetween(b2Vec2, b2Vec2);
b2Vec2 randomVector(int x1, int y1, int x2, int y2);
int getScore();
void setup(Snake* snake, Target* target);
bool startScreen(RenderWindow* window);
char overScreen(RenderWindow* window);
void advance(b2World* world);