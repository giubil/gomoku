#ifndef MULTIPLAYERS_HH_
#define MULTIPLAYERS_HH_

#include "gameClassInterface.hh"

class multiPlayers : public gameClassInterface {
public:
    multiPlayers ();
    ~multiPlayers ();
    void setWindows(int width, int height);
    int mainLoop(Map&, Referee&, sf::RenderWindow &);
    int eventsHandling(Map&, Referee&, sf::RenderWindow &);
};

#endif /* !MULTIPLAYERS_HH_ */
