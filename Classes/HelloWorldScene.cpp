
#include "HelloWorldScene.h"
#include "StartScene.h"
#include "MoveNode.h"
#include "ui/CocosGUI.h"
#include <string>
#include <iostream>

USING_NS_CC;

int Guanqia;
Vec2 BirthPlaces;

Scene* HelloWorld::createScene(int guanqia)
{
   
    auto Hello = Scene::createWithPhysics();
    
    Hello->getPhysicsWorld()->setGravity(Vec2(0.0f, -240.0f));
    auto phy = HelloWorld::create();
    Hello->addChild(phy);
    
    //Hello->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
    Guanqia = guanqia;
    switch (Guanqia)
    {
    case 1:
        BirthPlaces.x = 70.0f;
        BirthPlaces.y = 300.0f;
    default:
        break;
    }
    
    return Hello;

}



// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(float filename)
{
    printf("Error while loading: %f\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

Sprite* HelloWorld::addSpriteatPosition(Vec2 pos,std::string img)
{
    auto Spr = Sprite::create(img);
    Spr->setPosition(pos.x,pos.y);
    return Spr;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
    move->setName("move");
    this->addChild(move);
    

    auto ball = Sprite::create("kid.png");
    
    
    

    ball->setName("kid");
    ball->setPosition(BirthPlaces);
    ball->setScale(0.5f);
    ball->setOpacity(0);
    auto ballphy = PhysicsBody::createBox(Size(50.0f,50.0f),PhysicsMaterial(0.0f,0.0f,0.0f));

    ballphy->setRotationEnable(false);
    ballphy->setContactTestBitmask(1);
    ballphy->setCollisionBitmask(1);
    ballphy->setCategoryBitmask(1);
    ball->runAction(Sequence::create(FadeIn::create(1.0f),nullptr));
    ballphy->setGroup(3);
    ball->addComponent(ballphy);
    this->addChild(ball);
    
    auto movelis1 = EventListenerKeyboard::create();
    movelis1->onKeyPressed = [=](EventKeyboard::KeyCode c, Event* e)
    {
        
        switch (c)
        {
        case  EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            ball->setFlippedX(true);
            movex = -100.0f;
            ball->getPhysicsBody()->setVelocity(Vec2(movex, ball->getPhysicsBody()->getVelocity().y));
            break;
        };
        
    };
    movelis1->onKeyReleased = [=](EventKeyboard::KeyCode c, Event* e)
    {
        if (ball->getPhysicsBody())
        {
            switch (c)
            {
            case  EventKeyboard::KeyCode::KEY_LEFT_ARROW:
                movex = 0.0f;
                ball->getPhysicsBody()->setVelocity(Vec2(0.0f, ball->getPhysicsBody()->getVelocity().y));
                break;
            };

        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(movelis1, ball);

    this->CreateMap();
    
    auto movelis = EventListenerKeyboard::create();
    movelis->onKeyPressed = [=](EventKeyboard::KeyCode c, Event* e)
    {
        switch (c)
        {
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            ball->setFlippedX(false);
            movex = 100.0f;
            ball->getPhysicsBody()->setVelocity(Vec2(movex, ball->getPhysicsBody()->getVelocity().y));
            break;
        };
        
    };
    movelis->onKeyReleased = [=](EventKeyboard::KeyCode c, Event* e)
    {
        if (ball->getPhysicsBody())
        {
            switch (c)
            {
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
                movex = 0.0f;
                ball->getPhysicsBody()->setVelocity(Vec2(0.0f, ball->getPhysicsBody()->getVelocity().y));
                break;
            };



        }
        
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(movelis, ball);
    auto movelis2 = EventListenerKeyboard::create();
    movelis2->onKeyPressed = [=](EventKeyboard::KeyCode c, Event* e)
    {
        switch (c)
        {
        case EventKeyboard::KeyCode::KEY_SPACE:
            if (jumptime)
            {
                ball->getPhysicsBody()->setVelocity(Vec2(movex, 200.0f));
                
            }
            break;
        };
        
    };
    movelis2->onKeyReleased = [=](EventKeyboard::KeyCode c, Event* e)
    {
        if (ball->getPhysicsBody())
        {
            switch (c)
            {
            case EventKeyboard::KeyCode::KEY_SPACE:
                ball->getPhysicsBody()->setVelocity(Vec2(ball->getPhysicsBody()->getVelocity().x, ball->getPhysicsBody()->getVelocity().y));
                break;
            };

            
        }
        
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(movelis2, ball);
    EventListenerPhysicsContact* contact = EventListenerPhysicsContact::create();
    contact->onContactPreSolve = [=](PhysicsContact& contact,PhysicsContactPreSolve& slove)
    {
        auto NodeA = contact.getShapeA()->getBody();
        auto NodeB = contact.getShapeB()->getBody();
        if (NodeA&&NodeB)
        {
            if ((NodeA->getGroup() == 1 && NodeB->getGroup() == 3)||(NodeB->getGroup() == 1 && NodeA->getGroup() == 3  )) {
                this->jumptime = true;
                
            }
            if ((NodeA->getGroup() == 2 && NodeB->getGroup() == 3) || (NodeB->getGroup() == 2 && NodeA->getGroup() == 3)) {
                this->kill();
            }
            if ((NodeA->getGroup() == 4 && NodeB->getGroup() == 3) || (NodeA->getGroup() == 3 && NodeB->getGroup() == 4))
            {
                this->canmove = false;
                auto spa = Spawn::create(FadeOut::create(1.0f), nullptr);
                auto children = this->getChildren();
                for (Node* child : children)
                {

                    if (child->getName() == "kid")
                    {
                        child->removeAllComponents();
                        auto seq = Sequence::create(DelayTime::create(1.0f),spa, CallFunc::create([=]() {
                            child->removeAllChildrenWithCleanup(true);
                            }), nullptr);
                        
                        child->runAction(seq->clone());
                    }
                    else if (child->getName() == "move")
                    {
                        
                    }
                    else {
                        child->removeAllComponents();
                        auto seq = Sequence::create( spa, CallFunc::create([=]() {
                            child->removeAllChildrenWithCleanup(true);
                            }), nullptr);

                        child->runAction(seq->clone());
                    }
                    
                }

                this->runAction(Sequence::create(DelayTime::create(3.0f), CallFunc::create([=]() {
                    auto start = Start::createScene();
                    Director::getInstance()->replaceScene(TransitionFade::create(0.5f, start));
                }),nullptr));
                
            }
        }
        return true;
    };
    
    contact->onContactSeparate = [=](PhysicsContact& contact)
    {
        auto NodeA = contact.getShapeA()->getBody();
        auto NodeB = contact.getShapeB()->getBody();
        if (NodeA && NodeB)
        {
            if ((NodeA->getGroup() == 1 && NodeB->getGroup() == 3) || (NodeB->getGroup() == 1 && NodeA->getGroup() == 3)) {
                this->jumptime = false;
                
                
            }
            

        }
        return true;
    };

    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contact, this);

    
    return true;
}

void HelloWorld::CreateMap()
{
    int row = 25, col = 16;

    std::vector<std::vector<int>>GameMap(col, vector<int>(row));

    

    if (Guanqia==1)
    {
        GameMap[col - 16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 };
        GameMap[col - 15] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 };
        GameMap[col - 14] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 };
        GameMap[col - 13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 };
        GameMap[col - 12] = { 3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 };
        GameMap[col - 11] = { 1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,4 };
        GameMap[col - 10] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,4 };
        GameMap[col - 9] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 };
        GameMap[col - 8] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 };
        GameMap[col - 7] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 };
        GameMap[col - 6] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,4 };
        GameMap[col - 5] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 };
        GameMap[col - 4] = { 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,4 };
        GameMap[col - 3] = { 0,0,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,4 };
        GameMap[col - 2] = { 0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4 };
        GameMap[col - 1] = { 1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 };
    }

    int i = 0;
    int k = 0;

    auto VisibleSize = Director::getInstance()->getVisibleSize();

    for (i = 0; i < col; i++)
    {
        for (k = 0; k < row; k++)
        {
            if (GameMap[i][k] == 1)
            {
                
                auto s = addSpriteatPosition(Vec2((k+1) * this->getChildByName("kid")->getContentSize().width * 0.4f, VisibleSize.height- this->getChildByName("kid")->getContentSize().width * 0.4f - i * this->getChildByName("kid")->getContentSize().height * 0.4f-15), "Block.png");
                s->setScale(0.4f);
                auto phy1 = PhysicsBody::createBox(s->getContentSize(), PhysicsMaterial(0.2f, 0.0f, 0.0f));
                phy1->setContactTestBitmask(1);
                phy1->setCollisionBitmask(1);
                s->addComponent(phy1);
                s->getPhysicsBody()->setDynamic(false);
                s->getPhysicsBody()->setGroup(1);
                this->addChild(s);

                
            }
            if (GameMap[i][k] == 2||GameMap[i][k]==4||GameMap[i][k]==5||GameMap[i][k]==6)
            {
                auto s = addSpriteatPosition(Vec2((k+1) * this->getChildByName("kid")->getContentSize().width * 0.4f, VisibleSize.height- this->getChildByName("kid")->getContentSize().width * 0.4f - i * this->getChildByName("kid")->getContentSize().height * 0.4f-15), "Spike.png");
                s->setScale(0.4f);
                auto poly = AutoPolygon::generatePolygon("Spike.png");
                auto count = poly.triangles.indexCount;
                auto indc = poly.triangles.indices;
                auto verts = poly.triangles.verts;

                Vec2* ps=new Vec2[count];
                for (int t = 0;  t < count-1;  t++)
                {
                    ps[t].x = verts[indc[t]].vertices.x - s->getContentSize().width/2;
                    ps[t].y = verts[indc[t]].vertices.y - s->getContentSize().height / 2;
                }

                auto phy1 = PhysicsBody::createPolygon(ps, count);
                phy1->setContactTestBitmask(1);
                phy1->setCollisionBitmask(1);
                s->addComponent(phy1);
                s->getPhysicsBody()->setDynamic(false);
                s->getPhysicsBody()->setGroup(2);
                this->addChild(s);
                if (GameMap[i][k] == 6)
                {
                    s->setRotation(90.0f);
                }
                
                if (GameMap[i][k] == 4)
                {
                    s->setRotation(-90.0f);
                }
                if (GameMap[i][k] == 5)
                {
                    s->setRotation(180.0f);
                }
                if (GameMap[i][k] == 2)
                {
                    s->setRotation(0.0f);
                }

                delete []ps;
            } 
            if (GameMap[i][k] == 3)
            {
                auto s = addSpriteatPosition(Vec2((k + 1) * this->getChildByName("kid")->getContentSize().width * 0.4f, VisibleSize.height - this->getChildByName("kid")->getContentSize().width * 0.4f - i * this->getChildByName("kid")->getContentSize().height * 0.4f-15), "Warp.png");
                s->setScale(0.4f);
                auto poly = AutoPolygon::generatePolygon("Warp.png");
                auto count = poly.triangles.indexCount;
                auto indc = poly.triangles.indices;
                auto verts = poly.triangles.verts;

                Vec2* ps = new Vec2[count];
                for (int t = 0; t < count - 1; t++)
                {
                    ps[t].x = verts[indc[t]].vertices.x - s->getContentSize().width / 2;
                    ps[t].y = verts[indc[t]].vertices.y - s->getContentSize().height / 2;
                }

                auto phy1 = PhysicsBody::createPolygon(ps, count);
                phy1->setContactTestBitmask(1);
                phy1->setCollisionBitmask(1);
                s->addComponent(phy1);
                s->getPhysicsBody()->setDynamic(false);
                s->getPhysicsBody()->setGroup(4);
                this->addChild(s);
                
                
                
                delete[]ps;
            }
        }
    }
}

void HelloWorld::update(float dt)
{
    auto visi = Director::getInstance()->getVisibleSize();
    if (this->getChildByName("kid")->getPosition().x<-50|| this->getChildByName("kid")->getPosition().x > visi.width+50|| this->getChildByName("kid")->getPosition().y < -50|| this->getChildByName("kid")->getPosition().y > visi.height+50)
    {
        this->kill();
    }
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}

void HelloWorld::kill()
{
    this->jumptime = false;
    this->canmove = false;
    this->getChildByName("kid")->getPhysicsBody()->setEnabled(false);
    
    auto fade = Spawn::create(FadeOut::create(0.5f),ScaleTo::create(0.5f,0.4f),nullptr);
    auto out = Spawn::create(FadeIn::create(0.5f), ScaleTo::create(0.5f, 0.5f), nullptr);

    this->getChildByName("kid")->runAction(Sequence::create(fade,Place::create(static_cast<const Vec2>(BirthPlaces)),out, CallFunc::create([=]() {
        this->getChildByName("kid")->getPhysicsBody()->setEnabled(true);
        this->getChildByName("kid")->getPhysicsBody()->setVelocity(Vec2(0.0f,0.0f));
        this->canmove = true;
        }), nullptr));
    
}
