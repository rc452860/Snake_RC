#ifndef __TEST_LAYER_H__
#define __TEST_LAYER_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;


class TestLayer:public CCLayer
{
public:
	TestLayer();
	~TestLayer();
public:
	//初始化函数
	bool init();
	CREATE_FUNC(TestLayer);
	
	//触控函数
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	//函数回调
	
public:
	//主框架
	CCSprite* pFrame;
	//标识
	CCSprite* pFlag;
protected:
private:
};


#endif