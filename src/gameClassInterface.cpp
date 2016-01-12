#include "gameClassInterface.hh"

gameClassInterface::gameClassInterface() {
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
};

int gameClassInterface::mainLoop(Map &map, Referee &ref, sf::RenderWindow &_window)
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
