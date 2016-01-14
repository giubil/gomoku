#ifndef GAME_HH_
#define GAME_HH_

#include "AGame.hh"
#include "IPlayer.hh"

class Game : public AGame {
protected:
    IPlayer *_players[2];
public:
    void setWindows(int width, int height);
    int mainLoop(Map&, Referee&, sf::RenderWindow &);
    int eventsHandling(Map&, Referee&, sf::RenderWindow &);
    void setPlayer(unsigned, IPlayer *);
};

#endif /* !GAME_HH_ */
