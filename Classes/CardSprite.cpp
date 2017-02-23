//
//  CardSprite.cpp
//  
//
//  Created by zh_wj on 16/8/14.
//
//

#include "CardSprite.h"
CardSprite* CardSprite::createCardSprite(int number,int size,float x,float y)
{
    auto pRet = new (std::nothrow)CardSprite();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        pRet->enemyInit(number, size, x, y);
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool CardSprite::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    return true;
}

void CardSprite::enemyInit(int number,int size,float x,float y)
{
    this->m_number = number;
    layerColorBG = LayerColor::create(Color4B(216, 210, 214, 255),size - CARD_BORDER,size - CARD_BORDER);
    layerColorBG->setPosition(Vec2(x, y));
    
    if (m_number > 0)
    {
        labelNumber = Label::create();
        labelNumber->setString(__String::createWithFormat("%i",m_number)->getCString());
        labelNumber->setSystemFontSize(36);
        labelNumber->setPosition(Vec2((size - CARD_BORDER)/2, (size - CARD_BORDER)/2));
        layerColorBG->addChild(labelNumber);
    }
    else
    {
        labelNumber = Label::create();
        labelNumber->setString("");
        labelNumber->setSystemFontSize(36);
        labelNumber->setPosition(Vec2(size/2, size/2));
        layerColorBG->addChild(labelNumber);
    }
    this->addChild(layerColorBG);
}

int CardSprite::getNumber()
{
    return m_number;
}
void CardSprite::setNumber(int num)
{
    m_number = num;
    if (m_number > 0)
    {
        labelNumber->setString(__String::createWithFormat("%d",m_number)->getCString());
        if (m_number == 2) {
            layerColorBG->setColor(Color3B(255, 246, 247));
            labelNumber->setColor(Color3B(33, 33, 7));
        }
        else if (m_number == 4)
        {
            layerColorBG->setColor(Color3B(255, 218, 163));
            labelNumber->setColor(Color3B(255, 255, 255));
        }
        else if (m_number == 8)
        {
            layerColorBG->setColor(Color3B(255, 144, 91));
        }
        else if (m_number == 16)
        {
            layerColorBG->setColor(Color3B(255, 101, 64));
        }
        else if (m_number == 32)
        {
            layerColorBG->setColor(Color3B(255, 80, 46));
        }
        else if (m_number == 64)
        {
            layerColorBG->setColor(Color3B(254, 56, 60));
        }
        else if (m_number == 128)
        {
            layerColorBG->setColor(Color3B(6, 194, 240));
        }
        else if (m_number == 256)
        {
            layerColorBG->setColor(Color3B(5, 140, 240));
        }
        else if (m_number == 512)
        {
            layerColorBG->setColor(Color3B(4, 140, 200));
        }
        else if (m_number == 1024)
        {
            layerColorBG->setColor(Color3B(3, 112, 154));
        }
        else if (m_number == 2048)
        {
            layerColorBG->setColor(Color3B(2, 98, 131));
        }
        else if (m_number == 4096)
        {
            layerColorBG->setColor(Color3B(1, 93, 118));
        }
        else if (m_number == 8192)
        {
            layerColorBG->setColor(Color3B(58, 49, 132));
        }
        else if (m_number == 16384)
        {
            layerColorBG->setColor(Color3B(41, 41, 49));
        }
        else if (m_number == 32768)
        {
            layerColorBG->setColor(Color3B(33, 33, 7));
        }
        else
        {
            layerColorBG->setColor(Color3B(0, 0, 0));
        }
        
        //调整字大小
        if (num > 10000)
        {
            labelNumber->setSystemFontSize(24);
        }
        else if (num  > 1000)
        {
            labelNumber->setSystemFontSize(28);
        }
        else if (num  > 100)
        {
            labelNumber->setSystemFontSize(34);
        }
        else if (num  > 10)
        {
            labelNumber->setSystemFontSize(38);
        }
        else
        {
            labelNumber->setSystemFontSize(44);
        }
        
    }
    else
    {
        labelNumber->setString("");
        layerColorBG->setColor(Color3B(216, 210, 214));
    }
    
}

