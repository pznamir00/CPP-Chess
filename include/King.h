#ifndef KING_H
#define KING_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Figure.h"
#include "Rook.h"
using namespace std;
using namespace sf;


class King : public Figure
{
private:
    bool was_moved;
    static const unsigned left_texture_rect = 4;
public:
    King(char color, int x, int y);
    bool check_moved() const;
    void set_moved();
    void castling(string side, shared_ptr<Figure> (&board)[8][8]);
    vector<pair<int, int>> get_available_fields(shared_ptr<Figure> board[][8]);
};


#endif // KING_H
