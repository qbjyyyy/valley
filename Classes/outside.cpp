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
    // ���ݵ�ͼ�������ز�ͬ�� TMX ��ͼ�ļ�
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
    // ���ر���ͼƬ
    auto tiledMap = TMXTiledMap::create(tmxFileName);
    if (tiledMap) {
        // ���õ�ͼλ��
        tiledMap->setPosition(Vec2(-500, -200));
       
        this->addChild(tiledMap, 0);

        auto imageView = ImageView::create("picture/time.png");
        if (imageView) {
            // ����λ��
            imageView->setPosition(Vec2(1400, 1480));
            // ��ӵ�����
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

        // ����npc1��ť
        auto _npc1Button = Button::create(
            "picture/NPC1.png",
            "picture/NPC1.png"
        );

        // ����npc1��ť��λ��
        _npc1Button->setPosition(Vec2(x - 100, y - 100));
        auto moveTo1 = MoveTo::create(40.0f, Vec2(x - 600, y - 440)); // NPC1 ���ƶ�����
        auto scaleBy1 = ScaleBy::create(5.0f, 5.0f);
        _npc1Button->runAction(moveTo1);
        this->addChild(_npc1Button);

        // ��Ӵ����¼�������
        _npc1Button->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED) {
                auto dialogImage = Sprite::create("picture/npc1_dialog.png");
                if (!dialogImage) {
                    CCLOG("Error: Failed to create dialog image for NPC1!");
                    return;
                }
                dialogImage->setPosition(Vec2(600, 400)); // ���öԻ���λ��
                this->addChild(dialogImage, 10); // ��ӵ������У�ȷ�������ϲ�
                // �������һ����ʱ�������¼����رնԻ���
                auto delay = DelayTime::create(3.0f); // 3����Զ��ر�
                auto removeDialog = CallFunc::create([dialogImage]() {
                    dialogImage->removeFromParentAndCleanup(true);
                    });
                dialogImage->runAction(Sequence::create(delay, removeDialog, nullptr));
            }
            });

        // ����npc2��ť
        auto _npc2Button = Button::create(
            "picture/NPC2.png",
            "picture/NPC2.png"
        );

        // ����npc2��ť��λ��
        _npc2Button->setPosition(Vec2(x - 200, y - 150));
        auto moveTo2 = MoveTo::create(40.0f, Vec2(x - 1600, y - 850)); // NPC2 ���ƶ�����
        auto scaleBy2 = ScaleBy::create(5.0f, 5.0f);
        _npc2Button->runAction(moveTo2);
        this->addChild(_npc2Button);

        // ��Ӵ����¼�������
        _npc2Button->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED) {
                auto dialogImage = Sprite::create("picture/npc2_dialog.png");
                if (!dialogImage) {
                    CCLOG("Error: Failed to create dialog image for NPC2!");
                    return;
                }
                dialogImage->setPosition(Vec2(600, 400)); // ���öԻ���λ��
                this->addChild(dialogImage, 10); // ��ӵ������У�ȷ�������ϲ�
                // �������һ����ʱ�������¼����رնԻ���
                auto delay = DelayTime::create(3.0f); // 3����Զ��ر�
                auto removeDialog = CallFunc::create([dialogImage]() {
                    dialogImage->removeFromParentAndCleanup(true);
                    });
                dialogImage->runAction(Sequence::create(delay, removeDialog, nullptr));
            }
            });

        // ����npc3��ť
        auto _npc3Button = Button::create(
            "picture/NPC3.png",
            "picture/NPC3.png"
        );

        // ����npc3��ť��λ��
        _npc3Button->setPosition(Vec2(x - 300, y - 200));
        auto moveTo3 = MoveTo::create(40.0f, Vec2(x - 80, y - 1050)); // NPC3 ���ƶ�����
        auto scaleBy3 = ScaleBy::create(5.0f, 5.0f);
        _npc3Button->runAction(moveTo3);
        this->addChild(_npc3Button);

        // ��Ӵ����¼�������
        _npc3Button->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED) {
                auto dialogImage = Sprite::create("picture/npc3_dialog.png");
                if (!dialogImage) {
                    CCLOG("Error: Failed to create dialog image for NPC3!");
                    return;
                }
                dialogImage->setPosition(Vec2(600, 400)); // ���öԻ���λ��
                this->addChild(dialogImage, 10); // ��ӵ������У�ȷ�������ϲ�
                // �������һ����ʱ�������¼����رնԻ���
                auto delay = DelayTime::create(3.0f); // 3����Զ��ر�
                auto removeDialog = CallFunc::create([dialogImage]() {
                    dialogImage->removeFromParentAndCleanup(true);
                    });
                dialogImage->runAction(Sequence::create(delay, removeDialog, nullptr));
            }
            });

        this->scheduleUpdate();
        setViewPointCenter(characteraction->getPosition(), tiledMap);

        tiledMap_ = tiledMap;

        characteraction->setPosition(Vec2(x-300, y-400)); // ȷ��λ������Ļ��Χ��
        this->addChild(characteraction);


        auto keyboardListener = EventListenerKeyboard::create();
        keyboardListener->onKeyPressed = [characteraction](EventKeyboard::KeyCode keyCode, Event* event) {
            Vec2 direction = Vec2::ZERO; // �ֲ�����
            if (keyCode == EventKeyboard::KeyCode::KEY_W)
                direction.y = 1;
            if (keyCode == EventKeyboard::KeyCode::KEY_S)
                direction.y = -1; // ����
            if (keyCode == EventKeyboard::KeyCode::KEY_A)
                direction.x = -1; // ����
            if (keyCode == EventKeyboard::KeyCode::KEY_D)
                direction.x = 1; // ����
            characteraction->move(direction); // ���������봫�ݸ���ɫ
            };
        keyboardListener->onKeyReleased = [characteraction](EventKeyboard::KeyCode keyCode, Event* event) {
            Vec2 direction = Vec2::ZERO; // �ֲ�����
            if (keyCode == EventKeyboard::KeyCode::KEY_W)
                direction.y = 0;
            if (keyCode == EventKeyboard::KeyCode::KEY_S)
                direction.y = 0;
            if (keyCode == EventKeyboard::KeyCode::KEY_A)
                direction.x = 0;
            if (keyCode == EventKeyboard::KeyCode::KEY_D)
                direction.x = 0;
            characteraction->move(direction); // ���������봫�ݸ���ɫ
            };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
        // ����Ŀ������
      
        targetArea = Rect(200,100,200, 200);
      
        auto listener2 = EventListenerTouchOneByOne::create();
        listener2->onTouchBegan = [&](Touch* touch, Event* unused_event)->bool {
            Vec2 touchLocation = touch->getLocation();
            if (targetArea.containsPoint(touchLocation)) {
                if (_lastSprite && _lastSprite->getPosition() != touchLocation) {
                    this->removeChild(_lastSprite);
                    _lastSprite = nullptr;
                }

                // �����ǰ���λ��û��Sprite���򴴽�һ���µ�Sprite
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

    // ��ʼ����Ա����
    _personalInterfaceLayer = nullptr;
    _menuWindow = nullptr;
    _closeButton = nullptr;
    _isPersonalInterfaceVisible = false;
    _currentImageIndex = 1;
    _selectedButtonIndex = -1;

    // ��Ӽ����¼�������
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


    // ��ȡ���ڼ�
    const char* days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    std::stringstream ss;
    ss << days[timeinfo->tm_wday] << ", ";
    std::string dayOfWeek = ss.str();

    // ��ȡ��ǰʱ�䣨�������룩
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%H:%M", timeinfo);
    std::string currentTime = buffer;

    // ���������Label��������
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto dayLabel = Label::createWithTTF(dayOfWeek, "fonts/Marker Felt.ttf", 50);
    dayLabel->setPosition(Vec2(1400, 1553));
    
   
    this->addChild(dayLabel, 1);

    auto timeLabel = Label::createWithTTF(currentTime, "fonts/Marker Felt.ttf", 40);
    timeLabel->setPosition(Vec2(1400, 1405));
    this->addChild(timeLabel, 1);

    // ������Ϸ��ʱ��
    schedule(schedule_selector(outside::updateTime), 1.0f);

   
    // ����ǩ������
    auto qiandaoWindow = Sprite::create("picture/qiandao.png");
    qiandaoWindow->setPosition(Vec2(visibleSize.width / 8 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(qiandaoWindow, 10); // ���ýϸߵ�z�ᣬȷ�����������ϲ�

    // ����ǩ����ť
    auto qiandaoButton = Button::create("picture/bottom.png", "picture/bottom1.png");
    qiandaoButton->setPosition(Vec2(qiandaoWindow->getContentSize().width / 2, qiandaoWindow->getContentSize().height / 4));
    qiandaoButton->addTouchEventListener([qiandaoButton](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // �л���ťͼƬ
            if (qiandaoButton->getRendererNormal()->getTexture() == Director::getInstance()->getTextureCache()->addImage("picture/bottom.png")) {
                qiandaoButton->loadTextureNormal("picture/bottom1.png");
            }
            else {
                qiandaoButton->loadTextureNormal("picture/bottom.png");
            }
        }
        });
    qiandaoWindow->addChild(qiandaoButton);

    // �����رհ�ť
    auto closeButton = Button::create("picture/bottom2.png");
    closeButton->setPosition(Vec2(qiandaoWindow->getContentSize().width - closeButton->getContentSize().width / 2, qiandaoWindow->getContentSize().height - closeButton->getContentSize().height / 2));
    closeButton->addTouchEventListener([qiandaoWindow](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // �ر�ǩ������
            qiandaoWindow->removeFromParentAndCleanup(true);
        }
        });
    qiandaoWindow->addChild(closeButton);
  

    //����
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
                    CCLOG("spriteFish δ�ܳɹ�����!");
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
                Fishing->setDelayPerUnit(0.3f); // ����ÿ֡�Ĳ���ʱ��
                Fishing->setLoops(1); // ����ѭ������
                Animate* FishingAnimate = Animate::create(Fishing);
                Fishing->retain(); // �����������󣬷�ֹ���ͷ�

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

    // �������Ϸ��ʼ�����ڵ���ʵʱ�����ţ�����Ϊ��λ��
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(currentTime - gameStartTime).count();

    // ����ʵʱ��ת��Ϊ��Ϸ��ʱ�䣨ÿ0.7�������Ϸ�ڵ�һ���ӣ�
    int elapsedTime = static_cast<int>(duration / 0.7f);
    time_t rawtime;
    time(&rawtime);
    struct tm* timeinfo = localtime(&rawtime);

    // ���·�����
    timeinfo->tm_min += elapsedTime / 60;
    mktime(timeinfo); // ����ʱ��ṹ��

    // ����Label
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%H:%M", timeinfo); 

    // ��ȡLabel�������ַ���
    auto label = dynamic_cast<Label*>(getChildByName("timeLabel"));
    if (label) {
        label->setString(buffer);
    }
    else {
        // ���ת��ʧ�ܻ���û���ҵ���Ӧ��Label�����ӡ������Ϣ���߽�������������
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

    // ���ݴ���λ�ü����µ����λ��
    if (abs(diff.x) > abs(diff.y)) {
        playerPos.x += (diff.x > 0) ? tileSize.width : -tileSize.width;
    }
    else {
        playerPos.y += (diff.y > 0) ? tileSize.height : -tileSize.height;
    }

    // �߽���
    playerPos.x = MIN(MAX(playerPos.x, tileSize.width / 2), (mapSize.width * tileSize.width) - tileSize.width / 2);
    playerPos.y = MIN(MAX(playerPos.y, tileSize.height / 2), (mapSize.height * tileSize.height) - tileSize.height / 2);

    // �������λ��
    this->setPlayerPosition(playerPos, tiledMap);

    // �����ӿ�λ��
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

    // ���崥�������л���λ��
    Vec2 triggerPosition = Vec2(900, 1300); // �����Ը�����Ҫ�������λ��

    // �������Ƿ񵽴��˴���λ��
    if (playerPosition.x == triggerPosition.x && playerPosition.y == triggerPosition.y) {
        // ���������л�
        changeScene();
    }
}

void outside::changeScene() {
    // �������л���Scene2
    auto scene = intovalley::createintovalleyScene(); 
    Director::getInstance()->replaceScene(scene);
}


void outside::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    // ��鰴�µļ��Ƿ�Ϊ E ��
    if (keyCode == EventKeyboard::KeyCode::KEY_E)
    {
        // ������˽��治�ɼ�����ʾ���˽���
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

    // �������˽����
    _personalInterfaceLayer = Layer::create();
    this->addChild(_personalInterfaceLayer, 10); // ȷ���������������֮��

    // ���س�ʼͼƬ����
    _menuWindow = Sprite::create("picture/1.png");

    // ���ô���λ��Ϊ��Ļ����
    _menuWindow->setPosition(Vec2(400,500));

    // ���ô��ڴ�СΪ��Ļ�� 80%
    _menuWindow->setScale(1.0f);

    _personalInterfaceLayer->addChild(_menuWindow);

    // �����رհ�ť
    _closeButton = MenuItemImage::create(
        "picture/bottom2.png",
        "picture/bottom2.png",
        CC_CALLBACK_1(outside::closePersonalInterface, this) // ʹ�� CC_CALLBACK_1 �� this
    );

    // ���ùرհ�ť��λ��
    auto windowSize = _menuWindow->getContentSize();
    _closeButton->setPosition(Vec2(windowSize.width - _closeButton->getContentSize().width / 2 + 60, windowSize.height - _closeButton->getContentSize().height / 2 + 60)); // �ڴ������ʵ�λ��

    // �����˵�����ӹرհ�ť
    auto closeMenu = Menu::create(_closeButton, NULL);
    closeMenu->setPosition(Vec2::ZERO);
    _menuWindow->addChild(closeMenu);

    // ����������ѡ��ť
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

        // ���ð�ť�ĳ�ʼλ��
        button->setPosition(Vec2(-visibleSize.width / 2 + 80 * i, visibleSize.height / 2.55 - 80));
        buttonMenu->addChild(button, 0, i);
    }

    buttonMenu->setPosition(visibleSize / 2);
    _personalInterfaceLayer->addChild(buttonMenu, 1);
}



void outside::selectImage(int index)
{
    _currentImageIndex = index;

    // ������ͼƬ
    std::string imageName = StringUtils::format("picture/%d.png", _currentImageIndex);

    // �����ǰѡ���ͼƬ�� 3.png������ʾ���Ű�ť
    if (_currentImageIndex == 3)
    {
        showVerticalButtons();
    }
    else
    {
        // �����ǰѡ���ͼƬ���� 3.png�����Ƴ����Ű�ť
        removeVerticalButtons();
    }

    if (_menuWindow)
    {
        _menuWindow->setTexture(imageName);
    }

    // ��ȡ�˵���ť
    auto buttonMenu = dynamic_cast<Menu*>(_personalInterfaceLayer->getChildByTag(1));
    if (!buttonMenu) return;

    // �������а�ť�����°�ť��λ��Ч��
    for (int i = 1; i <= 7; ++i)
    {
        auto button = dynamic_cast<MenuItemImage*>(buttonMenu->getChildByTag(i));
        if (button)
        {
            if (i == index)
            {
                button->setPositionY(button->getPositionY() - 10); // ����Ч��
            }
            else
            {
                button->setPositionY(button->getPositionY() + 10); // �ָ���ʼλ��
            }
        }
    }
}


void outside::showVerticalButtons()
{
    // ��ȡ��ǰ���ڵĴ�С
    auto windowSize = _menuWindow->getContentSize();

    // ����һ���������ð�ť
    auto buttonLayer = Layer::create();
    _menuWindow->addChild(buttonLayer);

    // �� 3.png ͼƬ�����ŷ��� 5 ����ť bottom3.1.png
    for (int i = 1; i <= 5; ++i)
    {
        auto button = Button::create("picture/giftbottom1.png", "picture/giftbottom1.png");
        button->setPosition(Vec2(windowSize.width / 2 + 300, windowSize.height + 90 - 125 * i)); // ��ֱ����
        button->addTouchEventListener([this](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED) {
                showNewWindow(); // �����ť�������µĴ���
            }
            });
        buttonLayer->addChild(button);
    }
}

