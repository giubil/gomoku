#ifndef PLAYER_HH_
#define PLAYER_HH_
#include <SFML/Graphics.hpp>
#include "APlayer.hh"

class Player : public APlayer {
public:
    virtual std::tuple<int, int, bool> const * play(Map const &map, Referee &ref, sf::RenderWindow &window) const;
    virtual player_type get_player_type() const;
};

#endif /* !PLAYER_HH_ */
