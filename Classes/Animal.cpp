#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "Animal.h"

USING_NS_CC;

Animal::Animal(){
    targetPosition=Vec2(2400,700); // Ŀ���
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
    // �ڵ�ͼ��Χ���������Ŀ���
    float x = CCRANDOM_0_1() * Bounds.size.width + Bounds.origin.x;
    float y = CCRANDOM_0_1() * Bounds.size.height + Bounds.origin.y;
    targetPosition = Vec2(x, y);
}

void Animal::update(float delta) {
    Vec2 direction = targetPosition - this->getPosition();

    this->setPosition(this->getPosition() + direction * delta *speed);

    // ����Ƿ񵽴�Ŀ���
    if (this->getPosition().distance(targetPosition) < 10.0f) {
        generateNewTarget(); // ����Ŀ���������µ�Ŀ���
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
    animalmoveAnimation->setDelayPerUnit(0.1f); // ����ÿ֡�Ĳ���ʱ��
    animalmoveAnimation->setLoops(-1); // ����ѭ������
    animalmoveAnimate = Animate::create(animalmoveAnimation);
    //animalmoveAnimate->retain(); // �����������󣬷�ֹ���ͷ�
    this->runAction(animalmoveAnimate);
    // ÿ֡����
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
    animalmoveAnimation->setDelayPerUnit(0.1f); // ����ÿ֡�Ĳ���ʱ��
    animalmoveAnimation->setLoops(-1); // ����ѭ������
    animalmoveAnimate = Animate::create(animalmoveAnimation);
    //animalmoveAnimate->retain(); // �����������󣬷�ֹ���ͷ�
    this->runAction(animalmoveAnimate);
    // ÿ֡����
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
    animalmoveAnimation->setDelayPerUnit(0.1f); // ����ÿ֡�Ĳ���ʱ��
    animalmoveAnimation->setLoops(-1); // ����ѭ������
    animalmoveAnimate = Animate::create(animalmoveAnimation);
    //animalmoveAnimate->retain(); // �����������󣬷�ֹ���ͷ�
    this->runAction(animalmoveAnimate);
    // ÿ֡����
    this->scheduleUpdate();
    return true;
}