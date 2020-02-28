#include "StaticBox.h"

using namespace sf;

StaticBox::StaticBox(b2World* world, RenderWindow* window, float x, float y, float width, float height)
{
    StaticBox::window = window;
    def = new b2BodyDef;
    def->position.Set(x - 1, y - 1);

    body = world->CreateBody(def);

    box = new b2PolygonShape;
    box->SetAsBox(width, height);

    body->CreateFixture(box, 0.0f);

    shape = RectangleShape(Vector2f(width * 20, height * 20));
    shape.setFillColor(Color(100, 100, 255));
    shape.setPosition((x - width) * 10, (y - height) * 10);
}

StaticBox::~StaticBox()
{
    delete def;
    delete box;
}

void StaticBox::Draw()
{
    window->draw(shape);
}
