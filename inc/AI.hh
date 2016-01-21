#ifndef AI_HH_
#define AI_HH_
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "APlayer.hh"
#include "State.hh"
#include "Node.hh"


class AI : public APlayer {
protected:
    static const unsigned ITER_MAX = 512;
    static const unsigned NB_THREAD = 1;
    std::atomic<unsigned> _iterator;
    std::thread *_AI_helper;
    std::mutex *_search_done;
    APlayer::player_color *_player_turn;
    std::tuple<unsigned, unsigned> *_move;
public:
    AI();
    void threaded_play(State *rootstate, Node *rootnode);
    virtual std::tuple<int, int, bool> const * play(Map const &map, Referee &ref, sf::RenderWindow &window);
    void set_color(player_color c);
};

#endif /* !AI_HH_ */
