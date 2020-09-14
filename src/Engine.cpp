#include "Engine.h"

Engine::Engine()
{
    this->board_texture.loadFromFile("images/board.png");
    this->board_sprite.setTexture(this->board_texture);
    this->turn = 'w';
    this->control = make_unique<Control>();
    this->init_board();
}

//na podstawie "wzoru" default_board tworzy tablicę obiektów board (wykonuje się tylko na początku gry)
void Engine::init_board()
{
    for(int i=0;i<H;i++)
    for(int j=0;j<W;j++)
    {
        char c = this->default_board[i][j] > 0 ? 'w' : 'b';
        switch(abs(this->default_board[i][j]))
        {
            case 1: this->board[i][j] = make_shared<Pawn>(c,j,i);   break;
            case 2: this->board[i][j] = make_shared<Knight>(c,j,i); break;
            case 3: this->board[i][j] = make_shared<Bishop>(c,j,i); break;
            case 4: this->board[i][j] = make_shared<Rook>(c,j,i);   break;
            case 5: this->board[i][j] = make_shared<Hetman>(c,j,i); break;
            case 6: this->board[i][j] = make_shared<King>(c,j,i);   break;
            default: this->board[i][j] = nullptr;                   break;
        }
    }
}

//rysowanie wszystkich obiektów na planszy
void Engine::draw_all(RenderWindow& window)
{
    window.draw(this->board_sprite);
    for(auto& line : this->board)
        for(auto field : line)
            if(field) window.draw(field->sprite);
}

//akcja na postawienie figury
void Engine::placed_figure(int nx, int ny)
{
    //pobiera stare koordynaty
    const int px = this->active_fig->x, py = this->active_fig->y;
    this->board[this->active_fig->y][this->active_fig->x] = nullptr;
    this->board[ny][nx] = this->active_fig;
    this->active_fig->set_coordinates(nx, ny);

    //jeśli wykonany ruch zagraża królowi, należy go cofnąć
    if(this->will_be_check_mate()){
        this->board[this->active_fig->y][this->active_fig->x] = nullptr;
        this->board[py][px] = this->active_fig;
        this->active_fig->set_coordinates(px, py);
        return;
    }

    //król nie jest zagrożony
    this->check_spacial_actions();
    this->active_fig = nullptr;
    this->available_fields.clear();
    //zmiana tury
    this->turn = this->turn == 'w' ? 'b' : 'w';
}

//dezaktywuje aktywną ("złapaną") figurę
void Engine::reset_active()
{
    this->active_fig->update_sprite();
    this->active_fig = nullptr;
    this->available_fields.clear();
}

//wykonuje promocję piona na hetmana na polu x, y
void Engine::promotion(const Pawn* pawn, const int x, const int y)
{
    this->board[y][x] = make_shared<Hetman>(pawn->get_color(), x, y);
}

//wykonuje specialne akcję po wykonanym ruchu (np. dla piona ustawia was_moved co oznacza, że pion został ruszony)
void Engine::check_spacial_actions()
{
    if(this->active_fig->name == "pawn")
    {
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

        //sprawdza czy nie została wykonana roszada (jeśli x króla jest o 2 pola dalej niż początkowy jes]go stan to trzeba przestawić wieżę zgodnie z roszadą)
        if(!king->check_moved())
        {
            if(king->x == 2) king->castling("left", board);
            if(king->x == 6) king->castling("right", board);

            king->set_moved();
        }
    }
}

//sprawdza czy z aktualnymi ustawieniami figur jest zagrożenie matem
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

//sterowanie gry
void Engine::Control::handle(RenderWindow& window, Engine& engine)
{
    while (window.pollEvent(e)){
        if (e.type == sf::Event::Closed)
            window.close();
    }

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
    else if(engine.active_fig) //aktywna figura została upuszczona
    {
        const Vector2i mousePos = Mouse::getPosition(window);
        const int nx = floor(mousePos.x / Figure::dimension),
                  ny = floor(mousePos.y / Figure::dimension);

        bool ok = false;
        for(auto field : engine.available_fields){
            if(field.first == ny && field.second == nx){
                engine.placed_figure(nx, ny);
                ok = true;
            }
        }
        //jeśli pole jest niedostępne, trzeba zresetowć figurę aktywną
        if(!ok) engine.reset_active();
    }
}
