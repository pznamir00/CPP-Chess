#ifndef ROOK_H
#define ROOK_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Figure.h"
using namespace std;
using namespace sf;


class Rook : public Figure
{
private:
    bool was_moved;
public:
    Rook(char color, int x, int y);
    void set_moved();
    bool check_moved() const;
    vector<pair<int, int>> get_available_fields(shared_ptr<Figure> board[][8]);
};

#endif // ROOK_H
