#ifndef REFEREE_HH_
# define REFEREE_HH_

#include <vector>
#include <SFML/Graphics.hpp>

#include "Map.hh"

enum player_won
{
	NONE = 0,
	WHITE_WON = 1,
	BLACK_WON = 2
};

class Referee
{
private:
    std::vector<sf::Vector2i> _to_clean;
	Map *_map;
    player_won _result;
	unsigned _captured[2];
    player_won five_in_a_row();
    bool find_pattern(int direction, int (*pattern_tab)[2], int (*pattern_tab_inv)[2], unsigned int x, unsigned int y);
    void set_ref_winning_for_four() const;
public:
	Referee(Map *map);
    Referee(const Referee &);
    Referee &operator=(const Referee &);
    void feed_map(Map *map);
	void remove_capture_pieces(unsigned x, unsigned y);
	void calc(unsigned x, unsigned y);
	void set_disallowed(unsigned x, unsigned y) const;
    player_won get_winner() const;
    std::vector<sf::Vector2i> &get_to_clean();
	unsigned get_captured(int color) const;
	void print_captured() const;
	Map *get_map() const;
};

#endif
