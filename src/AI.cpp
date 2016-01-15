#include "AI.hh"

std::tuple<int, int, bool> const * AI::play(Map const &map, Referee &ref, sf::RenderWindow &window) const
{
    static_cast<void>(map);
    static_cast<void>(ref);
    static_cast<void>(window);
    return (new std::tuple<int, int, bool>(rand()%19, rand()%19, true));
}
