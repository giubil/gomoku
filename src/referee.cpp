#include <map>
#include <tuple>
#include "referee.hh"

#include <iostream>

Referee::Referee(Map &map) : _map(map) {
}

void Referee::feed_map(Map &map)
{
	_map = map;
}

player_won Referee::five_in_a_row() const
{
	int tab_buff[][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
	unsigned int buff_x, buff_y, buff_val;

	for (unsigned int x = 0; x < Map::Size; ++x)
		for (unsigned int y = 0; y < Map::Size; ++y)
		{
			buff_val = _map.get_occ_case(x, y);
			if (buff_val != case_type::EMPTY)
				for (size_t i = 0; i < 8; ++i)
					for (size_t j = 0; j < 5; j++)
					{
						buff_x = x + (tab_buff[i][0] * j);
						buff_y = y + (tab_buff[i][1] * j);
						if (!(buff_x >= Map::Size || buff_y >= Map::Size))
						{
							if (buff_val != _map.get_occ_case(buff_x, buff_y))
								break;
							else if (j == 4)
								return ((buff_val == case_type::WHITE) ? player_won::WHITE_WON : player_won::BLACK_WON);
						}
					}
		}
	return (player_won::NONE);
}

void Referee::calc() const
{
	std::cout << five_in_a_row() << std::endl;
}

void Referee::set_disallowed() const
{
	int tab_patern[][9] = {{1, 2, 2, 1, 1, 1, 0, 0, 0},
			       {0, 1, 2, 2, 1, 1, 0, 0, 0},
			       {0, 1, 2, 1, 1, 2, 1, 0, 0},
			       {0, 0, 1, 2, 1, 2, 1, 0, 0},
			       {0, 0, 1, 2, 1, 1, 2, 1, 0},
			       {0, 0, 0, 1, 1, 2, 2, 1, 0},
			       {0, 0, 0, 1, 1, 1, 2, 2, 1}};
	int tab_buff[][2] = {{0, -1}, {1, 0}, {1, 1}, {-1, 1}};
	unsigned buff_x, buff_y;

	for (unsigned x = 1; x < Map::Size - 1; ++x)
		for (unsigned y = 1; y < Map::Size - 1; ++y)
		{
			unsigned black = 0, white = 0;
			for (unsigned i = 1; i < 7; ++i)
			{
				for (unsigned k = 0; k <= 4; ++k)
				{
					unsigned j_max = 5 + (i / 2 + ((i % 2) ? 1 : 0));
					case_type color = EMPTY, buff_val;
					for (unsigned j = j_max - 5; j < j_max; ++j)
					{
						buff_x = x + (tab_buff[k][0] * (j - 4));
						buff_y = y + (tab_buff[k][1] * (j - 4));
						if (buff_x >= Map::Size || buff_y >= Map::Size)
							break;
						buff_val = _map.get_occ_case(buff_x, buff_y);
						if ((tab_patern[i][j] == 2 && buff_val == EMPTY)
						    || (tab_patern[i][j] == 1 && buff_val != EMPTY))
							break;
						if (tab_patern[i][j] == 2)
						{
							if (color == EMPTY)
								color = buff_val;
							else if (color != buff_val)
								break;
						}
						if (j == j_max - 1)
						{
							if (color == BLACK)
								black++;
							else
								white++;
						}
					}
					_map.set_ref_case(x, y, static_cast<case_ref_type>((black>1?DISALLOW_BLACK:0) | (white>1?DISALLOW_WHITE:0)));
				}
			}
		}
}
