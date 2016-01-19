#include "State.hh"

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
//        std::cout << "I won" << std::endl;
        _won = _ref->get_winner();
        _untried_moves = ret_moves;
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
                                    int buff_x = i + k;
                                    int buff_y = j + l;
                                    try {
                                        if (_map->get_occ_case(buff_x, buff_y) != case_type::EMPTY && !(k == 0 && l == 0))
                                        {
                                            nearby_piece = true;
                                            k = 2;
                                            l = 2;
                                        }
                                    } catch (std::exception) {}
                                }
                            if (nearby_piece)
                                ret_moves.push_back(std::tuple<int, int>(i, j));
                        }
                    }
            }
        }
    _untried_moves = ret_moves;
}

std::list<std::tuple<int, int>> State::get_moves()
{
    return (_untried_moves);
}

void State::do_move(std::tuple<int, int> move)
{
    _map->set_occ_case(std::get<0>(move), std::get<1>(move), (_whose_turn == APlayer::WHITE ? case_type::WHITE : case_type::BLACK));
    _ref->feed_map(_map);
    _ref->remove_capture_pieces(std::get<0>(move), std::get<1>(move));
    _ref->calc();
    _won = _ref->get_winner();
    _whose_turn = _whose_turn == APlayer::player_color::WHITE ? APlayer::player_color::BLACK : APlayer::player_color::WHITE;
    _tried_moves = std::list<std::tuple<int, int>>();
    update_moves();
}

player_won  State::get_results()
{
    return (_won);
}

std::tuple<int, int> State::get_random_move()
{
    std::list<std::tuple<int, int>> buff_moves = get_moves();

    std::list<std::tuple<int, int>>::iterator it = buff_moves.begin();

    std::advance(it, std::rand() % buff_moves.size());
    _tried_moves.push_back(*it);
    _untried_moves.remove(*it);
    //update_moves();
    return (*it);
}

void State::push_tried_move(std::tuple<int, int> move)
{
    _tried_moves.push_back(move);
}

APlayer::player_color State::get_turn() const { return (_whose_turn);}

void State::print_map() const
{
//    _map->print_occ_map();
}
