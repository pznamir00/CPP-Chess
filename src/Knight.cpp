#include "Knight.h"

Knight::Knight(char color, int x, int y) : Figure("knight", color, x, y, left_texture_rect) {}

vector<pair<int, int>> Knight::get_available_fields(shared_ptr<Figure> board[][8])
{
    vector<pair<int, int>> available_fields;

    pair<int, int> s[] = {
        make_pair(2, 1), make_pair(-2, 1), make_pair(2,-1), make_pair(-2,-1), make_pair(1, 2), make_pair(-1, 2), make_pair(-1,-2), make_pair(1,-2)
    };

    for(auto i : s){
        if(this->is_valid_field(this->y + i.first, this->x + i.second) && board[this->y + i.first][this->x + i.second] == nullptr)
            available_fields.push_back(make_pair(this->y + i.first, this->x + i.second));
        else if(this->is_valid_field(this->y + i.first, this->x + i.second) && board[this->y + i.first][this->x + i.second]->get_color() != this->color)
            available_fields.push_back(make_pair(this->y + i.first, this->x + i.second));
    }

    return available_fields;
}
