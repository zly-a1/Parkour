#ifndef __MOVE_NODE_H__
#define __MOVE_NODE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MoveWindowNode : public cocos2d::Node
{
public:
	MoveWindowNode();
	~MoveWindowNode();

	cocos2d::Sprite* Bar,*close,*bigest;

	CREATE_FUNC(MoveWindowNode);
	virtual bool init();
protected:
	void Down(cocos2d::EventMouse* e);
	void Up(cocos2d::EventMouse* e);
	void Move(cocos2d::EventMouse* e);
private:
	cocos2d::EventListenerMouse* m_listener;
	bool m_isDowned;
};


#endif // __MOVE_NODE_H__
