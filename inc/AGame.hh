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
    sf::Texture _textTile;
    sf::Texture _textBlack;
    sf::Texture _textWhite;
    sf::Texture _textSelectWhite;
    sf::Texture _textSelectBlack;

    sf::Font _font;

    sf::Text _textPlayer;
    sf::Text _textTurnPlayer;
    sf::Text _textNbCapturedPlayer1;
    sf::Text _textNbCapturedPlayer2;
    sf::Text _textCapturedPlayer1;
    sf::Text _textCapturedPlayer2;

    std::vector<std::vector<sf::Sprite>> _tiles;

    bool _playerTurn = true;
    sf::Vector2f _lastSelected;
    int _nbCaptured1 = 0;
    int _nbCaptured2 = 0;

public:
    AGame();
    virtual int mainLoop(Map&, Referee&, sf::RenderWindow &) = 0;
    virtual int eventsHandling(Map&, Referee&, sf::RenderWindow &) = 0;
};

#endif /* !AGame_HH_ */
