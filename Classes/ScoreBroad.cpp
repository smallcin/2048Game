//
//  ScoreBroad.cpp
//  
//
//  Created by zh_wj on 16/8/14.
//
//

#include "ScoreBroad.h"
ScoreBroad* ScoreBroad::createScoreBroad(int score ,int width , int height ,const char*title,int type,float x,float y)
{
    auto pRet = new (std::nothrow)ScoreBroad();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        pRet->enemyInit(score, width, height, title, type, x, y);
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool ScoreBroad::init()
{
    if (!Layer::init())
    {
        return false;
    }
    return true;
}
void ScoreBroad::enemyInit(int score, int width ,int height, const char* title,int type,float x,float y)
{
    m_type = type;
    m_score = score;
    if (type == 1)
    {
        m_background = LayerColor::create(Color4B(2, 168, 209, 255), width, height);
        m_background->setPosition(Vec2(x, y));
        addChild(m_background);
        m_scoreLabel = Label::create();
        m_scoreLabel->setString(__String::createWithFormat("%d",m_score)->getCString());
        m_scoreLabel->setSystemFontSize(40);
        m_scoreLabel->setPosition(width/2, height/2);
        m_background->addChild(m_scoreLabel);
    }
    else
    {
        m_background = LayerColor::create(Color4B(215, 224, 223, 255), width, height);
        m_background->setPosition(Vec2(x, y));
        addChild(m_background);
        
        auto label = Label::create();
        label->setString(title);
        label->setSystemFontSize(36);
        label->setPosition(width/2, height -40);
        m_background->addChild(label);
        
        m_scoreLabel = Label::create();
        m_scoreLabel->setString(__String::createWithFormat("%d",m_score)->getCString());
        m_scoreLabel->setSystemFontSize(40);
        m_scoreLabel->setPosition(width/2, 50);
        m_background->addChild(m_scoreLabel);
    }
}
void ScoreBroad::setScore(int number)
{
    m_score = number;
    m_scoreLabel->setString(__String::createWithFormat("%d",m_score)->getCString());
    UserDefault::getInstance()->setIntegerForKey(MSG_HIGH_SCORE, m_score);
    UserDefault::getInstance()->flush();
    
    
}
int ScoreBroad::getScore()
{
    return this->m_score;
}
