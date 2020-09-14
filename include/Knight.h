#ifndef KNIGHT_H
#define KNIGHT_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Figure.h"
using namespace std;
using namespace sf;


class Knight : public Figure
{
private:
    static const unsigned left_texture_rect = 1;
public:
    Knight(char color, int x, int y);
    vector<pair<int, int>> get_available_fields(shared_ptr<Figure> board[][8]);
};

#endif // KNIGHT_H
