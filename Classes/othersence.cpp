#include "othersence.h"
#include "outside.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "characterAciton.h"
#include "SceneStateManager.h"
USING_NS_CC;

Scene* othersence::createothersenceScene()
{
    auto scene = Scene::create();
    auto layer = othersence::create();
    scene->addChild(layer);
    return scene;
}



bool othersence::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //设置开始背景
    auto tiledMap = TMXTiledMap::create("tiledmap/othersence1.tmx");
    this->addChild(tiledMap, 0);
   tiledMap->setScale(3);

    characteraction = CharacterWithTools::create("character/Dana0.png");
    if (characteraction == nullptr) {
        CCLOG("Error: Failed to create character!");
        return false;
    }
    auto button = ui::Button::create("picture/out1.png", "picture/out2.png"); // 按钮的正常状态和按下状态图片
    button->setPosition(Vec2(3700,100));
    this->addChild(button);

    characteraction->setPosition(Vec2(3030+500,0));
    this->addChild(characteraction);

    this->scheduleUpdate();
    // 在每帧中更新视点位置，使地图始终跟随人物
    this->schedule([=](float deltaTime) {
        // 获取人物当前的世界坐标
        Vec2 characterPosition = characteraction->getPosition();

        // 更新视点，确保地图始终跟随人物
        setViewPointCenter(characterPosition, tiledMap);
        }, "view_point_update_key");

    button->addClickEventListener([=](Ref* sender) {
        // 回到旧场景时恢复状态
        //Scene* previousScene = outside::createSceneWithMapIndex(1); // 创建旧场景
        characteraction->setPosition(SceneStateManager::getInstance()->getCharacterPosition());
        tiledMap->setName(SceneStateManager::getInstance()->getMapName());
        //Director::getInstance()->replaceScene(TransitionCrossFade::create(0.5, previousScene));
        if (Director::getInstance()->getRunningScene()) {
            Director::getInstance()->popScene();
        }
        });

    return true;
}

void othersence::setViewPointCenter(Point position, cocos2d::TMXTiledMap* tiledMap) {
    const auto winSize = Director::getInstance()->getWinSize();
    float scale = tiledMap->getScale(); // 获取当前的缩放比例

    // 计算实际的视图中心坐标（考虑缩放）
    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);

    // 计算缩放后的地图尺寸
    float mapWidth = tiledMap->getMapSize().width * tiledMap->getTileSize().width * scale;
    float mapHeight = tiledMap->getMapSize().height * tiledMap->getTileSize().height * scale;

    // 确保视点不会超出地图的范围
    x = MIN(x, mapWidth - winSize.width / 2);
    y = MIN(y, mapHeight - winSize.height / 2);

    // 计算视点实际位置
    auto actualPosition = Point(x, y);

    // 屏幕中心点
    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);

    // 计算新的视点位置
    auto viewPoint = centerOfView - actualPosition;

    // 更新视图位置
    this->setPosition(viewPoint);
}
