#pragma once
#include <Box2D/Box2D.h>
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class Target
{
private:
	RenderWindow* window;
	b2Vec2* pos;
	CircleShape shape;
public:
	Target(float x, float y, RenderWindow* window);
	~Target();
	void setPosition(b2Vec2 newPos);
	b2Vec2 getPositionValue();
	b2Vec2* getPositionRef();
	void Draw();
};

