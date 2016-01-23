#include "Referee.hh"

Referee::Referee(Map *map) : _map(map), _result(player_won::NONE)
{
    _captured[0] = 0;
    _captured[1] = 0;
}

void Referee::feed_map(Map *map)
{
    _map = map;
}

Referee::Referee(const Referee &r)
: _map(nullptr), _result(r._result)
{
    _captured[0] = r._captured[0];
    _captured[1] = r._captured[1];
}

Referee &Referee::operator=(const Referee &r)
{
    return (*new Referee(r));
}

bool Referee::find_pattern(int direction, int (*pattern_tab)[2], int (*pattern_tab_inv)[2] ,unsigned int x, unsigned int y)
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
                    buff_y = y + (tab_buff[i][1] * (j == 0 ? pattern_tab[k][0] : pattern_tab_inv[k][0]));
                    if (buff_x >= Map::Size || buff_y >= Map::Size)
                        break;
                    if ((j == 0 ? pattern_tab[k][1] :  pattern_tab_inv[k][1]) != _map->get_occ_case(buff_x, buff_y))
                        break;
                    else if (k == 3)
                        return (true);
                }
        }
    }
    return (false);
}

player_won Referee::five_in_a_row()
{
    int tab_buff[][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
    unsigned int buff_x, buff_y, buff_val;
    bool is_breakable;
    size_t size_five, j;

    for (unsigned int x = 0; x < Map::Size; ++x)
        for (unsigned int y = 0; y < Map::Size; ++y)
        {
            _map->set_ref_winning(x, y, case_ref_winning::NONE_WINNING);
            buff_val = _map->get_occ_case(x, y);
            if (buff_val != case_type::EMPTY)
            {
                int pattern_tab[][2] = {{-1, case_type::EMPTY}, {0, static_cast<int>(buff_val)}, {1, static_cast<int>(buff_val)}, {2, (buff_val == case_type::WHITE ? case_type::BLACK : case_type::WHITE)}};
                int pattern_tab_inv[][2] = {{-2, case_type::EMPTY}, {-1, static_cast<int>(buff_val)}, {0, static_cast<int>(buff_val)}, {1, (buff_val == case_type::WHITE ? case_type::BLACK : case_type::WHITE)}};
                for (size_t i = 0; i < 8; ++i)
                {
                    size_five = 0;
                    for (j = 0; j < 5; j++)
                    {
                        size_five++;
                        buff_x = x + (tab_buff[i][0] * j);
                        buff_y = y + (tab_buff[i][1] * j);
                        if (!(buff_x >= Map::Size || buff_y >= Map::Size))
                        {
                            if (buff_val != _map->get_occ_case(buff_x, buff_y))
                                break;
                        }
                        else
                            break;
                    }
                    if (j == 5)
                    {
                        is_breakable = false;
                        for (int k = 0; k < 5; k++)
                        {
                            buff_x = x + (tab_buff[i][0] * k);
                            buff_y = y + (tab_buff[i][1] * k);
                            if (find_pattern(i, pattern_tab, pattern_tab_inv, buff_x, buff_y))
                                is_breakable = true;
                        }
                        if (!is_breakable)
                        {
                            return ((buff_val == case_type::WHITE) ? player_won::WHITE_WON : player_won::BLACK_WON);
                        }
                    }
                    else if (j == 4)
                    {
                        is_breakable = false;
/*                        for (int k = 0; k < 4; ++k)
                        {
                            buff_x = x + (tab_buff[i][0] * k);
                            buff_y = y + (tab_buff[i][1] * k);
                            if (find_pattern(i, pattern_tab, pattern_tab_inv, buff_x, buff_y))
                                is_breakable = true;
                        }*/
                        buff_x = x + (tab_buff[i][0] * -1);
                        buff_y = y + (tab_buff[i][1] * -1);
                        //std::cout << "-1 tab buff x = " << buff_x << " y = " << buff_y;
                        if (!(buff_x >= Map::Size || buff_y >= Map::Size))
                            _map->set_ref_winning(buff_x, buff_y, (buff_val == case_type::WHITE) ? case_ref_winning::WHITE_WINNING : case_ref_winning::BLACK_WINNING);
                        buff_x = x + (tab_buff[i][0] * 4);
                        buff_y = y + (tab_buff[i][1] * 4);
                        //std::cout << " 5 tab buff x = " << buff_x << "y = " << buff_y << std::endl;
                        if (!(buff_x >= Map::Size || buff_y >= Map::Size))
                            _map->set_ref_winning(buff_x, buff_y, (buff_val == case_type::WHITE) ? case_ref_winning::WHITE_WINNING : case_ref_winning::BLACK_WINNING);
                    }
                }
            }
        }
    return (player_won::NONE);
}

void Referee::set_disallowed(unsigned last_x, unsigned last_y) const
{
    int tab_patern[][9] = {{1, 2, 2, 1, 1, 1, 0, 0, 0},
        {0, 1, 2, 2, 1, 1, 0, 0, 0},
        {0, 1, 2, 1, 1, 2, 1, 0, 0},
        {0, 0, 1, 2, 1, 2, 1, 0, 0},
        {0, 0, 1, 2, 1, 1, 2, 1, 0},
        {0, 0, 0, 1, 1, 2, 2, 1, 0},
        {0, 0, 0, 1, 1, 1, 2, 2, 1}};
    int tab_buff[][2] = {{0, -1}, {1, 0}, {1, 1}, {-1, 1}};
    unsigned buff_x, buff_y,
    max_x = last_x + 5>Map::Size?(Map::Size-1):(last_x+5),
    max_y = last_y + 5>Map::Size?(Map::Size-1):(last_y+5),
    min_x = last_x - 5>Map::Size?1:(last_x-5),
    min_y = last_y - 5>Map::Size?1:(last_y-5);

    for (unsigned x = min_x; x < max_x; ++x)
    {
        for (unsigned y = min_y; y < max_y; ++y)
        {
            unsigned volatile black = 0;
            unsigned volatile white = 0;
            if (_map->get_occ_case(x, y) == EMPTY)
            {
                for (unsigned i = 1; i < 7; ++i)
                {
                    for (unsigned k = 0; k < 4; ++k)
                    {
                        unsigned j_max = 5 + (i / 2 + ((i % 2) ? 1 : 0));
                        case_type buff_val, color = EMPTY;
                        for (unsigned j = j_max - 5; j < j_max; ++j)
                        {
                            buff_x = x + (tab_buff[k][0] * (j - 4));
                            buff_y = y + (tab_buff[k][1] * (j - 4));
                            if (buff_x >= Map::Size || buff_y >= Map::Size)
                                break;
                            buff_val = _map->get_occ_case(buff_x, buff_y);
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
                                    black += 1;
                                else if (color == WHITE)
                                    white += 1;
                            }
                        }
                    }
                }
            }
            _map->set_ref_case(x, y, static_cast<case_ref_type>((black>1?DISALLOW_BLACK:0) | (white>1?DISALLOW_WHITE:0)));
        }
    }
}

