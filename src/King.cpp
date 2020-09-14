#include "King.h"

King::King(char color, int x, int y) : Figure("king", color, x, y, left_texture_rect) { this->was_moved = false; }

bool King::check_moved() const { return this->was_moved; }

void King::set_moved() { this->was_moved = true; }

void King::castling(string side, shared_ptr<Figure> (&board)[8][8])
{
    int old_rook_x = side == "left" ? 0 : 7;
    int new_rook_x = side == "left" ? 3 : 5;
    Rook* rook = (Rook*)(board[this->y][old_rook_x].get());

    board[this->y][new_rook_x] = board[this->y][old_rook_x];
    board[this->y][old_rook_x] = nullptr;

    rook->set_coordinates(new_rook_x, this->y);
    rook->set_moved();
}

vector<pair<int, int>> King::get_available_fields(shared_ptr<Figure> board[8][8])
{
    vector<pair<int, int>> available_fields;

    pair<int, int> s[] = {
        make_pair(1,1), make_pair(1,0), make_pair(0,1), make_pair(-1,-1), make_pair(-1,0), make_pair(0,-1), make_pair(1,-1), make_pair(-1,1)
    };
    for(auto i : s){
        if(this->is_valid_field(this->y + i.first, this->x + i.second) && board[this->y + i.first][this->x + i.second] == nullptr)
            available_fields.push_back(make_pair(this->y + i.first, this->x + i.second));
        else if(this->is_valid_field(this->y + i.first, this->x + i.second) && board[this->y + i.first][this->x + i.second]->get_color() != this->color)
            available_fields.push_back(make_pair(this->y + i.first, this->x + i.second));
    }

    //roszady
    if(!this->was_moved)
    {
        auto check_left_side = [](int x, int y, shared_ptr<Figure> board[8][8]){
            x--;
            while(x >= 0){
                if(board[y][x] == nullptr) { x--; continue; }
                else return board[y][x]->name == "rook" && !((Rook*)board[y][x].get())->check_moved();
            }
        };
        auto check_right_side = [](int x, int y, shared_ptr<Figure> board[8][8]){
            x++;
            while(x <= 7){
                if(board[y][x] == nullptr) { x++; continue; }
                else return board[y][x]->name == "rook" && !((Rook*)board[y][x].get())->check_moved();
            }
        };

        unsigned int x = this->x, y = this->y;
        if(check_left_side(x, y, board))  available_fields.push_back(make_pair(y, x-2));
        if(check_right_side(x, y, board)) available_fields.push_back(make_pair(y, x+2));
    }

    return available_fields;
}
