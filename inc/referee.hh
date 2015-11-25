#ifndef _REFEREE_HH
# define _REFEREE_HH

#include "map.hh"

enum player_won
{
	NONE = 0,
	WHITE_WON = 1,
	BLACK_WON = 2
};

class Referee
{
private:
	Map *_map;
	player_won five_in_a_row() const;
public:
	Referee(Map *map);
	void feed_map(Map *map);
	void calc() const;
	void set_disallowed() const;
};

#endif
