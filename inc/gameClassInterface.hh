#ifndef GAMECLASSINTERFACE_HH_
#define GAMECLASSINTERFACE_HH_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "referee.hh"

class gameClassInterface {
protected:
    sf::Event event;

    sf::Texture _textTile;
    sf::Texture _textBlack;
    sf::Texture _textWhite;
    sf::Texture _textSelectWhite;
    sf::Texture _textSelectBlack;

    std::vector<std::vector<sf::Sprite>> _tiles;

    bool playerTurn = true;
    sf::Vector2f lastSelected;

public:
    gameClassInterface();
    int mainLoop(Map&, Referee&, sf::RenderWindow &);
    virtual int eventsHandling(Map&, Referee&, sf::RenderWindow &) = 0;
};

#endif /* !GAMECLASSINTERFACE_HH_ */
