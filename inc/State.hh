#ifndef STATE_HH_
# define STATE_HH_
#include <list>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include "APlayer.hh"
#include "Map.hh"
#include "Referee.hh"

class State
{
    Map                             _map;
    APlayer::player_color           _whose_turn;
    Referee                         _ref;
    player_won                      _won;
    std::list<std::tuple<int, int>> _tried_moves;
    std::list<std::tuple<int, int>> _untried_moves;
    void update_moves();
public:
    State(Map map, APlayer::player_color whose_turn, Referee ref);
    std::list<std::tuple<int, int>> get_moves();
    void do_move(std::tuple<int, int> move);
    player_won  get_results();
    std::tuple<int, int> get_random_move();
    APlayer::player_color get_turn() const;
    void push_tried_move(std::tuple<int, int> move);
    void print_map() const;
};

#endif /* !STATE_HH_ */
