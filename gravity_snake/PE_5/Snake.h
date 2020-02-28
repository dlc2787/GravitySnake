#pragma once
#include <Box2D/Box2D.h>
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Snake
{
private:
	sf::RenderWindow* window;
	b2BodyDef* snakeDef;
	b2Body* snakeBody;
	b2CircleShape* snakeCircle;
	b2FixtureDef* fixtureDef;
	sf::CircleShape snakeShape;
public:
	Snake(b2World* world, sf::RenderWindow* window, float x, float y, float radius, float density, float friction);
	~Snake();
	b2Vec2 getPosition();
	b2Body* getSnake();
	void Draw();
};

