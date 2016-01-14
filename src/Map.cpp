#include <stdexcept>
#include <sstream>
#include "Map.hh"

Map::Map()
{
	memset(&_map, 0, sizeof(_map));
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

std::uint32_t Map::get_AI_data(unsigned x, unsigned y, case_type c) const
{
	switch (c) {
	case BLACK:
		return (_map[x][y].data_black);
	case WHITE:
		return (_map[x][y].data_white);
	default:
		throw std::out_of_range("Can't get the AI data of something not BLACK or WHITE");
	}
}

void Map::set_AI_data(unsigned x, unsigned y, case_type c, std::uint32_t value)
{
	switch (c) {
	case BLACK:
		_map[x][y].data_black = value;
	case WHITE:
		_map[x][y].data_white = value;
	default:
		throw std::out_of_range("Can't set the AI data of something not BLACK or WHITE");
	}
}
