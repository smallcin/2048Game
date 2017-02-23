//
//  GameView.cpp
//  
//
//  Created by zh_wj on 16/8/14.
//
//

#include "GameView.h"

Scene* GameView::createScene()
{
    auto scene = Scene::create();
    auto layer = GameView::create();
    scene->addChild(layer);
    return scene;
}

bool GameView::init()
{
    if (!Layer::init())
    {
        return false;
    }
    this->m_isLock = false;
    auto size = Director::getInstance()->getWinSize();
    int width = size.width;
    
    int cardSize = width/4;
    
    auto baseBG = LayerColor::create(Color4B::BLACK, width, width);
    baseBG->setPosition(2, 100);
    this->addChild(baseBG);
    
    m_listener = EventListenerTouchOneByOne::create();
    m_listener->onTouchBegan = CC_CALLBACK_2(GameView::onTouchBegan, this);
    m_listener->onTouchMoved = CC_CALLBACK_2(GameView::onTouchMoved, this);
    m_listener->onTouchEnded = CC_CALLBACK_2(GameView::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
    
    auto background = LayerColor::create(Color4B::WHITE);
    this->addChild(background);
    
    
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //初始化
            card[i][j] = CardSprite::createCardSprite(0, cardSize, cardSize * i + CARD_BORDER/2, cardSize * j + 100);
            addChild(card[i][j]);
        }
    }
    //创建两个新卡片
    this->createCard();
    this->createCard();
    
    //
    m_broad[0] = ScoreBroad::createScoreBroad(2048, 180, 160, "", 1, 15, size.height-200);
    addChild(m_broad[0]);
    
    //最高分
    int curScore = UserDefault::getInstance()->getIntegerForKey(MSG_HIGH_SCORE, 0);
    m_broad[1] = ScoreBroad::createScoreBroad(curScore, 160, 160, "high", 2, 240, size.height-200);
    addChild(m_broad[1]);
    
    //当前分数
    
    m_broad[2] = ScoreBroad::createScoreBroad(0, 160, 160, "score", 2, 450, size.height - 200);
    addChild(m_broad[2]);
    
    return true;
}
void GameView::onEnter()
{
    Layer::onEnter();
}
void GameView::onExit()
{
    Layer::onExit();
    _eventDispatcher->removeEventListener(m_listener);
}

void GameView::createCard()
{
    int i = CCRANDOM_0_1() * 4;
    int j = CCRANDOM_0_1() * 4;
    //判断这个位置是否已经存在卡片
    if (card[i][j]->getNumber() > 0)
    {
        createCard();
    }
    else
    {
        card[i][j]->setNumber(2);
    }
}

bool GameView::onTouchBegan(Touch *touch, Event *unused_event)
{
    //记录开始触摸时的坐标
    this->m_x = touch->getLocation().x;
    this->m_y = touch->getLocation().y;
    
    return true;
}
void GameView::onTouchMoved(Touch *touch, Event *unused_event)
{
    if (!m_isLock)
    {
        float dx = touch->getLocation().x - this->m_x;
        float dy = touch->getLocation().y - this->m_y;
        if (dx > TOUCH_LONG && std::fabs(dy) < TOUCH_SHORT)
        {
            
            if (doRight())
            {
                createCard();
            }
            this->m_isLock = true;
        }
        else if (dx < -TOUCH_LONG && std::fabs(dy) < TOUCH_SHORT)
        {
            
            if (doLeft())
            {
                createCard();
            }
            this->m_isLock = true;
        }
        else if ( dy > TOUCH_LONG && std::fabs(dx) < TOUCH_SHORT)
        {
            
            if (doUp())
            {
                createCard();
            }
            this->m_isLock = true;
        }
        else if (dy < -TOUCH_LONG && std::fabs(dx) < TOUCH_SHORT)
        {
            
            if (doDown())
            {
                createCard();
            }
            this->m_isLock = true;
        }
    }
}
void GameView::onTouchEnded(Touch *touch, Event *unused_event)
{
    //触摸结束
    this->m_isLock = false;
}

void GameView::updataScore(CardSprite* cardSpr)
{
    if (cardSpr != nullptr)
    {
        m_broad[2]->setScore(m_broad[2]->getScore() + cardSpr->getNumber());
        if (m_broad[1]->getScore() < m_broad[2]->getScore())
        {
            m_broad[1]->setScore(m_broad[2]->getScore());
        }
    }

}



bool GameView::doRight()
{
    //CCLOG("doRight");
    bool isdo = false;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 3; x >= 0; x--)
        {
            for (int x1 = x - 1; x1 >= 0; x1--)
            {
                if (card[x1][y]->getNumber() > 0)
                {
                    if (card[x][y]->getNumber() <= 0)
                    {
                        //当前卡片为零时直接移动其左侧卡片
                        card[x][y]->setNumber(card[x1][y]->getNumber());
                        card[x1][y]->setNumber(0);
                        x++;
                        isdo = true;
                    }
                    else if (card[x][y]->getNumber() == card[x1][y]->getNumber())
                    {
                        card[x][y]->setNumber(card[x][y]->getNumber()*2);
                        card[x1][y]->setNumber(0);
                        updataScore(card[x][y]);
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;

}
bool GameView::doLeft()
{
    //CCLOG("doLeft");
    bool isdo = false;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            for (int x1 = x + 1; x1 < 4; x1++)
            {
                if (card[x1][y]->getNumber() > 0)
                {
                    if (card[x][y]->getNumber() <= 0)
                    {
                        //当前卡片为零时直接移动其右侧卡片
                        card[x][y]->setNumber(card[x1][y]->getNumber());
                        card[x1][y]->setNumber(0);
                        x--;
                        isdo = true;
                    }
                    else if (card[x][y]->getNumber() == card[x1][y]->getNumber())
                    {
                        card[x][y]->setNumber(card[x][y]->getNumber()*2);
                        card[x1][y]->setNumber(0);
                        updataScore(card[x][y]);
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;
}

bool GameView::doUp()
{
    //CCLOG("doUp");
    bool isdo = false;
    for (int x = 0; x < 4; x++)
    {
        for (int y = 3; y >= 0; y--)
        {
            for (int y1 = y - 1; y1 >= 0; y1--)
            {
                if (card[x][y1]->getNumber() > 0)
                {
                    if (card[x][y]->getNumber() <= 0)
                    {
                        card[x][y]->setNumber(card[x][y1]->getNumber());
                        card[x][y1]->setNumber(0);
                        y++;
                        isdo = true;
                    }
                    else if (card[x][y]->getNumber() == card[x][y1]->getNumber())
                    {
                        card[x][y]->setNumber(card[x][y]->getNumber()*2);
                        card[x][y1]->setNumber(0);
                        updataScore(card[x][y]);
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;
}
bool GameView::doDown()
{
    ///CCLOG("doDown");
    bool isdo = false;
    for (int x = 0; x < 4; x++)
    {
        for (int y = 0; y < 4; y++)
        {
            for (int y1 = y + 1; y1 < 4; y1++)
            {
                if (card[x][y1]->getNumber() > 0)
                {
                    if (card[x][y]->getNumber() <= 0)
                    {
                        card[x][y]->setNumber(card[x][y1]->getNumber());
                        card[x][y1]->setNumber(0);
                        y--;
                        isdo = true;
                    }
                    else if (card[x][y]->getNumber() == card[x][y1]->getNumber())
                    {
                        card[x][y]->setNumber(card[x][y]->getNumber()*2);
                        card[x][y1]->setNumber(0);
                        updataScore(card[x][y]);
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    return isdo;

}

