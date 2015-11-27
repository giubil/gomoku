#include "ai.hh"

AI::AI(Map &map, int playing) : _map(map), _playing(playing) {
}

AI::AI(Map map) : _map(map) {
}

int AI::startAi(int playing, int depth)
{
	//std::cout << std::endl;
	//_map.displayMap();
	int won = _map.hasWon();
	if (won != 0)
		return ((won == PLAYING) ? -1 : 1);
	else if (won == 0 && _map.isFull())
		return (0);
	AI  *buff;
	int bestX, bestY, score, buffVal;
	bestX = -1;
	bestY = -1;
	score = 0;
	for (int x = 0; x < _map.getSizeX(); ++x)
		for (int y = 0; y < _map.getSizeY(); ++y)
			if (_map.getMapValue(x, y) == 0)
			{
				buff = new AI(Map(_map));
				buff->_map.setMapValue(x, y, (playing == 1) ? 2 : 1);
				buffVal = buff->startAi((playing == 1) ? 2 : 1, depth + 1);
				if ((playing == PLAYING && score <= buffVal)
				    || (playing != PLAYING && score >= buffVal))
				{
					bestX = x;
					bestY = y;
					score = buffVal;
				}
				if (buffVal > 0 && depth == 0)
					std::cout << "x = " << x << " y = " << y << " score = " << score << " depth = " << depth << std::endl;
				delete buff;
			}
	//std::cout << "BestX = " << bestX << " bestY = " << bestY << " score = " << score << " depth =" << depth <<std::endl;
	_bestX = bestX;
	_bestY = bestY;
	//_map.setMapValue(bestX, bestY, playing);
	return (score);
}

void AI::place(Map *map) const
{
	map->setMapValue(_bestX, _bestY, PLAYING);
}
