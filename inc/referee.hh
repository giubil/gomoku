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
	Map &_map;
    player_won _result;
    player_won five_in_a_row() const;
    bool find_pattern(int direction, int (*pattern_tab)[2], int (*pattern_tab_inv)[2], unsigned int x, unsigned int y) const;
public:
	Referee(Map &map);
	void feed_map(Map &map);
	void calc();
	void set_disallowed() const;
    player_won get_winner() const;
};

#endif
