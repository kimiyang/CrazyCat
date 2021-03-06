#ifndef __GAMEMAP_H__
#define __GAMEMAP_H__

#include "cocos2d.h"
#include <iostream>
using namespace std;
using namespace cocos2d;
#define MAP_DIM 9
#define MAX_VAL 1000

struct TreeNode {
	int val;
	int depth;
	float posX;
	float posY;
	bool obstacle;
	vector<int> childList;

	TreeNode(int v = 0, int d = 0, float x = 0.0f, float y = 0.0f, bool obst = false) :
		val(v), depth(d), posX(x), posY(y), obstacle(obst){}

	~TreeNode()
	{
		//TreeNode* n;
  //      for (auto var : childList)
		//{
		//	delete var;
		//}
	}
};

struct PathStruct {
	map<int, int> m_Hash;
	int m_Node;
};


class GameMap
{
public:
	GameMap(int dRadius = 7)
    {
        catAtNode = 40;
        for (int j = 0; j < MAP_DIM * MAP_DIM; j++)
            MapNodes[j] = NULL;
        radius = dRadius;
    }
	void InitMap(int gameWidth, int gameHight, float gameOriginX, float gameOriginY);
	void DrawMap(DrawNode* draw);
	void DrawAtPosition(DrawNode* draw, int dotNumber);
	int GetMinPathValueFromNeighbors(int node);
	int GetMinNeighbor(int node);
	vector<int> GetNeighborsNode(int node);
	vector<int> GetAvailableNeighborsNode(int node);
	bool IsBorder(int node);
	int GetAvailableNeighborsNodeNum(int node);
	int GetMaxPathNeighbor(int node);
	void InitDFSPath(int catPos);
	vector<int> DFSPathSearch(int startNode);
	void AppendPathNodeChildren(int node);

	~GameMap()
	{
        for(auto var : MapNodes)
            delete var;
	}
	TreeNode* MapNodes[81];
	int radius;
	int catAtNode;

	PathStruct ps;
private:
	
	float originX;
	float originY;

	
};

#endif // __GAMEMAP_H__
