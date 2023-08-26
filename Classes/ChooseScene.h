
#ifndef __CHOOSE_SCENE_H__
#define __CHOOSE_SCENE_H__

#include "cocos2d.h"
using namespace std;

class Choose : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    cocos2d::Sprite* addSpriteatPosition(cocos2d::Vec2 pos, std::string img,int tag);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Choose);
};

#endif 


