#include "AI.hh"

AI::AI()
{
}

std::tuple<int, int, bool> const * AI::play(Map const &map, Referee &ref, sf::RenderWindow &window) const
{
    static_cast<void>(map);
    static_cast<void>(ref);
    static_cast<void>(window);

    State rootstate = State(Map(map), APlayer::BLACK, Referee(ref));
    Node rootnode = Node(&rootstate);

    Node *buff_node;
    State *buff_state;
    std::tuple<int, int> buff_move;

    for (int i = 0; i < 1000; ++i)
    {
        buff_node = &rootnode;
        buff_state = new State(rootstate);

        //Selecting
        while (buff_node->get_state()->get_moves().empty() && !buff_node->get_childs().empty())
        {
            buff_node = buff_node->get_UTC_children();
            buff_state->do_move(buff_node->get_move());
        }

        //Expanding
        if (!buff_node->get_state()->get_moves().empty())
        {
            buff_move = buff_node->get_state()->get_random_move();
            buff_state->do_move(buff_move);
            buff_node = buff_node->create_children(buff_move, buff_state);
        }

        //Rolling out
        while (!buff_state->get_moves().empty())
            buff_state->do_move(buff_state->get_random_move());

        //Backpropagating
        while (buff_node != nullptr)
        {
            if ((buff_node->get_state()->get_results() == player_won::BLACK_WON
                && buff_node->get_state()->get_turn() == APlayer::BLACK)
                || (buff_node->get_state()->get_results() == player_won::WHITE_WON
                && buff_node->get_state()->get_turn() == APlayer::WHITE))
                buff_node->update(1);
            else
                buff_node->update(0);
            buff_node = buff_node->get_parent();
        }
    }
    buff_move = rootnode.get_most_visited()->get_move();
    return (new std::tuple<int, int, bool>(std::get<0>(buff_move), std::get<1>(buff_move), true));
}

void AI::set_color(player_color c)
{
    APlayer::set_color(c);
}