void Referee::remove_capture_pieces(unsigned x, unsigned y)
{
    int tab_patern[] = {2, 2, 1};
    int tab_buff[][2] = {{0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}};
    unsigned buff_x, buff_y;
    case_type color = _map->get_occ_case(x, y);

    _to_clean.clear();
    if (color == EMPTY)
        return;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 1; j < 4; j++)
        {
            buff_x = x + (tab_buff[i][0] * j);
            buff_y = y + (tab_buff[i][1] * j);
            if (buff_x >= Map::Size || buff_y >= Map::Size)
                break;
            case_type buff = _map->get_occ_case(buff_x, buff_y);
            if ((tab_patern[j - 1] == 2 && (buff == EMPTY || buff == color))
                || (tab_patern[j - 1] == 1 && (buff != color)))
                break;
            else if (j == 3)
            {
                _to_clean.push_back(sf::Vector2i(x + (tab_buff[i][0]), y + (tab_buff[i][1])));
                _map->set_occ_case(_to_clean.back().x, _to_clean.back().y, EMPTY);
                _to_clean.push_back(sf::Vector2i(x + (tab_buff[i][0] * 2), y + (tab_buff[i][1] * 2)));
                _map->set_occ_case(_to_clean.back().x, _to_clean.back().y, EMPTY);
                _captured[color - 1]++;
            }
        }
    }
}

void Referee::calc(unsigned x, unsigned y)
{
    remove_capture_pieces(x, y);
    _result = five_in_a_row();
    set_disallowed(x, y);
}

player_won Referee::get_winner() const
{
    if (_captured[0] >= 5)
        return WHITE_WON;
    else if (_captured[1] >= 5)
        return BLACK_WON;
    else
        return (_result);
}

std::vector<sf::Vector2i> &Referee::get_to_clean()
{
    return _to_clean;
}

void Referee::print_captured() const
{
    std::cout << "White : " << _captured[0] << " Black : " << _captured[1] << std::endl;
}

Map *Referee::get_map() const { return (_map);}
unsigned Referee::get_captured(int color) const
{
    return (_captured[color]);
}
