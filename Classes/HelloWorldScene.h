
#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
using namespace std;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int guanqia);

    

    virtual bool init();

    cocos2d::Sprite* addSpriteatPosition(cocos2d::Vec2 pos, std::string img);

    bool jumptime;

    float movex,movey;


    void update(float dt);

    void kill();

    bool canmove = true;

    void CreateMap();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__

