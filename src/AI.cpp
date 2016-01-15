#include "AI.hh"

AI::AI()
{
}

std::tuple<int, int, bool> const * AI::play(Map const &map, Referee &ref, sf::RenderWindow &window) const
{
    static_cast<void>(map);
    static_cast<void>(ref);
    static_cast<void>(window);
    return (new std::tuple<int, int, bool>(rand()%19, rand()%19, true));
}

void AI::set_color(player_color c)
{
    APlayer::set_color(c);
}
