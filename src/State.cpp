#include "State.hpp"

template <> int State::second_nearby_loop<2>(bool *nearby_piece, size_t i, size_t j, int k)
{
  return (2);
}

template <> int State::first_nearby_loop<2>(bool *nearby_piece, size_t i, size_t j)
{
  return(2);
}

template<> int State::second_map_loop<Map::Size>(int i, APlayer::player_color& buff_player, std::list<std::tuple<int, int>>& ret_moves)
{
  return (Map::Size);
}

template<> int State::first_map_loop<Map::Size>(APlayer::player_color& buff_player, std::list<std::tuple<int, int>>& ret_moves)
{
  return (Map::Size);
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
    std::list<std::tuple<int, int>>::iterator end;

    if (_ref->get_winner() != player_won::NONE)
    {
        /*std::cout << "I won" << std::endl;
        _map->print_occ_map();*/
        _won = _ref->get_winner();
        _untried_moves = ret_moves;
        return ;
    }
    first_map_loop<0>(buff_player, ret_moves);
    _untried_moves = ret_moves;
    //std::cout << "Updated moves with size = " << ret_moves.size() << std::endl;
}

std::list<std::tuple<int, int>> State::get_moves()
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
    _map->print_occ_map();
}
std::list<std::tuple<int, int>> State::get_untried_moves() { return (_untried_moves);}
