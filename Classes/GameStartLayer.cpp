#include "GameStartLayer.h"
#include "GameLayer.h"

bool GameStartLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	UILayer* UIGameStart = UILayer::create();
	this->addChild(UIGameStart);
	m_GameStart = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("GameStart/GameStart_1.ExportJson");
	UIGameStart->addWidget(m_GameStart);

	UIStart = (UIButton*)m_GameStart->getChildByName("Button_start");
	UIStart->setTag(1);
	UIExit = (UIButton*)m_GameStart->getChildByName("Button_exit");
	UIExit->setTag(2);
	UIStart->addTouchEventListener(UIStart,SEL_TouchEvent(&GameStartLayer::ButtonCallback));
	UIExit->addTouchEventListener(UIStart,SEL_TouchEvent(&GameStartLayer::ButtonCallback));
	return true;
}

void GameStartLayer::ButtonCallback(CCObject* sender, TouchEventType type)
{
	UIButton* clicker = (UIButton*)sender;
	if (clicker->getTag() == 1)
	{
		CCScene* pScene = CCScene::create();
		pScene->addChild(GameLayer::create());
		CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5,pScene));
	}
	else if (clicker->getTag() == 2)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
		CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
		CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
#endif
#endif
	}
}