//
//  TipsView.hpp
//  2048Game
//
//  Created by zh_wj on 2016/12/4.
//
//

#ifndef TipsView_hpp
#define TipsView_hpp

#include "cocos2d.h"
using namespace cocos2d;

class TipsView : public Layer
{
public:
    static TipsView* create(std::string label);
private:
    virtual bool init();
    

};



#endif /* TipsView_hpp */
