#include "Hetman.h"

Hetman::Hetman(char color, int x, int y) : Figure("hetman", color, x, y, left_texture_rect) {}

vector<pair<int, int>> Hetman::get_available_fields(shared_ptr<Figure> board[][8])
{
    Rook rook(this->color, this->x, this->y);
    Bishop bishop(this->color, this->x, this->y);

    vector<pair<int, int>> rF = rook.get_available_fields(board);
    vector<pair<int, int>> bF = bishop.get_available_fields(board);

    vector<pair<int, int>> available_fields;
    available_fields.reserve(rF.size() + bF.size());
    available_fields.insert(available_fields.end(), rF.begin(), rF.end());
    available_fields.insert(available_fields.end(), bF.begin(), bF.end());

    return available_fields;
}
