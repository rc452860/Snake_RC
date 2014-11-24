#include "GameLayer.h"
#include "snake.h"
#include "VisibleRect.h"
#include "snakeBlock.h"
#include "GameStartLayer.h"


GameLayer::GameLayer()
{
	m_Size =  CCDirector::sharedDirector()->getWinSize();
	isPause = false;
	isChangeDir = false;
	DirList.push_back(new ccp(-1,0));
	DirList.push_back(new ccp(0,1));
	DirList.push_back(new ccp(1,0));
	DirList.push_back(new ccp(0,-1));
	gameSpeed = 0.2f;
}
GameLayer::~GameLayer()
{
	delete snake;
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
	pMenu->setZOrder(1000);
	this->addChild(pMenu);
	snake = new Snake();
	snake->setParent(this);
	this->schedule(schedule_selector(GameLayer::Move),gameSpeed);
	initMapMaritx();
	return true;
}



//win下方向键支持
void GameLayer::keyArrowClicked(int arrow)  
{  
	if (!isChangeDir)
	{
		isChangeDir = true;
		if (arrow == kTypeLeftArrowClicked)
		{
			setDir(false);
			m_GameLayout->runAction(CCSequence::create(CCRotateBy::create(gameSpeed,90),CCCallFunc::create(this,callfunc_selector(GameLayer::animateOver)),NULL));
		}
		else if(arrow == kTypeRightArrowClicked)
		{
			setDir(true);
			m_GameLayout->runAction(CCSequence::create(CCRotateBy::create(gameSpeed,-90),CCCallFunc::create(this,callfunc_selector(GameLayer::animateOver)),NULL));
		}
		
		/*CCPoint* pDir = snake->getDir();
		if (arrow == kTypeLeftArrowClicked&&pDir->x!=1)  
		{  
			// 左方向键按下  
			setDir(false);
			m_GameLayout->runAction(CCRotateBy::create(0.2,90));
		}  
		else if (arrow == kTypeRightArrowClicked&&pDir->x!=-1)  
		{  
			// 右方向键按下 
			 setDir(true);
			 m_GameLayout->runAction(CCRotateBy::create(0.2,-90));
			//pGameMap->runAction(CCRotateBy::create(0.2,90));
			//this->setRotation(90);
		}  
		else if (arrow == kTypeUpArrowClicked&&pDir->y!=-1)  
		{  
			// 上方向键按下 
			 setDir(0,1);
		}  
		else if (arrow == kTypeDownArrowClicked&&pDir->y!=1)  
		{  
			// 下方向键按下  
			setDir(0,-1);
		}*/
		isChangeDir = true;
	}
}  

void GameLayer::keyEnterClicked()  
{  
	
	// Enter键按下  
}  

void GameLayer::Move(float dt)
{
	MoveMapMaritx();
	
}
 
