#ifndef MENU_HH_
#define MENU_HH_

#include "gameClassInterface.hh"

class Menu
{
private:
    sf::RenderWindow _window;
    sf::ContextSettings _settings;
    sf::Event event;
    gameClassInterface *Game;
    bool closeMenu = false;

public:
    Menu();
    ~Menu();
    int setWindows(int width, int height);
    int menuLoop(Map &, Referee &);
};

#endif /* !MENU_HH_ */
