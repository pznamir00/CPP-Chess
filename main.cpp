#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Figure.h"
#include "Engine.h"
#define HEIGHT 450
#define WIDTH 450
#define TITLE "Chess Game"


int main()
{
    sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), TITLE);
    window.setFramerateLimit(60);
    sf::Event e;
    Engine engine;

    while(window.isOpen())
    {
        while (window.pollEvent(e)){
            if (e.type == sf::Event::Closed)
                window.close();
        }

        engine.control->handle(window, engine);
        window.clear();
        engine.draw_all(window);
        window.display();
    }

    return 0;
}