void outside::removeVerticalButtons()
{
    // �Ƴ��������Ű�ť
    _menuWindow->removeAllChildrenWithCleanup(true);
}

void outside::showNewWindow()
{
    // �����µĴ���
    auto newWindow = Sprite::create("picture/back.png");
    newWindow->setPosition(Vec2(400, 500));
    newWindow->setScale(1.0f);

    // ��ӵ����˽����
    _personalInterfaceLayer->addChild(newWindow, 11); // ȷ���´��������ϲ�

    // �����ر��´��ڵİ�ť
    auto closeNewWindowButton = Button::create("picture/ok1.png", "picture/ok1.png");
    float scaleFactor = 1.5f; // ������Ҫ�������ű���
    closeNewWindowButton->setScale(scaleFactor);
    closeNewWindowButton->setPosition(Vec2(newWindow->getContentSize().width - closeNewWindowButton->getContentSize().width / 2 - 100, newWindow->getContentSize().height - closeNewWindowButton->getContentSize().height / 2 - 800));
    closeNewWindowButton->addTouchEventListener([newWindow](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            newWindow->removeFromParent(); // �ر��´���
        }
        });
    newWindow->addChild(closeNewWindowButton);

    // ����6����ť����������
    std::vector<Button*> giftButtons;
    for (int i = 1; i <= 6; ++i) {
        auto giftButton = Button::create("picture/gift" + std::to_string(i) + ".png", "picture/gift" + std::to_string(i) + ".png");
        // �������ű�����������С
        float scaleFactor = 3.0f; // ������Ҫ�������ű���
        giftButton->setScale(scaleFactor);
        giftButton->setPosition(Vec2(100 + (i - 1) * 150, 800)); // �������У�ÿ����ť���150����
        giftButton->addTouchEventListener([newWindow, &giftButtons](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED) {
                auto button = static_cast<Button*>(sender);
                // ����ť����¼�
            }
            });
        newWindow->addChild(giftButton);
        giftButtons.push_back(giftButton);

        // ��ÿ����ť�������һ�� bottom.png ��ť
        auto bottomButton = Button::create("picture/bottom.png", "picture/bottom1.png");
        bottomButton->setPosition(Vec2(giftButton->getPositionX(), giftButton->getPositionY() - 100)); // �ڰ�ť�·�100���ش�
        bottomButton->addTouchEventListener([bottomButton](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED) {
                // �л���ť״̬
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

    // �Ƴ����˽����
    _personalInterfaceLayer->removeFromParent();
    _personalInterfaceLayer = nullptr;
}






