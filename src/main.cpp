#include "map.hh"
#include "referee.hh"
#include "menu.hh"
#include <cstdlib>

int main()
{
	Map yolo;
	Referee referee(yolo);
	Menu menu;

	menu.setWindows(950,950);
	menu.menuLoop(yolo, referee);
    return (0);
}
