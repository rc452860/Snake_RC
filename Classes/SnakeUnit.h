#ifndef __SNAKEUNIT_H__
#define __SNAKEUNIT_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include "snakeBlock.h"
USING_NS_CC;
USING_NS_CC_EXT;

class snakeUnit
{
//���캯��
public:
	snakeUnit();
	~snakeUnit();
//����
public:
	void setDir(CCPoint* dir);
//�ֶ�
public:
	int x;
	int y;
	CCPoint Dir;
	snakeBlock* block;
protected:
private:
};

#endif