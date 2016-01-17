#ifndef NODE_HH_
#define NODE_HH_
#include <list>
#include <stdlib.h>
#include <cmath>
#include "APlayer.hh"
#include "State.hh"

class Node
{
    Node                            *_parent;
    std::list<Node *>               _child_list;
    int                             _wins;
    int                             _visits;
    State                           *_state;
    std::tuple<int, int>            *_move;
public:
    Node(State *state, Node *parent=nullptr, std::tuple<int, int> *move=nullptr);
    Node *create_children(std::tuple<int, int> move, State *state);
    void update(int result);
    Node *get_UTC_children();
    int get_wins() const;
    int get_visits() const;
    Node *get_parent() const;
    State *get_state() const;
    const std::list<Node *> &get_childs() const;
    std::tuple<int, int> get_move() const;
    Node *get_most_visited();
};

#endif /* !NODE_HH_ */
