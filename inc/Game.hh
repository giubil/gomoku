#ifndef GAME_HH_
#define GAME_HH_

#include "AGame.hh"
#include "APlayer.hh"

class Game : public AGame {
protected:
    APlayer *_players[2];
public:
    void setWindows(int width, int height);
    int mainLoop(Map&, Referee&, sf::RenderWindow &);
    int eventsHandling(Map&, Referee&, sf::RenderWindow &);
    void setPlayer(unsigned, APlayer *);
};

#endif /* !GAME_HH_ */
