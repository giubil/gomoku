#include "Node.hh"

Node::Node(State *state, Node *parent, std::tuple<int, int> *move) : _parent(parent),  _wins(0), _visits(0), _state(state), _move(move)
{
}

Node *Node::create_children(std::tuple<int, int> move, State *state)
{
    Node    *child_node = new Node(state, this, new std::tuple<int, int>(move));

    _state->push_tried_move(move);
    _child_list.push_back(child_node);
    return (child_node);
}

Node *Node::get_UTC_children()
{
    _child_list.sort([](const Node *a, const Node *b){
        double a_val = (double)a->get_wins()/(double)a->get_visits()
        * sqrt(2 * log((double)a->get_parent()->get_visits()) / (double)a->get_visits());
        double b_val = (double)b->get_wins()/(double)b->get_visits()
        * sqrt(2 * log((double)b->get_parent()->get_visits()) / (double)b->get_visits());
        return (a_val > b_val ? a : b);
    });
    return (_child_list.back());
}

void Node::update(int result)
{
    _visits += 1;
    _wins += result;
}

//Getters

int     Node::get_visits() const { return (_visits);}
int     Node::get_wins() const { return (_wins);}
Node    *Node::get_parent() const { return (_parent);}
State   *Node::get_state() const { return (_state);}
const std::list<Node *> &Node::get_childs() const { return (_child_list);}
std::tuple<int, int> Node::get_move() const
{
    return (*_move);
}

Node *Node::get_most_visited()
{
    _child_list.sort([](const Node *a, const Node *b){
        return (a->get_visits() > b->get_visits() ? a : b);
    });
    return (_child_list.front());
}

void Node::print_node() const
{
    std::cout   << "Hello I am a node, my move is x = " << std::get<0>(*_move) << " y = " << std::get<1>(*_move)
                << " I got visited " << _visits << " times and I got " << _wins << std::endl;
}
