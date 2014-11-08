#ifndef __SNAKE_H__
#define __SNAKE_H__
#include "SnakeUnit.h"
#include "cocos-ext.h"
#include "cocos2d.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;
class Snake
{
public:
	Snake();
	~Snake();
public:
	bool checkEatSelf();
	bool EatFoot(CCPoint* position);
	bool isInstanceOf(int x,int y);
public:
	CCPoint Dir;
	list<CCPoint*> *body;
	CCPoint* head;
	int len;
protected:

private:
};

#endif