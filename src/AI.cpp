#include "AI.hh"

AI::AI()
{
}

void AI::threaded_play(unsigned i, State &rootstate, Node &rootnode)
{
    Node *buff_node;
    State *buff_state;
    std::tuple<int, int> buff_move;
    
    for (; i < AI::ITER_MAX; ++i)
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
        
        while (!buff_state->get_moves().empty())
        {
            ++j;
            buff_state->do_move(buff_state->get_random_move());
        }
        
        /*std::cout << "j = " << j << std::endl;
         std::cout << buff_state->get_results() << std::endl;
         buff_state->print_map();*/
        
        //Backpropagating
        while (buff_node != nullptr)
        {
            //            if (buff_node->get_state()->get_results() != player_won::NONE)
            //                std::cout << buff_node->get_state()->get_results() << " won" << std::endl;
            if ((buff_state->get_results() == player_won::BLACK_WON
                 && buff_node->get_state()->get_turn() == APlayer::BLACK)
                || (buff_state->get_results() == player_won::WHITE_WON
                    && buff_node->get_state()->get_turn() == APlayer::WHITE))
                buff_node->update(1);
            else if ((buff_state->get_results() == player_won::BLACK_WON
                      && buff_node->get_state()->get_turn() == APlayer::WHITE)
                     || (buff_state->get_results() == player_won::WHITE_WON
                         && buff_node->get_state()->get_turn() == APlayer::BLACK))
                buff_node->update(-1);
            else
                buff_node->update(0);
            buff_node = buff_node->get_parent();
        }
    }
}

std::tuple<int, int, bool> const * AI::play(Map const &map, Referee &ref, sf::RenderWindow &window) const
{
    std::srand(time(0));
    Map *m = new Map(map);
    Referee *r = new Referee(ref);
    
    State rootstate(m, this->_color , r);
    Node rootnode = Node(&rootstate);
    
    std::tuple<int, int> buff_move;
    std::vector<std::thread*> threads(AI::NB_THREAD);
    std::atomic<unsigned> iterator(0);
    for (auto it = threads.begin(); it != threads.end(); ++it)
    {
        *it = new std::thread(&AI::threaded_play, this, std::ref(iterator), rootstate, rootnode);
    }
    for (auto it = threads.begin(); it != threads.end(); ++it)
    {
        (*it)->join();
    }
    
    /*for (auto it = rootnode.get_childs().begin(); it != rootnode.get_childs().end(); ++it)
     (*it)->print_node();*/
    rootnode.tree_to_string(0);
    buff_move = rootnode.get_most_visited()->get_move();
    return (new std::tuple<int, int, bool>(std::get<0>(buff_move), std::get<1>(buff_move), true));
}

void AI::set_color(player_color c)
{
    APlayer::set_color(c);
}
