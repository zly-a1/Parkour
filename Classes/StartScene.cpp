
#include "StartScene.h"
#include "ChooseScene.h"
#include "MoveNode.h"
#include <string>
#include <iostream>
#include "ui/CocosGUI.h"

USING_NS_CC;

 


Scene* Start::createScene()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto scene = Scene::create();
    auto st = Start::create();

    
    
    scene->addChild(st);
    return scene;
}



// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(float filename)
{
    printf("Error while loading: %f\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


// on "init" you need to initialize your instance
bool Start::init()
{
    //////////////////////////////
    // 1. super init first


    if (!Scene::init())
    {

        return false;


    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    this->scheduleUpdate();

    auto move = MoveWindowNode::create();
    this->addChild(move);

    
    

    auto button = Sprite::create("Button.png");
    button->setName("play");
    button->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(button);
    auto lis = EventListenerTouchOneByOne::create();
    lis->onTouchBegan = [=](Touch* t, Event* e)
    {
        if (!button->getBoundingBox().containsPoint(t->getLocation()))
        {
            return false;
        }
        button->runAction(Spawn::create(ScaleTo::create(0.5f, 0.7f), FadeTo::create(0.5f, 127), nullptr));
        return true;
    };

    lis->onTouchEnded = [=](Touch* t, Event* e)
    {
        
        if (!button->getBoundingBox().containsPoint(t->getLocation()))
        {
            return;
        }
        auto fun = [=]()
        {
            auto scene = Choose::createScene();
            scene->setName("Start");
            Director::getInstance()->replaceScene(TransitionFade::create(0.5f, scene, Color3B(0, 0, 0)));
        };
        auto call = CallFunc::create(fun);
        auto seq = Sequence::create(Spawn::create(ScaleTo::create(0.5f, 1.0f), FadeTo::create(0.5f, 255), nullptr), FadeOut::create(0.7f), call, nullptr);
        button->runAction(seq);
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(lis, button);

    return true;
}



