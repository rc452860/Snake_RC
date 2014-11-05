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
	Snake(int len);
	Snake(int len,ccColor3B color);
	~Snake();
public:
	bool checkEatSelf();
	bool EatFoot(SnakeUnit* unit);
public:
	int Dir;
	list<SnakeUnit*> *body;
	SnakeUnit* head;
	int len;
	ccColor3B color;
protected:
private:
};

#endif