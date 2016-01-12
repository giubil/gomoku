#include "AGame.hh"

AGame::AGame()
{
	int x = 0;
	int y = 0;
	sf::Sprite mem;
	if (!_textTile.loadFromFile("./ressources/Case.png"))
		throw (std::runtime_error("Failed to load case texture!"));
	if (!_textBlack.loadFromFile("./ressources/CaseBlack.png"))
		throw (std::runtime_error("Failed to load blacktile texture!"));
	if (!_textWhite.loadFromFile("./ressources/CaseWhite.png"))
		throw (std::runtime_error("Failed to load whitetile texture!"));
	if (!_textSelectWhite.loadFromFile("./ressources/CaseSelectorWhite.png"))
		throw (std::runtime_error("Failed to load whiteselector texture"));
	if (!_textSelectBlack.loadFromFile("./ressources/CaseSelectorBlack.png"))
		throw (std::runtime_error("Failed to load blackselector texture"));
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
}
