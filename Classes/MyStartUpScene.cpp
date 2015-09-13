#include "MyStartUpScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MainGamePlayScene.h"
//#include "MainScene.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MyStartUpScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MyStartUpScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MyStartUpScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("btn_start.png");
	backgroundSprite->setScale(1);
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);
	
	this->scheduleOnce(schedule_selector(MyStartUpScene::GoToMainScene), DISPLAY_STARTUPSCENE_TIME);

	return true;
}


void MyStartUpScene::GoToMainScene(float delay)
{
	auto scene = MainGamePlayScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

