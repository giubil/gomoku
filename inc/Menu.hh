#ifndef MENU_HH_
#define MENU_HH_

#include "Game.hh"

class Menu
{
private:
    sf::RenderWindow _window;
    sf::ContextSettings _settings;
    sf::Event event;
    Game *_game;
    bool closeMenu = false;

public:
    Menu();
    ~Menu();
    int setWindows(int width, int height);
    int menuLoop(Map &, Referee &);
};

#endif /* !MENU_HH_ */
