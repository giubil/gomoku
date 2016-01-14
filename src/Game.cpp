#include "Game.hh"

int Game::mainLoop(Map &map, Referee &ref, sf::RenderWindow &window)
{
	if (_players[0] == nullptr || _players[1] == nullptr)
		throw std::runtime_error("player missing");
    _playerTurn = true;
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
    else
        std::cout << "nobody won !" << std::endl;
    return (0);
}

int Game::eventsHandling(Map &map, Referee &ref, sf::RenderWindow &window)
{
	unsigned p = _playerTurn ? 0 : 1, x, y;
	std::tuple<int, int, bool> const *t;
	bool done = false;
		t = _players[p]->play(map, ref, window);
		if (t == nullptr)
            return (1);
        x = std::get<0>(*t);
		y = std::get<1>(*t);
		if (std::get<2>(*t))
		{
			try {
				if (map.get_ref_case(x, y) & (_playerTurn ? DISALLOW_WHITE : DISALLOW_WHITE)
                    && map.get_occ_case(x, y) == EMPTY)
				{
					done = false;
				}
				else
				{
					map.set_occ_case(x, y, _playerTurn ? WHITE : BLACK);
					_tiles[x][y].setTexture(_playerTurn ? _textWhite : _textBlack);
					ref.remove_capture_pieces(x, y);
					ref.calc();
                    _playerTurn =! _playerTurn;
					done = true;
				}
			} catch (std::exception) {
				done = false;
			}
		}
		else
		{
			if (map.get_occ_case(_lastSelected.x / 50, _lastSelected.y / 50) == EMPTY)
				_tiles[_lastSelected.x / 50][_lastSelected.y / 50].setTexture(_textTile);
			if (x < 19 && y < 19 && map.get_occ_case(x, y) == EMPTY )
			{
				if (_playerTurn)
					_tiles[x][y].setTexture(_textSelectWhite);
				else
					_tiles[x][y].setTexture(_textSelectBlack);
                _lastSelected = sf::Vector2f(x * 50, y * 50);
			}
		delete t;
	}
	return (0);
}

void Game::setPlayer(unsigned p, IPlayer *player)
{
	if (p >= 2)
		throw (std::runtime_error("Trying to set a player which is not the first or second"));
	_players[p] = player;
}
