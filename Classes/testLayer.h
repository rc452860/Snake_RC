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
	//��ʼ������
	bool init();
	CREATE_FUNC(TestLayer);
	
	//���غ���
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	//�����ص�
	
public:
	//�����
	CCSprite* pFrame;
	//��ʶ
	CCSprite* pFlag;
protected:
private:
};


#endif