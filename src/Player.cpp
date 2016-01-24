#include "Player.hh"

std::tuple<int, int, bool> const * Player::play(Map const &map, Referee &ref, sf::RenderWindow &window) const
{
    std::tuple<int, int, bool> *tuple = nullptr;
    static_cast<void>(map);
    static_cast<void>(ref);
    sf::Event event;
    int x = 0;
    int y = 0;
    if (window.pollEvent(event))
    {
        sf::Vector2i position = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(position);
        x = worldPos.x / 50;
        y = worldPos.y / 50;
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                tuple = new std::tuple<int, int, bool>(x, y, true);
                break;
            default:
                tuple = new std::tuple<int, int, bool>(x, y, false);
                break;
        }
        return (tuple);
    }
    return (nullptr);
}

APlayer::player_type Player::get_player_type() const
{
    return player_type::PLAYER;
}
