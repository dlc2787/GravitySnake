#pragma once
#include <Box2D/Box2D.h>
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class StaticBox
{
private:
	b2BodyDef* def;
	b2Body* body;
	b2PolygonShape* box;
	sf::RectangleShape shape;
	sf::RenderWindow* window;
public:
	StaticBox(b2World* world, sf::RenderWindow* window, float x, float y, float width, float height);
	~StaticBox();
	void Draw();
};

