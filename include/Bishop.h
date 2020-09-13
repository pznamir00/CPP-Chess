#ifndef BISHOP_H
#define BISHOP_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Figure.h"
using namespace std;
using namespace sf;


class Bishop : public Figure
{
public:
    Bishop(char color, int x, int y);
    vector<pair<int, int>> get_available_fields(shared_ptr<Figure> board[][8]);
};

#endif // BISHOP_H
