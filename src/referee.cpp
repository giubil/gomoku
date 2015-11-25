#include "referee.hh"

Referee::Referee(Map *map) : _map(map) {}

void Referee::feed_map(Map *map)
{
    _map = map;
}

void Referee::calc() const
{
    
}
