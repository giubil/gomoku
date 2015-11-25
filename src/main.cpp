#include "map.hh"
#include "referee.hh"

int main()
{
    Map yolo;
    Referee referee(&yolo);

    yolo.set_occ_case(0, 0, WHITE);
    yolo.set_occ_case(0, 1, BLACK);
    yolo.set_occ_case(1, 2, BLACK);
    yolo.set_occ_case(2, 3, BLACK);
    yolo.set_occ_case(3, 4, BLACK);
    yolo.set_occ_case(4, 5, BLACK);
    std::cout << yolo.get_occ_case(0, 1) << std::endl;
    std::cout << yolo.get_occ_case(0, 0) << std::endl;
    std::cout << yolo.get_occ_case(1, 1) << std::endl;
    yolo.print_occ_map();
    referee.calc();
    return (0);
}
