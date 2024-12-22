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
#include "othersence.h"
#include "SceneStateManager.h"
#include "Animal.h"

using namespace CocosDenshion;

USING_NS_CC;



Scene* outside::createSceneWithMapIndex(int mapIndex) {
    auto scene = Scene::create();
    auto layer = outside::create();

    layer->loadMapBackground(mapIndex);
    scene->addChild(layer);
    return scene;

}

void outside::loadMapBackground(int mapIndex) {
    // 根据地图索引加载不同的 TMX 地图文件
    std::string tmxFileName;
    switch (mapIndex) {
        case 0:
            tmxFileName = "tiledmap/Farm.tmx";
            break;
        case 1:
            tmxFileName = "tiledmap/new.tmx";
            break;
        case 2:
            tmxFileName = "tiledmap/Farm.tmx";
            break;
        case 3:
            tmxFileName = "tiledmap/Farm.tmx";
            break;
        default:
            //tmxFileName = "tiledmap/default.tmx";
            break;
    }
    // 加载背景图片
    auto tiledMap = TMXTiledMap::create(tmxFileName);
    if (tiledMap) {
        // 设置地图位置
        tiledMap->setPosition(Vec2(-500, -200));
        tiledMap->setScale(3);
        this->addChild(tiledMap, 0);

        auto imageView = ImageView::create("picture/time.png");
        if (imageView) {
            // 设置位置
            imageView->setPosition(Vec2(3 * 1500 - 100, 3 * 1100 + 1450 - 100));
            // 添加到场景
            this->addChild(imageView);
        }
       
    
        _meta = tiledMap->getLayer("meta");
        _meta->setVisible(false);

        TMXObjectGroup* objects = tiledMap->getObjectGroup("objects");
        CCASSERT(NULL != objects, "'objects' object group not found");
        auto spawnPoint = objects->getObject("lake");
        int x = spawnPoint["x"].asInt();
        int y = spawnPoint["y"].asInt();

        //创建动物
        //绵羊
        for (int i = 0; i < 5; i++) {
            auto sheep = Sheep::create("animal/Sheep1.png");
            if (sheep == nullptr) {
                CCLOG("Error: Failed to create sheep!");
                return;
            }
            this->addChild(sheep);
        }

        //牛
        auto cow=Cow::create("animal/Cow1.png");
        if (cow == nullptr) {
            CCLOG("Error: Failed to create cow!");
            return;
        }
        cow->setScale(3);
        this->addChild(cow);

        //鹦鹉
        auto parrot=Parrot::create("animal/Parrot1.png");
        if (parrot == nullptr) {
            CCLOG("Error: Failed to create parrot!");
            return;
        }
        parrot->setScale(3);
        this->addChild(parrot);

        //创建主角人物
        characteraction = CharacterWithTools::create("character/Dana0.png");
        if (characteraction == nullptr) {
            CCLOG("Error: Failed to create character!");
            return;
        }

        characteraction->setPosition(Vec2(3 * x + 600, 3 * y + 2000));
        this->addChild(characteraction);

        this->scheduleUpdate();
        // 在每帧中更新视点位置，使地图始终跟随人物
            this->schedule([=](float deltaTime) {
            // 获取人物当前的世界坐标
            Vec2 characterPosition = characteraction->getPosition();



            // 更新视点，确保地图始终跟随人物
            setViewPointCenter(characterPosition, tiledMap);


            if (characterPosition.x >= 3460 &&
                characterPosition.x <= 3500 &&
                characterPosition.y >= 3570 &&
                characterPosition.y <= 3610)
            {
                // 在切换场景之前保存状态
                SceneStateManager::getInstance()->saveSceneState(
                    characteraction->getPosition(),
                    tiledMap->getName()
                );
                
                // 如果人物进入指定范围，则切换场景
                if (!inZones["zone1"]) {
                    Scene* scene = intovalley::createintovalleyScene();
                    Director::getInstance()->pushScene(scene);
                    inZones["zone1"] =true;
                }
                else
                    inZones["zone1"] =false;
            }

            if (characterPosition.x >= 3000 &&
                characterPosition.x <= 3060 &&
                characterPosition.y >= 4740 &&
                characterPosition.y <= 4770)
            {
                // 如果人物进入指定范围，则切换场景
                if (!inZones["zone2"]) {
                    Scene* scene = othersence::createothersenceScene();
                    Director::getInstance()->pushScene(scene);
                    inZones["zone2"] = true;
                }
                else
                    inZones["zone2"] = false;
            }
            }, "view_point_update_key");
      
    }
    else {
        log("Failed to load TMX file: %s", tmxFileName.c_str());
    }

}

