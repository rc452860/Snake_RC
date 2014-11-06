#ifndef __SNAKE_UNIT_H__
#define __SNAKE_UNIT_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

class SnakeUnit:public CCSprite
{
public:
	SnakeUnit();
	~SnakeUnit();
	int x,y;
	bool init();
	void setPosition();
	bool checkOverflow(int x,int y);
	bool checkOverflow();
	bool init(ccColor3B color);
	static SnakeUnit* create(ccColor3B color);
	CREATE_FUNC(SnakeUnit);
protected:
private:
};
#endif