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

    this->scheduleUpdate();//ÿ֡����

    return true;

}
// ��������״̬
void Crop::update(float delta) {
    if (state == State::seed)
    {
        growthTime += delta;
        if (growthTime >= matureTime) {
            state = State::growing;//�ɳ�
            this->setTexture("cropgrowing.png");
        }

    }
    else if (state == State::growing) {
        growthTime += delta;
        if (growthTime >= matureTime * 2) {
            state = State::matured;//����
            this->setTexture("cropmature.png");  // ���ĳ����ͼƬ
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
            this->setVisible(false);  // �ջ����������

        }
    }
}

// ��ȡ�����״̬
State Crop::getState() const {
    return state;
}

// ��ȡ�����λ��
Vec2 Crop::getposition() const {
    Vec2 cropposition = this->getPosition();
    return cropposition;
}

// �ջ�����
void Crop::harvest() {
    if (state == State::matured) {
        state = State::harvested;
        this->setVisible(false);  // �ջ����������
    }
}