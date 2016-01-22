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
  sf::Event event;
  sf::Sprite button1;
  sf::Sprite button2;
  sf::Sprite button3;
  sf::Texture texturemulti;
  sf::Texture textureplay;
  sf::Texture texturequit;

  if(!texturemulti.loadFromFile("./ressources/multi.png"))
    {
<<<<<<< HEAD:src/menu.cpp
      std::cout << "Error load texture Background." << std::endl;
    }
  if(!texturequit.loadFromFile("./ressources/quit.png"))
    {
      std::cout << "Error load texture Background." << std::endl;
    }
  if (!textureplay.loadFromFile("./ressources/play.png"))
    {
      std::cout << "Error load texture Background." << std::endl;
    }
  button1.setTexture(textureplay);
  button2.setTexture(texturemulti);
  button3.setTexture(texturequit);

  button1.setTextureRect(sf::IntRect(250, 200, 500, 100));
  button1.setPosition(sf::Vector2f(250, 350));

  button2.setTextureRect(sf::IntRect(250, 200, 500, 100));
  button2.setPosition(sf::Vector2f(250, 550));

  button3.setTextureRect(sf::IntRect(250, 200, 500, 100));
  button3.setPosition(sf::Vector2f(250, 750));

  while (_window.isOpen() && closeMenu == false)
    {
  while (_window.pollEvent(event))
    {
  sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
  if (event.type == sf::Event::Closed)
    _window.close();
  else if (button1.getGlobalBounds().contains(mousePos.x, mousePos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
  std::cout << "ok" << std::endl;
  Game = new multiPlayers();
  closeMenu = true;
}
  else if (button3.getGlobalBounds().contains(mousePos.x, mousePos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left))
    _window.close();
}
  _window.clear();
  _window.draw(button1);
  _window.draw(button2);
  _window.draw(button3);
  _window.display();
}
  if (Game != NULL)
    Game->mainLoop(map, ref, _window);
  return (0);
=======
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
>>>>>>> 59f32eb5cc209213f682475068cfa8af6c2a15b7:src/Menu.cpp
}
