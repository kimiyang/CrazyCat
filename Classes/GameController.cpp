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
	return ShortestPathMethod(gmap);
}

void GameController::_CalculatePathValue(GameMap &gmap, int startNode, int dim)
{
	//top row & left col
	for (int i = 0; i < dim; i++)
	{
        if(gmap.MapNodes[startNode + i]->obstacle)
            gmap.MapNodes[startNode + i]->val = MAX_VAL;
		else if (gmap.IsBorder(startNode + i))
			gmap.MapNodes[startNode + i]->val = 0;
		else
		{
			gmap.MapNodes[startNode + i]->val = gmap.GetMinPathValueFromNeighbors(startNode + i) + 1;
		}
	}
    for (int i = 0; i < dim; i++)
    {
        if(gmap.MapNodes[startNode + i * MAP_DIM]->obstacle)
            gmap.MapNodes[startNode + i * MAP_DIM]->val = MAX_VAL;
        else if (gmap.IsBorder(startNode + i * MAP_DIM))
            gmap.MapNodes[startNode + i * MAP_DIM]->val = 0;
        else
        {
            gmap.MapNodes[startNode + i * MAP_DIM]->val = gmap.GetMinPathValueFromNeighbors(startNode + i * MAP_DIM) + 1;
        }
    }
    
    
    //top row & right col
	for (int i = dim - 1; i >= 0; i--)
	{
        if(gmap.MapNodes[startNode + i]->obstacle)
            gmap.MapNodes[startNode + i]->val = MAX_VAL;
		else if (gmap.IsBorder(startNode + i))
			gmap.MapNodes[startNode + i]->val = 0;
		else
		{
			gmap.MapNodes[startNode + i]->val = gmap.GetMinPathValueFromNeighbors(startNode + i) + 1;
		}
	}
    for (int i = 0; i < dim; i++)
    {
        if(gmap.MapNodes[i * MAP_DIM + startNode + dim - 1]->obstacle)
            gmap.MapNodes[i * MAP_DIM + startNode + dim - 1]->val = MAX_VAL;
        
        else if (gmap.IsBorder(i * MAP_DIM + startNode + dim - 1))
            gmap.MapNodes[i * MAP_DIM + startNode + dim - 1]->val = 0;
        else
        {
            gmap.MapNodes[i * MAP_DIM + startNode + dim - 1]->val = gmap.GetMinPathValueFromNeighbors(i * MAP_DIM + startNode + dim - 1) + 1;
        }
    }

	
	

	//bottom row & left col
	for (int i = 0; i < dim; i++)
	{
        if(gmap.MapNodes[(dim - 1)*MAP_DIM + startNode + i]->obstacle)
            gmap.MapNodes[(dim - 1)*MAP_DIM + startNode + i]->val = MAX_VAL;
		else if (gmap.IsBorder((dim - 1)*MAP_DIM + startNode + i))
			gmap.MapNodes[(dim - 1)*MAP_DIM + startNode + i]->val = 0;
		else
		{
			gmap.MapNodes[(dim - 1)*MAP_DIM + startNode + i]->val = gmap.GetMinPathValueFromNeighbors((dim - 1)*MAP_DIM + startNode + i) + 1;
		}
	}
    for (int i = dim - 1; i >= 0; i--)
    {
        if(gmap.MapNodes[startNode + i * MAP_DIM]->obstacle)
            gmap.MapNodes[startNode + i * MAP_DIM]->val = MAX_VAL;
        else if (gmap.IsBorder(startNode + i * MAP_DIM))
            gmap.MapNodes[startNode + i * MAP_DIM]->val = 0;
        else
        {
            gmap.MapNodes[startNode + i * MAP_DIM]->val = gmap.GetMinPathValueFromNeighbors(startNode + i * MAP_DIM) + 1;
        }
    }
    
    //bottom row & right col
	for (int i = dim - 1; i >= 0; i--)
	{
        if(gmap.MapNodes[(dim - 1)*MAP_DIM + startNode + i]->obstacle)
            gmap.MapNodes[(dim - 1)*MAP_DIM + startNode + i]->val = MAX_VAL;

		else if (gmap.IsBorder((dim - 1)*MAP_DIM + startNode + i))
			gmap.MapNodes[(dim - 1)*MAP_DIM + startNode + i]->val = 0;
		else
		{
			gmap.MapNodes[(dim - 1)*MAP_DIM + startNode + i]->val = gmap.GetMinPathValueFromNeighbors((dim - 1)*MAP_DIM + startNode + i) + 1;
		}
	}
    for (int i = dim - 1; i >= 0; i--)
    {
        if(gmap.MapNodes[i * MAP_DIM + startNode + dim - 1]->obstacle)
            gmap.MapNodes[i * MAP_DIM + startNode + dim - 1]->val = MAX_VAL;
        else if (gmap.IsBorder(i * MAP_DIM + startNode + dim - 1))
            gmap.MapNodes[i * MAP_DIM + startNode + dim - 1]->val = 0;
        else
        {
            gmap.MapNodes[i * MAP_DIM + startNode + dim - 1]->val = gmap.GetMinPathValueFromNeighbors(i * MAP_DIM + startNode + dim - 1) + 1;
        }
    }

	
	

}

void GameController::InitMapForShortestPath(GameMap &gmap)
{
	for (int i = 0; i < MAP_DIM * MAP_DIM; i++)
	{
		gmap.MapNodes[i]->val = MAX_VAL;
	}
	int dim = MAP_DIM;
	int startNode = 0;
	while (dim > 0)
	{
		_CalculatePathValue(gmap, startNode, dim);
		dim-=2;
		startNode = startNode + MAP_DIM + 1;
	}
}

int GameController::ShortestPathMethod(GameMap &gmap)
{
	InitMapForShortestPath(gmap);
	int neighbor = gmap.GetMinNeighbor(gmap.catAtNode);
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