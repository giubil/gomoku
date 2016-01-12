#ifndef AGame_HH_
#define AGame_HH_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Referee.hh"

class AGame {
protected:
    sf::Event _event;

    sf::Texture _textTile;
    sf::Texture _textBlack;
    sf::Texture _textWhite;
    sf::Texture _textSelectWhite;
    sf::Texture _textSelectBlack;

    std::vector<std::vector<sf::Sprite>> _tiles;

    bool playerTurn = true;
    sf::Vector2f lastSelected;

public:
    AGame();
    virtual int mainLoop(Map&, Referee&, sf::RenderWindow &) = 0;
    virtual int eventsHandling(Map&, Referee&, sf::RenderWindow &) = 0;
};

#endif /* !AGame_HH_ */
