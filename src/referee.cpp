#include "referee.hh"

Referee::Referee(Map *map) : _map(map) {}

void Referee::feed_map(Map *map)
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
            buff_val = _map->get_occ_case(x, y);
            if (buff_val != case_type::EMPTY)
                for (size_t i = 0; i < 8; ++i)
                    for (size_t j = 0; j < 5; j++)
                    {
                        buff_x = x + (tab_buff[i][0] * j);
                        buff_y = y + (tab_buff[i][1] * j);
                        if (!(buff_x >= Map::Size || buff_y >= Map::Size))
                        {
                            if (buff_val != _map->get_occ_case(buff_x, buff_y))
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
