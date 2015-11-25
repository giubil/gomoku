#include <exception>
#include <sstream>
#include "map.hh"

Map::Map()
{
        memset(&_map, 0, sizeof(_map));
}

case_type Map::get_occ_case(unsigned int x, unsigned int y) const
{
        if (x >= 19 || y >= 19) {
                std::stringstream ss;
                ss << "The position ("
                   << x
                   << ", "
                   << y
                   << ") is superior than (19, 19)";
                throw std::out_of_range(ss.str());
        }
        return (_map[x][y].occupancy);
}

void Map::set_occ_case(unsigned int x, unsigned int y, case_type content)
{
        if (x >= 19 || y >= 19) {
                std::stringstream ss;
                ss << "The position ("
                   << x
                   << ", "
                   << y
                   << ") is superior than (19, 19)";
                throw std::out_of_range(ss.str());
        }
        _map[x][y].occupancy = content;
}

void Map::print_occ_map() const
{
        for (int y = 0; y < 19; ++y)
        {
                for (int x = 0; x < 19; ++x)
                {
                        switch (get_occ_case(x, y))
                        {
                        case EMPTY:
                                std::cout << "-";
                                break;
                        case WHITE:
                                std::cout << "O";
                                break;
                        case BLACK:
                                std::cout << "X";
                                break;
                        }
                }
                std::cout << std::endl;
        }
}
