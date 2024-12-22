#include "outside.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "intovalley.h"
#include "SimpleAudioEngine.h"
#include "menu.h"
#include "GameTimeSystem.h"
#include "characterAciton.h"
#include "Plantingcrops.h"

using namespace CocosDenshion;

USING_NS_CC;

Crop::Crop() {
    state = State::seed;
    growthTime = 0; 
    pregrowthTime=0;
    matureTime = 1.0f;
    watered=false;
}
Crop::~Crop() {};

Crop* Crop::create(const std::string& filename)
{
    auto crop = new (std::nothrow) Crop();
    if (crop && crop->init(filename)) {
        crop->autorelease();
        return crop;
    }
    CC_SAFE_DELETE(crop);
    return nullptr;
}

bool Crop::init(const std::string& filename)
{
    if (!Sprite::initWithFile(filename)) {
        CCLOG("Error: Failed to load character image: %s", filename.c_str());
        return false;
    }

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(Crop::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(Crop::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    this->scheduleUpdate();//每帧更新

    return true;

}
// 更新作物状态
void Crop::update(float delta) {
    if (growthTime >= matureTime * 2 && state != State::harvested
        &&watered==false) {
        this->setTexture("plant/cropdead.png");
        state = State::dead;
    }

    if (state == State::seed) {
        growthTime += delta;
        if (growthTime >= matureTime) {
            state = State::growing;
            this->setTexture("plant/cropgrowing.png");
        }
    }
    else if (state == State::growing) {
        growthTime += delta;
        if (growthTime >= matureTime*2) {
            state = State::matured;
            this->setTexture("plant/cropmature.png");
        }
    }
    else if (state == State::matured) {
        growthTime += delta;
        if (growthTime >= matureTime*3) {
            state = State::harvested;
            this->setTexture("plant/cropharvested.png");
        }
    }
}

// 获取作物的状态
State Crop::getState() const {
    return state;
}

void Crop::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_J)
    {
            this->harvest();
    }
    if (keyCode == EventKeyboard::KeyCode::KEY_K)
    {
        watered = true;
    }
}



// 收获作物
void Crop::harvest() {
    if (state == State::harvested||state==State::dead) {
        Vec2 position=this->getPosition();
        
        int gridX = static_cast<int>(position.x / gridWidth);
        int gridY = static_cast<int>(position.y / gridHeight);

        Vec2 gridPosition(gridX, gridY);
        cropPositions[gridPosition]=false;

        this->removeFromParent();  // 从父节点中移除作物
    }
}