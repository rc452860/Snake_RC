#ifndef __GAMESTART_H__
#define __GAMESTART_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class GameStartLayer :public CCLayer
{
	//构造函数
public:
	/*Layout *m_GameStart;
	bool init();
	UIButton* UIStart;
	UIButton* UIExit;
	void ButtonCallback(CCObject* sender, TouchEventType type);*/
	//方法
public:
	CREATE_FUNC(GameStartLayer);
	bool init();
	void newGame(CCObject *sender);
	void Start(CCObject *sender);

	//字段
public:

private:
};
#endif