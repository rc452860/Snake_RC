#include "snakeBlock.h"

snakeBlock::snakeBlock(){}
snakeBlock::~snakeBlock(){}
snakeBlock* snakeBlock::create(snakeEnum block)
{
	snakeBlock *pobSprite = new snakeBlock();
	CCString* tempName;
	switch (block)
	{
	case snakeHead:
		tempName = CCString::create("snake/snakeHead.png");
		break;
	case snakeBody:
		tempName = CCString::create("snake/snakeBody.png");
		break;
	case snakeTail:
		tempName = CCString::create("snake/snakeTail.png");
		break;
	case snakeLeft:
		tempName = CCString::create("snake/snakeLeft.png");
		break;
	case snakeRight:
		tempName = CCString::create("snake/snakeRight.png");
		break;
	default:
		tempName = CCString::create("snake/snakeBody.png");
		break;
	}
	
	if (pobSprite && pobSprite->initWithFile(tempName->getCString()))
	{
		pobSprite->autorelease();
		return pobSprite;
	}
	CC_SAFE_DELETE(pobSprite);
	return NULL;
}
