#ifndef __GAME_START_H__

#define __GAME_START_H__

#define GRID 20 //格子大小
#define RECTANGLE 980
#define MARITX_X WIDTH/GRID
#define MARITX_Y HEIGHT/GRID

#include "cocos-ext.h"
#include "cocos2d.h"
#include "snake.h"
#include "GameMapLayer.h"
#include <iostream>
#include "MapUnit.h"

USING_NS_CC;
USING_NS_CC_EXT;

enum MapType{
	Space = 0,
	SnakeHead = 77,
	SnakeBody = 7
};

class GameLayer:public CCLayerColor
{
public:
	GameLayer();
	~GameLayer();
public:
	bool init();
	CREATE_FUNC(GameLayer);
	//void Move(float dt);
	//void draw();
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void GamePause(CCObject *sender);
	void GameRestart(CCObject *sender);
	void BackHome(CCObject *sender);
	void update(float dt);
	void MenuCallBack(CCObject *sender);
	//按键监控
	void keyArrowClicked(int arrow);  
	void keyEnterClicked();
	void AddFoot();
	//初始化地图
	void initMapMaritx();
	void initSnake();
	void initMapUnit();
	int CalculatePosition(int Num_1,int Num_2,bool isHorizontal,bool isZero);
	//移动地图
	void MapMaritx();
public:
	CCSize m_Size;
	CCRect GameMatrix;
	bool isPause;
	bool isChangeDir;
	CCRect GameRect;
	Snake* snake;
	GameMapLayer* pGameMap;
	CCPoint prePoint;
	std::vector<vector<int>> m_MapMaritx;
	std::vector<vector<MapUnit*>> m_MapBlockUnit;
	list<CCPoint> DirList;
	int m_height;
	int m_width;
protected:

private:
};



#endif