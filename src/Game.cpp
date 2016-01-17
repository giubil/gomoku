#include "Game.hh"

Game::Game()
: _map(*new Map()), _ref(*new Referee(_map))
{

}

int Game::mainLoop(sf::RenderWindow &window)
{
    if (_players[0] == nullptr || _players[1] == nullptr)
        throw std::runtime_error("player missing");
    _playerTurn = true;
    while (window.isOpen())
	{
		this->eventsHandling(window);
		window.clear();
		for (int i = 0; i < 19; i++)
		{
			_tiles.push_back(std::vector<sf::Sprite>());
			for (int j = 0; j < 19; j++)
			{
				window.draw(_tiles[i][j]);
			}
			window.draw(_textPlayer);
			window.draw(_textTurnPlayer);
			window.draw(_textNbCapturedPlayer1);
			window.draw(_textNbCapturedPlayer2);
			window.draw(_textCapturedPlayer1);
			window.draw(_textCapturedPlayer2);
		}
		window.display();
/*		if (_ref.get_winner() != NONE)
			window.close();*/
	}
	if (_ref.get_winner() == WHITE_WON)
		std::cout << "White player won !" << std::endl;
	else if (_ref.get_winner() == BLACK_WON)
		std::cout << "Black player won !" << std::endl;
    else
        std::cout << "nobody won !" << std::endl;
    return (0);
}

int Game::eventsHandling(sf::RenderWindow &window)
{
	unsigned p = _playerTurn ? 0 : 1, x, y;
	std::tuple<int, int, bool> const *t;
	std::vector<sf::Vector2i> itemsToClear;
	bool done = false;
    while (!done)
    {
		t = _players[p]->play(_map, _ref, window);
		if (t == nullptr)
            return (1);
        x = std::get<0>(*t);
		y = std::get<1>(*t);
		if (std::get<2>(*t))
		{
			try {
                if (_map.get_ref_case(x, y) & (_playerTurn ? DISALLOW_WHITE : DISALLOW_WHITE)
                    || _map.get_occ_case(x, y) != EMPTY)
				{
					done = false;
				}
				else
				{
					_map.set_occ_case(x, y, _playerTurn ? WHITE : BLACK);
					_tiles[x][y].setTexture(_playerTurn ? _textWhite : _textBlack);
					_ref.remove_capture_pieces(x, y);
					_ref.calc();
					itemsToClear = _ref.get_to_clean();
					for (unsigned int i = 0; i < itemsToClear.size(); i++)
					{
						_tiles[itemsToClear[i].x][itemsToClear[i].y].setTexture(_textTile);
						if (_playerTurn)
							_nbCaptured1++;
						else
							_nbCaptured2++;
					}
                    _playerTurn =! _playerTurn;
					_textNbCapturedPlayer1.setString(std::to_string(_nbCaptured1));
					_textNbCapturedPlayer2.setString(std::to_string(_nbCaptured2));
					if (_playerTurn)
						_textTurnPlayer.setString("Player White");
					else
						_textTurnPlayer.setString("Player Black");
					done = true;
				}
			} catch (std::exception) {
				done = false;
			}
		}
		else
		{
			if (_map.get_occ_case(_lastSelected.x / 50, _lastSelected.y / 50) == EMPTY)
				_tiles[_lastSelected.x / 50][_lastSelected.y / 50].setTexture(_textTile);
			if (x < 19 && y < 19 && _map.get_occ_case(x, y) == EMPTY )
			{
				if (_playerTurn)
					_tiles[x][y].setTexture(_textSelectWhite);
				else
					_tiles[x][y].setTexture(_textSelectBlack);
                _lastSelected = sf::Vector2f(x * 50, y * 50);
            }
            delete t;
        }
    }
    return (0);
}

void Game::setPlayer(unsigned p, APlayer *player)
{
    if (p >= 2)
        throw (std::invalid_argument("Trying to set a player which is not the first or second"));
    if (!player)
        throw (std::invalid_argument("Player must be different than nullptr"));
    player->set_color(APlayer::BLACK);
    player->set_map(&_map);
    _players[p] = player;
}
