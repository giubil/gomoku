#include "State.hh"

void print_mutex(char *mutex_name)
{
    static std::mutex m;
    std::lock_guard<std::mutex> guard(m);
    std::cout << mutex_name << std::endl;
    
}

State::State(Map *map, APlayer::player_color whose_turn, Referee *ref)
: _map(map), _ref(ref), _whose_turn(whose_turn), _won(player_won::NONE)
{
    _ref->feed_map(map);
    update_moves();
}

State::State(const State &s)
: _map(new Map(*s._map)), _ref(new Referee(*s._ref)), _whose_turn(s._whose_turn), _won(s._won)
{
    _ref->feed_map(_map);
    update_moves();
}

State &State::operator=(const State &s)
{
    return (*new State(s));
}


State::~State()
{
    delete _map;
    delete _ref;
}

void State::update_moves()
{
    APlayer::player_color buff_player;
    std::list<std::tuple<int, int>> ret_moves;
    
    
    if (_ref->get_winner() != player_won::NONE)
    {
        /*std::cout << "I won" << std::endl;
         _map->print_occ_map();*/
        _won = _ref->get_winner();
        _mutex_moves.lock();
        print_mutex("3. State.cpp:49 _mutex_moves : lock");
        _untried_moves = ret_moves;
        _mutex_moves.unlock();
        print_mutex("3. State.cpp:52 _mutex_moves : unlock");
        return ;
    }
    for (size_t i = 0; i < Map::Size; ++i)
        for (size_t j = 0; j < Map::Size; ++j)
        {
            if (_map->get_occ_case(i, j) == case_type::EMPTY)
            {
                buff_player = _whose_turn == APlayer::WHITE ? APlayer::BLACK : APlayer::WHITE;
                if ((buff_player == APlayer::WHITE && _map->get_ref_case(i, j) != DISALLOW_WHITE)
                    || (buff_player == APlayer::BLACK && _map->get_ref_case(i, j) != DISALLOW_BLACK))
                {
                    if (!(std::find(_tried_moves.begin(), _tried_moves.end(), std::tuple<int, int>(i ,j)) != _tried_moves.end()))
                    {
                        bool nearby_piece = false;
                        for (int k = -1; k < 2; ++k)
                            for (int l = -1; l < 2; ++l)
                            {
                                unsigned buff_x = i + k;
                                unsigned buff_y = j + l;
                                if (buff_x < Map::Size && buff_y < Map::Size
                                    && _map->get_occ_case(buff_x, buff_y) != case_type::EMPTY && !(k == 0 && l == 0))
                                {
                                    nearby_piece = true;
                                    k = 2;
                                    l = 2;
                                }
                            }
                        if (nearby_piece)
                            ret_moves.push_back(std::tuple<int, int>(i, j));
                    }
                }
            }
        }
//    print_mutex("State.cpp:86 _mutex_moves : lock-unlock");
    std::lock_guard<std::mutex> guard(_mutex_moves);
    _untried_moves = ret_moves;
    //std::cout << "Updated moves with size = " << ret_moves.size() << std::endl;
}

std::list<std::tuple<int, int>> &State::get_moves()
{
    return (_untried_moves);
}

void State::do_move(std::tuple<int, int> move)
{
    _map->set_occ_case(std::get<0>(move), std::get<1>(move), (_whose_turn == APlayer::WHITE ? case_type::WHITE : case_type::BLACK));
    _ref->feed_map(_map);
    _ref->calc(std::get<0>(move), std::get<1>(move));
    _won = _ref->get_winner();
    _whose_turn = _whose_turn == APlayer::player_color::WHITE ? APlayer::player_color::BLACK : APlayer::player_color::WHITE;
    //_tried_moves = std::list<std::tuple<int, int>>();
    update_moves();
}

player_won  State::get_results()
{
    return (_won);
}

std::tuple<int, int> State::get_random_move()
{
    std::lock_guard<std::mutex> guard(_mutex_moves);
    print_mutex("2. State.cpp:117 _mutex_moves : lock");
   std::list<std::tuple<int, int>>::iterator it = _untried_moves.begin();
    if (_untried_moves.size() == 0)
    {
        print_mutex("2. State.cpp:121 _mutex_moves : unlock");
        return (std::tuple<int, int>());
    }
    std::advance(it, std::rand() % _untried_moves.size());
    _tried_moves.push_back(*it);
    _untried_moves.remove(*it);
    //update_moves();
    print_mutex("2. State.cpp:128 _mutex_moves : unlock");
    return (*it);
}

void State::push_tried_move(std::tuple<int, int> move)
{
    _tried_moves.push_back(move);
}

APlayer::player_color State::get_turn() const
{
    return (_whose_turn);
}

void State::print_map() const
{
    _map->print_occ_map();
}
std::list<std::tuple<int, int>> &State::get_untried_moves()
{
    return (_untried_moves);
}

void State::lock_moves()
{
    _mutex_moves.lock();
    print_mutex("1. State.cpp:154 _mutex_moves : lock");
}

void State::unlock_moves()
{
    print_mutex("1. State.cpp:159 _mutex_moves : unlock");
    _mutex_moves.unlock();
}

