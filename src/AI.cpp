#include "AI.hh"

AI::AI()
{
}

std::tuple<int, int, bool> const * AI::play(Map const &map, Referee &ref, sf::RenderWindow &window) const
{
    std::srand(time(0));
    Map *m = new Map(map);
    Referee *r = new Referee(ref);

    State rootstate(m, this->_color , r);
    Node rootnode = Node(&rootstate);

    Node *buff_node;
    State *buff_state;
    std::tuple<int, int> buff_move;

    for (int i = 0; i < 2048; ++i)
    {
        if (i % 10 == 0)
            std::cout << "i = " << i << std::endl;
        buff_node = &rootnode;
        buff_state = new State(rootstate);

        //Selecting
        while (buff_node->get_state()->get_moves().empty() && !buff_node->get_childs().empty())
        {
            buff_node = buff_node->get_UTC_children();
            buff_state->do_move(buff_node->get_move());
        }

        //Expanding
        if (!buff_state->get_moves().empty())
        {
            //std::cout << "Expanding" << std::endl;
            buff_move = buff_node->get_state()->get_random_move();
            buff_state->do_move(buff_move);
            buff_node = buff_node->create_children(buff_move, buff_state);
        }

        //Rolling out

        int j = 0;

        while (!buff_state->get_moves().empty() && buff_state->get_depth() < 30)
        {
            ++j;
            buff_state->do_move(buff_state->get_random_move());
        }

        /*std::cout << "j = " << j << std::endl;
        std::cout << buff_state->get_results() << std::endl;
        buff_state->print_map();*/

        //Backpropagating
        bool updated = false;
        while (buff_node != nullptr)
        {
//            if (buff_node->get_state()->get_results() != player_won::NONE)
//                std::cout << buff_node->get_state()->get_results() << " won" << std::endl;
            if (rootstate.get_ref()->get_captured(_color) < buff_state->get_ref()->get_captured(_color)
                && buff_state->get_depth() < 2)
            {
                buff_node->update(40, false);
            }
            if (((buff_state->get_results() == player_won::BLACK_WON
                && _color == player_color::WHITE)
                || (buff_state->get_results() == player_won::WHITE_WON
                && _color == player_color::BLACK)) && buff_state->get_depth() < 7)
                {
                    buff_state->print_map();
                    if (buff_node->get_parent() != nullptr)
                        std::cout << "I lost with _color = " << _color << " and ref = " << buff_state->get_results() << " and move = " << std::get<0>(buff_node->get_move()) << "/" << std::get<1>(buff_node->get_move()) << std::endl;
                        if (buff_state->get_depth() < 4)
                            buff_node->update((int)(-10000.0 / (double)buff_state->get_depth()), true); //put the visits to zero and wins to -100
                        else
                            buff_node->update((int)(-10000.0 / (double)buff_state->get_depth()), false); //put the visits to zero and wins to -100

                }
            else if ((buff_state->get_results() == player_won::BLACK_WON
                && buff_node->get_state()->get_turn() == APlayer::BLACK)
                || (buff_state->get_results() == player_won::WHITE_WON
                && buff_node->get_state()->get_turn() == APlayer::WHITE))
                buff_node->update(5, false);
            else if ((buff_state->get_results() == player_won::BLACK_WON
                && buff_node->get_state()->get_turn() == APlayer::WHITE)
                || (buff_state->get_results() == player_won::WHITE_WON
                && buff_node->get_state()->get_turn() == APlayer::BLACK))
                buff_node->update(-1, false);
            else
                buff_node->update(1, false);
            buff_node = buff_node->get_parent();
        }
    }
    /*for (auto it = rootnode.get_childs().begin(); it != rootnode.get_childs().end(); ++it)
        (*it)->print_node();*/
    rootnode.tree_to_string(0);
    buff_move = rootnode.get_most_visited()->get_move();
    std::cout << "Returned x = " << std::get<0>(buff_move) << " y = " << std::get<1>(buff_move) << std::endl;
    return (new std::tuple<int, int, bool>(std::get<0>(buff_move), std::get<1>(buff_move), true));
}

void AI::set_color(player_color c)
{
    APlayer::set_color(c);
}
