#include "Game.hh"

int Game::mainLoop(Map &map, Referee &ref, sf::RenderWindow &window)
{
	while (window.isOpen())
	{
		eventsHandling(map, ref, window);
		window.clear();
		for (int i = 0; i < 19; i++)
		{
			_tiles.push_back(std::vector<sf::Sprite>());
			for (int j = 0; j < 19; j++)
			{
				window.draw(_tiles[i][j]);
			}
		}
		window.display();
		if (ref.get_winner() != NONE)
			window.close();
	}
	if (ref.get_winner() == WHITE_WON)
		std::cout << "White player won !" << std::endl;
	else if (ref.get_winner() == BLACK_WON)
		std::cout << "Black player won !" << std::endl;
	return (0);
}

int Game::eventsHandling(Map &map, Referee &ref, sf::RenderWindow &window)
{
	int x = 0;
	int y = 0;
	while (window.pollEvent(_event))
	{
		sf::Vector2i position = sf::Mouse::getPosition(window);
		sf::Vector2f worldPos = window.mapPixelToCoords(position);
		x = worldPos.x / 50;
		y = worldPos.y / 50;
		switch (_event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonPressed:
			if (_playerTurn && map.get_occ_case(x,y) == EMPTY)
			{
				map.set_occ_case(x,y, WHITE);
				_tiles[x][y].setTexture(_textWhite);
				_playerTurn = !_playerTurn;
				ref.calc();
			}
			else if (map.get_occ_case(x,y) == EMPTY)
			{
				map.set_occ_case(x,y, BLACK);
				_tiles[x][y].setTexture(_textBlack);
				_playerTurn = !_playerTurn;
				ref.calc();
			}
			break;
		default:
			break;
		}
		if (map.get_occ_case(_lastSelected.x / 50, _lastSelected.y / 50) == EMPTY)
			_tiles[_lastSelected.x / 50][_lastSelected.y / 50].setTexture(_textTile);
		if (x < 19 && x >= 0 && y < 19 && y >= 0 && map.get_occ_case(x, y) == EMPTY )
		{
			if (_playerTurn)
				_tiles[x][y].setTexture(_textSelectWhite);
			else
				_tiles[x][y].setTexture(_textSelectBlack);
			_lastSelected = worldPos;
		}
	}
	return (0);
}

void setPlayer(unsigned p, IPlayer &player)
{
	if (p >= 2)
		throw (std::runtime_error("Trying to set a player which is not the first or second"));
	_players[p] = player;
}
