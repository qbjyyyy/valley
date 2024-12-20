#include "outside.h"
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"
#include "intovalley.h"
#include "SimpleAudioEngine.h"
#include "menu.h"
#include "GameTimeSystem.h"
#include "characterAciton.h"

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
       
        this->addChild(tiledMap, 0);

        auto imageView = ImageView::create("picture/time.png");
        if (imageView) {
            // 设置位置
            imageView->setPosition(Vec2(1400, 1480));
            // 添加到场景
            this->addChild(imageView);
        }
       
    
        _meta = tiledMap->getLayer("meta");
        _meta->setVisible(false);

        TMXObjectGroup* objects = tiledMap->getObjectGroup("objects");
        CCASSERT(NULL != objects, "'objects' object group not found");
        auto spawnPoint = objects->getObject("character");
        int x = spawnPoint["x"].asInt();
        int y = spawnPoint["y"].asInt();

        auto characteraction = CharacterWithTools::create("character/Dana0.png");
        if (characteraction == nullptr) {
            CCLOG("Error: Failed to create character!");
        }

        this->scheduleUpdate();
        setViewPointCenter(characteraction->getPosition(), tiledMap);

        tiledMap_ = tiledMap;

        characteraction->setPosition(Vec2(x-300, y-400)); // 确保位置在屏幕范围内
        this->addChild(characteraction);


        auto keyboardListener = EventListenerKeyboard::create();
        keyboardListener->onKeyPressed = [characteraction](EventKeyboard::KeyCode keyCode, Event* event) {
            Vec2 direction = Vec2::ZERO; // 局部变量
            if (keyCode == EventKeyboard::KeyCode::KEY_W)
                direction.y = 1;
            if (keyCode == EventKeyboard::KeyCode::KEY_S)
                direction.y = -1; // 向下
            if (keyCode == EventKeyboard::KeyCode::KEY_A)
                direction.x = -1; // 向左
            if (keyCode == EventKeyboard::KeyCode::KEY_D)
                direction.x = 1; // 向右
            characteraction->move(direction); // 将键盘输入传递给角色
            };
        keyboardListener->onKeyReleased = [characteraction](EventKeyboard::KeyCode keyCode, Event* event) {
            Vec2 direction = Vec2::ZERO; // 局部变量
            if (keyCode == EventKeyboard::KeyCode::KEY_W)
                direction.y = 0;
            if (keyCode == EventKeyboard::KeyCode::KEY_S)
                direction.y = 0;
            if (keyCode == EventKeyboard::KeyCode::KEY_A)
                direction.x = 0;
            if (keyCode == EventKeyboard::KeyCode::KEY_D)
                direction.x = 0;
            characteraction->move(direction); // 将键盘输入传递给角色
            };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
        // 设置目标区域
      
        targetArea = Rect(200,100,200, 200);
      
        auto listener2 = EventListenerTouchOneByOne::create();
        listener2->onTouchBegan = [&](Touch* touch, Event* unused_event)->bool {
            Vec2 touchLocation = touch->getLocation();
            if (targetArea.containsPoint(touchLocation)) {
                if (_lastSprite && _lastSprite->getPosition() != touchLocation) {
                    this->removeChild(_lastSprite);
                    _lastSprite = nullptr;
                }

                // 如果当前点击位置没有Sprite，则创建一个新的Sprite
                if (!_lastSprite) {
                    _lastSprite = Sprite::create("picture/lan.png");
                    _lastSprite->setPosition(touchLocation);
                    this->addChild(_lastSprite);
                }
                return true;
            }
            return false;
            };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener2, this);

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

    // 添加键盘事件监听器
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(outside::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);


    auto a = Sprite::create("picture/tofish.png");
    a->setPosition(Vec2(900, 1300));
    this->addChild(a,5);
    

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

    // 创建并添加Label到场景中
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto dayLabel = Label::createWithTTF(dayOfWeek, "fonts/Marker Felt.ttf", 50);
    dayLabel->setPosition(Vec2(1400, 1553));
    
   
    this->addChild(dayLabel, 1);

    auto timeLabel = Label::createWithTTF(currentTime, "fonts/Marker Felt.ttf", 40);
    timeLabel->setPosition(Vec2(1400, 1405));
    this->addChild(timeLabel, 1);

    // 更新游戏内时间
    schedule(schedule_selector(outside::updateTime), 1.0f);

    // 创建签到窗口
    auto qiandaoWindow = Sprite::create("picture/qiandao.png");
    qiandaoWindow->setPosition(Vec2(visibleSize.width / 8 + origin.x, visibleSize.height / 1.5 + origin.y));
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
    fishing->setPosition(Vec2(915,750));
    this->addChild(fishing,3);
    _isfishingVisible = false;
    fishing->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            
            if (!_isfishingVisible&&!fishman&&!spriteFish) {//
                fishImage = ImageView::create("picture/fishingback.png");
                fishImage->setPosition(Vec2(400, 900));
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
                spriteFish->setPosition(Vec2(350, 1000));
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


void outside::setPlayerPosition(cocos2d::Point position, cocos2d::TMXTiledMap* tiledMap) {
    Point tileCoord = this->tileCoordForPosition(position, tiledMap);
    int tileGid = _meta->getTileGIDAt(tileCoord);
    if (tileGid) {
        auto properties =  tiledMap->getPropertiesForGID(tileGid).asValueMap();
        if (!properties.empty()) {
            auto collision = properties["Collidable"].asString();
            auto collectable = properties["Collectable"].asString();
            if ("True" == collision) {
                return;
            }
            if ("True" == collectable) {
                _meta->removeTileAt(tileCoord);
                _foreground->removeTileAt(tileCoord);

            }
        }
    }
    _player->setPosition(position);
}


void outside::onTouchEnded(Touch* touch, Event* unused_event, cocos2d::TMXTiledMap* tiledMap)
{
    auto touchLocation = touch->getLocation();
    touchLocation = this->convertToNodeSpace(touchLocation);

    auto playerPos = _player->getPosition();
    auto diff = touchLocation - playerPos;
    auto tileSize = tiledMap->getTileSize();
    auto mapSize = tiledMap->getMapSize();

    // 根据触摸位置计算新的玩家位置
    if (abs(diff.x) > abs(diff.y)) {
        playerPos.x += (diff.x > 0) ? tileSize.width : -tileSize.width;
    }
    else {
        playerPos.y += (diff.y > 0) ? tileSize.height : -tileSize.height;
    }

    // 边界检查
    playerPos.x = MIN(MAX(playerPos.x, tileSize.width / 2), (mapSize.width * tileSize.width) - tileSize.width / 2);
    playerPos.y = MIN(MAX(playerPos.y, tileSize.height / 2), (mapSize.height * tileSize.height) - tileSize.height / 2);

    // 设置玩家位置
    this->setPlayerPosition(playerPos, tiledMap);

    // 更新视口位置
    this->setViewPointCenter(_player->getPosition(), tiledMap);
}

void outside::setViewPointCenter(Point position, cocos2d::TMXTiledMap* tiledMap) {
    auto winSize = Director::getInstance()->getWinSize();

    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);

    x = MIN(x, ( tiledMap->getMapSize().width *  tiledMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, ( tiledMap->getMapSize().height *  tiledMap->getTileSize().height) - winSize.height / 2);
    auto actualPosition = Point(x, y);

    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);
    auto viewPoint = centerOfView - actualPosition;
    this->setPosition(viewPoint);
}