bool outside::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 初始化成员变量
    _personalInterfaceLayer = nullptr;
    _menuWindow = nullptr;
    _closeButton = nullptr;
    _isPersonalInterfaceVisible = false;
    _currentImageIndex = 1;
    _selectedButtonIndex = -1;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    _rainParticleSystem = ParticleRain::create();
    this->addChild(_rainParticleSystem, 12);
    _rainParticleSystem->setPosition(Vec2(3470, 3560));
    _rainParticleSystem->resetSystem(); // 开始发射粒子
    _rainParticleSystem->setStartSize(10.0f); // 粒子生命周期的开始大小
    _rainParticleSystem->setEndSize(20.0f);   // 粒子生命周期的结束大小

    // 设置粒子的开始颜色为海的蓝色（完全不透明）
    _rainParticleSystem->setStartColor(Color4F(0.0f, 0.5f, 1.0f, 1.0f));

    // 设置粒子的结束颜色为海的蓝色（半透明）
    _rainParticleSystem->setEndColor(Color4F(0.0f, 0.3f, 0.6f, 0.5f));


    _rainParticleSystem->setStartSize(15.0f);
    _rainParticleSystem->setEndSize(15.0f);

    this->scheduleOnce([&](float dt) {
        _rainParticleSystem->stopSystem(); // 停止粒子系统
        }, 40.0f, "stopRainTimer");

    // 添加键盘事件监听器
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(outside::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);


    // 创建 NPC1 
    auto npcButton = Button::create("bag/npc1.png", "bag/npc2.png"); // 点击前为 npc1.png，点击后为 npc2.png
    npcButton->setPosition(Vec2(800, 700));
    float scaleFactor = 4.0f; // 根据需要调整缩放比例
    npcButton->setScale(scaleFactor);
    this->addChild(npcButton, 5);

    // 添加按钮点击事件监听器
    npcButton->addTouchEventListener([this, npcButton](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // 获取 NPC 按钮和角色的横坐标
            Vec2 npcPosition = npcButton->getPosition();
            Vec2 characterPosition = characteraction->getPosition();
            float distance = characterPosition.x - npcPosition.x; // 计算横坐标差值

            // 如果横坐标差值小于 100，则执行逻辑
            if (distance < 100) {
                // 切换到 npc2.png
                npcButton->loadTextureNormal("bag/npc2.png");

                // 弹出对话框
                auto dialogBox = Sprite::create("picture/dialog.png"); // 替换为你的对话框图片路径
                dialogBox->setPosition(Vec2(900, 400)); // 设置对话框位置
                dialogBox->setScale(0.6f);
                this->addChild(dialogBox, 6); // 确保对话框在 NPC 按钮上方

                // 3 秒后移除对话框并恢复
                auto delay = DelayTime::create(3.0f);
                auto restoreNPC = CallFunc::create([npcButton]() {
                    npcButton->loadTextureNormal("bag/npc1.png"); // 恢复为 npc1.png
                    });
                auto removeDialog = CallFunc::create([dialogBox]() {
                    dialogBox->removeFromParent();
                    });
                auto sequence = Sequence::create(delay, restoreNPC, removeDialog, nullptr);
                dialogBox->runAction(sequence);
            }
        }
        });

    // 创建 NPC2 
    auto npcButton1 = Button::create("bag/npc3.png", "bag/npc4.png"); // 点击前为 npc1.png，点击后为 npc2.png
    npcButton1->setPosition(Vec2(4100, 650));
    npcButton1->setScale(0.8f);
    this->addChild(npcButton1, 5);

    // 添加按钮点击事件监听器
    npcButton1->addTouchEventListener([this, npcButton1](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // 获取 NPC 按钮和角色的横坐标
            Vec2 npcPosition1 = npcButton1->getPosition();
            Vec2 characterPosition = characteraction->getPosition();
            float distance = npcPosition1.x - characterPosition.x; // 计算横坐标差值

            // 如果横坐标差值小于 100，则执行逻辑
            if (distance < 100) {
                npcButton1->loadTextureNormal("bag/npc4.png");

                // 弹出对话框
                auto dialogBox = Sprite::create("picture/dialog2.png"); // 替换为你的对话框图片路径
                dialogBox->setPosition(Vec2(4100, 400)); // 设置对话框位置
                dialogBox->setScale(0.6f);
                this->addChild(dialogBox, 6); // 确保对话框在 NPC 按钮上方

                // 3 秒后移除对话框并恢复
                auto delay = DelayTime::create(3.0f);
                auto restoreNPC = CallFunc::create([npcButton1]() {
                    npcButton1->loadTextureNormal("bag/npc3.png"); // 恢复
                    });
                auto removeDialog = CallFunc::create([dialogBox]() {
                    dialogBox->removeFromParent();
                    });
                auto sequence = Sequence::create(delay, restoreNPC, removeDialog, nullptr);
                dialogBox->runAction(sequence);
            }
        }
        });

    struct tm* timeinfo;
    time_t rawtime;
    time(&rawtime);
    timeinfo = localtime(&rawtime);


    // 获取星期几
    const char* days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    std::stringstream ss;
    ss << days[timeinfo->tm_wday] << ", ";
    std::string dayOfWeek = ss.str();

    // 获取当前时间（不包含秒）
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%H:%M", timeinfo);
    std::string currentTime = buffer;


    auto dayLabel = Label::createWithTTF(dayOfWeek, "fonts/Marker Felt.ttf", 50);
    dayLabel->setAnchorPoint(Vec2(1, 1));
    dayLabel->setPosition(Vec2(3 * 1500, 3 * 1100 + 1450));//1400, 1553
    
   
    this->addChild(dayLabel, 1);

    auto timeLabel = Label::createWithTTF(currentTime, "fonts/Marker Felt.ttf", 40);
    timeLabel->setPosition(Vec2(3 * 1500 - 125, 3 * 1100 + 1450 - 170));//1400, 1405
    this->addChild(timeLabel, 1);

    // 更新游戏内时间
    schedule(schedule_selector(outside::updateTime), 1.0f);

   
    // 创建签到窗口
    auto qiandaoWindow = Sprite::create("picture/qiandao.png");

    qiandaoWindow->setPosition(3 * 890 + 600, 3 * 740 + 1300);
    this->addChild(qiandaoWindow, 10); // 设置较高的z轴，确保窗口在最上层

    // 创建签到按钮
    auto qiandaoButton = Button::create("picture/bottom.png", "picture/bottom1.png");
    qiandaoButton->setPosition(Vec2(qiandaoWindow->getContentSize().width / 2, qiandaoWindow->getContentSize().height / 4));
    qiandaoButton->addTouchEventListener([qiandaoButton](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // 切换按钮图片
            if (qiandaoButton->getRendererNormal()->getTexture() == Director::getInstance()->getTextureCache()->addImage("picture/bottom.png")) {
                qiandaoButton->loadTextureNormal("picture/bottom1.png");
            }
            else {
                qiandaoButton->loadTextureNormal("picture/bottom.png");
            }
        }
        });
    qiandaoWindow->addChild(qiandaoButton);

    // 创建关闭按钮
    auto closeButton = Button::create("picture/bottom2.png");
    closeButton->setPosition(Vec2(qiandaoWindow->getContentSize().width - closeButton->getContentSize().width / 2, qiandaoWindow->getContentSize().height - closeButton->getContentSize().height / 2));
    closeButton->addTouchEventListener([qiandaoWindow](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // 关闭签到窗口
            qiandaoWindow->removeFromParentAndCleanup(true);
        }
        });
    qiandaoWindow->addChild(closeButton);
  

    //钓鱼
    auto fishing = Button::create("picture/tofish.png", "picture/tofish2.png");
    fishing->setPosition(Vec2(3 * 890 + 1000, 3 * 740 - 210));
    this->addChild(fishing,3);
    _isfishingVisible = false;
    fishing->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            
            if (!_isfishingVisible&&!fishman&&!spriteFish) {//
                fishImage = ImageView::create("picture/fishingback.png");
                fishImage->setPosition(Vec2(3 * 890 + 500, 3 * 740 - 210));//400, 900
                fishImage->setScale(0.9);
                this->addChild(fishImage);

                spriteFish = Sprite::create("character/fishman1.png");
                if (spriteFish == nullptr) {
                    CCLOG("spriteFish 未能成功创建!");
                    return;
                }
                if (!spriteFish) {
                    CCLOG("Failed to load spriteFish texture");
                    return;
                }
                spriteFish->setPosition(Vec2(3 * 890 + 500 - 50, 3 * 740 - 210 + 100));//350, 1000
                this->addChild(spriteFish);

                Animation* Fishing = Animation::create();
                for (int i = 1; i <= 5; i++)
                {
                    std::string frameName = "character/fishman" + std::to_string(i) + ".png";
                    Fishing->addSpriteFrameWithFile(frameName);
                }
                Fishing->setDelayPerUnit(0.3f); // 设置每帧的播放时间
                Fishing->setLoops(1); // 设置循环播放
                Animate* FishingAnimate = Animate::create(Fishing);
                Fishing->retain(); // 保留动画对象，防止被释放

                spriteFish->runAction(FishingAnimate);
                _isfishingVisible = true;

            }
            else {
                if (fishImage) {
                    this->removeChild(fishImage);
                    fishImage = nullptr;
                }
                if (fishman) {
                    this->removeChild(fishman);
                    fishman = nullptr;
                }
                if (spriteFish) {
                    //spriteFish->stopAllActions();
                    this->removeChild(spriteFish);
                    spriteFish = nullptr;
                }
                _isfishingVisible = false;

            }
        }
        });
    
  
    this->scheduleUpdate();
    
    return true;
}

