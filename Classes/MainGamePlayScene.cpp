#include "MainGamePlayScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "PluginChartboost/PluginChartboost.h"


USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainGamePlayScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainGamePlayScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool MainGamePlayScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	//auto rootNode = CSLoader::createNode("MainScene.csb");

	//addChild(rootNode);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    stepsTaken = 0;

    gmap.radius = 8;
    
	auto backgroundSprite = Sprite::create("bg.jpg"); 
	backgroundSprite->setScale(1.2);
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite,1,"background");
    
    
    auto successSprite = Sprite::create("victory.png");
    successSprite->setScale(1);
    this->addChild(successSprite, 0, "successSprite");
    successSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 3 / 4 + origin.y));
    
    auto failedSprite = Sprite::create("failed.png");
    failedSprite->setScale(1);
    this->addChild(failedSprite, 0, "failedSprite");
    failedSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 3 / 4 + origin.y));

    
    SpriteFrameCache * spriteCacheDance = SpriteFrameCache::getInstance();
    spriteCacheDance->addSpriteFramesWithFile("stayDancing.plist");
    
    
    
    Vector<SpriteFrame*> framesDance;
    std::ostringstream osr;
    for (int i = 1; i <= 16; ++i){
        osr << "stay" << i << ".png";
        framesDance.pushBack(spriteCacheDance->getSpriteFrameByName(osr.str()));
        osr.str("");
    }
    auto animation = Animation::createWithSpriteFrames(framesDance, 0.08f);
    auto animate = Animate::create(animation);
    
    auto spriteDancingAnimation = Sprite::createWithSpriteFrame(spriteCacheDance->getSpriteFrameByName("stay1.png"));
    spriteDancingAnimation->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    spriteDancingAnimation->runAction(RepeatForever::create(animate));
    this->addChild(spriteDancingAnimation,15,"spriteDancingAnimation");
    
    
    
    SpriteFrameCache * spriteCacheCaught = SpriteFrameCache::getInstance();
    spriteCacheCaught->addSpriteFramesWithFile("caught.plist");
    Vector<SpriteFrame*> framesCaught;
    osr.str("");
    for (int i = 1; i <= 15; ++i){
        osr << "caught" << i << ".png";
        framesCaught.pushBack(spriteCacheCaught->getSpriteFrameByName(osr.str()));
        osr.str("");
    }
    auto animationCaught = Animation::createWithSpriteFrames(framesCaught, 0.08f);
    auto animateCaught = Animate::create(animationCaught);
    
    auto spriteCaughtAnimation = Sprite::createWithSpriteFrame(spriteCacheCaught->getSpriteFrameByName("caught1.png"));
    spriteCaughtAnimation->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    
    spriteCaughtAnimation->runAction(RepeatForever::create(animateCaught));
    this->addChild(spriteCaughtAnimation,0,"spriteCaughtAnimation");

	auto draw = DrawNode::create();

    gmap.InitMap(visibleSize.width, visibleSize.height, origin.x, origin.y);
    gmap.DrawMap(draw);
	
    float catPosOffset = gmap.radius;
    spriteDancingAnimation->setPosition(Point(gmap.MapNodes[40]->posX, gmap.MapNodes[40]->posY + catPosOffset));
    
	this->addChild(draw, 10, "draw");
	

    auto replayButton = MenuItemImage::create(
                                           "replay.png",
                                           "replay.png",
                                           CC_CALLBACK_1(MainGamePlayScene::menuReplayCallback, this));
    
    replayButton->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.7 + origin.y));
    
    
    
    auto menu = Menu::create(replayButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 0,"replayButton");
	
	
	/*for (int i = 0; i < 10; i++)
	{
		draw->drawDot(Vec2(visibleSize.width / 2, visibleSize.height / 2), 10 * (10 - i), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
	}*/


	/*auto circle = Sprite::create("doc-gray-circle.png");
	circle->setScale(0.15);
	circle->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(circle);*/


	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(MainGamePlayScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(MainGamePlayScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(MainGamePlayScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
		 
	return true;
}


void MainGamePlayScene::GoToMainGameScene(cocos2d::Ref *sender)
{
	/*auto scene = MainGameScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));*/
}

void MainGamePlayScene::GoToScoreResultScene(cocos2d::Ref *sender)
{
	/*auto scene = ScoreResultScene::createScene(-1,false);
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));*/
}

bool MainGamePlayScene::onTouchBegan(cocos2d::CCTouch  *pTouche, cocos2d::CCEvent *pEvent)
{

	return true;

}

void MainGamePlayScene::onTouchMoved(cocos2d::CCTouch  *pTouche, cocos2d::CCEvent *pEvent)
{


}

void MainGamePlayScene::onTouchEnded(cocos2d::CCTouch  *pTouche, cocos2d::CCEvent *pEvent)
{
    if(gcontroller.IsCaught(gmap))
        return;
    
	Vec2 pos = pTouche->getLocation();
    auto danceAnimationSprite = this->getChildByName("spriteDancingAnimation");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if ((gmap.MapNodes[i * 9 + j]->posX - pos.x)*(gmap.MapNodes[i * 9 + j]->posX - pos.x) + (gmap.MapNodes[i * 9 + j]->posY - pos.y)*(gmap.MapNodes[i * 9 + j]->posY - pos.y) <= gmap.radius * gmap.radius)
            {
                if(gmap.MapNodes[i * 9 + j]->obstacle)
                    break;
                DrawNode* draw = (DrawNode*)this->getChildByName("draw");
                gmap.DrawAtPosition(draw,i * 9 + j);
                gmap.MapNodes[i * 9 + j]->obstacle = true;
                int nextCatMove = gcontroller.NextMove(gmap);
                stepsTaken++;
                if (nextCatMove >= 0)
                {
                    danceAnimationSprite->setPosition(Vec2(gmap.MapNodes[nextCatMove]->posX, gmap.MapNodes[nextCatMove]->posY + gmap.radius));
                    gmap.catAtNode = nextCatMove;
                    if (gmap.IsBorder(gmap.catAtNode))
                    {
                        this->getChildByName("failedSprite")->setZOrder(20);
                        this->getChildByName("replayButton")->setZOrder(20);
                        break;
                    }
                }
                if(nextCatMove < 0 || gcontroller.IsCaught(gmap))
                {
                    this->getChildByName("successSprite")->setZOrder(20);
                    danceAnimationSprite->setZOrder(0);
                    auto caughtAnimationSprite = this->getChildByName("spriteCaughtAnimation");
                    caughtAnimationSprite->setZOrder(15);
                    caughtAnimationSprite->setPosition(danceAnimationSprite->getPosition());
                    this->getChildByName("replayButton")->setZOrder(20);
                    std::ostringstream scoreStream;
                    scoreStream << stepsTaken;
                    string scoreText = "你用了 " + scoreStream.str() + " 步";
                    Label* scoreTextLabel = Label::createWithSystemFont(scoreText, "Arial", 8);
                    scoreTextLabel->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.75 + origin.y));
                    this->addChild(scoreTextLabel, 20, "scoreLabel");
                    scoreTextLabel->setTextColor(Color4B::BLACK);

                }
                
                break;
            }
        }
    }
}

void MainGamePlayScene::menuReplayCallback(cocos2d::Ref* pSender)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    DrawNode* draw = (DrawNode*)this->getChildByName("draw");
    gmap.InitMap(visibleSize.width, visibleSize.height, origin.x, origin.y);
    gmap.DrawMap(draw);
    gmap.catAtNode = 40;
    stepsTaken = 0;
    
    auto danceAnimationSprite = this->getChildByName("spriteDancingAnimation");
    float catPosOffset = gmap.radius;
    danceAnimationSprite->setPosition(Point(gmap.MapNodes[40]->posX, gmap.MapNodes[40]->posY + catPosOffset));
    danceAnimationSprite->setZOrder(20);
    
    auto caughtAnimationSprite = this->getChildByName("spriteCaughtAnimation");
    caughtAnimationSprite->setZOrder(0);
    
    this->getChildByName("failedSprite")->setZOrder(0);
    this->getChildByName("successSprite")->setZOrder(0);
    this->getChildByName("replayButton")->setZOrder(0);
    this->removeChildByName("scoreLabel");
    
    sdkbox::PluginChartboost::show(sdkbox::CB_Location_Default);
}

