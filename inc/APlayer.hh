#ifndef APLAYER_HH_
#define APLAYER_HH_
#include <SFML/Graphics.hpp>
#include "Map.hh"
#include "Referee.hh"

class APlayer
{
    
public:
    enum player_color
    {
        WHITE = 0,
        BLACK = 1
    };
    
protected:
    player_color _color;
    Map *_map;
public:
    virtual std::tuple<int, int, bool> const * play(Map const & map, Referee &ref, sf::RenderWindow &window) = 0;
    void set_color(player_color c);
    void set_map(Map *);
};

#endif /* !APLAYER_HH_ */
