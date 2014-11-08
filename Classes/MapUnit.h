#ifndef __MAPUNIT_H__
#define __MAPUNIT_H__

#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_EXT;


class MapUnit:public CCSprite
{
public:
	MapUnit(){};
	~MapUnit(){};
public:
	int x;
	int y;
protected:
private:
};
#endif