void outside::updateTime(float dt) {

    auto currentTime = std::chrono::high_resolution_clock::now();

    // 计算从游戏开始到现在的现实时间流逝（以秒为单位）
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - gameStartTime).count();

    // 将现实时间转换为游戏内时间（每0.7秒等于游戏内的一分钟）
    int elapsedTime = static_cast<int>(duration / 0.7f);
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);

    // 更新分钟数
    timeinfo->tm_min += elapsedTime / 60;
    mktime(timeinfo); // 更新时间结构体

    // 更新Label
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%H:%M", timeinfo); 

    // 获取Label并更新字符串
    auto label = dynamic_cast<Label*>(getChildByName("timeLabel"));
    if (label) {
        label->setString(buffer);
    }
    else {
        // 如果转换失败或者没有找到对应的Label，则打印错误信息或者进行其他错误处理
        CCLOG("Failed to get timeLabel or it's not a Label type");
    }
}

void outside::setViewPointCenter(Point position, cocos2d::TMXTiledMap* tiledMap) {
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


Point outside::tileCoordForPosition(cocos2d::Point position, cocos2d::TMXTiledMap* tiledMap)
{
    int x = position.x /  tiledMap->getTileSize().width;
    int y = (( tiledMap->getMapSize().height *  tiledMap->getTileSize().height) - position.y) /  tiledMap->getTileSize().height;
    return Point(x, y);
}


void outside::update(float delta, cocos2d::Sprite* _player,cocos2d::TMXTiledMap* tiledMap) {
    Vec2 playerPosition = _player->getPosition();

    // 定义触发场景切换的位置
    Vec2 triggerPosition = Vec2(900, 1300); 

    // 检查玩家是否到达了触发位置
    if (playerPosition.x == triggerPosition.x && playerPosition.y == triggerPosition.y) {
        // 触发场景切换
        changeScene();
    }

    Vec2 characterPosition = characteraction->getPosition();

    // 更新视点，确保人物始终位于屏幕中心
    setViewPointCenter(characterPosition, tiledMap);
}

void outside::changeScene() {
    // 创建并切换到Scene2
    auto scene = intovalley::createintovalleyScene(); 
    Director::getInstance()->replaceScene(scene);
}


void outside::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    // 检查按下的键是否为 E 键
    if (keyCode == EventKeyboard::KeyCode::KEY_E)
    {
        // 切换个人界面的显示状态
        if (_isPersonalInterfaceVisible)
        {
            hidePersonalInterface();
        }
        else
        {
            showPersonalInterface();
        }
    }
}

