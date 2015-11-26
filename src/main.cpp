#include "map.hh"
#include "referee.hh"
#include <cstdlib>

int main()
{
	Map yolo;
	Referee referee(yolo);

    yolo.set_occ_case(1, 0, BLACK);
    yolo.set_occ_case(1, 1, BLACK);
    yolo.set_occ_case(1, 2, BLACK);
    yolo.set_occ_case(2, 3, BLACK);
    yolo.set_occ_case(1, 3, BLACK);
    yolo.set_occ_case(3, 3, WHITE);
    yolo.set_occ_case(1, 4, BLACK);
    yolo.print_occ_map();
    referee.calc();
    return (0);
}
