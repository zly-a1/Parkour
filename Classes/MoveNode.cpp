
#include "MoveNode.h"

USING_NS_CC;

MoveWindowNode::MoveWindowNode():m_listener(nullptr),m_isDowned(false)
{

}
MoveWindowNode::~MoveWindowNode()
{
	if (m_listener)
	{
		Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
	}
}

bool MoveWindowNode::init()
{
	if (!Node::init())
	{
		return false;
	}
	auto VisibleSize = Director::getInstance()->getVisibleSize();

	Bar = Sprite::create("Bar.png");
	Bar->setPosition(Vec2(VisibleSize.width / 2, VisibleSize.height));
	Bar->setScaleX(VisibleSize.width / Bar->getContentSize().width);
	Bar->setOpacity(1);
	Bar->setScaleY(1.4f);
	this->addChild(Bar);

	

	close = Sprite::create("close.png");
	close->setPosition(Vec2(VisibleSize.width-15.0f,VisibleSize.height-17.0f));
	close->setScale(0.03f);
	this->addChild(close);

	


	m_listener = EventListenerMouse::create();
	m_listener->onMouseDown = CC_CALLBACK_1(MoveWindowNode::Down, this);
	m_listener->onMouseUp = CC_CALLBACK_1(MoveWindowNode::Up, this);
	m_listener->onMouseMove = CC_CALLBACK_1(MoveWindowNode::Move, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);
	return true;
}

static POINT p1, p2;
static RECT r1, r2;

void MoveWindowNode::Down(EventMouse* e)
{
	auto visi = Director::getInstance()->getVisibleSize();
	auto hwnd = Director::getInstance()->getOpenGLView()->getWin32Window();
	SetCapture(hwnd);
	GetCursorPos(&p1);
	GetWindowRect(hwnd, &r1);
	r2.right = r1.right - r1.left;
	r2.bottom = r1.bottom - r1.top;

	if (this->Bar->getBoundingBox().containsPoint(Vec2(e->getLocation().x,visi.height-e->getLocation().y)))
	{
		m_isDowned = true;
	}
	if (this->close->getBoundingBox().containsPoint(Vec2(e->getLocationInView().x-15.0f,e->getLocationInView().y)))
	{
		
		Director::getInstance()->end();
	}
	

}

void MoveWindowNode::Up(EventMouse* e)
{
	m_isDowned = false;
	ReleaseCapture();
}

void MoveWindowNode::Move(EventMouse* e)
{
	if (m_isDowned)
	{
		GetCursorPos(&p2);

		auto hwnd = Director::getInstance()->getOpenGLView()->getWin32Window();
		r2.left = r1.left + (p2.x - p1.x);
		r2.top = r1.top + (p2.y - p1.y);
		MoveWindow(hwnd, r2.left, r2.top, r2.right, r2.bottom, true);

		p1 = p2;
		GetWindowRect(hwnd, &r1);
		r2.right = r1.right - r1.left;
		r2.bottom = r1.bottom - r1.top;
	}
}
