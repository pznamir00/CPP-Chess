#ifndef ENGINE_H
#define ENGINE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <math.h>
#include "Figure.h"
#include "Pawn.h"
#include "Bishop.h"
#include "Knight.h"
#include "Rook.h"
#include "Hetman.h"
#include "King.h"
using namespace std;
using namespace sf;


class Engine
{
private:
    char turn;
    Texture board_texture;
    shared_ptr<Figure> active_fig;
    vector<pair<int, int>> available_fields;
    class Control {
        public: void handle(RenderWindow& window, Engine& engine);
    };
    friend class Control;

public:
    Sprite board_sprite;
    unique_ptr<Control> control;
    shared_ptr<Figure> board[8][8] = {  //inicjalizacja planszy
        {make_shared<Rook>('b',0,0), make_shared<Knight>('b',1,0), make_shared<Bishop>('b',2,0), make_shared<Hetman>('b',3,0),
         make_shared<King>('b',4,0), make_shared<Bishop>('b',5,0), make_shared<Knight>('b',6,0), make_shared<Rook>('b',7,0)},
        {make_shared<Pawn>('b',0,1), make_shared<Pawn>('b',1,1), make_shared<Pawn>('b',2,1), make_shared<Pawn>('b',3,1),
         make_shared<Pawn>('b',4,1), make_shared<Pawn>('b',5,1), make_shared<Pawn>('b',6,1), make_shared<Pawn>('b',7,1)},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {make_shared<Pawn>('w',0,6), make_shared<Pawn>('w',1,6), make_shared<Pawn>('w',2,6), make_shared<Pawn>('w',3,6),
         make_shared<Pawn>('w',4,6), make_shared<Pawn>('w',5,6), make_shared<Pawn>('w',6,6), make_shared<Pawn>('w',7,6)},
        {make_shared<Rook>('w',0,7), make_shared<Knight>('w',1,7), make_shared<Bishop>('w',2,7), make_shared<Hetman>('w',3,7),
         make_shared<King>('w',4,7), make_shared<Bishop>('w',5,7), make_shared<Knight>('w',6,7), make_shared<Rook>('w',7,7)}
    };
    Engine();
    void set_turn(const int turn);
    int get_turn() const;
    void draw_all(RenderWindow& window);
    void placed_figure(int x, int y);
    void reset_active();
    void check_spacial_actions();
    bool will_be_check_mate();
    void promotion(const Pawn* pawn, const int x, const int y);
};

#endif // ENGINE_H