void GameLayer::update(float dt)
{

}
void GameLayer::MoveMapMaritx()
{
#pragma region 转向
	//左上右下的顺序
	if (snake->getDir()->x == -1&&snake->getDir()->y == 0)
	{
		for (int nRowIndex = (m_MapBlockUnit.size()-1);nRowIndex>=0;nRowIndex--)
		{
			for (int nColIndex = (m_MapBlockUnit.size()-1);nColIndex>=0;nColIndex--)
			{
				MapUnit* tempUnit = m_MapBlockUnit[nRowIndex][nColIndex];
				tempUnit->setPosition(ccp(tempUnit->getPositionX()+GRID,tempUnit->getPositionY()));
				if (nRowIndex+1 == m_MapBlockUnit.size())
				{
					tempUnit->removeFromParent();
				}
				if (nRowIndex-1>= 0)
				{
					m_MapBlockUnit[nRowIndex][nColIndex] = m_MapBlockUnit[nRowIndex-1][nColIndex];
				}
				else
				{
					int x = (tempUnit->x-1)<0?(m_MapMaritx.size()-1):(tempUnit->x-1),y = tempUnit->y;
					tempUnit = MapUnit::create(m_MapMaritx[x][y]);
					tempUnit->x = x;
					tempUnit->y = y;
					tempUnit->setPosition(ccp(nRowIndex*(GRID)+(GRID/2),nColIndex*(GRID)+(GRID/2)));
					m_GameLayout->addChild(tempUnit);
					m_MapBlockUnit[nRowIndex][nColIndex] = tempUnit;
				}
			}
		}
	}
	else if(snake->getDir()->x ==0&&snake->getDir()->y ==1)
	{
		for (int nRowIndex = 0;nRowIndex<m_MapBlockUnit.size();nRowIndex++)
		{
			for (int nColIndex =0;nColIndex<m_MapBlockUnit.size();nColIndex++)
			{
				MapUnit* tempUnit = m_MapBlockUnit[nRowIndex][nColIndex];
				tempUnit->setPosition(ccp(tempUnit->getPositionX(),tempUnit->getPositionY()-GRID));
				if (nColIndex == 0)
				{
					tempUnit->removeFromParent();
				}
				if (nColIndex+1<m_MapBlockUnit.size())
				{
					m_MapBlockUnit[nRowIndex][nColIndex] = m_MapBlockUnit[nRowIndex][nColIndex+1];
				}
				else
				{
					int x = tempUnit->x;
					int y = (tempUnit->y+1)>=m_MapMaritx.size()?0:tempUnit->y+1;
					tempUnit = MapUnit::create(m_MapMaritx[x][y]);
					tempUnit->x = x;
					tempUnit->y = y;
					tempUnit->setPosition(ccp(nRowIndex*(GRID)+(GRID/2),nColIndex*(GRID)+(GRID/2)));
					m_GameLayout->addChild(tempUnit);
					m_MapBlockUnit[nRowIndex][nColIndex] = tempUnit;
				}
			}
		}
	}
	else if(snake->getDir()->x == 1&&snake->getDir()->y == 0)
	{
		for (int nRowIndex=0;nRowIndex<m_MapBlockUnit.size();nRowIndex++)
		{
			for (int nColIndex = 0;nColIndex<m_MapBlockUnit.size();nColIndex++)
			{
				MapUnit* tempUnit = m_MapBlockUnit[nRowIndex][nColIndex];
				tempUnit->setPosition(ccp(tempUnit->getPositionX()-GRID,tempUnit->getPositionY()));
				if (nRowIndex == 0)
				{
					tempUnit->removeFromParent();
				}
				if (nRowIndex+1<m_MapBlockUnit.size())
				{
					m_MapBlockUnit[nRowIndex][nColIndex] = m_MapBlockUnit[nRowIndex+1][nColIndex];
				}
				else
				{
					int x = (tempUnit->x+1)>=m_MapMaritx.size()?0:tempUnit->x+1,y = tempUnit->y;
					tempUnit = MapUnit::create(m_MapMaritx[x][y]);
					tempUnit->x = x;
					tempUnit->y = y;
					tempUnit->setPosition(ccp(nRowIndex*(GRID)+(GRID/2),nColIndex*(GRID)+(GRID/2)));
					m_GameLayout->addChild(tempUnit);
					m_MapBlockUnit[nRowIndex][nColIndex] = tempUnit;
				}
			}
		}
	}
	else if (snake->getDir()->x == 0&&snake->getDir()->y == -1)
	{
		for (int nRowIndex =(m_MapBlockUnit.size()-1);nRowIndex>=0;nRowIndex--)
		{
			for (int nColIndex = (m_MapBlockUnit.size()-1);nColIndex>=0;nColIndex--)
			{
				MapUnit* tempUnit = m_MapBlockUnit[nRowIndex][nColIndex];
				tempUnit->setPosition(ccp(tempUnit->getPositionX(),tempUnit->getPositionY()+GRID));
				if (nColIndex == (m_MapBlockUnit.size()-1))
				{
					tempUnit->removeFromParent();
				}
				if (nColIndex-1>=0)
				{
					m_MapBlockUnit[nRowIndex][nColIndex] = m_MapBlockUnit[nRowIndex][nColIndex-1];
				}
				else
				{
					int x = tempUnit->x,y = tempUnit->y;
					if (y-1>=0)
					{
						tempUnit = MapUnit::create(m_MapMaritx[x][y-1]);
						tempUnit->x= x;
						tempUnit->y = y-1;

					}
					else
					{
						tempUnit = MapUnit::create(m_MapMaritx[x][(m_MapMaritx.size()-1)]);
						tempUnit->x= x;
						tempUnit->y = (m_MapMaritx.size()-1);
					}
					m_MapBlockUnit[nRowIndex][nColIndex] = tempUnit;
					tempUnit->setPosition(ccp(nRowIndex*(GRID)+(GRID/2),nColIndex*(GRID)+(GRID/2)));
					m_GameLayout->addChild(tempUnit);

				}
			}
		}
	}
#pragma endregion 转向
	
	snake->shiftSnake(isChangeDir);
	makeSnake();
	//方向左
	/*for (int nRowIndex = (m_MapBlockUnit.size()-1);nRowIndex>=0;nRowIndex--)
	{
		for (int nColIndex = (m_MapBlockUnit.size()-1);nColIndex>=0;nColIndex--)
		{
			MapUnit* tempUnit = m_MapBlockUnit[nRowIndex][nColIndex];
			tempUnit->setPosition(ccp(tempUnit->getPositionX()+GRID,tempUnit->getPositionY()));
			if (nRowIndex+1 == m_MapBlockUnit.size())
			{
				tempUnit->removeFromParent();
			}
			if (nRowIndex-1>= 0)
			{
				m_MapBlockUnit[nRowIndex][nColIndex] = m_MapBlockUnit[nRowIndex-1][nColIndex];
			}
			else
			{
				int x = (tempUnit->x-1)<0?(m_MapMaritx.size()-1):(tempUnit->x-1),y = tempUnit->y;
				tempUnit = MapUnit::create(m_MapMaritx[x][y]);
				tempUnit->x = x;
				tempUnit->y = y;
				tempUnit->setPosition(ccp(nRowIndex*(GRID)+(GRID/2),nColIndex*(GRID)+(GRID/2)));
				m_GameLayout->addChild(tempUnit);
				m_MapBlockUnit[nRowIndex][nColIndex] = tempUnit;
			}
		}
	}*/
	//方向右
	/*for (int nRowIndex=0;nRowIndex<m_MapBlockUnit.size();nRowIndex++)
	{
		for (int nColIndex = 0;nColIndex<m_MapBlockUnit.size();nColIndex++)
		{
			MapUnit* tempUnit = m_MapBlockUnit[nRowIndex][nColIndex];
			tempUnit->setPosition(ccp(tempUnit->getPositionX()-GRID,tempUnit->getPositionY()));
			if (nRowIndex == 0)
			{
				tempUnit->removeFromParent();
			}
			if (nRowIndex+1<m_MapBlockUnit.size())
			{
				m_MapBlockUnit[nRowIndex][nColIndex] = m_MapBlockUnit[nRowIndex+1][nColIndex];
			}
			else
			{
				int x = (tempUnit->x+1)>=m_MapMaritx.size()?0:tempUnit->x+1,y = tempUnit->y;
				tempUnit = MapUnit::create(m_MapMaritx[x][y]);
				tempUnit->x = x;
				tempUnit->y = y;
				tempUnit->setPosition(ccp(nRowIndex*(GRID)+(GRID/2),nColIndex*(GRID)+(GRID/2)));
				m_GameLayout->addChild(tempUnit);
				m_MapBlockUnit[nRowIndex][nColIndex] = tempUnit;

				
			}
		}
	}*/
	/*if (snake->Dir.x == 0 && snake->Dir.y == 1)
	{
		//向上移动
		for (int nRowIndex = 0;nRowIndex<m_MapBlockUnit.size();nRowIndex++)
		{
			for (int nColIndex =0;nColIndex<m_MapBlockUnit.size();nColIndex++)
			{
				MapUnit* tempUnit = m_MapBlockUnit[nRowIndex][nColIndex];
				tempUnit->setPosition(ccp(tempUnit->getPositionX(),tempUnit->getPositionY()-GRID));
				if (nColIndex == 0)
				{
					tempUnit->removeFromParent();
				}
				if (nColIndex+1<m_MapBlockUnit.size())
				{
					m_MapBlockUnit[nRowIndex][nColIndex] = m_MapBlockUnit[nRowIndex][nColIndex+1];
				}
				else
				{
					int x = tempUnit->x;
					int y = tempUnit->y;
					if (y+1 >= m_MapMaritx.size())
					{
						tempUnit = MapUnit::create(m_MapMaritx[x][0]);
						tempUnit->x = x;
						tempUnit->y = 0;
					}
					else
					{
						tempUnit = MapUnit::create(m_MapMaritx[x][y+1]);
						tempUnit->x = x;
						tempUnit->y = y+1;
					}
					tempUnit->setPosition(ccp(nRowIndex*(GRID)+(GRID/2),nColIndex*(GRID)+(GRID/2)));
					m_GameLayout->addChild(tempUnit);
					m_MapBlockUnit[nRowIndex][nColIndex] = tempUnit;
				}
			}
		}
	/*}
	else if (snake->Dir.x == 0&& snake->Dir.y == -1 )
	{
	//向下移动
		for (int nRowIndex =(m_MapBlockUnit.size()-1);nRowIndex>=0;nRowIndex--)
		{
			for (int nColIndex = (m_MapBlockUnit.size()-1);nColIndex>=0;nColIndex--)
			{
				MapUnit* tempUnit = m_MapBlockUnit[nRowIndex][nColIndex];
				tempUnit->setPosition(ccp(tempUnit->getPositionX(),tempUnit->getPositionY()+GRID));
				if (nColIndex == (m_MapBlockUnit.size()-1))
				{
					tempUnit->removeFromParent();
				}
				if (nColIndex-1>=0)
				{
					m_MapBlockUnit[nRowIndex][nColIndex] = m_MapBlockUnit[nRowIndex][nColIndex-1];
				}
				else
				{
					int x = tempUnit->x,y = tempUnit->y;
					if (y-1>=0)
					{
						tempUnit = MapUnit::create(m_MapMaritx[x][y-1]);
						tempUnit->x= x;
						tempUnit->y = y-1;

					}
					else
					{
						tempUnit = MapUnit::create(m_MapMaritx[x][(m_MapMaritx.size()-1)]);
						tempUnit->x= x;
						tempUnit->y = (m_MapMaritx.size()-1);
					}
					m_MapBlockUnit[nRowIndex][nColIndex] = tempUnit;
					tempUnit->setPosition(ccp(nRowIndex*(GRID)+(GRID/2),nColIndex*(GRID)+(GRID/2)));
					m_GameLayout->addChild(tempUnit);
						
				}
			}
		}
		}
	//矩阵逆时针转置90°
	/*vector<vector<MapUnit*>> tempMapBlockUnit(m_MapBlockUnit.size());
	for (int i = 0;i<m_MapBlockUnit.size();i++)
	{
		tempMapBlockUnit[i].resize(m_MapBlockUnit.size());
	}
	for (int nRowIndex = 0;nRowIndex<m_MapBlockUnit.size();nRowIndex++)
	{
		for (int nColIndex = 0;nColIndex<m_MapBlockUnit.size();nColIndex++)
		{
			MapUnit* tempUnit = m_MapBlockUnit[nColIndex][(m_MapBlockUnit.size()-1)-nRowIndex];
			tempMapBlockUnit[nRowIndex][nColIndex] = tempUnit;
			tempUnit->setPosition(ccp(nRowIndex*(GRID)+(GRID/2),nColIndex*(GRID)+(GRID/2)));
		}
	}
	m_MapBlockUnit = tempMapBlockUnit;
	
	*/

	
	
}
/*
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
SnakeUnit* item =/ *(SnakeUnit*)&* / *begin;
list<SnakeUnit*>::iterator swap = begin;
if (++swap !=snake->body->end())
{
SnakeUnit* item2= *swap;
item->setPosition(item2->x,item2->y);
}
}
isChangeDir = false;
}*/

