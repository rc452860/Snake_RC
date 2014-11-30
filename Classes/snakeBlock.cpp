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
snakeBlock* snakeBlock::create(snakeEnum block,CCPoint dir)
{
	snakeBlock* pobSprite = snakeBlock::create(block);
	if(dir.x == 1)
		pobSprite->setRotation(180);
	else if(dir.x == -1)
		pobSprite->setRotation(0);
	else if(dir.y == 1)
		pobSprite->setRotation(90);
	else if(dir.y == -1)
		pobSprite->setRotation(270);
	return pobSprite;
}
