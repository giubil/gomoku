
#include "Map.hh"
#include "Referee.hh"
#include "Menu.hh"
#include <cstdlib>
#include <iostream>

int main()
{
    Menu menu;
    
    menu.setWindows(1150,950);
    try {
        menu.menuLoop();
    } catch (std::exception e)
    {
        std::cerr << e.what() << std::endl;
    }
    
    return (0);
}
