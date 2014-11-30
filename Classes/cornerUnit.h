#ifndef __CORNERUNIT_H__
#define __CORNERUNIT_H__

#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;
class cornerUnit
{
public:
	cornerUnit(CCPoint position,CCPoint currDir,CCPoint beforeDir);
	~cornerUnit();
public:

public:
	CCPoint position;
	CCPoint currDir;
	CCPoint beforeDir;
protected:
private:
};
#endif