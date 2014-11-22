#ifndef __GAME_START_H__

#define __GAME_START_H__

#define GRID 60 //格子大小
#define RECTANGLE 1260
#define MARITX_X WIDTH/GRID
#define MARITX_Y HEIGHT/GRID

#include "cocos-ext.h"s
#include "cocos2d.h"
#include "snake.h"
#include <iostream>
#include "MapUnit.h"

USING_NS_CC;
USING_NS_CC_EXT;



class GameLayer:public CCLayerColor
{
public:
	GameLayer();
	~GameLayer();
public:
	bool init();
	CREATE_FUNC(GameLayer);
	void Move(float dt);
	//void draw();
	void update(float dt);
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	void GamePause(CCObject *sender);
	void GameRestart(CCObject *sender);
	void BackHome(CCObject *sender);
	void MenuCallBack(CCObject *sender);
	//按键监控
	void keyArrowClicked(int arrow);  
	void keyEnterClicked();
	void AddFoot();
	//初始化地图
	void initMapMaritx();
	//void initSnake();
	void initMapUnit();
	int CalculatePosition(int Num_1,int Num_2,bool isHorizontal,bool isZero);
	//移动地图
	void MoveMapMaritx();
	void makeSnake();
	//设置方向
	void setDir(bool positive);
	void setDir(int position);
	void setDir(int x,int y);
	//游戏方向旋转动作结束
	void animateOver();
public:
	CCSize m_Size;
	CCRect GameMatrix;
	bool isPause;
	bool isChangeDir;
	CCRect GameRect;
	Snake* snake;
	CCPoint prePoint;
	std::vector<vector<int>> m_MapMaritx;
	std::vector<vector<MapUnit*>> m_MapBlockUnit;
	list<CCPoint*> DirList;
	int m_height;
	int m_width;
	CCSprite *m_GameLayout;
protected:

private:
};



#endif