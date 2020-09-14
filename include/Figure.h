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
    static unsigned left_texture_rect; //liczba "która z kolei" od lewej figura na graficę figures.png
public:
    const string name;
    Sprite sprite;
    int x;
    int y;
    const static unsigned dimension = 56; //wymiar (wysokość = szerokość) 1 figury w pikselach
    Figure(string name, char color, int x, int y, int left_rect);
    char get_color() const;
    void set_coordinates(const int new_x, const int new_y);
    bool is_valid_field(const int y, const int x) const;
    void update_sprite();
    virtual vector<pair<int, int>> get_available_fields(shared_ptr<Figure> board[][8]) = 0; //zwraca dostępne dla figury pola (np. skoczek litery "L"
                                                                                            //w różnych kombinacjach jeśli pole jest puste lub jest
                                                                                            //figura przyciwnika itd.)
};

#endif // FIGURE_H
