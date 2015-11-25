#ifndef _REFEREE_HH
# define _REFEREE_HH

#include "map.hh"

class Referee
{
private:
    Map *_map;
public:
    Referee(Map *map);
    void feed_map(Map *map);
    void calc() const;
};

#endif
