//
//  GameView.h
//  
//
//  Created by zh_wj on 16/8/14.
//
//

#ifndef ____GameView__
#define ____GameView__

#include "cocos2d.h"
#include "CardSprite.h"
#include "ScoreBroad.h"
USING_NS_CC;
#define TOUCH_LONG 50
#define TOUCH_SHORT 20

class GameView : public Layer
{
public:
    static Scene* createScene();
private:
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    GameView(){};
    ~GameView(){};
    CREATE_FUNC(GameView);
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    
    
    bool doRight();
    bool doLeft();
    bool doUp();
    bool doDown();
    void createCard();
    void updataScore(CardSprite* cardSpr);
private:
    CardSprite* card[4][4];
    ScoreBroad* m_broad[3];
    EventListenerTouchOneByOne* m_listener;
    bool m_isLock;
    //起始点击点
    float m_x;
    float m_y;
    bool isdo;
    
    int m_record;//最高记录
    int m_score;//当前分数
    int m_demo;//目标分数
};

#endif /* defined(____GameView__) */
