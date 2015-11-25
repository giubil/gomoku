#include <exception>
#include <sstream>
#include "map.hh"

Map::Map()
{
	memset(&_map, 0, sizeof(_map));
}

case_type Map::get_occ_case(unsigned int x, unsigned int y) const
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
	return (_map[x][y].occupancy);
}

void Map::set_occ_case(unsigned int x, unsigned int y, case_type content)
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

void Map::set_ref_case(unsigned int x, unsigned int y, case_ref_type content)
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
	_map[x][y].referee = content;
}

case_ref_type Map::get_ref_case(unsigned int x, unsigned int y) const
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
	return (_map[x][y].referee);
}
