#include <unistd.h>
#include "AI.hh"

AI::AI()
{
}

void AI::threaded_play(std::tuple<int, int, bool> *move, std::mutex *mutex, std::mutex *mutex_kill, Map const map, Referee ref) const
{
    Map *m = new Map(map);
    Referee *r = new Referee(ref);
    
    State rootstate(m, this->_color , r);
    Node rootnode = Node(&rootstate);
    
    Node *buff_node;
    Node *buff_node_child = nullptr;
    State *buff_state;
    std::srand(time(0));
    std::tuple<int, int, int> buff_move;
    unsigned buff_weight;
    player_color buff_color, buff_color_inv;
    
    for (int i = 0; i < ITER_MAX; ++i)
    {
        if (mutex_kill->try_lock())
        {
            mutex->unlock();
            return;
        }
        if (i % 10 == 0)
            std::cout << "i = " << i << std::endl;
        buff_node = &rootnode;
        buff_state = new State(rootstate);
        
        //Selecting
        while (buff_node->get_state()->get_moves_size() == 0 && !buff_node->get_childs().empty())
        {
            buff_node = buff_node->get_UTC_children();
            buff_state->do_move(buff_node->get_move());
        }
        
        //Expanding
        if (buff_state->get_moves_size() != 0)
        {
            //std::cout << "Expanding" << std::endl;
            buff_move = buff_node->get_state()->get_random_move();
            buff_state->do_move(buff_move);
            buff_node = buff_node->create_children(buff_move, buff_state);
        }
        
        //Rolling out
        
        while (buff_state->get_moves_size() != 0 && buff_state->get_depth() < MAX_DEPTH)
            buff_state->do_move(buff_state->get_random_move());
        buff_weight = 1;//std::get<2>(buff_node->get_first_child()->get_move());
        while (buff_node->get_parent() != nullptr)
        {
            //            if (buff_node->get_state()->get_results() != player_won::NONE)
            //                std::cout << buff_node->get_state()->get_results() << " won" << std::endl;
            buff_color = buff_node->get_state()->get_turn();
            buff_color_inv = buff_color == WHITE ? BLACK : WHITE;
            if (rootstate.get_ref()->get_captured(buff_color_inv) < buff_node->get_state()->get_ref()->get_captured(buff_color_inv))
            {
                buff_node->update(20, false);
            }
            if (rootstate.get_ref()->get_captured(buff_color) < buff_node->get_state()->get_ref()->get_captured(buff_color))
                buff_node->update(-20, false);
            if (((buff_state->get_results() == player_won::BLACK_WON
                  && _color == player_color::WHITE)
                 || (buff_state->get_results() == player_won::WHITE_WON
                     && _color == player_color::BLACK)) && buff_state->get_depth() < 7)
            {
                buff_state->print_map();
                if (buff_node->get_parent() != nullptr)
                    std::cout << "I lost with _color = " << _color << " and ref = " << buff_state->get_results() << " and move = " << std::get<0>(buff_node->get_move()) << "/" << std::get<1>(buff_node->get_move()) << std::endl;
                if (buff_state->get_depth() < 2)
                    buff_node->update((int)(-10000.0 / (double)buff_state->get_depth()), true); //put the visits to zero and wins to -100
                else
                    buff_node->update((int)(-100.0 / (double)buff_state->get_depth()), false); //put the visits to zero and wins to -100
                
            }
            else if ((buff_state->get_results() == player_won::BLACK_WON
                      && buff_node->get_state()->get_turn() == APlayer::BLACK)
                     || (buff_state->get_results() == player_won::WHITE_WON
                         && buff_node->get_state()->get_turn() == APlayer::WHITE))
                buff_node->update((int)((double)(MAX_DEPTH + 500) / (double)buff_state->get_depth()), false);
            else if ((buff_state->get_results() == player_won::BLACK_WON
                      && buff_node->get_state()->get_turn() == APlayer::WHITE)
                     || (buff_state->get_results() == player_won::WHITE_WON
                         && buff_node->get_state()->get_turn() == APlayer::BLACK))
                buff_node->update((int)((double)(-MAX_DEPTH - 50) / (double)buff_state->get_depth()), false);
            else
                buff_node->update(0, false);
            if (buff_node_child == nullptr)
                buff_node_child = buff_node;
            else
            {
                if (buff_node_child->get_wins() > 100 && buff_node->get_wins() > 0)
                    buff_node->set_wins(buff_node_child->get_wins() * -1);
                else if (buff_node_child->get_wins() < -100 && buff_node->get_wins() < 0)
                    buff_node->set_wins(buff_node_child->get_wins() * -1);
            }
            buff_node = buff_node->get_parent();
        }
    }
    for (auto it = rootnode.get_childs().begin(); it != rootnode.get_childs().end(); ++it)
        for (auto it_c = (*it)->get_childs().begin(); it_c != (*it)->get_childs().end(); ++it_c)
            if (((*it_c)->get_wins() > 100 && (*it)->get_wins() > 0)
                || ((*it_c)->get_wins() < -100 && (*it)->get_wins() < 0))
                (*it)->set_wins((*it_c)->get_wins() * -1);
    /*for (auto it = rootnode.get_childs().begin(); it != rootnode.get_childs().end(); ++it)
     (*it)->print_node();*/
    rootnode.tree_to_string(0);
    if (rootnode.get_most_visited() == nullptr)
    {
        std::get<0>(*move) = 9;
        std::get<1>(*move) = 9;
    }
    else
    {
        buff_move = rootnode.get_most_visited()->get_move();
        m->print_weighted_map();
        std::cout << "Returned x = " << std::get<0>(buff_move) << " y = " << std::get<1>(buff_move) << std::endl;
        std::get<0>(*move) = std::get<0>(buff_move);
        std::get<1>(*move) = std::get<1>(buff_move);
    }
    mutex->unlock();
}

std::tuple<int, int, bool> const * AI::play(Map const &map, Referee &ref, sf::RenderWindow &window) const
{
    Map m = Map(map);
    Referee r = Referee(ref);
    
    static_cast<void>(window);
    std::tuple<int, int, bool> *move = new std::tuple<int, int, bool>(0,0,true);
    std::mutex mutex;
    std::mutex mutex_kill;
    mutex.lock();
    mutex_kill.lock();
    std::thread thread_play(&AI::threaded_play, this, move, &mutex, &mutex_kill, m, r);
    sf::Event event;
    while (!mutex.try_lock())
    {
        if (window.pollEvent(event) && event.type == sf::Event::Closed)
        {
            mutex_kill.unlock();
            window.close();
        }
        usleep(100);
    }
    thread_play.join();
    return move;
}

void AI::set_color(player_color c)
{
    APlayer::set_color(c);
}

APlayer::player_type AI::get_player_type() const
{
    return player_type::AI;
}
