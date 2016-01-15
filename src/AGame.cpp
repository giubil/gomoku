

#include "AGame.hh"

AGame::AGame()
{
	int x = 0;
	int y = 0;
	sf::Sprite mem;
	if (!_textBackGround.loadFromFile("./ressources/BackGround.png"))
		throw (std::runtime_error("Failed to load Background texture!"));
	if (!_textTile.loadFromFile("./ressources/Casev2.png"))
		throw (std::runtime_error("Failed to load case texture!"));
	if (!_textBlack.loadFromFile("./ressources/CaseBlackv2.png"))
		throw (std::runtime_error("Failed to load blacktile texture!"));
		if (!_textWhite.loadFromFile("./ressources/CaseWhitev2.png"))
		throw (std::runtime_error("Failed to load whitetile texture!"));
	if (!_textSelectWhite.loadFromFile("./ressources/CaseSelectorWhitev2.png"))
		throw (std::runtime_error("Failed to load whiteselector texture"));
		if (!_textSelectBlack.loadFromFile("./ressources/CaseSelectorBlackv2.png"))
		throw (std::runtime_error("Failed to load blackselector texture"));
	if (!_font.loadFromFile("./ressources/OpenSans-Regular.ttf"))
		throw (std::runtime_error("Failed to load font"));
	_BackGround.setTexture(_textBackGround);
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
	_lastSelected.x = 0;
	_lastSelected.y = 0;
	_textPlayer.setFont(_font);
	_textPlayer.setScale(0.5,0.5);
	_textPlayer.setString("Turn of :");
	_textPlayer.setColor(sf::Color::White);
	_textTurnPlayer.setFont(_font);
  	_textTurnPlayer.setScale(0.5,0.5);
	_textTurnPlayer.setString("Player white");
	_textTurnPlayer.setColor(sf::Color::White);
	_textCapturedPlayer1.setFont(_font);
	_textCapturedPlayer1.setScale(0.5,0.5);
	_textCapturedPlayer1.setString("Player White nb captured :");
	_textCapturedPlayer1.setColor(sf::Color::White);
	_textCapturedPlayer2.setFont(_font);
	_textCapturedPlayer2.setScale(0.5,0.5);
	_textCapturedPlayer2.setString("Player Black nb captured :");
	_textCapturedPlayer2.setColor(sf::Color::White);
	_textNbCapturedPlayer1.setFont(_font);
	_textNbCapturedPlayer1.setScale(0.5,0.5);
	_textNbCapturedPlayer1.setString("0");
	_textNbCapturedPlayer1.setColor(sf::Color::White);
	_textNbCapturedPlayer2.setFont(_font);
	_textNbCapturedPlayer2.setScale(0.5,0.5);
	_textNbCapturedPlayer2.setString("0");
	_textNbCapturedPlayer2.setColor(sf::Color::White);
	_textPlayer.setPosition(960, 20);
	_textTurnPlayer.setPosition(960, 40);
	_textCapturedPlayer1.setPosition(960, 80);
	_textNbCapturedPlayer1.setPosition(960, 100);
	_textCapturedPlayer2.setPosition(960, 120);
	_textNbCapturedPlayer2.setPosition(960, 140);
}