Point outside::tileCoordForPosition(cocos2d::Point position, cocos2d::TMXTiledMap* tiledMap)
{
    int x = position.x /  tiledMap->getTileSize().width;
    int y = (( tiledMap->getMapSize().height *  tiledMap->getTileSize().height) - position.y) /  tiledMap->getTileSize().height;
    return Point(x, y);
}


void outside::update(float delta, cocos2d::Sprite* _player) {
    Vec2 playerPosition = _player->getPosition();

    // 定义触发场景切换的位置
    Vec2 triggerPosition = Vec2(900, 1300); // 您可以根据需要调整这个位置

    // 检查玩家是否到达了触发位置
    if (playerPosition.x == triggerPosition.x && playerPosition.y == triggerPosition.y) {
        // 触发场景切换
        changeScene();
    }
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
        // 如果个人界面不可见，显示个人界面
        if (!_isPersonalInterfaceVisible)
        {
            showPersonalInterface();
        }
    }
}

void outside::showPersonalInterface()
{
    if (_isPersonalInterfaceVisible) return;

    _isPersonalInterfaceVisible = true;

    // 创建个人界面层
    _personalInterfaceLayer = Layer::create();
    this->addChild(_personalInterfaceLayer, 10); // 确保这个层在其他层之上

    // 加载初始图片窗口
    _menuWindow = Sprite::create("picture/1.png");

    // 设置窗口位置为屏幕中央
    _menuWindow->setPosition(Vec2(600,700));

    // 设置窗口大小为屏幕的 80%
    _menuWindow->setScale(1.2f);

    _personalInterfaceLayer->addChild(_menuWindow);

    // 创建关闭按钮
    /*_closeButton = MenuItemImage::create(
        "picture/bottom2.png",
        "picture/bottom2.png",
        [](Ref* sender) {
            auto scene = Director::getInstance()->getRunningScene();
            outside* helloWorld = dynamic_cast<outside*>(scene);
            if (helloWorld) {
                helloWorld->closePersonalInterface();
            }
        }
    );*/

    /*auto closeButton = Button::create("picture/bottom2.png");
    closeButton->setPosition(Vec2(qiandaoWindow->getContentSize().width - closeButton->getContentSize().width / 2, qiandaoWindow->getContentSize().height - closeButton->getContentSize().height / 2));
    closeButton->addTouchEventListener([qiandaoWindow](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // 关闭签到窗口
            qiandaoWindow->removeFromParentAndCleanup(true);
        }
        });
    qiandaoWindow->addChild(closeButton);*/

    // 设置关闭按钮的位置
    auto windowSize = _menuWindow->getContentSize();
    _closeButton->setPosition(Vec2(windowSize.width + 40, windowSize.height + 40)); // 在窗口内适当位置

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
        button->setPosition(Vec2(-visibleSize.width / 3 + 80 * i, visibleSize.height / 2 - 80));
        buttonMenu->addChild(button, 0, i);
    }

    buttonMenu->setPosition(visibleSize / 2);
    _personalInterfaceLayer->addChild(buttonMenu, 1);
}

void outside::selectImage(int index)
{
    _currentImageIndex = index;

    // 更新主图片
    std::string imageName = StringUtils::format("picture/%d.png", _currentImageIndex);
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

void outside::switchImage(int direction)
{
    _currentImageIndex = (_currentImageIndex + direction + 7 - 1) % 7 + 1; // 循环切换 1 到 7

    std::string imageName = StringUtils::format("picture/%d.png", _currentImageIndex);
    if (_menuWindow)
    {
        _menuWindow->setTexture(imageName);
    }

    selectImage(_currentImageIndex); // 更新按钮效果
}

void outside::closePersonalInterface()
{
    if (!_isPersonalInterfaceVisible) return;

    _isPersonalInterfaceVisible = false;

    // 移除个人界面层
    _personalInterfaceLayer->removeFromParent();
    _personalInterfaceLayer = nullptr;
}






