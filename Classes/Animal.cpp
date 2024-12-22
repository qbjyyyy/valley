#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "Animal.h"

USING_NS_CC;

Animal::Animal(){
    targetPosition=Vec2(2400,700); // 目标点
    Bounds = Rect(2000, 790, 600, 300);
    animalmoveAnimate=nullptr;
    animalmoveAnimation=nullptr;
    speed=1;
}
Animal::~Animal() {};

Animal* Animal::create(const std::string& filename) {
    return nullptr;
}
void Animal::generateNewTarget() {
    // 在地图范围内随机生成目标点
    float x = CCRANDOM_0_1() * Bounds.size.width + Bounds.origin.x;
    float y = CCRANDOM_0_1() * Bounds.size.height + Bounds.origin.y;
    targetPosition = Vec2(x, y);
}

void Animal::update(float delta) {
    Vec2 direction = targetPosition - this->getPosition();

    this->setPosition(this->getPosition() + direction * delta *speed);

    // 检查是否到达目标点
    if (this->getPosition().distance(targetPosition) < 10.0f) {
        generateNewTarget(); // 到达目标点后生成新的目标点
    }
}

Sheep* Sheep::create(const std::string& filename) {
    auto animal = new (std::nothrow) Sheep();
    if (animal && animal->init(filename)) {
        animal->autorelease();
        return animal;
    }
    CC_SAFE_DELETE(animal);
    return nullptr;
}
Sheep::Sheep() {};
Sheep::~Sheep() {};
bool Sheep::init(const std::string& filename){
    if (!Sprite::initWithFile(filename)) {
        CCLOG("Error: Failed to load animal image: %s", filename.c_str());
        return false;
    }

    animalmoveAnimation = Animation::create();
    for (int i = 1; i <= 4; i++) {
        std::string frameName = "animal/Sheep" + std::to_string(i) + ".png";
        animalmoveAnimation->addSpriteFrameWithFile(frameName);
    }
    animalmoveAnimation->setDelayPerUnit(0.1f); // 设置每帧的播放时间
    animalmoveAnimation->setLoops(-1); // 设置循环播放
    animalmoveAnimate = Animate::create(animalmoveAnimation);
    //animalmoveAnimate->retain(); // 保留动画对象，防止被释放
    this->runAction(animalmoveAnimate);
    // 每帧更新
    this->scheduleUpdate();
    return true;
}

Cow* Cow::create(const std::string& filename) {
    auto animal = new (std::nothrow) Cow();
    if (animal && animal->init(filename)) {
        animal->autorelease();
        return animal;
    }
    CC_SAFE_DELETE(animal);
    return nullptr;
}

bool Cow::init(const std::string& filename) {
    if (!Sprite::initWithFile(filename)) {
        CCLOG("Error: Failed to load animal image: %s", filename.c_str());
        return false;
    }

    animalmoveAnimation = Animation::create();
    for (int i = 1; i <= 4; i++) {
        std::string frameName = "animal/Cow" + std::to_string(i) + ".png";
        animalmoveAnimation->addSpriteFrameWithFile(frameName);
    }
    animalmoveAnimation->setDelayPerUnit(0.1f); // 设置每帧的播放时间
    animalmoveAnimation->setLoops(-1); // 设置循环播放
    animalmoveAnimate = Animate::create(animalmoveAnimation);
    //animalmoveAnimate->retain(); // 保留动画对象，防止被释放
    this->runAction(animalmoveAnimate);
    // 每帧更新
    this->scheduleUpdate();
    return true;
}

Parrot::Parrot() {
    speed=3;
    Bounds = Rect(2000, 790, 1000, 1000);

};

Parrot* Parrot::create(const std::string& filename) {
    auto animal = new (std::nothrow) Parrot();
    if (animal && animal->init(filename)) {
        animal->autorelease();
        return animal;
    }
    CC_SAFE_DELETE(animal);
    return nullptr;
}

bool Parrot::init(const std::string& filename) {
    if (!Sprite::initWithFile(filename)) {
        CCLOG("Error: Failed to load animal image: %s", filename.c_str());
        return false;
    }

    animalmoveAnimation = Animation::create();
    for (int i = 1; i <= 4; i++) {
        std::string frameName = "animal/Parrot" + std::to_string(i) + ".png";
        animalmoveAnimation->addSpriteFrameWithFile(frameName);
    }
    animalmoveAnimation->setDelayPerUnit(0.1f); // 设置每帧的播放时间
    animalmoveAnimation->setLoops(-1); // 设置循环播放
    animalmoveAnimate = Animate::create(animalmoveAnimation);
    //animalmoveAnimate->retain(); // 保留动画对象，防止被释放
    this->runAction(animalmoveAnimate);
    // 每帧更新
    this->scheduleUpdate();
    return true;
}