#ifndef PLAYER_HH_
#define PLAYER_HH_
#include <SFML/Graphics.hpp>
#include "IPlayer.hh"

class Player : public IPlayer {
public:
    virtual std::tuple<int, int, bool> const * play(Map &map, Referee &ref, sf::RenderWindow &window) const;
};

#endif /* !PLAYER_HH_ */
