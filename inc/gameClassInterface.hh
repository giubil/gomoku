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
    gameClassInterface() {
        int x = 0;
        int y = 0;
        sf::Sprite mem;
        if (!_textTile.loadFromFile("./ressources/Case.png"))
            std::cout << "Failed to load case texture!" << std::endl;
        if (!_textBlack.loadFromFile("./ressources/CaseBlack.png"))
            std::cout << "Failed to load blacktile texture!" << std::endl;
        if (!_textWhite.loadFromFile("./ressources/CaseWhite.png"))
            std::cout << "Failed to load whitetile texture!" << std::endl;
        if (!_textSelectWhite.loadFromFile("./ressources/CaseSelectorWhite.png"))
            std::cout << "Failed to load whiteselector texture" << std::endl;
        if (!_textSelectBlack.loadFromFile("./ressources/CaseSelectorBlack.png"))
            std::cout << "Failed to load blackselector texture" << std::endl;
        mem.setPosition(x, y);
        mem.setTexture(_textTile);
        for (int i = 0; i < 19; i++)
        {
            y = 0;
            _tiles.push_back(std::vector<sf::Sprite>());
            for (int j = 0; j < 19; j++)
            {
                mem.setPosition(x, y);
                y += 50;
                _tiles[_tiles.size() - 1].push_back(mem);
            }
            x += 50;
        }
        lastSelected.x = 0;
        lastSelected.y = 0;
    };
    virtual int mainLoop(Map&, Referee&, sf::RenderWindow &) = 0;
    virtual int eventsHandling(Map&, Referee&, sf::RenderWindow &) = 0;
};

#endif /* !GAMECLASSINTERFACE_HH_ */
