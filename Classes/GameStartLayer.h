#ifndef __GAMESTART_H__
#define __GAMESTART_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class GameStartLayer :public CCLayer
{
public:
	Layout *m_GameStart;
	bool init();
	UIButton* UIStart;
	UIButton* UIExit;
	void ButtonCallback(CCObject* sender, TouchEventType type);
	CREATE_FUNC(GameStartLayer);
private:
};
#endif