bool GameLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	prePoint = pTouch->getLocation();
	return true;
}
void GameLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	/*if (true)
	{
		CCPoint curPoint = pTouch->getLocation();
		
		if(curPoint.x-prePoint.x>30&&fabs(curPoint.x-prePoint.x)>fabs(curPoint.y-prePoint.y)&&snake->Dir.x!=-1){//右
			CCLog("right");
			//这段代码还没想清楚s
			/ *vector<vector<int>> tempMapMaritx(m_MapMaritx.size());
			for (int i = 0;i<m_MapMaritx.size();i++)
				tempMapMaritx[i].resize(m_MapMaritx.size());
			for (int i = 0;i<m_MapMaritx.size();i++)
			{
				for (int j = 0;j<m_MapMaritx.size();j++)
				{
					tempMapMaritx[j][(m_MapMaritx.size()-1)-i] = m_MapMaritx[i][j];
				}
			}
			m_MapMaritx = tempMapMaritx;
			for (int nColIndex = 0;nColIndex<m_MapBlockUnit.size();nColIndex++)
			{
				for (int nRowIndex = 0;nRowIndex<m_MapBlockUnit.size();nRowIndex++)
				{
					MapUnit* tempUnit = m_MapBlockUnit[nColIndex][nRowIndex];
					MapUnit* swapUnit = MapUnit::create(m_MapMaritx[tempUnit->x][tempUnit->y]);
					swapUnit->x = tempUnit->x;swapUnit->y = tempUnit->y;
					swapUnit->setPosition(ccp(nColIndex*(GRID)+(GRID/2),nRowIndex*(GRID)+(GRID/2)));
					tempUnit->removeFromParent();
					m_MapBlockUnit[nColIndex][nRowIndex] = swapUnit;
					m_GameLayout->addChild(swapUnit);
				}
			}* /
			/ *vector<vector<MapUnit*>> tempMapBlockUnit(m_MapBlockUnit.size());
			for (int i = 0;i<m_MapBlockUnit.size();i++)
			{
				tempMapBlockUnit[i].resize(m_MapBlockUnit.size());
			}
			for (int nRowIndex = 0;nRowIndex<m_MapBlockUnit.size();nRowIndex++)
			{
				for (int nColIndex = 0;nColIndex<m_MapBlockUnit.size();nColIndex++)
				{
					MapUnit* tempUnit = m_MapBlockUnit[nRowIndex][nColIndex];
					tempMapBlockUnit[nColIndex][(m_MapBlockUnit.size()-1)-nRowIndex] = tempUnit;
					tempUnit->setPosition(ccp(nColIndex*(GRID)+(GRID/2),((m_MapBlockUnit.size()-1)-nRowIndex)*(GRID)+(GRID/2)));
				}
			}
			m_MapBlockUnit = tempMapBlockUnit;* /
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
	}*/
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

	this->m_height = 20;
	this->m_width = 20;
	vector<int> intV;
	//测试数据
	for (int i = 0;i<20;i++)
	{
		intV.clear();
		for (int j = 0;j<20;j++)
			intV.push_back(1);
		m_MapMaritx.push_back(intV);
	}
	/*for (int i = 0;i<4;i++)
	{
		if (i == 3)
		{
			m_MapMaritx[10][i] = 77;
		}
		else
		{
			m_MapMaritx[10][i] = 7;
		}
	}*/
	snake->head  = new ccp(19,4);
	snake->body->push_back(snake->head);
	snake->body->push_back(new ccp(19,3));
	snake->body->push_back(new ccp(19,2));
	snake->body->push_back(new ccp(19,1));
	setDir(0,1);
	/*int x = 0;
	bool isFinish = false;
	while (x<this->m_width && !isFinish)
	{
		int y = 0;
		while(y<this->m_height && !isFinish)
		{
			if (m_MapMaritx[x][y] == MapType(SnakeHead))
			{
				snake->head->x = x;
				snake->head->y = y;
				snake->body->push_back(snake->head);
				isFinish = true;
			}
			y++;
		}
		x++;
	}*/
	//initSnake();
	initMapUnit();
}


