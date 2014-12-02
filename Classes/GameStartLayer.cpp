#include "GameStartLayer.h"
#include "GameLayer.h"
#include "VisibleRect.h"

bool GameStartLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	/*UILayer* UIGameStart = UILayer::create();
	this->addChild(UIGameStart);
	m_GameStart = (Layout *)GUIReader::shareReader()->widgetFromJsonFile("GameStart/GameStart_1.ExportJson");
	UIGameStart->addWidget(m_GameStart);

	UIStart = (UIButton*)m_GameStart->getChildByName("Button_start");
	UIStart->setTag(1);
	UIExit = (UIButton*)m_GameStart->getChildByName("Button_exit");
	UIExit->setTag(2);
	UIStart->addTouchEventListener(UIStart,SEL_TouchEvent(&GameStartLayer::ButtonCallback));
	UIExit->addTouchEventListener(UIStart,SEL_TouchEvent(&GameStartLayer::ButtonCallback));*/
	CCArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Main_Interface/Main_Interface0.png","Main_Interface/Main_Interface0.plist","Main_Interface/Main_Interface.ExportJson");
	CCArmature* pMainInterface = CCArmature::create("Main_Interface");
	CCArmature* pEyes = CCArmature::create("Main_Interface");
	pMainInterface->getAnimation()->playByIndex(0);
	pEyes->getAnimation()->playByIndex(1);
	pMainInterface->setPosition(VisibleRect::center());
	pEyes->setPosition(VisibleRect::center());
	CCMenuItemImage* pMenuNewGame = CCMenuItemImage::create("Main_Interface/newgame.png","Main_Interface/newgame2.png",this,menu_selector(GameStartLayer::newGame));
	CCMenuItemImage* pMenuStart = CCMenuItemImage::create("Main_Interface/start.png","Main_Interface/start2.png",this,menu_selector(GameStartLayer::Start));
	pEyes->setZOrder(10000);
	CCMenu* menu = CCMenu::create();
	menu->addChild(pMenuNewGame);
	menu->addChild(pMenuStart);
	this->addChild(menu);
	menu->setPosition(VisibleRect::center());
	//menu->setZOrder(10000);
	CCBone* pNewGame = pMainInterface->getBone("Layer12");
	pNewGame->addDisplay(pMenuNewGame,1);
	pNewGame->changeDisplayByIndex(1,true);
	CCBone* pStart = pMainInterface->getBone("Layer13");
	pStart->addDisplay(pMenuStart,1);
	pStart->changeDisplayByIndex(1,true);
	
	this->addChild(pEyes);
	
	this->addChild(pMainInterface);


	return true;
}

void GameStartLayer::newGame(CCObject *sender)
{
	//To Do Something
	CCScene* pScene = CCScene::create();
	pScene->addChild(GameLayer::create());
	CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5,pScene));
	CCLog("new game"); 
}

void GameStartLayer::Start(CCObject *sender)
{
	//To Do Something
	CCLog("start"); 
}

/*
void GameStartLayer::ButtonCallback(CCObject* sender, TouchEventType type)
{
	if (type!=TouchEventType(TOUCH_EVENT_ENDED))
		return;
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
}*/