#ifndef AI_HH_
#define AI_HH_
#include <thread>
#include <SFML/Graphics.hpp>
#include "APlayer.hh"
#include "State.hh"
#include "Node.hh"

class AI : public APlayer {
    std::thread *_AI_helper;
    std::mutex *_search_done;
    APlayer::player_color *_player_turn;
    std::tuple<unsigned, unsigned> *_move;
public:
    AI();
    virtual std::tuple<int, int, bool> const * play(Map const &map, Referee &ref, sf::RenderWindow &window) const;
    void set_color(player_color c);
};

#endif /* !AI_HH_ */
