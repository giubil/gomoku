#ifndef SOLOPLAYER_HH
#define SOLOPLAYER_HH

#include "gameClassInterface.hh"

class soloPlayer : public gameClassInterface {
public:
    soloPlayer ();
    ~soloPlayer ();
    void setWindows(int width, int height);
    int mainLoop(Map&, Referee&, sf::RenderWindow &);
    int eventsHandling(Map&, Referee&, sf::RenderWindow &);
};

#endif /* !SOLOPLAYER_HH */