/*
void GameLayer::initSnake()
{
	bool ifFinishBody = false;
	CCPoint* preBody;
	int x = snake->head->x,y = snake->head->y;
	//找到蛇的方向
	if (m_MapMaritx[x+1][y] == MapType(SnakeBody))
	{
		snake->Dir =CCPoint(-1,0);
		preBody = new CCPoint(++x,y);
	}
	else if (m_MapMaritx[x-1][y]  == MapType(SnakeBody))
	{
		snake->Dir =CCPoint(1,0);
		preBody = new CCPoint(--x,y);
	}
	else if (m_MapMaritx[x][y-1] == MapType(SnakeBody))
	{
		snake->Dir =CCPoint(0,1);
		preBody = new CCPoint(x,--y);
	}
	else if (m_MapMaritx[x][y+1]== MapType(SnakeBody))
	{
		snake->Dir = CCPoint(x,-1);
		preBody = new CCPoint(x,++y);
	}
	snake->body->push_back(preBody);
	//找到蛇的身体
	while (!ifFinishBody)
	{
		CCPoint *pTemp = snake->body->back();
		if (y-1<0)
		{
			y = 1;
		}
		if (y+1>m_height)
		{
			y = m_height -1;
		}
		if (x-1<0)
		{
			x= 1;
		}
		if (x+1>m_width)
		{
			x = m_width-1;
		}

		if (m_MapMaritx[x+1][y] == MapType(SnakeBody)&&!snake->isInstanceOf(x+1,y))
		{
			preBody = new CCPoint(++x,y);
		}
		else if (m_MapMaritx[x-1][y]  == MapType(SnakeBody)&&!snake->isInstanceOf(x-1,y))
		{
			preBody = new CCPoint(--x,y);
		}
		else if (m_MapMaritx[x][y-1] == MapType(SnakeBody)&&!snake->isInstanceOf(x,y-1))
		{
			preBody = new CCPoint(x,--y);
		}
		else if (m_MapMaritx[x][y+1]== MapType(SnakeBody)&&!snake->isInstanceOf(x,y+1))
		{
			preBody = new CCPoint(x,++y);
		}
		else
		{
			ifFinishBody = true;
		}
		if (!snake->isInstanceOf(preBody->x,preBody->y))
		{
			snake->body->push_back(preBody);
		}
	}
	CCLog("finish find snake body");
}
*/


