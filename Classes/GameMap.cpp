#include "GameMap.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace cocos2d;

GameMap::GameMap()
{
	catAtNode = 40;
}


void GameMap::InitMap(int gameWidth, int gameHight, float gameOriginX, float gameOriginY, int dotRadius)
{
	float fromHeight = gameHight * 0.3;
	float fromWidth = gameWidth * 0.3;
	originX = gameOriginX;
	originY = gameOriginY;
	radius = dotRadius;

	float oddOffSet = gameWidth * 0.05;
	float offSet = 0.0f;
    
	for (int i = 1; i <= MAP_DIM; i++)
	{
		fromHeight = gameHight * 0.11 * 0.6 * i;
		if (i % 2 == 0)
			offSet = oddOffSet;
		else offSet = 0.0f;
		for (int j = 1; j <= MAP_DIM; j++)
		{
			fromWidth = gameWidth * 0.11 * 0.85 * j;
            TreeNode* node = MapNodes[(i - 1) * MAP_DIM + j - 1];
			if( node == NULL)
                node = new TreeNode();
            node->val = MAX_VAL;
            node->obstacle = false;
			node->posX = fromWidth + offSet + originX;
			node->posY = fromHeight + originY;
			MapNodes[(i - 1) * MAP_DIM + j - 1] = node;
		}
	}
    
    timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long reed = tv.tv_sec*1000+tv.tv_usec/1000;

    srand(reed);

	int randomNums = 12;
	vector<int> rNumsCandidates;
	for (int i = 0; i < 81; i++)
        if(i == 40)continue;
		else rNumsCandidates.push_back(i);
	for (int i = 0; i < randomNums; i++)
	{
		int vsize = rNumsCandidates.size();
		int rN = CCRANDOM_0_1()*vsize;
		MapNodes[rNumsCandidates[rN]]->obstacle = true;
		int temp = rNumsCandidates[vsize - 1];
		rNumsCandidates[vsize - 1] = rNumsCandidates[rN];
		rNumsCandidates[rN] = temp;
		rNumsCandidates.pop_back();
	}

}

void GameMap::DrawMap(DrawNode* draw)
{
	for (int i = 0; i < MAP_DIM; i++)
	{
		for (int j = 0; j < MAP_DIM; j++)
		{
			Color4F color = MapNodes[i * MAP_DIM + j]->obstacle ? Color4F::RED : Color4F::GRAY;
			draw->drawDot(Vec2(MapNodes[i * MAP_DIM + j]->posX, MapNodes[i * MAP_DIM + j]->posY), radius, color);
		}
	}
}




void GameMap::DrawAtPosition(DrawNode* draw, int dotNumber)
{
	draw->drawDot(Vec2(MapNodes[dotNumber]->posX, MapNodes[dotNumber]->posY), radius, Color4F::RED);
}

bool GameMap::IsBorder(int node)
{
	if (node < MAP_DIM || node > MAP_DIM*(MAP_DIM - 1) || node % MAP_DIM == 0 || (node + 1) % MAP_DIM == 0)
	{
		return true;
	}
	return false;
}

vector<int> GameMap::GetNeighborsNode(int node)
{
	vector<int> around;
	if (IsBorder(node))
	{
		return around;
	}

	int oddCompensate;
	if ((int)(node / MAP_DIM) % 2 == 0)
		oddCompensate = 0;
	else
		oddCompensate = 1;
	around.push_back(node - 1);
	around.push_back(node - (MAP_DIM + 1) + oddCompensate);
	around.push_back(node - MAP_DIM + oddCompensate);
	around.push_back(node + 1);
	around.push_back(node + MAP_DIM + oddCompensate);
	around.push_back(node + (MAP_DIM - 1) + oddCompensate);
	return around;
}

vector<int> GameMap::GetAvailableNeighborsNode(int node)
{
	vector<int> around;
	if (IsBorder(node))
	{
		return around;
	}

	int oddCompensate;
	if ((int)(node / MAP_DIM) % 2 == 0)
		oddCompensate = 0;
	else
		oddCompensate = 1;
	if (!MapNodes[node-1]->obstacle)
		around.push_back(node - 1);
	if (!MapNodes[node - (MAP_DIM + 1) + oddCompensate]->obstacle)
		around.push_back(node - (MAP_DIM + 1) + oddCompensate);
	if (!MapNodes[node - MAP_DIM + oddCompensate]->obstacle)
		around.push_back(node - MAP_DIM + oddCompensate);
	if (!MapNodes[node + 1]->obstacle)
		around.push_back(node + 1);
	if (!MapNodes[node + MAP_DIM + oddCompensate]->obstacle)
		around.push_back(node + MAP_DIM + oddCompensate);
	if (!MapNodes[node + (MAP_DIM - 1) + oddCompensate]->obstacle)
		around.push_back(node + (MAP_DIM - 1) + oddCompensate);
	return around;
}

int GameMap::GetMinNeighbor(int node)
{
	int minValue = MAX_VAL;
	int rtNeighbor = -1;
	vector<int>neighbor = GetAvailableNeighborsNode(node);
	for (int pos = 0; pos < neighbor.size(); ++pos)
	{
		if (MapNodes[neighbor[pos]]->val < minValue)
		{
			minValue = MapNodes[neighbor[pos]]->val;
			rtNeighbor = neighbor[pos];
		}
	}
	return rtNeighbor;
}

int GameMap::GetMinPathValueFromNeighbors(int node)
{
	int minValue = MAX_VAL;
	vector<int>neighbor = GetNeighborsNode(node);
	for (int pos = 0; pos < neighbor.size(); ++pos)
	{
		if (MapNodes[neighbor[pos]]->val < minValue)
			minValue = MapNodes[neighbor[pos]]->val;
	}
	return minValue;
}