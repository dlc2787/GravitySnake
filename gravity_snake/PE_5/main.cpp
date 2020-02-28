// PE_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#define SFML_STATIC
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#include "snakeGame.h"
#include "Snake.h"
#include "StaticBox.h"
#include "Target.h"

using namespace sf;
using namespace std;

void wrapper();

int main()
{
    wrapper();
    _CrtDumpMemoryLeaks();
}

void wrapper() {
    //set up world
    b2Vec2* gravity = new b2Vec2(0.0f, 98.0f);
    b2World* world = new b2World(*gravity);

    RenderWindow window(VideoMode(800, 600), "Gravity Snake");

    //set up ground body
    //create a body definition
    StaticBox* ground = new StaticBox(world, &window,  40.0f, 60.0f, 40.0f, 1.0f);

    //ceilingwall
    StaticBox* ceiling = new StaticBox(world, &window, 40.0f, 0.0f, 40.0f, 1.0f);

    //leftwall
    StaticBox* lWall = new StaticBox(world, &window, 0.0f, 30.0f, 1.0f, 29.0f);

    //rightwall
    StaticBox* rWall = new StaticBox(world, &window, 80.0f, 30.0f, 1.0f, 29.0f);

    Snake* snake = new Snake(world, &window, 40.0f, 30.0f, 1.0f, 1.0f, 0.3f);

    b2Vec2 start = randomVector(2, 2, 78, 58);
    Target* target = new Target(start.x, start.y, &window);

    bool done = false;
    int targets = 0;

    char gameState = 'm';

    setup(snake, target);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(Color::Black);
        switch (gameState) {
        default:
            if (startScreen(&window)) {
                gameState = 'g';
            }
            break;
        case 'g': {
            b2Vec2 position = snake->getPosition();
            targets += update(world, &position, target);
            if (applyForces(snake->getSnake()))
                gameState = 'o';

            ground->Draw();

            ceiling->Draw();

            lWall->Draw();

            rWall->Draw();

            target->Draw();

            snake->Draw();

            display(&position, target->getPositionRef(), &window);

            if (targets > 5)
            {
                gameState = 'o';
            }
            break; }
        case 'o':
            system("CLS");
            cout << "You win! Your score: " << getScore() << endl;
            gameState = overScreen(&window);
            if (gameState == 'g')
            {
                setup(snake, target);
                targets = 0;
            }
            break;
        case 'd':
            window.close();
            break;
        }
        window.display();
    }

    cout << "Game Over!" << endl;

    //delete everything from the heap
    delete snake;
    snake = nullptr;

    delete ceiling;
    ceiling = nullptr;

    delete ground;
    ground = nullptr;

    delete lWall;
    lWall = nullptr;

    delete rWall;
    rWall = nullptr;

    delete target;
    target = nullptr;

    delete gravity;
    gravity = nullptr;

    delete world;
    world = nullptr;
}
