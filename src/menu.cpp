#include "menu.hh"
#include "multiPlayers.hh"

Menu::Menu()
{
}

Menu::~Menu()
{
}

int Menu::setWindows(int width, int height)
{
    _window.create(sf::VideoMode(width, height), "Gomoku", sf::Style::Default, _settings);
    _window.setFramerateLimit(60);
    return (0);
}

int Menu::menuLoop(Map &map, Referee &ref)
{
    while (_window.isOpen() && closeMenu == false)
    {
        while (_window.pollEvent(event))
        {
            switch (event.type)
            {
              case sf::Event::Closed:
                _window.close();
              break;
              case sf::Event::MouseButtonPressed:
                  std::cout << "click" << std::endl;
                  Game = new multiPlayers();
                  closeMenu = true;
              break;
              default:
              break;
            }
        }
        _window.clear();
        // PRINT SOMETHING HERE
        _window.display();
    }
    if (Game != NULL)
        Game->mainLoop(map, ref, _window);
    return (0);
}
