#include "Pawn.h"

Pawn::Pawn(char color, int x, int y) : Figure("pawn", color, x, y, 5) { this->first_move = true; }

void Pawn::was_moved() { this->first_move = false; }

bool Pawn::check_promotion() { return this->y == (this->color == 'w' ? 0 : 7); }

vector<pair<int, int>> Pawn::get_available_fields(shared_ptr<Figure> board[][8])
{
    vector<pair<int, int>> available_fields;
    int dir = (this->color == 'b') ? 1 : -1;

    if(this->is_valid_field(this->y+dir, this->x) && board[this->y+dir][this->x] == nullptr)
        available_fields.push_back(make_pair(this->y+dir, this->x));

    if(this->first_move)
        if(this->is_valid_field(this->y+(2*dir), this->x) && board[this->y+(2*dir)][this->x] == nullptr)
            available_fields.push_back(make_pair(this->y+(2*dir), this->x));

    if(this->is_valid_field(this->y+dir, this->x-1) && board[this->y+dir][this->x-1] != nullptr && board[this->y+dir][this->x-1]->get_color() != this->color)
        available_fields.push_back(make_pair(this->y+dir, this->x-1));

    if(this->is_valid_field(this->y+dir, this->x+1) && board[this->y+dir][this->x+1] != nullptr && board[this->y+dir][this->x+1]->get_color() != this->color)
        available_fields.push_back(make_pair(this->y+dir, this->x+1));

    return available_fields;
}
