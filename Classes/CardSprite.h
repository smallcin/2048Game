//
//  CardSprite.h
//  
//
//  Created by zh_wj on 16/8/14.
//
//

#ifndef ____CardSprite__
#define ____CardSprite__

#include "cocos2d.h"
USING_NS_CC;

#define CARD_BORDER 4
class CardSprite : public Sprite
{
public:
    int getNumber();
    void setNumber(int num);
    static CardSprite* createCardSprite(int number,int size,float x,float y);
    void enemyInit(int number,int size,float x,float y);
    virtual bool init();
    CREATE_FUNC(CardSprite);
    
private:
    int m_number;
    Label* labelNumber;
    LayerColor* layerColorBG;
    
};

#endif /* defined(____CardSprite__) */
