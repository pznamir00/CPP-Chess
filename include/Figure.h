#ifndef FIGURE_H
#define FIGURE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
using namespace std;
using namespace sf;


class Figure
{
protected:
    Texture texture;
    const char color; //przyjmuje wartoœci 'w' i 'b'
    void update_sprite();
public:
    const string name;
    Sprite sprite;
    int x;
    int y;
    const static unsigned dimension = 56;
    Figure(string name, char color, int x, int y, int left_rect);
    char get_color() const;
    void set_coordinates(const int new_x, const int new_y);
    bool is_valid_field(const int y, const int x) const;
    virtual vector<pair<int, int>> get_available_fields(shared_ptr<Figure> board[][8]) = 0;
};

#endif // FIGURE_H
