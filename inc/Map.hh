#ifndef MAP_HH_
# define MAP_HH_

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

enum case_ref_winning
{
	NONE_WINNING = 0,
	WHITE_WINNING = 1,
	BLACK_WINNING = 2,
	WHITE_POSSIBLE = 3,
	BLACK_POSSIBLE = 4
};

typedef struct __attribute__((__packed__)) case_field {
	case_type occupancy : 2;
	case_ref_type referee : 2;
	case_ref_winning winning : 3;
} case_field;

class Map
{
public:
	const static size_t Size = 19;
private:
	case_field _map[Map::Size][Map::Size];
	void check_case_exist(unsigned x, unsigned y) const;
public:
	Map();
    Map(const Map &m);
    Map &operator=(const Map &);
	case_type get_occ_case(unsigned int x, unsigned int y) const;
	void set_occ_case(unsigned int x, unsigned int y, case_type content);
	void print_occ_map() const;
	case_ref_type get_ref_case(unsigned int x, unsigned int y) const;
	void set_ref_case(unsigned int x, unsigned int y, case_ref_type content);
	case_ref_winning get_ref_winning(unsigned int x, unsigned int y) const;
	void set_ref_winning(unsigned int x, unsigned int y, case_ref_winning content);
	void print_weighted_map() const;

};

#endif
