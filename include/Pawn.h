#ifndef PAWN_H
#define PAWN_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Figure.h"
using namespace std;
using namespace sf;


class Pawn : public Figure
{
private:
    bool first_move;
public:
    Pawn(char color, int x, int y);
    void was_moved();
    bool check_promotion();
    vector<pair<int, int>> get_available_fields(shared_ptr<Figure> board[][8]);
};

#endif // PAWN_H
