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
        tiledMap->setScale(3);
        this->addChild(tiledMap, 0);

        auto imageView = ImageView::create("picture/time.png");
        if (imageView) {
            // ����λ��
            imageView->setPosition(Vec2(3 * 1500 - 100, 3 * 1100 + 1450 - 100));
            // ��ӵ�����
            this->addChild(imageView);
        }
       
    
        _meta = tiledMap->getLayer("meta");
        _meta->setVisible(false);

        TMXObjectGroup* objects = tiledMap->getObjectGroup("objects");
        CCASSERT(NULL != objects, "'objects' object group not found");
        auto spawnPoint = objects->getObject("lake");
        int x = spawnPoint["x"].asInt();
        int y = spawnPoint["y"].asInt();

        //��������
        //����
        for (int i = 0; i < 5; i++) {
            auto sheep = Sheep::create("animal/Sheep1.png");
            if (sheep == nullptr) {
                CCLOG("Error: Failed to create sheep!");
                return;
            }
            this->addChild(sheep);
        }

        //ţ
        auto cow=Cow::create("animal/Cow1.png");
        if (cow == nullptr) {
            CCLOG("Error: Failed to create cow!");
            return;
        }
        cow->setScale(3);
        this->addChild(cow);

        //����
        auto parrot=Parrot::create("animal/Parrot1.png");
        if (parrot == nullptr) {
            CCLOG("Error: Failed to create parrot!");
            return;
        }
        parrot->setScale(3);
        this->addChild(parrot);

        //������������
        characteraction = CharacterWithTools::create("character/Dana0.png");
        if (characteraction == nullptr) {
            CCLOG("Error: Failed to create character!");
            return;
        }

        characteraction->setPosition(Vec2(3 * x + 600, 3 * y + 2000));
        this->addChild(characteraction);

        this->scheduleUpdate();
        // ��ÿ֡�и����ӵ�λ�ã�ʹ��ͼʼ�ո�������
            this->schedule([=](float deltaTime) {
            // ��ȡ���ﵱǰ����������
            Vec2 characterPosition = characteraction->getPosition();



            // �����ӵ㣬ȷ����ͼʼ�ո�������
            setViewPointCenter(characterPosition, tiledMap);


            if (characterPosition.x >= 3460 &&
                characterPosition.x <= 3500 &&
                characterPosition.y >= 3570 &&
                characterPosition.y <= 3610)
            {
                // ���л�����֮ǰ����״̬
                SceneStateManager::getInstance()->saveSceneState(
                    characteraction->getPosition(),
                    tiledMap->getName()
                );
                
                // ����������ָ����Χ�����л�����
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
                // ����������ָ����Χ�����л�����
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

    // ��ʼ����Ա����
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
    _rainParticleSystem->resetSystem(); // ��ʼ��������
    _rainParticleSystem->setStartSize(10.0f); // �����������ڵĿ�ʼ��С
    _rainParticleSystem->setEndSize(20.0f);   // �����������ڵĽ�����С

    // �������ӵĿ�ʼ��ɫΪ������ɫ����ȫ��͸����
    _rainParticleSystem->setStartColor(Color4F(0.0f, 0.5f, 1.0f, 1.0f));

    // �������ӵĽ�����ɫΪ������ɫ����͸����
    _rainParticleSystem->setEndColor(Color4F(0.0f, 0.3f, 0.6f, 0.5f));


    _rainParticleSystem->setStartSize(15.0f);
    _rainParticleSystem->setEndSize(15.0f);

    this->scheduleOnce([&](float dt) {
        _rainParticleSystem->stopSystem(); // ֹͣ����ϵͳ
        }, 40.0f, "stopRainTimer");

    // ��Ӽ����¼�������
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(outside::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);


    // ���� NPC1 
    auto npcButton = Button::create("bag/npc1.png", "bag/npc2.png"); // ���ǰΪ npc1.png�������Ϊ npc2.png
    npcButton->setPosition(Vec2(800, 700));
    float scaleFactor = 4.0f; // ������Ҫ�������ű���
    npcButton->setScale(scaleFactor);
    this->addChild(npcButton, 5);

    // ��Ӱ�ť����¼�������
    npcButton->addTouchEventListener([this, npcButton](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // ��ȡ NPC ��ť�ͽ�ɫ�ĺ�����
            Vec2 npcPosition = npcButton->getPosition();
            Vec2 characterPosition = characteraction->getPosition();
            float distance = characterPosition.x - npcPosition.x; // ����������ֵ

            // ����������ֵС�� 100����ִ���߼�
            if (distance < 100) {
                // �л��� npc2.png
                npcButton->loadTextureNormal("bag/npc2.png");

                // �����Ի���
                auto dialogBox = Sprite::create("picture/dialog.png"); // �滻Ϊ��ĶԻ���ͼƬ·��
                dialogBox->setPosition(Vec2(900, 400)); // ���öԻ���λ��
                dialogBox->setScale(0.6f);
                this->addChild(dialogBox, 6); // ȷ���Ի����� NPC ��ť�Ϸ�

                // 3 ����Ƴ��Ի��򲢻ָ�
                auto delay = DelayTime::create(3.0f);
                auto restoreNPC = CallFunc::create([npcButton]() {
                    npcButton->loadTextureNormal("bag/npc1.png"); // �ָ�Ϊ npc1.png
                    });
                auto removeDialog = CallFunc::create([dialogBox]() {
                    dialogBox->removeFromParent();
                    });
                auto sequence = Sequence::create(delay, restoreNPC, removeDialog, nullptr);
                dialogBox->runAction(sequence);
            }
        }
        });

    // ���� NPC2 
    auto npcButton1 = Button::create("bag/npc3.png", "bag/npc4.png"); // ���ǰΪ npc1.png�������Ϊ npc2.png
    npcButton1->setPosition(Vec2(4100, 650));
    npcButton1->setScale(0.8f);
    this->addChild(npcButton1, 5);

    // ��Ӱ�ť����¼�������
    npcButton1->addTouchEventListener([this, npcButton1](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // ��ȡ NPC ��ť�ͽ�ɫ�ĺ�����
            Vec2 npcPosition1 = npcButton1->getPosition();
            Vec2 characterPosition = characteraction->getPosition();
            float distance = npcPosition1.x - characterPosition.x; // ����������ֵ

            // ����������ֵС�� 100����ִ���߼�
            if (distance < 100) {
                npcButton1->loadTextureNormal("bag/npc4.png");

                // �����Ի���
                auto dialogBox = Sprite::create("picture/dialog2.png"); // �滻Ϊ��ĶԻ���ͼƬ·��
                dialogBox->setPosition(Vec2(4100, 400)); // ���öԻ���λ��
                dialogBox->setScale(0.6f);
                this->addChild(dialogBox, 6); // ȷ���Ի����� NPC ��ť�Ϸ�

                // 3 ����Ƴ��Ի��򲢻ָ�
                auto delay = DelayTime::create(3.0f);
                auto restoreNPC = CallFunc::create([npcButton1]() {
                    npcButton1->loadTextureNormal("bag/npc3.png"); // �ָ�
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


    // ��ȡ���ڼ�
    const char* days[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
    std::stringstream ss;
    ss << days[timeinfo->tm_wday] << ", ";
    std::string dayOfWeek = ss.str();

    // ��ȡ��ǰʱ�䣨�������룩
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

    // ������Ϸ��ʱ��
    schedule(schedule_selector(outside::updateTime), 1.0f);

   
    // ����ǩ������
    auto qiandaoWindow = Sprite::create("picture/qiandao.png");

    qiandaoWindow->setPosition(3 * 890 + 600, 3 * 740 + 1300);
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
                    CCLOG("spriteFish δ�ܳɹ�����!");
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
    
  
    this->scheduleUpdate();
    
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

void outside::setViewPointCenter(Point position, cocos2d::TMXTiledMap* tiledMap) {
    const auto winSize = Director::getInstance()->getWinSize();
    float scale = tiledMap->getScale(); // ��ȡ��ǰ�����ű���

    // ����ʵ�ʵ���ͼ�������꣨�������ţ�
    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);

    // �������ź�ĵ�ͼ�ߴ�
    float mapWidth = tiledMap->getMapSize().width * tiledMap->getTileSize().width * scale;
    float mapHeight = tiledMap->getMapSize().height * tiledMap->getTileSize().height * scale;

    // ȷ���ӵ㲻�ᳬ����ͼ�ķ�Χ
    x = MIN(x, mapWidth - winSize.width / 2);
    y = MIN(y, mapHeight - winSize.height / 2);

    // �����ӵ�ʵ��λ��
    auto actualPosition = Point(x, y);

    // ��Ļ���ĵ�
    auto centerOfView = Point(winSize.width / 2, winSize.height / 2);

    // �����µ��ӵ�λ��
    auto viewPoint = centerOfView - actualPosition;

    // ������ͼλ��
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

    // ���崥�������л���λ��
    Vec2 triggerPosition = Vec2(900, 1300); 

    // �������Ƿ񵽴��˴���λ��
    if (playerPosition.x == triggerPosition.x && playerPosition.y == triggerPosition.y) {
        // ���������л�
        changeScene();
    }

    Vec2 characterPosition = characteraction->getPosition();

    // �����ӵ㣬ȷ������ʼ��λ����Ļ����
    setViewPointCenter(characterPosition, tiledMap);
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
        // �л����˽������ʾ״̬
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
    // ���ظ��˽�����߼�
    if (_personalInterfaceLayer)
    {
        this->removeChild(_personalInterfaceLayer); // �Ƴ����˽����
        _personalInterfaceLayer = nullptr; // ��ղ�ָ��
    }
    _isPersonalInterfaceVisible = false;
}


void outside::showPersonalInterface()
{
    if (_isPersonalInterfaceVisible) return;

    _isPersonalInterfaceVisible = true;

    // �������˽����
    _personalInterfaceLayer = Layer::create();
    this->addChild(_personalInterfaceLayer, 10); // ȷ���������������֮��

    // ���س�ʼͼƬ����
    _menuWindow = Sprite::create("bag/1.png");

    Vec2 characterPosition = characteraction->getPosition();

    // ���˵�����Ϊ��Ļ����
    _menuWindow->setPosition(characterPosition);

    // ���ô��ڴ�С
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

    // ������ͼƬ
    std::string imageName = StringUtils::format("bag/%d.png", _currentImageIndex);

    // �����ǰѡ���ͼƬ�� 3.png������ʾ���Ű�ť
    if (index == 1) // ������ѡ�� 1.png ʱ��ӿ��϶���ͼƬ
    {
        // ��ȡ��ǰ���ڵĴ�С
        auto windowSize = _menuWindow->getContentSize();

        // ��ȡ _menuWindow ��λ��
        Vec2 menuWindowPosition = _menuWindow->getPosition();

        auto draggableSprite = Sprite::create("bag/tool1.png");

        float scaleFactor = 4.0f; // ������Ҫ�������ű���
        draggableSprite->setScale(scaleFactor);

        // ���þ����λ��Ϊ _menuWindow ������λ��
        draggableSprite->setPosition(Vec2(windowSize.width - 200, windowSize.height - 300));

        _menuWindow->addChild(draggableSprite, 10);


        // �������Ͱ
        auto trashCanSprite = Sprite::create("bag/trashcan.png");
        trashCanSprite->setPosition(Vec2(windowSize.width + 50, windowSize.height - 500)); // ��������Ͱλ��
        _menuWindow->addChild(trashCanSprite);

        // �����϶��¼�
        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);

        // ��ʼ�϶�
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

        // �϶���
        listener->onTouchMoved = [=](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            target->setPosition(target->getPosition() + touch->getDelta());
            };

        // �϶�����
        listener->onTouchEnded = [=](Touch* touch, Event* event) {
            auto target = static_cast<Sprite*>(event->getCurrentTarget());
            Vec2 endPosition = target->getPosition();

            // ����Ƿ��϶�������Ͱλ��
            Rect trashCanRect = trashCanSprite->getBoundingBox();
            if (trashCanRect.containsPoint(endPosition))
            {
                // �Ƴ����϶���ͼƬ
                target->removeFromParentAndCleanup(true);
            }
            };

        // ע���¼�������
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, draggableSprite);

        // ��ʾ money ����
        int money = 500; // ��ʼֵΪ 500
        auto moneyLabel = Label::createWithSystemFont(StringUtils::format("%d", money), "Arial", 30);
        moneyLabel->setColor(Color3B::BLACK); // ����������ɫΪ��ɫ
        moneyLabel->setPosition(Vec2(windowSize.width / 2 + 200, windowSize.height / 2 - 110)); // ����λ��Ϊ��������
        _menuWindow->addChild(moneyLabel, 20); // ��ӵ� _menuWindow���㼶��������Ԫ��


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
    buttonLayer->setName("buttonLayer"); // ���ò�����ƣ�ȷ�����Ա���ȷ��׽
    _menuWindow->addChild(buttonLayer);

    // �� 3.png ͼƬ�����ŷ��� 5 ����ť bottom3.1.png
    for (int i = 1; i <= 5; ++i)
    {
        auto button = Button::create("picture/giftbottom1.png", "picture/giftbottom1.png");
        button->setPosition(Vec2(windowSize.width / 2 + 300, windowSize.height + 90 - 125 * i)); // ��ֱ����
        button->setTag(i); // Ϊ��ť����Ψһ�� Tag
        button->addTouchEventListener([this, i](Ref* sender, Widget::TouchEventType type) {
            if (type == Widget::TouchEventType::ENDED) {
                _clickedButtonIndex = i; // ��¼����İ�ťλ��
                showNewWindow(); // �����ť�������µĴ���
            }
            });
        buttonLayer->addChild(button);
    }
}


void outside::showVerticalButtons2()
{
    // ��ȡ��ǰ���ڵĴ�С
    auto windowSize = _menuWindow->getContentSize();

    // ����һ���������ð�ť
    auto buttonLayer = Layer::create();
    buttonLayer->setName("buttonLayer"); // ���ò�����ƣ�ȷ�����Ա���ȷ��׽
    _menuWindow->addChild(buttonLayer);

    // �� 6.png ͼƬ�����ŷ��� 4 ����ť bottom3.1.png
    for (int i = 1; i <= 4; ++i)
    {
        auto button = Button::create("picture/bottom.png", "picture/bottom2.png");
        button->setPosition(Vec2(windowSize.width / 6 - 90, windowSize.height - 70 - 90 * i)); // ��ֱ����
        button->setTag(i);

        // ��Ӵ����¼�������
        button->addTouchEventListener([this, button](Ref* sender, Widget::TouchEventType type) {
            // �жϴ����¼�����
            if (type == Widget::TouchEventType::ENDED) {
                // �л���ť״̬
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
    // �Ƴ��������Ű�ť
    _menuWindow->removeAllChildrenWithCleanup(true);
}

void outside::showNewWindow()
{
    // �����µĴ���
    auto newWindow = Sprite::create("picture/back.png");

    Vec2 characterPosition = characteraction->getPosition();

    // ���˵�����Ϊ��Ļ����
    newWindow->setPosition(characterPosition);
    newWindow->setScale(1.0f);

    // ��ӵ����˽����
    _personalInterfaceLayer->addChild(newWindow, 11); // ȷ���´��������ϲ�

    // �����ر��´��ڵİ�ť
    auto closeNewWindowButton = Button::create("picture/ok1.png", "picture/ok1.png");
    float scaleFactor = 1.5f; // ������Ҫ�������ű���
    closeNewWindowButton->setScale(scaleFactor);
    closeNewWindowButton->setPosition(Vec2(newWindow->getContentSize().width - closeNewWindowButton->getContentSize().width / 2 - 100, newWindow->getContentSize().height - closeNewWindowButton->getContentSize().height / 2 - 800));
    closeNewWindowButton->addTouchEventListener([newWindow, this](Ref* sender, Widget::TouchEventType type) {
        if (type == Widget::TouchEventType::ENDED) {
            // �ر��´���
            newWindow->removeFromParent();

            // ��ȡ��ť��
            auto buttonLayer = dynamic_cast<Layer*>(_menuWindow->getChildByName("buttonLayer"));
            if (buttonLayer) {
                auto giftButton = dynamic_cast<Button*>(buttonLayer->getChildByTag(_clickedButtonIndex));
                if (giftButton) {
                    // ��ȡ��ǰ��ť�ĵ������
                    int clickCount = _buttonClickCounts[_clickedButtonIndex]++;
                    // ���ݵ�����������Ƿ���ӶԺŰ�ť
                    if (clickCount < 2) {
                        auto bottomButton = Button::create("picture/bottom1.png", "picture/bottom1.png");
                        float scaleFactor = 0.8f; // ������Ҫ�������ű���
                        bottomButton->setScale(scaleFactor);

                        // ���ݵ�����������ԺŰ�ť��λ��
                        float offsetX = clickCount * 48; // ÿ�ε������ƫ�� 30 ����
                        bottomButton->setPosition(Vec2(giftButton->getPositionX() - 30 + offsetX, giftButton->getPositionY() - 57));

                        buttonLayer->addChild(bottomButton);
                    }
                    if (clickCount == 2) {

                        auto popupImage = Sprite::create("bag/back.png"); // �滻Ϊ��ĵ���ͼƬ·�� 
                        popupImage->setPosition(Vec2(giftButton->getPositionX() - 30, giftButton->getPositionY() - 57));
                        popupImage->setScale(0.5f);
                        buttonLayer->addChild(popupImage);

                        // 5����Ƴ�����ͼƬ
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

    // ����6����ť����������
    std::vector<Button*> giftButtons;
    for (int i = 1; i <= 6; ++i) {
        auto giftButton = Button::create("picture/gift" + std::to_string(i) + ".png", "picture/gift" + std::to_string(i) + ".png");
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