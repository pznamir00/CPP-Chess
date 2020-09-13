#include "Engine.h"

Engine::Engine()
{
    this->board_texture.loadFromFile("images/board.png");
    this->board_sprite.setTexture(this->board_texture);
    this->turn = 'w';
    this->control = make_unique<Control>();
}

void Engine::set_turn(const int turn){ this->turn = turn; }

int Engine::get_turn() const { return this->turn; }

void Engine::draw_all(RenderWindow& window)
{
    window.draw(this->board_sprite);
    for(auto& line : this->board)
        for(auto field : line)
            if(field) window.draw(field->sprite);
}

void Engine::placed_figure(int x, int y)
{
    const int px = this->active_fig->x, py = this->active_fig->y;
    this->board[this->active_fig->y][this->active_fig->x] = nullptr;
    this->board[y][x] = this->active_fig;
    this->active_fig->set_coordinates(x, y);
    if(this->will_be_check_mate()){
        //zrobiony ruch grozi matem, więc należy go cofnąć
        this->board[this->active_fig->y][this->active_fig->x] = nullptr;
        this->board[py][px] = this->active_fig;
        this->active_fig->set_coordinates(px, py);
        return;
    }

    this->check_spacial_actions();
    this->active_fig = nullptr;
    this->available_fields.clear();
    //zmiana tury
    this->set_turn(this->turn == 'w' ? 'b' : 'w');
}

void Engine::reset_active()
{
    this->active_fig->set_coordinates(this->active_fig->x, this->active_fig->y);
    this->active_fig = nullptr;
    this->available_fields.clear();
}

void Engine::promotion(const Pawn* pawn, const int x, const int y)
{
    this->board[y][x] = make_shared<Hetman>(pawn->get_color(), x, y);
}

void Engine::check_spacial_actions()
{
    if(this->active_fig->name == "pawn")
    {
        //pion został ruszony
        Pawn* pawn = (Pawn*)this->active_fig.get();
        pawn->was_moved();
        if(pawn->check_promotion())
            this->promotion(pawn, this->active_fig->x, this->active_fig->y);
    }
    if(this->active_fig->name == "rook")
    {
        Rook* rook = (Rook*)this->active_fig.get();
        rook->set_moved();
    }
    if(this->active_fig->name == "king")
    {
        King* king = (King*)this->active_fig.get();

        if(!king->check_moved())
        {
            if(king->x == 2) king->castling("left", board);
            if(king->x == 6) king->castling("right", board);

            king->set_moved();
        }
    }
}

bool Engine::will_be_check_mate()
{
    auto get_king_coords = [this](){
        for(auto& line : this->board)
            for(auto figure : line)
                if(figure != nullptr && figure->name == "king" && figure->get_color() == this->turn)
                    return make_pair(figure->x, figure->y);
    };

    vector<pair<int, int>> eF;
    for(auto& line : this->board)
        for(auto figure : line)
            if(figure != nullptr)
                if(figure->get_color() != this->turn){
                    vector<pair<int, int>> fF = figure->get_available_fields(this->board);
                    eF.insert(eF.end(), fF.begin(), fF.end());
                }

    pair<int, int> kC = get_king_coords();
    for(int i=0;i<eF.size();i++)
        if(eF[i].first == kC.second && eF[i].second == kC.first)
            return true;

    return false;
}

void Engine::Control::handle(RenderWindow& window, Engine& engine)
{
    if(Mouse::isButtonPressed(Mouse::Left))
    {
        for(auto& line : engine.board)
        for(auto figure : line){
            if(figure){
                if(figure->sprite.getGlobalBounds().contains(window.mapPixelToCoords(Mouse::getPosition(window)))){
                    //klikniêto na figurê
                    if(engine.active_fig == nullptr && figure->get_color() == engine.turn){
                        engine.active_fig = figure;
                        engine.available_fields = figure->get_available_fields(engine.board);
                    }
                }
                if(engine.active_fig == figure){
                    const Vector2i mousePos = Mouse::getPosition(window);
                    figure->sprite.setPosition(mousePos.x - Figure::dimension/2, mousePos.y - Figure::dimension/2);
                }
            }
        }
    }
    else if(engine.active_fig)
    {
        //figure została puszczona
        const Vector2i mousePos = Mouse::getPosition(window);
        const int nx = floor(mousePos.x / Figure::dimension),
                  ny = floor(mousePos.y / Figure::dimension);

        bool valid = false;
        for(auto field : engine.available_fields){
            if(field.first == ny && field.second == nx){
                engine.placed_figure(nx, ny);
                valid = true;
            }
        }
        if(!valid) engine.reset_active();
    }
}
