#ifndef AI_HH_
#define AI_HH_
#include <SFML/Graphics.hpp>
#include "APlayer.hh"

class AI : public APlayer {
public:
    virtual std::tuple<int, int, bool> const * play(Map const &map, Referee &ref, sf::RenderWindow &window) const;
};

#endif /* !AI_HH_ */
