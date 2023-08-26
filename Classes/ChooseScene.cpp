
#include "ChooseScene.h"
#include "HelloWorldScene.h"
#include "MoveNode.h"
#include <string>
#include <iostream>
#include "ui/CocosGUI.h"

USING_NS_CC;



Scene* Choose::createScene()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto scene = Scene::create();
    auto sc = Choose::create();
    
   
    
    
    scene->addChild(sc);
    
    return scene;
}



// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(float filename)
{
    printf("Error while loading: %f\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


Sprite* Choose::addSpriteatPosition(Vec2 pos, std::string img,int tag)
{
    auto Spr = Sprite::create(img);
    Spr->setPosition(pos.x, pos.y);
    Spr->setTag(tag);
    return Spr;
}

// on "init" you need to initialize your instance
bool Choose::init()
{
    //////////////////////////////
    // 1. super init first


    if (!Scene::init())
    {

        return false;


    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto move = MoveWindowNode::create();
    this->addChild(move);

    

    auto candrag = false;

    std::string pngname[10] = {"one.png","two.png","three.png","four.png","five.png","six.png","seven.png","eight.png","nine.png","ten.png"};
    int sptag[10] = {1,2,3,4,5,6,7,8,9,10};

    for (int i = 0; i < 10; i++)
    {
        auto s = Sprite::create(pngname[i]);
        s->setTag(sptag[i]);
        if (i < 5)
        {
            s->setPosition(Vec2(visibleSize.width/6+i*visibleSize.width/6,visibleSize.height/3*2));
        }
        if (i >= 5)
        {
            s->setPosition(Vec2(visibleSize.width / 6 + (i-5) * visibleSize.width / 6, visibleSize.height / 3 * 1));
        }
        this->addChild(s);
        
    }
    candrag = true;
    auto chooselis = EventListenerTouchOneByOne::create();
    chooselis->onTouchBegan = [=](Touch* t, Event* e)
    {
        if (candrag)
        {
            auto spawn = Spawn::create(ScaleTo::create(0.1f, 0.8f), FadeTo::create(0.1f, 127), nullptr);
            auto guan = 0;
            if (this->getChildByTag(1)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 1;
            }
            if (this->getChildByTag(2)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 2;
            }
            if (this->getChildByTag(3)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 3;
            }
            if (this->getChildByTag(4)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 4;
            }
            if (this->getChildByTag(5)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 5;
            }
            if (this->getChildByTag(6)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 6;
            }
            if (this->getChildByTag(7)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 7;
            }
            if (this->getChildByTag(8)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 8;
            }
            if (this->getChildByTag(9)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 9;
            }
            if (this->getChildByTag(10)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 10;
            }
            if (guan!=0)
            {
                this->getChildByTag(guan)->runAction(spawn);
            }

            
        }
        return true;
    };
    chooselis->onTouchEnded = [=](Touch* t, Event* e)
    {
        if (candrag)
        {
            auto spawn = Spawn::create(ScaleTo::create(0.1f, 1.0f), FadeTo::create(0.1f, 255), nullptr);
            int guan = 0;
            if (this->getChildByTag(1)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 1;
            }
            if (this->getChildByTag(2)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 2;
            }
            if (this->getChildByTag(3)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 3;
            }
            if (this->getChildByTag(4)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 4;
            }
            if (this->getChildByTag(5)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 5;
            }
            if (this->getChildByTag(6)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 6;
            }
            if (this->getChildByTag(7)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 7;
            }
            if (this->getChildByTag(8)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 8;
            }
            if (this->getChildByTag(9)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 9;
            }
            if (this->getChildByTag(10)->getBoundingBox().containsPoint(t->getLocation()))
            {
                guan = 10;
            }
            if (guan!=0)
            {
                auto call = CallFunc::create([=]()
                    {
                        auto scene = HelloWorld::createScene(guan);
                        Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene));
                    });
                auto seq = Sequence::create(spawn, FadeOut::create(0.5f), call, nullptr);
                this->getChildByTag(guan)->runAction(seq);
            }
        }
    };
    for (int o = 1; o < 11; o++)
    {
        _eventDispatcher->addEventListenerWithSceneGraphPriority(chooselis->clone(), this->getChildByTag(o));
    }
    
    return true;
}


