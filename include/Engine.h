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
#define H 8
#define W 8
using namespace std;
using namespace sf;


class Engine
{
private:
    char turn; //tura
    Texture board_texture; //tekstura planszy
    shared_ptr<Figure> active_fig; //aktywna/z³apana figura
    vector<pair<int, int>> available_fields; //pola dostêpne dla aktywnej figury
    class Control {
        private: Event e;
        public: void handle(RenderWindow& window, Engine& engine);
    };
    friend class Control;
    const int default_board[H][W] = { //domyœlny "wzór" planszy
        {-4,-2,-3,-5,-6,-3,-2,-4},
        {-1,-1,-1,-1,-1,-1,-1,-1},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 0, 0, 0, 0, 0, 0, 0, 0},
        { 1, 1, 1, 1, 1, 1, 1, 1},
        { 4, 2, 3, 5, 6, 3, 2, 4}
    };
    void init_board();
public:
    Sprite board_sprite; //sprajt planszy
    unique_ptr<Control> control;
    shared_ptr<Figure> board[H][W]; //plansza
    Engine();
    void draw_all(RenderWindow& window);
    void placed_figure(int x, int y);
    void reset_active();
    void check_spacial_actions();
    bool will_be_check_mate();
    void promotion(const Pawn* pawn, const int x, const int y);
};

#endif // ENGINE_H
