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
	// 使用 initWithFile 加载图片
	if (!Sprite::initWithFile(filename)) {
		CCLOG("Error: Failed to load character image: %s", filename.c_str());
		return false;
	}

	// 初始化角色的其他属性
	velocity = Vec2::ZERO;

    // 加载向左走路动画
    walkLeftAnimation = Animation::create();
    for (int i = 1; i <= 3; i++) {
        std::string frameName = "character/Danaleft" + std::to_string(i) + ".png";
        walkLeftAnimation->addSpriteFrameWithFile(frameName);
    }
    walkLeftAnimation->setDelayPerUnit(0.1f); // 设置每帧的播放时间
    walkLeftAnimation->setLoops(-1); // 设置循环播放
    walkLeftAnimate = Animate::create(walkLeftAnimation);
    walkLeftAnimate->retain(); // 保留动画对象，防止被释放

    // 加载向右走路动画
    walkRightAnimation = Animation::create();
    for (int i = 1; i <= 3; i++) {
        std::string frameName = "character/Danaright" + std::to_string(i) + ".png";
        walkRightAnimation->addSpriteFrameWithFile(frameName);
    }
    walkRightAnimation->setDelayPerUnit(0.1f); // 设置每帧的播放时间
    walkRightAnimation->setLoops(-1); // 设置循环播放
    walkRightAnimate = Animate::create(walkRightAnimation);
    walkRightAnimate->retain(); // 保留动画对象，防止被释放

    // 加载向上走路动画
    walkUpAnimation = Animation::create();
    for (int i = 1; i <= 3; i++) {
        std::string frameName = "character/Danaback" + std::to_string(i) + ".png";
        walkUpAnimation->addSpriteFrameWithFile(frameName);
    }
    walkUpAnimation->setDelayPerUnit(0.1f); // 设置每帧的播放时间
    walkUpAnimation->setLoops(-1); // 设置循环播放
    walkUpAnimate = Animate::create(walkUpAnimation);
    walkUpAnimate->retain(); // 保留动画对象，防止被释放

    // 加载向下走路动画
    walkDownAnimation = Animation::create();
    for (int i = 1; i <= 3; i++) {
        std::string frameName = "character/Dana" + std::to_string(i) + ".png";
        walkDownAnimation->addSpriteFrameWithFile(frameName);
    }
    walkDownAnimation->setDelayPerUnit(0.1f); // 设置每帧的播放时间
    walkDownAnimation->setLoops(-1); // 设置循环播放
    walkDownAnimate = Animate::create(walkDownAnimation);
    walkDownAnimate->retain(); // 保留动画对象，防止被释放

    // 注册键盘监听器
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(CharacterWithTools::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(CharacterWithTools::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);


	// 每帧更新
	this->scheduleUpdate();

	return true;
}

void CharacterWithTools::move() {

    // 检查是否已经有相同标签的动作在运行
    auto action = this->getActionByTag(1);
    if (velocity != Vec2::ZERO) {
        // 根据方向播放不同的动画
        if (velocity.x < 0) { // 向左
            if (!action || action != walkLeftAnimate) {
                this->stopAllActions();
                walkLeftAnimate->setTag(1); // 设置动画标签
                this->runAction(walkLeftAnimate);
            }
        }
        else if (velocity.x > 0) { // 向右
            if (!action || action != walkRightAnimate) {
                this->stopAllActions();
                walkRightAnimate->setTag(1); // 设置动画标签
                this->runAction(walkRightAnimate);
            }
        }
        else if (velocity.y > 0) { // 向上
            if (!action || action != walkUpAnimate) {
                this->stopAllActions();
                walkUpAnimate->setTag(1); // 设置动画标签
                this->runAction(walkUpAnimate);
            }
        }
        else if (velocity.y < 0) { // 向下
            if (!action || action != walkDownAnimate) {
                this->stopAllActions();
                walkDownAnimate->setTag(1); // 设置动画标签
                this->runAction(walkDownAnimate);
            }
        }
    }
    else {
        // 如果 velocity 为零，则停止动画
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

    // 设置工具的相对位置
    Vec2 relative_position(50, 20);
    tool->setPosition(relative_position);


    tool->setAnchorPoint(Vec2(0, 0));//设锚点为左下角


    // 将斧头添加为人物的子节点
    this->addChild(tool);

    tool->runAction(Sequence::create(
        RotateBy::create(0.3f, 90),    // 旋转 -90°
        RotateBy::create(0.3f, -90),     // 恢复旋转 90°
        DelayTime::create(0.1f),
        CallFunc::create([tool]() { tool->removeFromParent(); }), // 动画结束后移除工具
        nullptr
    ));
}

void CharacterWithTools::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    velocity=Vec2::ZERO;
    switch (keyCode)
    {
        case EventKeyboard::KeyCode::KEY_J:
            usetools("tools/axe.png");//砍树
            break;
        case EventKeyboard::KeyCode::KEY_K:
            usetools("tools/kettle.png");//浇水
            break;
        case EventKeyboard::KeyCode::KEY_L:
            usetools("tools/pickaxe.png");//砍石头
            break;
        default:
            break;
    }
    velocity=Vec2::ZERO;
    if (keyCode == EventKeyboard::KeyCode::KEY_W)
        velocity.y = 1;
    if (keyCode == EventKeyboard::KeyCode::KEY_S)
        velocity.y = -1; // 向下
    if (keyCode == EventKeyboard::KeyCode::KEY_A)
        velocity.x = -1; // 向左
    if (keyCode == EventKeyboard::KeyCode::KEY_D)
        velocity.x = 1; // 向右
    this->move(); // 将键盘输入传递给角色
}

void CharacterWithTools::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
    velocity = Vec2::ZERO;
    if (keyCode == EventKeyboard::KeyCode::KEY_W)
        velocity.y = 0;
    if (keyCode == EventKeyboard::KeyCode::KEY_S)
        velocity.y = 0; // 向下
    if (keyCode == EventKeyboard::KeyCode::KEY_A)
        velocity.x = 0; // 向左
    if (keyCode == EventKeyboard::KeyCode::KEY_D)
        velocity.x = 0; // 向右
    this->move(); // 将键盘输入传递给角色
}

void CharacterWithTools::update(float delta) {
	// 根据速度更新角色的位置
	this->setPosition(this->getPosition() + velocity * delta * 1000);
}