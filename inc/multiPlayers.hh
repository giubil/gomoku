#ifndef MULTIPLAYERS_HH
#define MULTIPLAYERS_HH

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "referee.hh"

class multiPlayers {
private:
    sf::RenderWindow _window;
    sf::ContextSettings _settings;
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
    multiPlayers ();
    ~multiPlayers ();
    void setWindows(int width, int height);
    int mainLoop(Map&, Referee&);
    int eventsHandling(Map&, Referee&);
};

#endif /* !MULTIPLAYERS_HH */
