#ifndef __SNAKE_H__
#define __SNAKE_H__
#include "cocos-ext.h"
#include "cocos2d.h"
#include "queue"
#include "snakeUnit.h"
#include "cornerUnit.h"
using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;


class Snake
{
public:
	Snake();
	~Snake();
public:
	void init(CCPoint start,CCPoint dir);
	void setParent(CCNode* pt);
	snakeUnit* getHead();
	snakeUnit* getTail();
	CCPoint getDir();
	void setDir(int x,int y);
	void shiftSnake();
	void pushCorner(bool isCorner);
	void clearCorner();
	cornerUnit* isCorner(snakeUnit* body);
	void reviseOverflow(snakeUnit* item);
public:
	//list中第一个为头结点
	list<snakeUnit*>* body;
	list<cornerUnit*>* corner;
protected:

private:
	CCNode* parent;
};

#endif