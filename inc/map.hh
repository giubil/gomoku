#ifndef _MAP_HH
# define _MAP_HH

#include <iostream>
#include <cstring>

enum case_type
{
	EMPTY = 0, //-
	WHITE = 1, //O
	BLACK = 2 //X
};

typedef struct __attribute__((__packed__)) case_field {
	std::uint32_t data_black : 30;
	std::uint32_t data_white : 30;
	case_type occupancy : 2;
	std::uint8_t referee : 2;
} case_field;

class Map
{
private:
	case_field _map[19][19];
public:
	Map();
	case_type get_occ_case(unsigned int x, unsigned int y) const;
	void set_occ_case(unsigned int x, unsigned int y, case_type content);
	void print_occ_map() const;
};

#endif
