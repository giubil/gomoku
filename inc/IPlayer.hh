#ifndef IPLAYER_HH_
#define IPLAYER_HH_
#include <SFML/Graphics.hpp>
#include "Map.hh"
#include "Referee.hh"

class IPlayer {
public:
    virtual std::tuple<int, int, bool> const * play(Map &map, Referee &ref, sf::RenderWindow &window) const = 0;
};

#endif /* !IPLAYER_HH_ */
