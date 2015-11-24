#include "map.hh"

int main()
{
    Map yolo;

    yolo.set_case(0, 0, WHITE);
    yolo.set_case(0, 1, BLACK);
    std::cout << yolo.get_case(0, 1) << std::endl;
    std::cout << yolo.get_case(0, 0) << std::endl;
    std::cout << yolo.get_case(1, 1) << std::endl;
    yolo.print_map();
    return (0);
}
