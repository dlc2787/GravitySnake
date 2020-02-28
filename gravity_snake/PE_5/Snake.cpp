#include "Snake.h"

using namespace sf;

Snake::Snake(b2World* world, RenderWindow* window, float x, float y, float radius, float density, float friction)
{
    Snake::window = window;
    snakeDef = new b2BodyDef;
    snakeDef->type = b2_dynamicBody;
    snakeDef->position.Set(x, y);

    snakeBody = world->CreateBody(snakeDef);

    snakeCircle = new b2CircleShape;
    snakeCircle->m_p.Set(0, 0);
    snakeCircle->m_radius = radius;


    fixtureDef = new b2FixtureDef;
    fixtureDef->shape = snakeCircle;
    fixtureDef->density = density;
    fixtureDef->friction = friction;

    snakeBody->CreateFixture(fixtureDef);

    snakeShape = CircleShape(radius * 10);
    snakeShape.setFillColor(Color(100, 255, 100));
    snakeShape.setPosition(x * 10, y * 10);
}

Snake::~Snake()
{
    delete snakeDef;
    delete snakeCircle;
    delete fixtureDef;
}

b2Vec2 Snake::getPosition()
{
    return snakeBody->GetPosition();
}

b2Body* Snake::getSnake()
{
    return snakeBody;
}

void Snake::Draw() {
    b2Vec2 pos = getPosition();
    snakeShape.setPosition(pos.x * 10, pos.y * 10);
    window->draw(snakeShape);
}


