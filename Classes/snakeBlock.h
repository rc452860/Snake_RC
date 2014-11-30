#ifndef __SNAKEBLOCK_H__
#define __SNAKEBLOCK_H__
#include "cocos2d.h"
#include "cocos-ext.h"
USING_NS_CC;
USING_NS_CC_EXT;

enum snakeEnum{
	snakeHead,
	snakeBody,
	snakeLeft,
	snakeRight,
	snakeTail
};

class snakeBlock:public CCSprite
{
	///���캯��
public:
	snakeBlock();
	~snakeBlock();
	///����
public:
	static snakeBlock* create(snakeEnum block);
	static snakeBlock* create(snakeEnum block,CCPoint dir);
	CREATE_FUNC(snakeBlock);
	///�ֶ�
public:
protected:
private:
};
#endif