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
        EMPTY = 0, //-
        WHITE = 1, //O
        BLACK = 2 //X
    };
    
protected:
    player_color _color;
    
public:
    virtual std::tuple<int, int, bool> const * play(Map const & map, Referee &ref, sf::RenderWindow &window) const = 0;
    void set_color(player_color c);
};

#endif /* !APLAYER_HH_ */
