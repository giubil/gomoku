#include "Map.hh"
#include "Referee.hh"
#include "Menu.hh"
#include <cstdlib>

int main()
{
	Map yolo;
	Referee referee(yolo);
	Menu menu;

	menu.setWindows(1150,950);
	menu.menuLoop(yolo, referee);
    return (0);
}
