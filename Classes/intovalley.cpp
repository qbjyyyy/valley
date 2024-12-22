#include "intovalley.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "SceneStateManager.h"
#include "characterAciton.h"

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


    characteraction = CharacterWithTools::create("character/Dana0.png");
    if (characteraction == nullptr) {
        CCLOG("Error: Failed to create character!");
        return false;
    }
    auto button = ui::Button::create("picture/out1.png", "picture/out2.png"); // 按钮的正常状态和按下状态图片
    button->setPosition(Vec2(975, 230));
    this->addChild(button);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    characteraction->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(characteraction);

    this->scheduleUpdate();
    // 在每帧中更新视点位置，使地图始终跟随人物
    this->schedule([=](float deltaTime) {
        // 获取人物当前的世界坐标
        Vec2 characterPosition = characteraction->getPosition();

        button->addClickEventListener([&](Ref* sender) {
            // 回到旧场景时恢复状态
            Scene* scene = outside::createSceneWithMapIndex(1);
            Director::getInstance()->popScene();
            });

        }, "view_point_update_key");

    return true;
}


