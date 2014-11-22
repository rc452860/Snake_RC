#ifndef __SNAKE_H__
#define __SNAKE_H__
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
	void shiftSnake();
	CCPoint* getDir();
	void setParent(CCNode* parent);
	CCNode* getParent();
public:
	list<CCPoint*>::iterator Dir;
	list<CCPoint*> *body;
	list<CCPoint*> *corner;
	CCPoint* head;
	int len;
	
protected:

private:
	CCNode* parent;
};

#endif