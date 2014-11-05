#include "GameLayer.h"
#include "SnakeUnit.h"
#include "snake.h"
#include "VisibleRect.h"
#include "GameStartLayer.h"
#include "GameMapLayer.h"


GameLayer::GameLayer()
{
	m_Size =  CCDirector::sharedDirector()->getWinSize();
	GameMatrix = CCRect(m_Size.width/2-(WIDTH/2),m_Size.height/2-(HEIGHT/2),WIDTH,HEIGHT);
	isPause = false;
	isChangeDir = false;
	DirList.push_back(ccp(-1,0));
	DirList.push_back(ccp(0,1));
	DirList.push_back(ccp(1,0));
	DirList.push_back(ccp(0,-1));
}
GameLayer::~GameLayer()
{

}

void GameLayer::AddFoot()
{

	this->foot = SnakeUnit::create(ccc3(255,255,0));
	bool flag = true;	
	while(flag)
	{
		flag = false;
		foot->x = rand()%MARITX_X;
		foot->y = rand()%MARITX_Y;
		list<SnakeUnit*>::iterator begin = snake->body->begin();
		while(begin!= snake->body->end())
		{
			SnakeUnit* item = *begin;
			if (item->x == foot->x && item->y == foot->y)
			{
				flag = true;
				break;
			}
			begin++;
		}
	}
	foot->setPosition(foot->x,foot->y);
	this->addChild(foot);
}
bool GameLayer::init()
{

	setKeypadEnabled(true); 
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,0,true);
	this->initWithColor(ccc4(255,255,255,255));
	

	CCMenu* pMenu = CCMenu::create();
	CCMenuItemImage* pMenuItme = CCMenuItemImage::create("pause.png","pause.png","",this,menu_selector(GameLayer::GamePause));
	pMenuItme->setPosition(ccp(VisibleRect::bottom().x,VisibleRect::bottom().y+60));
	CCMenuItemImage* pMenuItme2 = CCMenuItemImage::create("restart.png","restart.png","",this,menu_selector(GameLayer::GameRestart));
	pMenuItme2->setPosition(ccp(VisibleRect::rightBottom().x-60,VisibleRect::rightBottom().y+60));
	CCMenuItemImage* pMenuItme3 = CCMenuItemImage::create("home.png","home.png","",this,menu_selector(GameLayer::BackHome));
	pMenuItme3->setPosition(ccp(VisibleRect::leftBottom().x+60,VisibleRect::rightBottom().y+60));

	pMenu->setPosition(CCPointZero);
	pMenu->addChild(pMenuItme);
	pMenu->addChild(pMenuItme2);
	pMenu->addChild(pMenuItme3);
	this->addChild(pMenu);
	snake = new Snake(4);
	list<SnakeUnit*>::iterator begin;
	for (begin=snake->body->begin(); begin!=snake->body->end(); ++begin) 
	{
 		SnakeUnit* item =/*(SnakeUnit*)&*/ *begin;
		this->addChild(item);
	}
	AddFoot();
	this->scheduleUpdate();
	this->schedule(schedule_selector(GameLayer::Move), 0.2f);

/*
	this->pGameMap = GameMapLayer::create();
	this->addChild(pGameMap);*/
	return true;
}


void GameLayer::draw()
{
	CCLayerColor::draw();
	CHECK_GL_ERROR_DEBUG();
	glLineWidth( 1.0f ); 
	ccDrawColor4B(191,191,191,255);
	ccDrawRect(ccp(GameMatrix.getMinX(),GameMatrix.getMinY()),ccp(GameMatrix.getMaxX(),GameMatrix.getMaxY()));
	for (int i=0;i<MARITX_X;i++)
	{
		ccDrawLine(ccp(i*GRID+GameMatrix.getMinX(),GameMatrix.getMinY()),ccp(i*GRID+GameMatrix.getMinX(),GameMatrix.getMaxY()));
	}
	for (int i=0;i<MARITX_Y;i++)
	{
		ccDrawLine(ccp(GameMatrix.getMinX(),i*GRID+GameMatrix.getMinY()),ccp(GameMatrix.getMaxX(),i*GRID+GameMatrix.getMinY()));
	}
}
//win下方向键支持
void GameLayer::keyArrowClicked(int arrow)  
{  
	if (!isChangeDir)
	{
		if (arrow == kTypeLeftArrowClicked&&snake->Dir.x!=1)  
		{  
			// 左方向键按下  
			snake->Dir = ccp(-1,0);
		}  
		else if (arrow == kTypeRightArrowClicked&&snake->Dir.x!=-1)  
		{  
			// 右方向键按下 
			snake->Dir = ccp(1,0);
			//pGameMap->runAction(CCRotateBy::create(0.2,90));
			//this->setRotation(90);

		}  
		if (arrow == kTypeUpArrowClicked&&snake->Dir.y!=-1)  
		{  
			// 上方向键按下 
			snake->Dir = ccp(0,1);
		}  
		else if (arrow == kTypeDownArrowClicked&&snake->Dir.y!=1)  
		{  
			// 下方向键按下  
			snake->Dir = ccp(0,-1);
		}
		isChangeDir = true;
	}
}  

