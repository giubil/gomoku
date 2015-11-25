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

enum case_ref_type
{
	ALLOW = 0,
	DISALLOW_WHITE = 1,
	DISALLOW_BLACK = 2
};

typedef struct __attribute__((__packed__)) case_field {
	std::uint32_t data_black : 30;
	std::uint32_t data_white : 30;
	case_type occupancy : 2;
	case_ref_type referee : 2;
} case_field;

class Map
{
	const static size_t Size = 19;
private:
	case_field _map[Map::Size][Map::Size];
public:
	Map();
	case_type get_occ_case(unsigned int x, unsigned int y) const;
	void set_occ_case(unsigned int x, unsigned int y, case_type content);
	void print_occ_map() const;
	void set_ref_case(unsigned int x, unsigned int y, case_ref_type content);
	case_ref_type get_ref_case(unsigned int x, unsigned int y ) const;
};

#endif