void outside::hidePersonalInterface()
{
    // 隐藏个人界面的逻辑
    if (_personalInterfaceLayer)
    {
        this->removeChild(_personalInterfaceLayer); // 移除个人界面层
        _personalInterfaceLayer = nullptr; // 清空层指针
    }
    _isPersonalInterfaceVisible = false;
}


void outside::showPersonalInterface()
{
    if (_isPersonalInterfaceVisible) return;

    _isPersonalInterfaceVisible = true;

    // 创建个人界面层
    _personalInterfaceLayer = Layer::create();
    this->addChild(_personalInterfaceLayer, 10); // 确保这个层在其他层之上

    // 加载初始图片窗口
    _menuWindow = Sprite::create("bag/1.png");

    Vec2 characterPosition = characteraction->getPosition();

    // 将菜单设置为屏幕中央
    _menuWindow->setPosition(characterPosition);

    // 设置窗口大小
    _menuWindow->setScale(1.0f);

    _personalInterfaceLayer->addChild(_menuWindow);

    // 创建关闭按钮
    _closeButton = MenuItemImage::create(
        "picture/bottom2.png",
        "picture/bottom2.png",
        CC_CALLBACK_1(outside::closePersonalInterface, this) // 使用 CC_CALLBACK_1 绑定 this
    );

    // 设置关闭按钮的位置
    auto windowSize = _menuWindow->getContentSize();
    _closeButton->setPosition(Vec2(windowSize.width - _closeButton->getContentSize().width / 2 + 60, windowSize.height - _closeButton->getContentSize().height / 2 + 60)); // 在窗口内适当位置

    // 创建菜单并添加关闭按钮
    auto closeMenu = Menu::create(_closeButton, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    _menuWindow->addChild(closeMenu);

    // 创建顶部的选择按钮
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto buttonMenu = Menu::create();

    for (int i = 1; i <= 7; ++i)
    {
        std::string buttonNormal = StringUtils::format("picture/%d%d.png", i, i);
        std::string buttonSelected = StringUtils::format("picture/%d%d.png", i, i);

        auto button = MenuItemImage::create(
            buttonNormal,
            buttonSelected,
            [this, i](Ref* sender) {
                selectImage(i);
            }
        );

        // 设置按钮的初始位置
        button->setPosition(Vec2(characterPosition.x - 1600 + 80 * i, characterPosition.y - 170));
        buttonMenu->addChild(button, 0, i);
    }

    buttonMenu->setPosition(visibleSize / 2);
    _personalInterfaceLayer->addChild(buttonMenu, 1);
}



void outside::selectImage(int index)
{
    _currentImageIndex = index;

    removeVerticalButtons();

    // 更新主图片
    std::string imageName = StringUtils::format("bag/%d.png", _currentImageIndex);

    // 如果当前选择的图片是 3.png，则显示竖排按钮
    if (index == 1) // 假设在选择 1.png 时添加可拖动的图片
    {
        // 获取当前窗口的大小
        auto windowSize = _menuWindow->getContentSize();

        // 获取 _menuWindow 的位置
        Vec2 menuWindowPosition = _menuWindow->getPosition();

        auto draggableSprite = Sprite::create("bag/tool1.png");

        float scaleFactor = 4.0f; // 根据需要调整缩放比例
        draggableSprite->setScale(scaleFactor);

        // 设置精灵的位置为 _menuWindow 的中心位置
        draggableSprite->setPosition(Vec2(windowSize.width - 200, windowSize.height - 300));

        _menuWindow->addChild(draggableSprite, 10);


        // 添加垃圾桶
        auto trashCanSprite = Sprite::create("bag/trashcan.png");
        trashCanSprite->setPosition(Vec2(windowSize.width + 50, windowSize.height - 500)); // 设置垃圾桶位置
        _menuWindow->addChild(trashCanSprite);

        // 设置拖动事件
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);

        // 开始拖动
        listener->onTouchBegan = [=](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 touchPoint = target->convertToNodeSpace(touch->getLocation());
            Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
            if (rect.containsPoint(touchPoint))
            {
                return true;
            }
            return false;
            };

        // 拖动中
        listener->onTouchMoved = [=](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            target->setPosition(target->getPosition() + touch->getDelta());
            };

        // 拖动结束
        listener->onTouchEnded = [=](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 endPosition = target->getPosition();

            // 检测是否拖动到垃圾桶位置
            Rect trashCanRect = trashCanSprite->getBoundingBox();
            if (trashCanRect.containsPoint(endPosition))
            {
                // 移除可拖动的图片
                target->removeFromParentAndCleanup(true);
            }
            };

        // 注册事件监听器
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, draggableSprite);

        // 显示 money 变量
        int money = 500; // 初始值为 500
        auto moneyLabel = Label::createWithSystemFont(StringUtils::format("%d", money), "Arial", 30);
        moneyLabel->setColor(Color3B::BLACK); // 设置字体颜色为白色
        moneyLabel->setPosition(Vec2(windowSize.width / 2 + 200, windowSize.height / 2 - 110)); // 设置位置为窗口中心
        _menuWindow->addChild(moneyLabel, 20); // 添加到 _menuWindow，层级高于其他元素


    }
    else if (_currentImageIndex == 3)
    {
        showVerticalButtons();
    }
    else if (_currentImageIndex == 7) {
        showVerticalButtons2();
    }


    if (_menuWindow)
    {
        _menuWindow->setTexture(imageName);
    }

    // 获取菜单按钮
    auto buttonMenu = dynamic_cast<Menu*>(_personalInterfaceLayer->getChildByTag(1));
    if (!buttonMenu) return;

    // 遍历所有按钮，更新按钮的位移效果
    for (int i = 1; i <= 7; ++i)
    {
        auto button = dynamic_cast<MenuItemImage*>(buttonMenu->getChildByTag(i));
        if (button)
        {
            if (i == index)
            {
                button->setPositionY(button->getPositionY() - 10); // 下移效果
            }
            else
            {
                button->setPositionY(button->getPositionY() + 10); // 恢复初始位置
            }
        }
    }
}


