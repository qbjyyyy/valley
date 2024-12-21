#include "characterAciton.h"
#include "outside.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "intovalley.h"
#include "SimpleAudioEngine.h"
#include "menu.h"
#include "GameTimeSystem.h"
#include "Plantingcrops.h"


CharacterWithTools::CharacterWithTools():walkLeftAnimation(nullptr), walkRightAnimation(nullptr),
walkUpAnimation(nullptr), walkDownAnimation(nullptr),
walkLeftAnimate(nullptr), walkRightAnimate(nullptr),
walkUpAnimate(nullptr), walkDownAnimate(nullptr) { velocity = Vec2(0, 0); }

CharacterWithTools::~CharacterWithTools() {}

CharacterWithTools* CharacterWithTools::create(const std::string& filename) {
	auto character = new (std::nothrow) CharacterWithTools();
	if (character && character->init(filename)) {
		character->autorelease();
		return character;
	}
	CC_SAFE_DELETE(character);
	return nullptr;
}

bool CharacterWithTools::init(const std::string& filename) {
	// ʹ�� initWithFile ����ͼƬ
	if (!Sprite::initWithFile(filename)) {
		CCLOG("Error: Failed to load character image: %s", filename.c_str());
		return false;
	}

	// ��ʼ����ɫ����������
	velocity = Vec2::ZERO;

    // ����������·����
    walkLeftAnimation = Animation::create();
    for (int i = 1; i <= 3; i++) {
        std::string frameName = "character/Danaleft" + std::to_string(i) + ".png";
        walkLeftAnimation->addSpriteFrameWithFile(frameName);
    }
    walkLeftAnimation->setDelayPerUnit(0.1f); // ����ÿ֡�Ĳ���ʱ��
    walkLeftAnimation->setLoops(-1); // ����ѭ������
    walkLeftAnimate = Animate::create(walkLeftAnimation);
    walkLeftAnimate->retain(); // �����������󣬷�ֹ���ͷ�

    // ����������·����
    walkRightAnimation = Animation::create();
    for (int i = 1; i <= 3; i++) {
        std::string frameName = "character/Danaright" + std::to_string(i) + ".png";
        walkRightAnimation->addSpriteFrameWithFile(frameName);
    }
    walkRightAnimation->setDelayPerUnit(0.1f); // ����ÿ֡�Ĳ���ʱ��
    walkRightAnimation->setLoops(-1); // ����ѭ������
    walkRightAnimate = Animate::create(walkRightAnimation);
    walkRightAnimate->retain(); // �����������󣬷�ֹ���ͷ�

    // ����������·����
    walkUpAnimation = Animation::create();
    for (int i = 1; i <= 3; i++) {
        std::string frameName = "character/Danaback" + std::to_string(i) + ".png";
        walkUpAnimation->addSpriteFrameWithFile(frameName);
    }
    walkUpAnimation->setDelayPerUnit(0.1f); // ����ÿ֡�Ĳ���ʱ��
    walkUpAnimation->setLoops(-1); // ����ѭ������
    walkUpAnimate = Animate::create(walkUpAnimation);
    walkUpAnimate->retain(); // �����������󣬷�ֹ���ͷ�

    // ����������·����
    walkDownAnimation = Animation::create();
    for (int i = 1; i <= 3; i++) {
        std::string frameName = "character/Dana" + std::to_string(i) + ".png";
        walkDownAnimation->addSpriteFrameWithFile(frameName);
    }
    walkDownAnimation->setDelayPerUnit(0.1f); // ����ÿ֡�Ĳ���ʱ��
    walkDownAnimation->setLoops(-1); // ����ѭ������
    walkDownAnimate = Animate::create(walkDownAnimation);
    walkDownAnimate->retain(); // �����������󣬷�ֹ���ͷ�

    // ע����̼�����
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(CharacterWithTools::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(CharacterWithTools::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);


	// ÿ֡����
	this->scheduleUpdate();

	return true;
}

void CharacterWithTools::move() {

    // ����Ƿ��Ѿ�����ͬ��ǩ�Ķ���������
    auto action = this->getActionByTag(1);
    if (velocity != Vec2::ZERO) {
        // ���ݷ��򲥷Ų�ͬ�Ķ���
        if (velocity.x < 0) { // ����
            if (!action || action != walkLeftAnimate) {
                this->stopAllActions();
                walkLeftAnimate->setTag(1); // ���ö�����ǩ
                this->runAction(walkLeftAnimate);
            }
        }
        else if (velocity.x > 0) { // ����
            if (!action || action != walkRightAnimate) {
                this->stopAllActions();
                walkRightAnimate->setTag(1); // ���ö�����ǩ
                this->runAction(walkRightAnimate);
            }
        }
        else if (velocity.y > 0) { // ����
            if (!action || action != walkUpAnimate) {
                this->stopAllActions();
                walkUpAnimate->setTag(1); // ���ö�����ǩ
                this->runAction(walkUpAnimate);
            }
        }
        else if (velocity.y < 0) { // ����
            if (!action || action != walkDownAnimate) {
                this->stopAllActions();
                walkDownAnimate->setTag(1); // ���ö�����ǩ
                this->runAction(walkDownAnimate);
            }
        }
    }
    else {
        // ��� velocity Ϊ�㣬��ֹͣ����
        if (action) {
            this->stopAllActions();
        }
    }
}

void CharacterWithTools::usetools(const std::string& filename)
{
    auto tool = Sprite::create(filename);
    if (tool == nullptr) {
        CCLOG("Error: Failed to create axe sprite!");
        return;
    }

    // ���ù��ߵ����λ��
    Vec2 relative_position(50, 20);
    tool->setPosition(relative_position);


    tool->setAnchorPoint(Vec2(0, 0));//��ê��Ϊ���½�


    // ����ͷ���Ϊ������ӽڵ�
    this->addChild(tool);

    tool->runAction(Sequence::create(
        RotateBy::create(0.3f, 90),    // ��ת -90��
        RotateBy::create(0.3f, -90),     // �ָ���ת 90��
        DelayTime::create(0.1f),
        CallFunc::create([tool]() { tool->removeFromParent(); }), // �����������Ƴ�����
        nullptr
    ));
}

void CharacterWithTools::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    velocity=Vec2::ZERO;
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_J:
            usetools("tools/axe.png");//����
            break;
        case EventKeyboard::KeyCode::KEY_K:
            usetools("tools/kettle.png");//��ˮ
            break;
        case EventKeyboard::KeyCode::KEY_L:
            usetools("tools/pickaxe.png");//��ʯͷ
            break;
        default:
            break;
    }
    velocity=Vec2::ZERO;
    if (keyCode == EventKeyboard::KeyCode::KEY_W)
        velocity.y = 1;
    if (keyCode == EventKeyboard::KeyCode::KEY_S)
        velocity.y = -1; // ����
    if (keyCode == EventKeyboard::KeyCode::KEY_A)
        velocity.x = -1; // ����
    if (keyCode == EventKeyboard::KeyCode::KEY_D)
        velocity.x = 1; // ����
    this->move(); // ���������봫�ݸ���ɫ
}

void CharacterWithTools::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    velocity = Vec2::ZERO;
    if (keyCode == EventKeyboard::KeyCode::KEY_W)
        velocity.y = 0;
    if (keyCode == EventKeyboard::KeyCode::KEY_S)
        velocity.y = 0; // ����
    if (keyCode == EventKeyboard::KeyCode::KEY_A)
        velocity.x = 0; // ����
    if (keyCode == EventKeyboard::KeyCode::KEY_D)
        velocity.x = 0; // ����
    this->move(); // ���������봫�ݸ���ɫ
}

void CharacterWithTools::update(float delta) {
	// �����ٶȸ��½�ɫ��λ��
	this->setPosition(this->getPosition() + velocity * delta * 1000);
}