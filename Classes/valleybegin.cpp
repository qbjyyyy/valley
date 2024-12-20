#include "valleybegin.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "menu.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* valleybegin::createvalleybeginScene()
{
    auto scene = Scene::create();
    auto layer = valleybegin::create();
    scene->addChild(layer);
    return scene;
}



bool valleybegin::init()
{
    if (!Layer::init())
    {
        return false;
    }
    log("11111");
    //设置开始背景
    auto spriteback = Sprite::create("picture/background.png");
    spriteback->setAnchorPoint(Vec2::ZERO);
    spriteback->setPosition(Vec2(0, 0));
    this->addChild(spriteback);

    timerunning = false;

    //开始与退出按钮
    auto startBtn = MenuItemImage::create("picture/startBtn1.png","picture/startBtn2.png"
        ,CC_CALLBACK_1(valleybegin::Startgame,this));
    startBtn->setPosition(Vec2(800, 520));

    auto endBtn = MenuItemImage::create("picture/endBtn1.png", "picture/endBtn2.png",
        CC_CALLBACK_1(valleybegin::Endgame, this));
    endBtn->setPosition(Vec2(1340, 520));

    auto menu = Menu::create(startBtn, endBtn, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);

    auto audio = SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic("valley.mp3", true);

    return true;
}

/*void valleybegin::Startgame(Ref* obj) {
    Scene* scene = intovalley::createintovalleyScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
    timerunning = true;
}*/


void valleybegin::Startgame(Ref* obj) {
    Scene* scene = menu::createmenuScene();
    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, scene));
    timerunning = true;
}

void valleybegin::Endgame(Ref* obj) {
    Director::getInstance()->end();
}

/*int valleybegin::gettimebool()
{
    return timerunning;
}*/

