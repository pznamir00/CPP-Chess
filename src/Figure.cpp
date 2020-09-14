#include "Figure.h"

Figure::Figure(string name, char color, int x, int y, int left_rect) : name(name), color(color)
{
    this->x = x;
    this->y = y;
    //grafika
    int top_rect = (int)(color == 'w');
    this->texture.loadFromFile("images/figures.png", IntRect(left_rect*Figure::dimension, top_rect*Figure::dimension, Figure::dimension, Figure::dimension));
    this->sprite.setTexture(this->texture);
    this->sprite.setPosition(this->x * Figure::dimension, this->y * Figure::dimension);
}

//aktualizuje sprajta na podstawie x i y
void Figure::update_sprite() { this->sprite.setPosition(this->x * Figure::dimension, this->y * Figure::dimension); }

//pobiera kolor
char Figure::get_color() const { return this->color; }

//sprawdza czy koordyaty s¹ poprawne
bool Figure::is_valid_field(const int y, const int x) const { return x >= 0 && x < 8 && y >= 0 && y < 8; }

//ustawia nowe koordynaty
void Figure::set_coordinates(const int new_x, const int new_y)
{
    this->x = new_x;
    this->y = new_y;
    this->update_sprite();
}
