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

    matureTime = 1.0f;
}

Crop* Crop::created(const std::string& filename)
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

    this->scheduleUpdate();//每帧更新

    return true;

}
// 更新作物状态
void Crop::update(float delta) {
    if (state == State::seed)
    {
        growthTime += delta;
        if (growthTime >= matureTime) {
            state = State::growing;//成长
            this->setTexture("cropgrowing.png");
        }

    }
    else if (state == State::growing) {
        growthTime += delta;
        if (growthTime >= matureTime * 2) {
            state = State::matured;//成熟
            this->setTexture("cropmature.png");  // 更改成熟的图片
        }
    }
    else if (state == State::matured) {
        growthTime += delta;
        if (growthTime >= matureTime * 3) {
            state = State::harvested;
            this->setTexture("cropharvested.png");
        }
    }
    else if (state == State::harvested) {
        growthTime += delta;
        if (growthTime >= matureTime * 4) {
            CCLOG("Crop has been harvested.");
            this->setVisible(false);  // 收获后隐藏作物

        }
    }
}

// 获取作物的状态
State Crop::getState() const {
    return state;
}

// 获取作物的位置
Vec2 Crop::getposition() const {
    Vec2 cropposition = this->getPosition();
    return cropposition;
}

// 收获作物
void Crop::harvest() {
    if (state == State::matured) {
        state = State::harvested;
        this->setVisible(false);  // 收获后隐藏作物
    }
}