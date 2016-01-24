#include <stdexcept>
#include <sstream>
#include "Map.hh"

Map::Map()
{
	memset(&_map, 0, sizeof(_map));
}

Map::Map(const Map &m)
{
    for (unsigned i = 0; i < Map::Size; i++)
    {
        for (unsigned j = 0; j < Map::Size; j++)
        {
            this->_map[i][j] = m._map[i][j];
        }
    }
}

Map &Map::operator=(const Map &m)
{
    return *new Map(m);
}

void Map::check_case_exist(unsigned x, unsigned y) const
{
	if (x >= Map::Size || y >= Map::Size)
	{
		std::stringstream ss;
		ss << "The position ("
		   << x
		   << ", "
		   << y
		   << ") is superior than ("
		   << Map::Size
		   << ", "
		   << Map::Size
		   << ")";
		throw std::out_of_range(ss.str());
	}
}

case_type Map::get_occ_case(unsigned int x, unsigned int y) const
{
	check_case_exist(x, y);
	return (_map[x][y].occupancy);
}

void Map::set_occ_case(unsigned int x, unsigned int y, case_type content)
{
//    std::cout << "map " << this << std::endl;
    check_case_exist(x, y);
	_map[x][y].occupancy = content;
}

void Map::print_occ_map() const
{
	for (size_t y = 0; y < Map::Size; ++y)
	{
		for (size_t x = 0; x < Map::Size; ++x)
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

void Map::print_weighted_map() const
{
	for (size_t y = 0; y < Map::Size; ++y)
	{
		for (size_t x = 0; x < Map::Size; ++x)
		{
//			if (get_occ_case(x, y) == EMPTY)
				switch (get_ref_winning(x, y))
				{
				case NONE_WINNING:
					std::cout << "-";
					break;
				case WHITE_WINNING:
					std::cout << "w";
					break;
				case BLACK_WINNING:
					std::cout << "b";
					break;
				case BLACK_POSSIBLE:
					std::cout << "B";
					break;
				case WHITE_POSSIBLE:
					std::cout << "W";
					break;
				}
			// else
			// 	switch (get_occ_case(x, y))
			// 	{
			// 	case EMPTY:
			// 		std::cout << "-";
			// 		break;
			// 	case WHITE:
			// 		std::cout << "O";
			// 		break;
			// 	case BLACK:
			// 		std::cout << "X";
			// 		break;
			// 	}

		}
		std::cout << std::endl;
	}
}

void Map::set_ref_case(unsigned int x, unsigned int y, case_ref_type content)
{
	check_case_exist(x, y);
	_map[x][y].referee = content;
}

case_ref_type Map::get_ref_case(unsigned int x, unsigned int y) const
{
	check_case_exist(x, y);
	return (_map[x][y].referee);
}

case_ref_winning Map::get_ref_winning(unsigned int x, unsigned int y) const
{
	check_case_exist(x, y);
	return (_map[x][y].winning);
}

void Map::set_ref_winning(unsigned int x, unsigned int y, case_ref_winning content)
{
	check_case_exist(x, y);
	_map[x][y].winning = content;
}
