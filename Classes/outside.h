#ifndef _OUTSIDE_H_
#define _OUTSIDE_H_
#include"cocostudio/CocoStudio.h"
#include"ui/CocosGUI.h"
#include "cocos2d.h"

class outside : public cocos2d::Layer
{
public:
    //static cocos2d::Scene* createoutsideScene();
    virtual bool init();
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event, cocos2d::TMXTiledMap* tiledMap);
 
    void setViewPointCenter(cocos2d::Point position, cocos2d::TMXTiledMap* tiledMap);
    void setPlayerPosition(cocos2d::Point position, cocos2d::TMXTiledMap* tiledMap);
    cocos2d::Point tileCoordForPosition(cocos2d::Point position, cocos2d::TMXTiledMap* tiledMap);

    static cocos2d::Scene* createSceneWithMapIndex(int mapIndex);
    void loadMapBackground(int mapIndex);

    void onTouchEndedWrapper(cocos2d::Touch* touch, cocos2d::Event* event) {
        onTouchEnded(touch, event, tiledMap_);
    }

    outside() {
        // ��ʼ����Ϸ��ʼʱ��
        gameStartTime = std::chrono::high_resolution_clock::now();
        gameTime = 0; // ��Ϸ��ʼʱ����Ϸ��ʱ��Ϊ0
    }


    void updateTime(float dt);
    void iniData(cocos2d::TMXTiledMap* map, cocos2d::Sprite* player);

    void update(float delta, cocos2d::Sprite* _player);
    void changeScene();

    // ��ʾ���Ű�ť
    void showVerticalButtons();

    // �Ƴ����Ű�ť
    void removeVerticalButtons();

    // ��ʾ�´���
    void showNewWindow();

    // ����ָ������
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // չʾ���˽���
    void showPersonalInterface();

    // �رո��˽���
    void closePersonalInterface(Ref* sender);

    // ѡ��ͼ��
    void selectImage(int index);

    // �л�ͼ��
    void switchImage(int direction);


    CREATE_FUNC(outside);
private:
    //cocos2d::TMXTiledMap* _tiledmap;
    cocos2d::TMXLayer* _background;
    cocos2d::Sprite* _player;
    cocos2d::TMXLayer* _meta;
    cocos2d::TMXLayer* _foreground;
    cocos2d::TMXTiledMap* tiledMap_;
    cocos2d::ui::ImageView* fishImage;
    cocos2d::Sprite* fishman;
    cocos2d::Sprite* spriteFish;
    //cocos2d::TMXTiledMap* tiledMap = nullptr;
    bool _isfishingVisible;
    cocos2d::Rect targetArea;
    cocos2d::Sprite* _lastSprite = nullptr;
    cocos2d::MenuItemImage* _closeButton;   // �رհ�ť
    std::chrono::high_resolution_clock::time_point gameStartTime; // ��Ϸ��ʼʱ��
    int gameTime; // ��Ϸ�ڵ�ʱ�䣨�Է���Ϊ��λ��

    // ���ڴ洢���Ű�ť�Ĳ�
    cocos2d::Layer * _verticalButtonLayer;

    cocos2d::Layer* _personalInterfaceLayer; // ���˽����
    cocos2d::Sprite* _menuWindow;           // �˵�����
    bool _isPersonalInterfaceVisible;      // ���ٸ��˽����Ƿ�ɼ�
    int _currentImageIndex;                // ��ǰͼ������
    int _selectedButtonIndex;              // ѡ��ť����

    
};
#endif // !_HELLOWORLD_SCENE_H_