#include "testLayer.h"
#include "VisibleRect.h"

TestLayer::TestLayer(){}
TestLayer::~TestLayer(){}


bool TestLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	//���ô���
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
	//��������ʾ���
	pFrame = CCSprite::create();
	pFrame->setTextureRect(CCRect(0,0,480,480));
	pFrame->setColor(ccc3(125,125,125));
	pFrame->setPosition(VisibleRect::center());
	this->addChild(pFrame);

	//���ñ�ʶ
	pFlag = CCSprite::create();
	pFlag->setTextureRect(CCRect(0,0,20,20));
	pFlag->setColor(ccc3(255,255,255));
	pFlag->setPosition(ccp(240,10));
	pFrame->addChild(pFlag);
	return true;
}


bool TestLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	pFlag->runAction(CCMoveBy::create(2,ccp(0,20)));
	pFrame->runAction(CCRotateTo::create(2,90));
	return true;
}


void TestLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	
}