#include "../inc/multiPlayers.hh"

multiPlayers::multiPlayers()
{
}

multiPlayers::~multiPlayers()
{
}

int multiPlayers::mainLoop(Map &map, Referee &ref, sf::RenderWindow &_window)
{
  while (_window.isOpen())
  {
      eventsHandling(map, ref, _window);
      _window.clear();
      for (int i = 0; i < 19; i++)
      {
          _tiles.push_back(std::vector<sf::Sprite>());
          for (int j = 0; j < 19; j++)
          {
              _window.draw(_tiles[i][j]);
          }
      }
    _window.display();
    if (ref.get_winner() != NONE)
      _window.close();
  }
  if (ref.get_winner() == WHITE_WON)
    std::cout << "White player won !" << std::endl;
  else if (ref.get_winner() == BLACK_WON)
    std::cout << "Black player won !" << std::endl;
  return (0);
}

int multiPlayers::eventsHandling(Map &map, Referee &ref, sf::RenderWindow &_window)
{
  int x = 0;
  int y = 0;
  while (_window.pollEvent(event))
  {
      sf::Vector2i position = sf::Mouse::getPosition(_window);
      sf::Vector2f worldPos = _window.mapPixelToCoords(position);
      x = worldPos.x / 50;
      y = worldPos.y / 50;
      switch (event.type)
      {
        case sf::Event::Closed:
          _window.close();
        break;
        case sf::Event::MouseButtonPressed:
            if (playerTurn)
            {
                map.set_occ_case(x,y, WHITE);
                _tiles[x][y].setTexture(_textWhite);
                playerTurn = !playerTurn;
                ref.calc();
            }
            else
            {
                map.set_occ_case(x,y, BLACK);
                _tiles[x][y].setTexture(_textBlack);
                playerTurn = !playerTurn;
                ref.calc();
            }
        break;
        default:
        break;
      }
      if (map.get_occ_case(lastSelected.x / 50, lastSelected.y / 50) == EMPTY)
        _tiles[lastSelected.x / 50][lastSelected.y / 50].setTexture(_textTile);
      if (x < 19 && x >= 0 && y < 19 && y >= 0 && map.get_occ_case(x, y) == EMPTY )
      {
          if (playerTurn)
            _tiles[x][y].setTexture(_textSelectWhite);
          else
            _tiles[x][y].setTexture(_textSelectBlack);
          lastSelected = worldPos;
      }
  }
  return (0);
}
