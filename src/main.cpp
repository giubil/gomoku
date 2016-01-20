
#include "Map.hh"
#include "Referee.hh"
#include "Menu.hh"
#include <cstdlib>

int main()
{
	Menu menu;

	menu.setWindows(1150,950);
	menu.menuLoop();
    return (0);
}
