#include "map.hh"
#include "referee.hh"
#include "multiPlayers.hh"
#include <cstdlib>

int main()
{
	Map yolo;
	Referee referee(yolo);
	multiPlayers Graphics;

	Graphics.setWindows(950,950);
	Graphics.mainLoop(yolo, referee);
    return (0);
}
