#include "Game.hh"
#include "AI.hh"

Game::Game()
: _map(*new Map()), _ref(*new Referee(&_map))
{
}

void Game::manage_suggestion()
{
    AI ai_sugestion;
    ai_sugestion.set_map(&_map);
    std::mutex buff;
    std::tuple<int, int, bool> move(0, 0, false);
    while (!_kill_suggestion.try_lock())
    {
        _mutex_suggestion.lock();
        _suggest_slow = false;
        ai_sugestion.set_color(_playerTurn?(APlayer::WHITE):(APlayer::BLACK));
        ai_sugestion.threaded_play(&move, &buff, &_stop_suggestion, _map, _ref);
        if (_kill_suggestion.try_lock())
            return;
        else if (!_suggest_slow)
            setSuggestion(std::get<0>(move), std::get<1>(move));
        // std::cout << (_playerTurn?("WHITE"):("BLACK")) << std::endl;
        _stop_suggestion.try_lock();
        _stop_suggestion.unlock();
    }
}

int Game::mainLoop(sf::RenderWindow &window)
{
    if (_players[0] == nullptr || _players[1] == nullptr)
        throw std::runtime_error("player missing");
    _mutex_suggestion.lock();
    _kill_suggestion.lock();
    _thread_suggestion = std::thread(&Game::manage_suggestion, this);
    _playerTurn = true;
    bool previous = !_playerTurn;
    while (window.isOpen())
    {
        if (previous != _playerTurn && _stop_suggestion.try_lock()
            && _players[_playerTurn?0:1]->get_player_type() == APlayer::PLAYER)
            _mutex_suggestion.unlock();
        previous = _playerTurn;
        if (!_Win)
            this->eventsHandling(window);
        window.clear();
        window.draw(_BackGround);
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
            if (_printSuggest)
                window.draw(_Suggestion);
        }
        if (_Win)
        {
            window.draw(_rectWin);
            window.draw(_textWin);
            if (_clock.getElapsedTime().asSeconds() > 3)
            {
                _mutex_suggestion.unlock();
                _kill_suggestion.unlock();
                _stop_suggestion.unlock();
                _thread_suggestion.join();
                window.close();
                return (0);
            }

        }
        window.display();
    }
    _mutex_suggestion.unlock();
    _kill_suggestion.unlock();
    _stop_suggestion.unlock();
    _thread_suggestion.join();
    return (0);
}
void Game::setSuggestion(int x, int y)
{
    _Suggestion.setPosition(x * 50, y * 50);
    _printSuggest = true;
}

int Game::eventsHandling(sf::RenderWindow &window)
{
    unsigned p = _playerTurn ? 0 : 1, x, y;
    std::tuple<int, int, bool> const *t;
    std::vector<sf::Vector2i> itemsToClear;
    bool done = false;
    // Dismiss unwated events
    while (!done)
    {
        Map *m = new Map(_map);
        t = _players[p]->play(*m, _ref, window);
        delete m;
        if (t == nullptr)
            return (1);
        x = std::get<0>(*t);
        y = std::get<1>(*t);
        if (std::get<2>(*t))
        {
            try {
                if (_map.get_ref_case(x, y) & (_playerTurn ? DISALLOW_WHITE : DISALLOW_BLACK)
                    || _map.get_occ_case(x, y) != EMPTY)
                {
                    done = false;
                }
                else
                {
                    _map.set_occ_case(x, y, _playerTurn ? WHITE : BLACK);
                    _tiles[x][y].setTexture(_playerTurn ? _textWhite : _textBlack);
                    _ref.calc(x, y);
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
                    _suggest_slow = true;
                    _stop_suggestion.unlock();
                    _printSuggest = false;
                    if (_ref.get_winner() != NONE)
                    {
                        if (!_Win)
                            _clock.restart();
                        _Win = true;
                        if (_ref.get_winner() == WHITE_WON)
                            _textWin.setString("White player won !");
                        else if (_ref.get_winner() == BLACK_WON)
                            _textWin.setString("Black player won !");
                        else
                            _textWin.setString("nobody won !");
                        _textWin.setOrigin(_textWin.getLocalBounds().width/2.0f,_textWin.getLocalBounds().height/2.0f);
                        _rectWin.setSize(sf::Vector2f(_textWin.getLocalBounds().width + 20, _textWin.getLocalBounds().height + 20));
                        _rectWin.setOrigin(_rectWin.getLocalBounds().width/2.0f,_rectWin.getLocalBounds().height/2.0f);
                        _clock.restart();
                    }
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
