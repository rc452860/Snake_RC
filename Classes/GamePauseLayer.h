#ifndef __GAME_PAUSE_H__
#define __GAME_PAUSE_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class GamePauseLayer:public CCLayer
{
public:
	bool init();
	Layout* m_GamePause;
	UIButton* m_GameKeepButton;
	UIButton* m_GameRestartButton;
	UIButton* m_GameHomeButton;

	void ButtonCallback(CCObject* sender, TouchEventType type);
	CREATE_FUNC(GamePauseLayer);
private:
};
#endif