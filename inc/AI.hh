#ifndef AI_HH_
#define AI_HH_
#include <SFML/Graphics.hpp>
#include "IPlayer.hh"

class AI : public IPlayer {
public:
    virtual std::tuple<int, int, bool> const * play(Map &map, Referee &ref, sf::RenderWindow &window) const;
};

#endif /* !AI_HH_ */
