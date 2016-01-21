#include "Node.hh"

Node::Node(State *state, Node *parent, std::tuple<int, int> *move) : _parent(parent),  _wins(0), _visits(0), _state(state), _move(move)
{
}

Node::~Node()
{
  delete _move;
  std::list<Node *>::iterator it;
  it = _child_list.begin();
  while (it != _child_list.end())
  {
    delete *it;
    ++it;
  }
}

Node *Node::create_children(std::tuple<int, int> move, State *state)
{
    std::lock_guard<std::mutex> guard(_mutex);
    Node    *child_node = new Node(new State(*state), this, new std::tuple<int, int>(move));

    _state->push_tried_move(move);
    _child_list.push_back(child_node);
    return (child_node);
}

Node *Node::get_UTC_children()
{
    std::lock_guard<std::mutex> guard(_mutex);
    print_mutex("Node.cpp:32 _mutex : lock");
    /*auto it = _child_list.begin();

    std::advance(it, std::rand() % _child_list.size());
    return (*it);*/

    double best_value = 0;
    Node *selected = nullptr;

    for (auto it = _child_list.begin(); it != _child_list.end(); ++it)
    {
        double buff_val = ((double)(*it)->get_wins()) / ((double)(*it)->get_visits())
        * sqrt(2 * log((double)(*it)->get_parent()->get_visits()) / ((double)(*it)->get_visits()));
        if (buff_val > best_value)
        {
            best_value = buff_val;
            selected = (*it);
        }
    }
    if (selected == nullptr)
    {
        print_mutex("Node.cpp:53 _mutex : unlock");
        return _child_list.front();
    }
    print_mutex("Node.cpp:56 _mutex : unlock");
    return (selected);
    _child_list.sort([](const Node *a, const Node *b){
        double a_val = ((double)a->get_wins()) / ((double)a->get_visits())
        * sqrt(2 * log((double)a->get_parent()->get_visits()) / ((double)a->get_visits()));
        double b_val = ((double)b->get_wins()) / ((double)b->get_visits())
        * sqrt(2 * log((double)b->get_parent()->get_visits()) / ((double)b->get_visits()));
        return (a_val > b_val ? a : b);
    });
    print_mutex("Node.cpp:61 _mutex : unlock");
    return (_child_list.front());
}

void Node::update(int result)
{
    std::lock_guard<std::mutex> guard(_update_mutex);
    _visits += 1;
    _wins += result;
}

//Getters

int     Node::get_visits() const { return (_visits);}
int     Node::get_wins() const { return (_wins);}
Node    *Node::get_parent() const { return (_parent);}
State   *Node::get_state()
{
    std::lock_guard<std::mutex> guard(_state_mutex);
//    print_mutex("Node.cpp:80 _mutex : lock-unlock");
    return (_state);
}
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

void Node::print_node()
{
    std::cout << "[M:[" << std::get<0>(*_move) << ";" << std::get<1>(*_move) << "] W/V:" << _wins << "/" << _visits << " U:" << _state->get_untried_moves().size() << std::endl;
}

void Node::tree_to_string(int indent)
{
    if (indent != 0)
    {
        for (int i = 1; i < indent; ++i)
            std::cout << "    ";
        print_node();
    }
    for (auto it = _child_list.begin(); it != _child_list.end(); ++it)
        (*it)->tree_to_string(indent + 1);
}
