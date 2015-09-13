#ifndef __MAINSCENE_SCENE_H__
#define __MAINSCENE_SCENE_H__

#include "cocos2d.h"
#include "GameController.h"
#include "GameMap.h"
#include "Definitions.h"
using namespace cocos2d;

class MainGamePlayScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();


	// implement the "static create()" method manually
	CREATE_FUNC(MainGamePlayScene);

	virtual bool onTouchBegan(cocos2d::CCTouch  *pTouches, cocos2d::CCEvent *pEvent);
	virtual void onTouchMoved(cocos2d::CCTouch  *pTouches, cocos2d::CCEvent *pEvent);
    virtual void onTouchEnded(cocos2d::CCTouch  *pTouches, cocos2d::CCEvent *pEvent);
    void menuReplayCallback(cocos2d::Ref* pSender);
private:
	void GoToMainGameScene(cocos2d::Ref *sender);
	void GoToScoreResultScene(cocos2d::Ref *sender);

    GameController gcontroller;
    GameMap gmap;
    int stepsTaken;


};

#endif // __MAINSCENE_SCENE_H__
