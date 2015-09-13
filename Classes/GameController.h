#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include "cocos2d.h"
#include "GameMap.h"

using namespace std;
using namespace cocos2d;


class GameController
{
public:
	GameController(){}
	void InitController();
	int NextMove(GameMap &gmap);
	~GameController(){};
private:
	void InitMapForShortestPath(GameMap &gmap);
	void _CalculatePathValue(GameMap &gmap);
	int RandomMethod(GameMap &gmap);
	int ShortestPathMethod(GameMap &gmap);
	int DFSTreeMethod(GameMap &gmap);
    void _CalculatePathValueAtNode(GameMap &gmap, int index);
};

#endif // __GAMECONTROLLER_H__