void outside::showVerticalButtons()
{
    // 获取当前窗口的大小
    auto windowSize = _menuWindow->getContentSize();

    // 创建一个层来放置按钮
    auto buttonLayer = Layer::create();
    buttonLayer->setName("buttonLayer"); // 设置层的名称，确保可以被正确捕捉
    _menuWindow->addChild(buttonLayer);

    // 在 3.png 图片上竖排放置 5 个按钮 bottom3.1.png
    for (int i = 1; i <= 5; ++i)
    {
        auto button = Button::create("picture/giftbottom1.png", "picture/giftbottom1.png");
        button->setPosition(Vec2(windowSize.width / 2 + 300, windowSize.height + 90 - 125 * i)); // 竖直排列
        button->setTag(i); // 为按钮设置唯一的 Tag
        button->addTouchEventListener([this, i](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED) {
                _clickedButtonIndex = i; // 记录点击的按钮位置
                showNewWindow(); // 点击按钮后跳出新的窗口
            }
            });
        buttonLayer->addChild(button);
    }
}


void outside::showVerticalButtons2()
{
    // 获取当前窗口的大小
    auto windowSize = _menuWindow->getContentSize();

    // 创建一个层来放置按钮
    auto buttonLayer = Layer::create();
    buttonLayer->setName("buttonLayer"); // 设置层的名称，确保可以被正确捕捉
    _menuWindow->addChild(buttonLayer);

    // 在 6.png 图片上竖排放置 4 个按钮 bottom3.1.png
    for (int i = 1; i <= 4; ++i)
    {
        auto button = Button::create("picture/bottom.png", "picture/bottom2.png");
        button->setPosition(Vec2(windowSize.width / 6 - 90, windowSize.height - 70 - 90 * i)); // 竖直排列
        button->setTag(i);

        // 添加触摸事件监听器
        button->addTouchEventListener([this, button](Ref* sender, Widget::TouchEventType type) {
            // 判断触摸事件类型
            if (type == Widget::TouchEventType::ENDED) {
                // 切换按钮状态
                if (button->getRendererNormal()->getTexture() == Director::getInstance()->getTextureCache()->addImage("picture/bottom.png")) {
                    button->loadTextureNormal("picture/bottom2.png");
                }
                else {
                    button->loadTextureNormal("picture/bottom.png");
                }
            }
            });

        buttonLayer->addChild(button);
    }
}