void GameLayer::initMapUnit()
{
	m_GameLayout = CCSprite::create();
	m_GameLayout->setTextureRect(CCRect(0,0,RECTANGLE,RECTANGLE));
	m_GameLayout->setContentSize(CCSize(ccp(RECTANGLE,RECTANGLE)));
	int center = (((RECTANGLE /GRID)-1)/2)+1;

	int x_zero,y_zero;
	vector<MapUnit*> MapTempUnit;
	for (int i = 0;i<RECTANGLE/GRID;i++)
	{
		MapTempUnit.clear();
		for (int j = 0;j<RECTANGLE /GRID;j++)
		{
			if (i==0&&j==0)
			{
				MapUnit* item = MapUnit::create(m_MapMaritx[CalculatePosition(snake->head->x,center,true,true)][CalculatePosition(snake->head->y,center,false,true)]);
				item->x = x_zero =CalculatePosition(snake->head->x,center-1,true,true);
				item->y = y_zero = CalculatePosition(snake->head->y,center-1,false,true);
				item->setPosition(ccp((GRID/2),(GRID/2)));
				MapTempUnit.push_back(item);
				m_GameLayout->addChild(item);
			}
			else
			{
				MapUnit* item = MapUnit::create(m_MapMaritx[CalculatePosition(x_zero,i,true,false)][CalculatePosition(y_zero,j,false,false)]);
				item->x =CalculatePosition(x_zero,i,true,false);
				item->y = CalculatePosition(y_zero,j,false,false);
				item->setPosition(ccp(i*(GRID)+(GRID/2),j*(GRID)+(GRID/2)));
				MapTempUnit.push_back(item);
				m_GameLayout->addChild(item);
			}
		}
		m_MapBlockUnit.push_back(MapTempUnit); 
	}
	m_GameLayout->setPosition(ccp(320,480));
	this->addChild(m_GameLayout);
	makeSnake();
}

