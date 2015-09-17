#include "GameController.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

void GameController::InitController()
{

}


int GameController::NextMove(GameMap &gmap)
{
    int next = DFSTreeMethod(gmap);
    if(next != -1)
        return next;
    return ShortestPathMethod(gmap);
}

void GameController::_CalculatePathValueAtNode(GameMap &gmap, int index)
{
    if(gmap.MapNodes[index]->obstacle)
        gmap.MapNodes[index]->val = MAX_VAL;
    else if (gmap.IsBorder(index))
        gmap.MapNodes[index]->val = 0;
    else
    {
        gmap.MapNodes[index]->val = gmap.GetMinPathValueFromNeighbors(index) + 1;
    }

}

void GameController::_CalculatePathValue(GameMap &gmap)
{
    
    for(int i=0;i<MAP_DIM;i++)
    {
        for(int j=0;j<MAP_DIM;j++)
        {
            _CalculatePathValueAtNode(gmap,i*MAP_DIM+j);
            _CalculatePathValueAtNode(gmap,j*MAP_DIM+i);
        }
    }
    
    for(int i=0;i<MAP_DIM;i++)
    {
        for(int j=0;j<MAP_DIM;j++)
        {
            _CalculatePathValueAtNode(gmap,i * MAP_DIM + 8 - j);
            _CalculatePathValueAtNode(gmap,j * MAP_DIM + 8 - i);
        }
    }

    
    for(int i=0;i<MAP_DIM;i++)
    {
        for(int j=0;j<MAP_DIM;j++)
        {
            _CalculatePathValueAtNode(gmap,(8-i)*MAP_DIM+j);
            _CalculatePathValueAtNode(gmap,(8-j)*MAP_DIM+i);

        }
    }

    
    for(int i=0;i<MAP_DIM;i++)
    {
        for(int j=0;j<MAP_DIM;j++)
        {
            _CalculatePathValueAtNode(gmap,(8-i)*MAP_DIM+8-j);
            _CalculatePathValueAtNode(gmap,(8-j)*MAP_DIM+8-i);

        }
    }
}

void GameController::InitMapForShortestPath(GameMap &gmap)
{
	for (int i = 0; i < MAP_DIM * MAP_DIM; i++)
	{
		gmap.MapNodes[i]->val = MAX_VAL;
	}
    _CalculatePathValue(gmap);
	
}

int GameController::DFSTreeMethod(GameMap &gmap)
{
    gmap.InitDFSPath(gmap.catAtNode);
    vector<int> children = gmap.MapNodes[gmap.catAtNode]->childList;
	for (size_t i = 0; i < children.size(); ++i)
	{
		if (gmap.IsBorder(children[i]))
			return children[i];
	}
	vector<int> result = gmap.DFSPathSearch(gmap.ps.m_Node);
	if (result.back() == -1)
		return ShortestPathMethod(gmap);
	else
		return result[1];
}

int GameController::ShortestPathMethod(GameMap &gmap)
{
	InitMapForShortestPath(gmap);
	int neighbor = gmap.GetMinNeighbor(gmap.catAtNode);
	if (neighbor > 0)
		return neighbor;
	neighbor = gmap.GetMaxPathNeighbor(gmap.catAtNode);
	if (neighbor > 0)
		return neighbor;
	return RandomMethod(gmap);
}
int GameController::RandomMethod(GameMap &gmap)
{
	vector<int> around = gmap.GetAvailableNeighborsNode(gmap.catAtNode);
	if (around.size() > 0)
		return around[CCRANDOM_0_1()*(around.size() - 1)];
	return -1;
}

bool GameController::IsCaught(GameMap &gmap)
{
    return gmap.GetAvailableNeighborsNode(gmap.catAtNode).size() == 0;
}