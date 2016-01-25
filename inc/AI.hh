#ifndef AI_HH_
#define AI_HH_
#include <thread>
#include <mutex>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "APlayer.hh"
#include "State.hpp"
#include "Node.hh"

# define MAX_DEPTH 15
# define ITER_MAX 1024

class AI : public APlayer {
public:
    void threaded_play(std::tuple<int, int, bool> *move, std::mutex *mutex, std::mutex *mutex_kill, Map const map, Referee ref) const;
    AI();
    virtual std::tuple<int, int, bool> const * play(Map const &map, Referee &ref, sf::RenderWindow &window) const;
    void set_color(player_color c);
    virtual player_type get_player_type() const;
};

#endif /* !AI_HH_ */
