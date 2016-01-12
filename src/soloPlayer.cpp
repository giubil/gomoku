#include "../inc/soloPlayer.hh"

soloPlayer::soloPlayer()
{
}

soloPlayer::~soloPlayer()
{
}

int soloPlayer::eventsHandling(Map &map, Referee &ref, sf::RenderWindow &_window)
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
            if (playerTurn && map.get_occ_case(x,y) == EMPTY)
            {
                map.set_occ_case(x,y, WHITE);
                _tiles[x][y].setTexture(_textWhite);
                playerTurn = !playerTurn;
                ref.calc();
                // SAY TO IA TO PLAY
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
