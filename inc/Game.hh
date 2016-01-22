#ifndef GAME_HH_
#define GAME_HH_

#include "AGame.hh"
#include "APlayer.hh"

class Game : public AGame {
protected:
    APlayer *_players[2];
    Map &_map;
    Referee &_ref;
public:
    Game();
    void setWindows(int width, int height);
    virtual int mainLoop(sf::RenderWindow &);
    virtual int eventsHandling(sf::RenderWindow &);
    void setPlayer(unsigned, APlayer *);
    int mainLoop(Map&, Referee&, sf::RenderWindow &);
    int eventsHandling(Map&, Referee&, sf::RenderWindow &);
    void setSuggestion(int x, int y);
};

#endif /* !GAME_HH_ */