int GameLayer::CalculatePosition(int Num_1,int Num_2,bool isHorizontal,bool isZero)
{
	int result = -1;
	if (isZero)
	{
		result = Num_1 - Num_2;
		while (!(result >= 0))
		{
			if (isHorizontal)
				result += m_width;	
			else
				result += m_height;
		}
		return result;
	}
	else
	{
		result = Num_1+Num_2;
		bool flag = false;
		if (isHorizontal)
		{
			while (result>(m_width-1))
			{
				result -= m_width;
			}
		}
		else
		{
			while (result>(m_height-1))
			{
				result -= m_height;
			}
		}
		return result;
	}
}

void GameLayer::setGameLayerDir()
{
	CCPoint* pDir = snake->getDir();
}
void GameLayer::setDir(bool positive)
{
	if (positive)
	{
		if (++snake->Dir == DirList.end())
			snake->Dir = DirList.begin();
	}
	else
	{
		if (snake->Dir == DirList.begin())
			snake->Dir = --DirList.end();
		else
			--snake->Dir;
	}
}

void GameLayer::setDir(int position)
{
	if (position+1 > DirList.size())
	{
		CCLog("position is unexpected");
		return;
	}

	list<CCPoint*>::iterator begin = DirList.begin();
	for (int i = position;i>=0;i--)
	{
		begin ++;
	}
	snake->Dir = begin;
}