void outside::removeVerticalButtons()
{
    // 移除所有竖排按钮
    _menuWindow->removeAllChildrenWithCleanup(true);
}

void outside::showNewWindow()
{
    // 创建新的窗口
    auto newWindow = Sprite::create("picture/back.png");

    Vec2 characterPosition = characteraction->getPosition();

    // 将菜单设置为屏幕中央
    newWindow->setPosition(characterPosition);
    newWindow->setScale(1.0f);

    // 添加到个人界面层
    _personalInterfaceLayer->addChild(newWindow, 11); // 确保新窗口在最上层

    // 创建关闭新窗口的按钮
    auto closeNewWindowButton = Button::create("picture/ok1.png", "picture/ok1.png");
    float scaleFactor = 1.5f; // 根据需要调整缩放比例
    closeNewWindowButton->setScale(scaleFactor);
    closeNewWindowButton->setPosition(Vec2(newWindow->getContentSize().width - closeNewWindowButton->getContentSize().width / 2 - 100, newWindow->getContentSize().height - closeNewWindowButton->getContentSize().height / 2 - 800));
    closeNewWindowButton->addTouchEventListener([newWindow, this](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // 关闭新窗口
            newWindow->removeFromParent();

            // 获取按钮层
            auto buttonLayer = dynamic_cast<Layer*>(_menuWindow->getChildByName("buttonLayer"));
            if (buttonLayer) {
                auto giftButton = dynamic_cast<Button*>(buttonLayer->getChildByTag(_clickedButtonIndex));
                if (giftButton) {
                    // 获取当前按钮的点击次数
                    int clickCount = _buttonClickCounts[_clickedButtonIndex]++;
                    // 根据点击次数决定是否添加对号按钮
                    if (clickCount < 2) {
                        auto bottomButton = Button::create("picture/bottom1.png", "picture/bottom1.png");
                        float scaleFactor = 0.8f; // 根据需要调整缩放比例
                        bottomButton->setScale(scaleFactor);

                        // 根据点击次数调整对号按钮的位置
                        float offsetX = clickCount * 48; // 每次点击向右偏移 30 像素
                        bottomButton->setPosition(Vec2(giftButton->getPositionX() - 30 + offsetX, giftButton->getPositionY() - 57));

                        buttonLayer->addChild(bottomButton);
                    }
                    if (clickCount == 2) {

                        auto popupImage = Sprite::create("bag/back.png"); // 替换为你的弹出图片路径 
                        popupImage->setPosition(Vec2(giftButton->getPositionX() - 30, giftButton->getPositionY() - 57));
                        popupImage->setScale(0.5f);
                        buttonLayer->addChild(popupImage);

                        // 5秒后移除弹出图片
                        auto delay = DelayTime::create(2.0f);
                        auto removePopup = CallFunc::create([popupImage]() {
                            popupImage->removeFromParent();
                            });
                        auto sequence = Sequence::create(delay, removePopup, nullptr);
                        popupImage->runAction(sequence);
                    }
                }
            }
            else {
                CCLOG("Error: buttonLayer not found!");
            }
        }
        });
    newWindow->addChild(closeNewWindowButton);

    // 创建6个按钮并横向排列
    std::vector<Button*> giftButtons;
    for (int i = 1; i <= 6; ++i) {
        auto giftButton = Button::create("picture/gift" + std::to_string(i) + ".png", "picture/gift" + std::to_string(i) + ".png");
        float scaleFactor = 3.0f; // 根据需要调整缩放比例
        giftButton->setScale(scaleFactor);
        giftButton->setPosition(Vec2(100 + (i - 1) * 150, 800)); // 横向排列，每个按钮间隔150像素
        giftButton->addTouchEventListener([newWindow, &giftButtons](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED) {
                auto button = static_cast<Button*>(sender);
                // 处理按钮点击事件
            }
            });
        newWindow->addChild(giftButton);
        giftButtons.push_back(giftButton);

        // 在每个按钮下面添加一个 bottom.png 按钮
        auto bottomButton = Button::create("picture/bottom.png", "picture/bottom1.png");
        bottomButton->setPosition(Vec2(giftButton->getPositionX(), giftButton->getPositionY() - 100)); // 在按钮下方100像素处
        bottomButton->addTouchEventListener([bottomButton](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED) {
                // 切换按钮状态
                if (bottomButton->getRendererNormal()->getTexture() == Director::getInstance()->getTextureCache()->addImage("picture/bottom.png")) {
                    bottomButton->loadTextureNormal("picture/bottom1.png");
                }
                else {
                    bottomButton->loadTextureNormal("picture/bottom.png");
                }
            }
            });
        newWindow->addChild(bottomButton);
    }
}


void outside::closePersonalInterface(Ref* sender)
{
    if (!_isPersonalInterfaceVisible) return;

    _isPersonalInterfaceVisible = false;

    // 移除个人界面层
    _personalInterfaceLayer->removeFromParent();
    _personalInterfaceLayer = nullptr;
}