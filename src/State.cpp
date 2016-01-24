#include "State.hpp"

template <> int State::second_nearby_loop<2>(bool *nearby_piece, size_t i, size_t j, int k)
{
  (void)nearby_piece;
  (void)i;
  (void)j;
  (void)k;
  return (2);
}

template <> int State::first_nearby_loop<2>(bool *nearby_piece, size_t i, size_t j)
{
  (void)nearby_piece;
  (void)i;
  (void)j;
  return(2);
}

template<> int State::second_map_loop<Map::Size>(int i, APlayer::player_color& buff_player, std::list<std::tuple<int, int, int>>& ret_moves)
{
  (void)buff_player;
  (void)i;
  (void)ret_moves;
  return (Map::Size);
}

template<> int State::first_map_loop<Map::Size>(APlayer::player_color& buff_player, std::list<std::tuple<int, int, int>>& ret_moves)
{
  (void)buff_player;
  (void)ret_moves;
  return (Map::Size);
}

State::State(Map *map, APlayer::player_color whose_turn, Referee *ref)
: _map(map), _ref(ref), _whose_turn(whose_turn), _won(player_won::NONE), _depth(0)
{
    _depth = 0;
    _ref->feed_map(map);
    //_buff_map = new Map(_map);
    update_moves();
}

State::State(const State &s)
: _map(new Map(*s._map)), _ref(new Referee(*s._ref)), _whose_turn(s._whose_turn), _won(s._won), _depth(s._depth)
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
    std::list<std::tuple<int, int, int>> ret_moves;
    std::list<std::tuple<int, int, int>>::iterator end;

    if (_ref->get_winner() != player_won::NONE)
    {
        /*std::cout << _ref->get_winner() << " won" << std::endl;
        std::cout << "My map" << std::endl;
        _map->print_occ_map();
        std::cout << "Ref map" << std::endl;
        _ref->get_map()->print_occ_map();*/
        //_ref->print_captured();
        _won = _ref->get_winner();
        _untried_moves = ret_moves;
        return ;
    }
    first_map_loop<0>(buff_player, ret_moves);
    _untried_moves = ret_moves;
    //std::cout << "Updated moves with size = " << ret_moves.size() << std::endl;
}

int State::get_moves_size() const
{
    return (_untried_moves.size());
}

void State::do_move(std::tuple<int, int, int> move)
{
    _map->set_occ_case(std::get<0>(move), std::get<1>(move), (_whose_turn == APlayer::WHITE ? case_type::WHITE : case_type::BLACK));
    _ref->feed_map(_map);
    _ref->calc(std::get<0>(move), std::get<1>(move));
    _won = _ref->get_winner();
    _whose_turn = _whose_turn == APlayer::player_color::WHITE ? APlayer::player_color::BLACK : APlayer::player_color::WHITE;
    //_tried_moves = std::list<std::tuple<int, int>>();
    _depth += 1;
    update_moves();
}

player_won  State::get_results()
{
    return (_won);
}

std::tuple<int, int, int> State::get_random_move()
{
    std::list<std::tuple<int, int, int>>::iterator it = _untried_moves.begin();
    unsigned total_weight = 0;
    unsigned rand_chosen;

    for (; it != _untried_moves.end(); ++it)
        total_weight += std::get<2>(*it);
    rand_chosen = std::rand() % total_weight;
    total_weight = 0;
    for (it = _untried_moves.begin(); it != _untried_moves.end(); ++it)
    {
        total_weight += std::get<2>(*it);
        if (total_weight > rand_chosen)
            break;
    }
    // std::advance(it, std::rand() % _untried_moves.size());
    _tried_moves.push_back(*it);
    _untried_moves.remove(*it);
    //update_moves();
    return (*it);
}

void State::push_tried_move(std::tuple<int, int, int> move)
{
    _tried_moves.push_back(move);
}

APlayer::player_color State::get_turn() const { return (_whose_turn);}

void State::print_map() const
{
    _map->print_occ_map();
}
unsigned State::get_depth() const { return (_depth);}
Referee *State::get_ref() const { return (_ref);}
