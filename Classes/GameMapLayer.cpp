#include "GameMapLayer.h"

GameMapLayer::GameMapLayer(){}
GameMapLayer::~GameMapLayer(){}

bool GameMapLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	//this->setAnchorPoint(ccp(0,0));
	//pGameLayer = CCSprite::create("item.png");
	/*pGameLayer->setTextureRect(CCRect(0,0,480,480));
	pGameLayer->setColor(ccc3(155,155,155));
	this->setContentSize(CCSize(480,480));*/
	//this->addChild(pGameLayer);
	initMap();
	m_Snake = new Snake(4);
	list<SnakeUnit*>::iterator begin;
	for (begin=m_Snake->body->begin(); begin!=m_Snake->body->end(); ++begin) 
	{
		SnakeUnit* item = *begin;
		this->addChild(item);
	}
	this->schedule(schedule_selector(GameMapLayer::MapMoveDown),0.2f);
	return true;
	//Initialize the map array
	
}

void GameMapLayer::initMap()
{
	CCSpriteBatchNode* pBaseBatch = CCSpriteBatchNode::create("block.png");
	//Initialize the map all element of 1
	memset(this->Maritx,1,sizeof(this->Maritx));
	for (int nRowIndex = 0;nRowIndex<MARITX_X+2;nRowIndex++)
	{
		for (int nCloIndex = 0;nCloIndex<MARITX_Y+2;nCloIndex++)
		{

			CCSprite* pBlock = NULL;
			pBlock=CCSprite::createWithTexture(pBaseBatch->getTexture());
			pBlock->setPosition(ccp((MARITX_X-nRowIndex+1)*GRID,nCloIndex*GRID+GRID/2));
			m_BlokcUnit[nRowIndex][nCloIndex] = pBlock;
			this->addChild(pBlock);
		}
	}
}
void GameMapLayer::MapMoveDown(float dt)
{
	for (int nRowIndex = 0;nRowIndex<MARITX_X+2;nRowIndex++)
	{
		for (int nCloIndex = 0;nCloIndex<MARITX_Y+2;nCloIndex++)
		{
			CCSprite* pBlock=m_BlokcUnit[nRowIndex][nCloIndex];
			if(!pBlock)
				continue;
			pBlock->setPosition(ccp(pBlock->getPositionX(),pBlock->getPositionY()-10));
		}
	}

	//If Need Change m_nBlockUtil's Point(When Step over One BLOCK_SIZE)
	if ((MARITX_X-0+1)*GRID - m_BlokcUnit[0][0]->getPositionY()==GRID)
	{
		CCSprite* BlockUtil[MARITX_X+2][MARITX_Y+2];//Temp BlockUtils
		for (int nRowIndex = 0;nRowIndex<MARITX_X+1;nRowIndex++)
		{
			for (int nCloIndex = 0;nCloIndex<MARITX_Y+2;nCloIndex++)
			{
				BlockUtil[nRowIndex+1][nCloIndex]=m_BlokcUnit[nRowIndex][nCloIndex];
			}
		}
		for (int nCloIndex = 0;nCloIndex<MARITX_Y+2;nCloIndex++)
		{
			BlockUtil[0][nCloIndex]=m_BlokcUnit[MARITX_X+1][nCloIndex];
			BlockUtil[0][nCloIndex]->setPosition(ccp(nCloIndex*GRID+GRID/2,(MARITX_X-0+1)*GRID));
		}

		//ReWirte m_nBlockUtil's Point
		for (int nRowIndex = 0;nRowIndex<MARITX_X+2;nRowIndex++)
		{
			for (int nCloIndex = 0;nCloIndex<MARITX_Y+2;nCloIndex++)
			{

				m_BlokcUnit[nRowIndex][nCloIndex] = BlockUtil[nRowIndex][nCloIndex];
			}
		}
	}
	list<SnakeUnit*>* body = m_Snake->body;
	list<SnakeUnit*>::iterator begin;
	for (begin=m_Snake->body->begin(); begin!=m_Snake->body->end(); ++begin) 
	{
		SnakeUnit* item = *begin;
		list<SnakeUnit*>::iterator swap = begin;
		if (++swap !=m_Snake->body->end())
		{
			SnakeUnit* item2= *swap;
			item->setPosition(item2->x,item2->y);
		}
	}
	//m_Snake->head->setPosition(m_Snake->head->x+m_Snake->Dir.x,m_Snake->head->y+m_Snake->Dir.y);
} 