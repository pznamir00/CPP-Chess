#ifndef HETMAN_H
#define HETMAN_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Figure.h"
#include "Rook.h"
#include "Bishop.h"
using namespace std;
using namespace sf;


class Hetman : public Figure
{
private:
    static const unsigned left_texture_rect = 3;
public:
    Hetman(char color, int x, int y);
    vector<pair<int, int>> get_available_fields(shared_ptr<Figure> board[][8]);
};

#endif // HETMAN_H
