#ifndef NPC_H
#define NPC_H
#include <vector>
#include <string>
#include "cocos2d.h"

class NPC : public cocos2d::Sprite {
public:
    enum NPCType {
        NPC1,
        NPC2,
        NPC3
    };

    NPC();
    ~NPC();

    bool init(const std::string& spriteFile, const NPCType& _npctype);
    static NPC* create(const std::string& spriteFile, const NPCType& _npctype);

    std::string getDialog() const;
    void advanceDialog();
    void jumpToDialog(int index);

private:
    NPCType npctype;
    std::vector<std::string> dialog;
    int dialogIndex;

    // ����Ի�����
    const std::vector<std::string> NPC1_DIALOG = {
        "����������治��"
    };

    const std::vector<std::string> NPC2_DIALOG = {
        "����Ҫʲô������"
    };

    const std::vector<std::string> NPC3_DIALOG = {
        "�ܸ��˼����㣡"
    };
};

#endif // NPC_H
