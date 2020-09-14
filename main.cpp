#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Figure.h"
#include "Engine.h"
#define HEIGHT 450
#define WIDTH 450
#define TITLE "Chess Game"

//klasy:
//Engine - silnik gry
//Control - sterowanie
//Figure - klasa abstrakcyjna, dla poszczególnych figur:
    //Pawn - pion
    //Rook - wie¿a
    //Knight - skoczek
    //King - król
    //Hetman - dama
    //Bishop - goniec


int main()
{
    sf::RenderWindow window(sf::VideoMode(HEIGHT, WIDTH), TITLE);
    window.setFramerateLimit(60);
    Engine engine;

    while(window.isOpen())
    {
        //sterowanie
        engine.control->handle(window, engine);
        //czyszczenie okna
        window.clear();
        //rysowanie planszy oraz wszystkich figur na niej
        engine.draw_all(window);
        //wyświetlanie
        window.display();
    }

    return 0;
}


