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
    Map                             *_map;
    //Map                             *_buff_map;
    Referee                         *_ref;
    APlayer::player_color           _whose_turn;
    player_won                      _won;
    std::list<std::tuple<int, int>> _tried_moves;
    std::list<std::tuple<int, int>> _untried_moves;
    unsigned                        _depth;
    void update_moves();
public:
    State(Map *map, APlayer::player_color whose_turn, Referee *ref);
    State(const State&);
    State &operator=(const State&);
    ~State();
    std::list<std::tuple<int, int>> get_moves();
    void do_move(std::tuple<int, int> move);
    player_won  get_results();
    std::tuple<int, int> get_random_move();
    APlayer::player_color get_turn() const;
    void push_tried_move(std::tuple<int, int> move);
    std::list<std::tuple<int, int>> get_untried_moves();
    void print_map() const;
    unsigned get_depth() const;
    Referee *get_ref() const;
};

#endif /* !STATE_HH_ */
