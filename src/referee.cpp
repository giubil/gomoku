#include "referee.hh"

Referee::Referee(Map &map) : _map(map), _result(player_won::NONE) {
}

void Referee::feed_map(Map &map)
{
	_map = map;
}

bool Referee::find_pattern(int direction, int (*pattern_tab)[2], int (*pattern_tab_inv)[2] ,unsigned int x, unsigned int y) const
{
    int tab_buff[][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
    unsigned int buff_x, buff_y;

    for (int i = 0; i < 8; ++i)
    {
        if (i % 4 != direction % 4)
        {
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 4; ++k)
                {
                    buff_x = x + (tab_buff[i][0] * (j == 0 ? pattern_tab[k][0] : pattern_tab_inv[k][0]));
                    buff_y = y + (tab_buff[i][1] * (j == 0 ? pattern_tab[k][1] : pattern_tab_inv[k][0]));
                    if (buff_x >= Map::Size || buff_y >= Map::Size)
                        break;
                    if ((j == 0 ? pattern_tab[k][1] :  pattern_tab_inv[k][1]) != _map.get_occ_case(buff_x, buff_y))
                        break;
                    else if (k == 3)
                        return (true);
                }
        }
    }
    return (false);
}

player_won Referee::five_in_a_row() const
{
    int tab_buff[][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
    unsigned int buff_x, buff_y, buff_val;

    for (unsigned int x = 0; x < Map::Size; ++x)
        for (unsigned int y = 0; y < Map::Size; ++y)
        {
            buff_val = _map.get_occ_case(x, y);
            if (buff_val != case_type::EMPTY)
            {
                int pattern_tab[][2] = {{-1, case_type::EMPTY}, {0, static_cast<int>(buff_val)}, {1, static_cast<int>(buff_val)}, {2, (buff_val == case_type::WHITE ? case_type::BLACK : case_type::WHITE)}};
                int pattern_tab_inv[][2] = {{-2, case_type::EMPTY}, {-1, static_cast<int>(buff_val)}, {0, static_cast<int>(buff_val)}, {1, (buff_val == case_type::WHITE ? case_type::BLACK : case_type::WHITE)}};
                for (size_t i = 0; i < 8; ++i)
                    for (size_t j = 0; j < 5; j++)
                    {
                        buff_x = x + (tab_buff[i][0] * j);
                        buff_y = y + (tab_buff[i][1] * j);
                        if (!(buff_x >= Map::Size || buff_y >= Map::Size))
                        {
                            if (buff_val != _map.get_occ_case(buff_x, buff_y))
                                break;
                            if (find_pattern(i , pattern_tab, pattern_tab_inv, buff_x, buff_y))
                                return (player_won::NONE);
                            else if (j == 4)
                                return ((buff_val == case_type::WHITE) ? player_won::WHITE_WON : player_won::BLACK_WON);
                        }
                    }
            }
        }
    return (player_won::NONE);
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

void Referee::calc()
{
    _result = five_in_a_row();
    set_disallowed();
}

player_won Referee::get_winner() const
{
    return (_result);
}
