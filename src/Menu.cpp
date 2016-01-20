#include "Menu.hh"
#include "Game.hh"

#include "Player.hh"
#include "AI.hh"

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

int Menu::menuLoop()
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
                  try
                  {
                    _game = new Game();
                    //TODO : menu to choose

                    // temp
                    _game->setPlayer(0, new Player());
                    _game->setPlayer(1, new AI());
                    // !temp
                  }
                  catch (std::runtime_error e)
                  {
                    std::cout << e.what() << std::endl;
                  }
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
    if (_game != nullptr)
        _game->mainLoop(_window);
    return (0);
}
