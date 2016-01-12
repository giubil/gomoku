#ifndef GAME_HH_
#define GAME_HH_

#include "AGame.hh"

class Game : public AGame {
public:
    void setWindows(int width, int height);
    int mainLoop(Map&, Referee&, sf::RenderWindow &);
    int eventsHandling(Map&, Referee&, sf::RenderWindow &);
};

#endif /* !GAME_HH_ */
