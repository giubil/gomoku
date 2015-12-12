#include "../inc/multiPlayers.hh"

multiPlayers::multiPlayers()
{
    int x = 0;
    int y = 0;
    sf::Sprite mem;
    if (!_textTile.loadFromFile("./ressources/Case.png"))
        std::cout << "Failed to load case texture!" << std::endl;
    if (!_textBlack.loadFromFile("./ressources/CaseBlack.png"))
        std::cout << "Failed to load blacktile texture!" << std::endl;
    if (!_textWhite.loadFromFile("./ressources/CaseWhite.png"))
        std::cout << "Failed to load whitetile texture!" << std::endl;
    if (!_textSelectWhite.loadFromFile("./ressources/CaseSelectorWhite.png"))
        std::cout << "Failed to load whiteselector texture" << std::endl;
    if (!_textSelectBlack.loadFromFile("./ressources/CaseSelectorBlack.png"))
        std::cout << "Failed to load blackselector texture" << std::endl;

    mem.setPosition(x, y);
    mem.setTexture(_textTile);
    for (int i = 0; i < 19; i++)
    {
        y = 0;
        _tiles.push_back(std::vector<sf::Sprite>());
        for (int j = 0; j < 19; j++)
        {
            mem.setPosition(x, y);
            y += 50;
            _tiles[_tiles.size() - 1].push_back(mem);
        }
        x += 50;
    }
    lastSelected.x = 0;
    lastSelected.y = 0;
}

multiPlayers::~multiPlayers()
{
}

void multiPlayers::setWindows(int width, int height)
{
    _window.create(sf::VideoMode(width, height), "Zappy_Graphics", sf::Style::Default, _settings);
    sf::RenderWindow window(sf::VideoMode(width, height), "Zappy_Graphics");
    _window.setFramerateLimit(60);
}

int multiPlayers::mainLoop(Map &map, Referee &ref)
{
  while (_window.isOpen())
  {
      eventsHandling(map, ref);
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
  else
    std::cout << "Black player won !" << std::endl;
  return (0);
}

int multiPlayers::eventsHandling(Map &map, Referee &ref)
{
  while (_window.pollEvent(event))
  {
      sf::Vector2i position = sf::Mouse::getPosition(_window);
      sf::Vector2f worldPos = _window.mapPixelToCoords(position);
      int x = worldPos.x / 50;
      int y = worldPos.y / 50;
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
      if (map.get_occ_case(x, y) == EMPTY && x < 19 && x >= 0 && y < 19 && y >= 0)
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
