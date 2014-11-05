#include "GamePauseLayer.h"
#include "GameStartLayer.h"
#include "GameLayer.h"
bool GamePauseLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	UILayer* UIGamePause = UILayer::create();
	m_GamePause =(Layout*)GUIReader::shareReader()->widgetFromJsonFile("GamePause/GamePause_1.ExportJson");
	UIGamePause->addWidget(m_GamePause);
	this->addChild(UIGamePause);

	m_GameKeepButton =(UIButton*) m_GamePause->getChildByName("Button_KeepGame");
	m_GameKeepButton->setTag(0);
	m_GameKeepButton->addTouchEventListener(m_GameKeepButton,SEL_TouchEvent(&GamePauseLayer::ButtonCallback));
	m_GameHomeButton =(UIButton*) m_GamePause->getChildByName("Button_Back");
	m_GameHomeButton->setTag(1);
	m_GameHomeButton->addTouchEventListener(m_GameKeepButton,SEL_TouchEvent(&GamePauseLayer::ButtonCallback));
	m_GameRestartButton =(UIButton*) m_GamePause->getChildByName("Button_Restart");
	m_GameRestartButton->setTag(2);
	m_GameRestartButton->addTouchEventListener(m_GameKeepButton,SEL_TouchEvent(&GamePauseLayer::ButtonCallback));




	return true;
}



void GamePauseLayer::ButtonCallback(CCObject* sender, TouchEventType type)
{
	int tag = ((UIButton*)sender)->getTag();
		CCScene* pScence = CCScene::create();
	switch (tag)
	{
	case  0:
		((GameLayer*)this->getParent())->GamePause(NULL);
		this->removeFromParent();
		break;
	case  1:
		pScence->addChild(GameLayer::create());
		CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5,pScence));
		break;
	case  2:
		pScence->addChild(GameStartLayer::create());
		CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5,pScence));
		break;
	default:
		
		break;
	}
}