#include "intovalley.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"

USING_NS_CC;

Scene* intovalley::createintovalleyScene()
{
    auto scene = Scene::create();
    auto layer = intovalley::create();
    scene->addChild(layer);
    return scene;
}



bool intovalley::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //设置开始背景
    auto spriteback = Sprite::create("picture/home.png");
    spriteback->setAnchorPoint(Vec2::ZERO);
    spriteback->setPosition(Vec2(700, 200));
    this->addChild(spriteback);

    timelable = Label::create();
    timelable->setTextColor(Color4B::WHITE);
    timelable->setSystemFontSize(48);
    timelable->setPosition(1800, 900);
    timelable->setString("00:00");
    addChild(timelable);




    //单张图组成帧动画
    auto character = Sprite::create("picture/character1.png",Rect(0,0,144,156));
    character->setPosition(Vec2(1080, 522));
    character->setTag(0); // 设置角色的标签为0
    this->addChild(character);

    Vector<SpriteFrame*>move;
    for (int i = 1; i <= 3; i++) {
        char imagename[40];
        sprintf(imagename, "picture/character%d.png", i);
        SpriteFrame* spriteFrame = SpriteFrame::create(imagename, Rect(0, 0, 144, 156));
        move.pushBack(spriteFrame);
    }
    Animation* ani = Animation::createWithSpriteFrames(move,1);
    Animate* animate = Animate::create(ani);
    character->runAction(RepeatForever::create(animate));

    this->scheduleUpdate(); //这样每一帧都会进入 update 函数 我们在里面判断键盘有没有被按压住
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event* event) {
        log("press");
        keys[keycode] = true;
            if (keycode == cocos2d::EventKeyboard::KeyCode::KEY_0) {
                auto jump = JumpTo::create(0.5, Vec2(character->getPositionX(), character->getPositionY()), 70, 1);
                character->runAction(jump);
            }
        };

    listener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, Event* event) {
        log("release");
        keys[keycode] = false;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    //开始与退出按钮
    auto outDr = MenuItemImage::create("picture/out1.png", "picture/out2.png"
        , CC_CALLBACK_1(intovalley::outdoor, this));
    outDr->setPosition(Vec2(975, 230));


    auto menu = Menu::create(outDr,  NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    return true;
}



void intovalley::update(float delta)
{
    auto left = cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW;
    auto right = cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW;
    auto up = cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW;
    auto down = cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW;
    const int leftBoundary = 850;
    const int rightBoundary = 1300; 
    const int topBoundary = 750; 
    const int bottomBoundary = 400;

    int offsetX = 0;
    int offsetY = 0;
    if (keys[left]) {
        offsetX = -2;
    }
    if (keys[right]) {
        offsetX = 2;
    }
    if (keys[down]) {
        offsetX = 2;
    }
    if (keys[up]) {
        offsetY = 2;
    }
    if (keys[down]) {
        offsetY = -2;
        offsetX = 0;
    }
    if (offsetX == 0&&offsetY==0) {
        return;
    }

    Node* sprite = this->getChildByTag(0);
    Vec2 spritePosition = sprite->getPosition();
    float newX = spritePosition.x + offsetX;
    float newY = spritePosition.y + offsetY;
    
    if (newX < leftBoundary) {
        newX = leftBoundary;
    }
    else if (newX > rightBoundary) {
        newX = rightBoundary;
    }
    if (newY < bottomBoundary) {
        newY = bottomBoundary;
    }
    else if (newY > topBoundary) {
        newY = topBoundary;
    }

    if (newX > 1220 && newY < 550) {
        newX = newX- 2*offsetX;
        newY = newY - 2*offsetY;
    }
    if (newX > 1160 && newY > 650) {
        newX = newX - 2 * offsetX;
        newY = newY - 2 * offsetY;
    }

    auto moveTo = MoveTo::create(0.2, Vec2(newX, newY));
    sprite->runAction(moveTo);

}


void intovalley::outdoor(Ref* obj) {
    //Scene* scene = outside::createoutsideScene();
    //Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
}


void intovalley::timeupdate(float dt) {

}

