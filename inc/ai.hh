#ifndef _AI_HH
# define _AI_HH

#include <list>
#include <stack>
#include "map.hh"

#define PLAYING 1

class AI
{
	Map _map;
	int _playing;
	int _bestX;
	int _bestY;
	AI(Map map);
public:
	AI(Map &map, int playing);
	int startAi(int playing, int depth);
	void place(Map *map) const;
};

#endif
