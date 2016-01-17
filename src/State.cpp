#include "State.hh"

State::State(Map map, APlayer::player_color whose_turn, Referee ref) : _map(map), _whose_turn(whose_turn), _ref(ref), _won(player_won::NONE)
{
    _ref.feed_map(map);
}

std::list<std::tuple<int, int>> State::get_moves()
{
    APlayer::player_color buff_player;
    std::list<std::tuple<int, int>> ret_moves;

    if (_ref.get_winner() != player_won::NONE)
    {
        _won = _ref.get_winner();
        return (ret_moves);
    }
    for (size_t i = 0; i < Map::Size; ++i)
        for (size_t j = 0; j < Map::Size; ++j)
        {
            if (_map.get_occ_case(i, j) != case_type::EMPTY)
            {
                buff_player = _whose_turn == APlayer::WHITE ? APlayer::BLACK : APlayer::WHITE;
                if ((buff_player == APlayer::WHITE && _map.get_ref_case(i, j) != DISALLOW_WHITE)
                    || (buff_player == APlayer::BLACK && _map.get_ref_case(i, j) != DISALLOW_BLACK))
                    {
                        std::cout << "bushed_back" << std::endl;
                        ret_moves.push_back(std::tuple<int, int>(i, j));
                    }
            }
        }
    return (ret_moves);
}

void State::do_move(std::tuple<int, int> move)
{
    std::cout << "x = " << std::get<0>(move) << " y = " << std::get<1>(move) << std::endl;
    _map.set_occ_case(std::get<0>(move), std::get<1>(move), (_whose_turn == APlayer::WHITE ? case_type::WHITE : case_type::BLACK));
    _ref.remove_capture_pieces(std::get<0>(move), std::get<1>(move));
    _ref.calc();
    _won = _ref.get_winner();
    _whose_turn = _whose_turn == APlayer::player_color::WHITE ? APlayer::player_color::BLACK : APlayer::player_color::WHITE;
}

player_won  State::get_results()
{
    return (_won);
}

std::tuple<int, int> State::get_random_move()
{
    std::list<std::tuple<int, int>> buff_moves = get_moves();

    for (auto it = buff_moves.begin(); it != buff_moves.end(); ++it)
    {
        std::cout << "val x = " << std::get<0>(*it) << " y  = " << std::get<1>(*it) << std::endl;
    }

    auto it = buff_moves.begin();
    int length = std::rand() % buff_moves.size();


    for (int i = 0; i <= length; ++i)
        ++it;

    std::cout << "get x = " << std::get<0>(*it) << " y  = " << std::get<1>(*it) << std::endl;
    return (*it);
}

APlayer::player_color State::get_turn() const { return (_whose_turn);}
