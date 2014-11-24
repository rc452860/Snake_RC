#ifndef __SNAKE_H__
#define __SNAKE_H__
#include "cocos-ext.h"
#include "cocos2d.h"
#include "queue"
#include "snakeUnit.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;


class Snake
{
public:
	Snake();
	~Snake();
public:
	bool init();
	bool checkEatSelf();
	bool EatFoot(CCPoint* position);
	bool isInstanceOf(int x,int y);
	void shiftSnake(bool ischangeDir);
	CCPoint* getDir();
	void setParent(CCNode* parent);
	CCNode* getParent();
public:
	list<CCPoint*>::iterator Dir;
	list<CCPoint*> *body;
	queue<snakeUnit*> *corner;
	int cornerNum;
	CCPoint* head;
	int len;
	
protected:

private:
	CCNode* parent;
};

#endif