void GameLayer::setDir(int x,int y)
{
	bool isFind =false;
	for (list<CCPoint*>::iterator begin = DirList.begin();begin!= DirList.end();begin++)
	{
		CCPoint* pPoint = *begin;
		if (pPoint->x == x&&pPoint->y == y)
		{
			snake->Dir = begin;
			isFind = true;
		}
	}
	if(isFind)
		CCLog("find dir");
	else
		CCLog("not find");
	setGameLayerDir();
}

void GameLayer::makeSnake()
{
	for(int nRowIndex = 0;nRowIndex<m_MapBlockUnit.size()-1;nRowIndex++)
	{
		for (int nColIndex = 0;nColIndex<m_MapBlockUnit.size()-1;nColIndex++)
		{
			MapUnit* tempUnit = m_MapBlockUnit[nRowIndex][nColIndex];
			tempUnit->removeAllChildren();
			list<CCPoint*>::iterator begin = snake->body->begin();
			while (begin!= snake->body->end())
			{
				CCPoint* pPoint = *begin;
				if (tempUnit->x == pPoint->x && tempUnit->y == pPoint->y)
				{
					snakeBlock* snakeBodyUnit = snakeBlock::create(snakeBody);
					//MapUnit* snakeBodyUnit = MapUnit::create(7);
					snakeBodyUnit->setPosition(ccp(nRowIndex*GRID+(GRID/2),nColIndex*GRID+(GRID/2)));
					snakeBodyUnit->setPosition(ccp((GRID/2),(GRID/2)));
					tempUnit->addChild(snakeBodyUnit);
				}
				begin++;
			}
		}
	}
}


void GameLayer::animateOver()
{
	this->isChangeDir = false;
}

/*
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
}*/