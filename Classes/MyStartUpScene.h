#ifndef __MYSTARTUPSCENE_SCENE_H__
#define __MYSTARTUPSCENE_SCENE_H__

#include "cocos2d.h"
#include "Definitions.h"

class MyStartUpScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();


	// implement the "static create()" method manually
	CREATE_FUNC(MyStartUpScene);
private:
	void GoToMainScene(float delay);
};

#endif // __MYSTARTUPSCENE_SCENE_H__