void GameLayer::keyEnterClicked()  
{  
	// Enter键按下  
}  



void GameLayer::update(float dt)
{
	//默认定时器
	//CCLog("%f",snake->head->getPositionX()+dt);
	
	
}

void GameLayer::Move(float dt)
{
	if (snake->head->checkOverflow(snake->head->x+snake->Dir.x,snake->head->y+snake->Dir.y))
	{
		if (snake->head->x<0)
		{
			snake->head->x = MARITX_X-1;
		}
		else if (snake->head->x>MARITX_X-1)
		{
			snake->head->x = 0;
		}
		else if (snake->head->y>MARITX_Y-1)
		{
			snake->head->y = 0;
		}
		else if (snake->head->x < 0)
		{
			snake->head->y = MARITX_Y-1;
		}
		
	}
	//设定定时器
	if (snake->checkEatSelf())
	{
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
		
		unschedule(schedule_selector(GameLayer::Move));
		return;
	}
	if (snake->EatFoot(foot))
	{
		AddFoot();
	}
	list<SnakeUnit*>* body = snake->body;
	list<SnakeUnit*>::iterator begin;
	for (begin=snake->body->begin(); begin!=snake->body->end(); ++begin) 
	{
		SnakeUnit* item =/*(SnakeUnit*)&*/ *begin;
		list<SnakeUnit*>::iterator swap = begin;
		if (++swap !=snake->body->end())
		{
			SnakeUnit* item2= *swap;
			item->setPosition(item2->x,item2->y);
		}
	}
	snake->head->setPosition(snake->head->x+snake->Dir.x,snake->head->y+snake->Dir.y);
	isChangeDir = false;
}

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	prePoint = pTouch->getLocation();
	return true;
}
void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	if (!isChangeDir)
	{
		CCPoint curPoint = pTouch->getLocation();
		if(curPoint.x-prePoint.x>30&&fabs(curPoint.x-prePoint.x)>fabs(curPoint.y-prePoint.y)&&snake->Dir.x!=-1){//右
			CCLog("right");
			snake->Dir = ccp(1,0);
		}
		else if(curPoint.x-prePoint.x<-30&&fabs(curPoint.x-prePoint.x)>fabs(curPoint.y-prePoint.y)&&snake->Dir.x!=1)//左
		{
			CCLog("left");
			snake->Dir = ccp(-1,0);
		}
		else if(curPoint.y - prePoint.y>30&&fabs(curPoint.y-prePoint.y)>fabs(curPoint.x-prePoint.x)&&snake->Dir.y!=-1)//上
		{
			CCLog("up");
			snake->Dir = ccp(0,1);
		}
		else if(curPoint.y - prePoint.y<-30&&fabs(curPoint.y-prePoint.y)>fabs(curPoint.x-prePoint.x)&&snake->Dir.y!=1)//下
		{
			CCLog("down");
			snake->Dir = ccp(0,-1);
		}
		//this->Move(0);
		isChangeDir = true;
	}
}
void GameLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	
}


void GameLayer::GamePause(CCObject *sender)
{
	CCMenuItemImage* Item = (CCMenuItemImage*)sender;

	if (isPause)
	{
		isPause = false;
		CCSprite* pSprite = CCSprite::create("pause.png");
		Item->setNormalImage(pSprite);
		//this->schedule(schedule_selector(GameLayer::Move), 0.5f);
	}
	else
	{
		isPause = true;
		CCSprite* pSprite = CCSprite::create("start.png");
		Item->setNormalImage(pSprite);
		//this->unschedule(schedule_selector(GameLayer::Move));
	}
}

void GameLayer::BackHome(CCObject *sender)
{
	CCScene* pScene = CCScene::create();
	pScene->addChild(GameStartLayer::create());
	CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5,pScene));

}

void GameLayer::GameRestart(CCObject *sender)
{
	CCScene* pScene = CCScene::create();
	pScene->addChild(GameLayer::create());
	CCDirector::sharedDirector()->replaceScene(CCTransitionTurnOffTiles::create(0.5,pScene));
}


void GameLayer::initMapMaritx()
{	
	vector<int> intV;
	for (int i = 0;i<20;i++)
	{
		 intV.clear();javascript:;
		 for (int j = 0;j<20;j++)
			intV.push_back(1);
		 m_MapMaritx.push_back(intV);
	}
	for (int i = 0;i<4;i++)
	{
		m_MapMaritx[10][i] = 7;
		if (i == 3)
		{
			i = 77;
		}
	}
	vector<CCSprite*> CCspriteUnit;
	int x = 0,y = 0;
	bool isFind = false;
	while (!isFind)
	{
		while(!isFind)
		{
			if (m_MapMaritx[x][y] == 77)
			{
				isFind = true;
			}
			y++;
		}
		x++;
	}
}

