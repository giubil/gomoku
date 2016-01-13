#include "Player.hh"

std::tuple<int, int, bool> const * Player::play(Map &map, Referee &ref, sf::RenderWindow &window) const
{
	static bool aaa = false;
	static_cast<void>(map);
	static_cast<void>(ref);
	sf::Event event;
	int x = 0;
	int y = 0;
	window.pollEvent(event);
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
		std::cout << "swag" << std::endl;
		aaa = true;
		return (new std::tuple<int, int, bool>(x, y, true));
		break;
	default:
		break;
	}
	if (!aaa)
		std::cout << "yolo" << std::endl;
	return (new std::tuple<int, int, bool>(x, y, false));
}
