#include "Target.h"
#include <iostream>

using namespace sf;

Target::Target(float x, float y, RenderWindow* window)
{
	Target::window = window;
	pos = new b2Vec2(x, y);
	shape = CircleShape(5);
	shape.setFillColor(Color(255, 100, 100));
	shape.setPosition(pos->x * 10, pos->y * 10);
}

Target::~Target()
{
	delete pos;
}

void Target::setPosition(b2Vec2 newPos)
{
	pos->Set(newPos.x, newPos.y);
	shape.setPosition(pos->x * 10, pos->y * 10);
}

b2Vec2 Target::getPositionValue() {
	return *pos;
}
b2Vec2* Target::getPositionRef() {
	return pos;
}

void Target::Draw() {
	window->draw(shape);
}