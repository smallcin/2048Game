//
//  ScoreBroad.h
//  
//
//  Created by zh_wj on 16/8/14.
//
//

#ifndef ____ScoreBroad__
#define ____ScoreBroad__

#include "cocos2d.h"
USING_NS_CC;

#define MSG_HIGH_SCORE   "msg_high_score"  //当前分数
class ScoreBroad : public Layer
{
public:
    static ScoreBroad* createScoreBroad(int score ,int width , int height ,const char*title,int type,float x,float y);
    void setScore(int number);
    int getScore();
private:
    CREATE_FUNC(ScoreBroad);
    virtual bool init();
    void enemyInit(int score, int width ,int height, const char* title,int type,float x,float y);
    
private:
    int m_type;
    int m_score;
    Label* m_scoreLabel;
    LayerColor* m_background;
};

#endif /* defined(____ScoreBroad__) */
