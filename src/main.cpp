#include "map.hh"

int main()
{
    Map yolo;

    yolo.set_occ_case(0, 0, WHITE);
    yolo.set_occ_case(0, 1, BLACK);
    yolo.set_occ_case(10, 1100, BLACK);
    std::cout << yolo.get_occ_case(0, 1) << std::endl;
    std::cout << yolo.get_occ_case(0, 0) << std::endl;
    std::cout << yolo.get_occ_case(1, 1) << std::endl;
    yolo.print_occ_map();
    return (0);
}
