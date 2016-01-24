#ifndef STATE_HPP_
# define STATE_HPP_
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
    Referee                         *_ref;
    APlayer::player_color           _whose_turn;
    player_won                      _won;
    std::list<std::tuple<int, int, int>> _tried_moves;
    std::list<std::tuple<int, int, int>> _untried_moves;
    unsigned                        _depth;
    void update_moves();
    template <int L> int second_nearby_loop(bool *nearby_piece, size_t i, size_t j, int k)
    {
      unsigned buff_x = i + k;
      unsigned buff_y = j + L;
      if (buff_x < Map::Size && buff_y < Map::Size
          && _map->get_occ_case(buff_x, buff_y) != case_type::EMPTY && !(k == 0 && L == 0))
      {
          *nearby_piece = true;
          k = 2;
          return (2);
      }
      if (L < 2)
        return (second_nearby_loop<L + 1>(nearby_piece, i, j, k));
      else
        return (2);
    };

    template <int K> int first_nearby_loop(bool *nearby_piece, size_t i, size_t j)
    {
      if (second_nearby_loop<-1>(nearby_piece, i, j, K) < 2)
        return (first_nearby_loop<K + 1>(nearby_piece, i, j));
      else
        return (2);
    };
    template <int J>int second_map_loop(int i, APlayer::player_color& buff_player, std::list<std::tuple<int, int, int>>& ret_moves)
    {
      std::list<std::tuple<int, int, int>>::iterator end;
      case_ref_winning buff_color;
      if (J < Map::Size)
      {
        if (_map->get_occ_case(i, J) == case_type::EMPTY)
        {
            buff_player = _whose_turn == APlayer::WHITE ? APlayer::BLACK : APlayer::WHITE;
            int buff_ref = _map->get_ref_case(i, J);
            if ((buff_player == APlayer::WHITE && buff_ref != DISALLOW_WHITE)
                || (buff_player == APlayer::BLACK && buff_ref != DISALLOW_BLACK))
                {
                    if (!(std::find(_tried_moves.begin(), _tried_moves.end(), std::tuple<int, int, int>(i ,J, 1)) != _tried_moves.end()) && !(std::find(_tried_moves.begin(), _tried_moves.end(), std::tuple<int, int, int>(i ,J, 100)) != _tried_moves.end()))
                    {
                        buff_color = _map->get_ref_winning(i, J);
                        if (buff_color == WHITE_WINNING || buff_color == BLACK_WINNING)
                        {
                            ret_moves.push_back(std::tuple<int, int, int>(i, J, 1000));
                        }
                        else if (buff_color != NONE_WINNING)
                        {
                            if ((buff_color == WHITE_POSSIBLE && _whose_turn == APlayer::player_color::WHITE)
                            || (buff_color == BLACK_POSSIBLE && _whose_turn == APlayer::player_color::BLACK))
                                ret_moves.push_back(std::tuple<int, int, int>(i, J, 200));
                            else
                                ret_moves.push_back(std::tuple<int, int, int>(i, J, 100));
                        }
                        else
                        {
                            bool nearby_piece = false;
                            for (int k = -1; k < 2; ++k)
                                for (int l = -1; l < 2; ++l)
                                {
                                    unsigned buff_x = i + k;
                                    unsigned buff_y = J + l;
                                    if (buff_x < Map::Size && buff_y < Map::Size
                                        && !(k == 0 && l == 0)
                                        && _map->get_occ_case(buff_x, buff_y) != case_type::EMPTY)
                                    {
                                        nearby_piece = true;
                                        k = 2;
                                        l = 2;
                                    }
                                }
                            if (nearby_piece)
                                ret_moves.push_back(std::tuple<int, int, int>(i, J, 1));
                        }
                    }
                }
        }
        return (second_map_loop<J + 1>(i, buff_player, ret_moves));
      }
      else
        return (Map::Size);
    };
    template <int I>int first_map_loop(APlayer::player_color& buff_player, std::list<std::tuple<int, int, int>>& ret_moves)
    {
      if (I < Map::Size)
      {
        if ((unsigned)second_map_loop<0>(I, buff_player, ret_moves) > Map::Size)
            return (Map::Size);
        return (first_map_loop<I + 1>(buff_player, ret_moves));
      }
      else
        return (Map::Size);
    };

public:
    State(Map *map, APlayer::player_color whose_turn, Referee *ref);
    State(const State&);
    State &operator=(const State&);
    ~State();
    void do_move(std::tuple<int, int, int> move);
    player_won  get_results();
    std::tuple<int, int, int> get_random_move();
    APlayer::player_color get_turn() const;
    void push_tried_move(std::tuple<int, int, int> move);
    void print_map() const;
    unsigned get_depth() const;
    Referee *get_ref() const;
    int get_moves_size() const;
};

#endif /* !STATE_HPP_ */
