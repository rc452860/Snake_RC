#ifndef __SNAKEUNIT_H__
#define __SNAKEUNIT_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "snakeBlock.h"
USING_NS_CC;
USING_NS_CC_EXT;

class snakeUnit
{
//构造函数
public:
	snakeUnit(CCPoint bodyUnit,CCPoint dir);
	~snakeUnit();
//方法
public:
	void setDir(CCPoint* dir);
//字段
public:
	int x;
	int y;
	CCPoint Dir;
protected:
private:
	CCNode* parent;
};

#endif