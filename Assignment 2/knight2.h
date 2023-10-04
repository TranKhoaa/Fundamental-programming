#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
class BaseKnight;
class BaseItem;
class Events;
enum ItemType {Antidote, PhoenixDownI, PhoenixDownII, PhoenixDownIII, PhoenixDownIV};

class BaseBag {
protected:
    class Node{
        public:
            BaseItem * data;
            Node * next;
    };
    BaseKnight * knight;
    int nItems = 0;
    int capacity = 0;
    Node * head;
public: 
    BaseBag(BaseKnight * knight);
    int getnItems(){
        return nItems;
    }
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    virtual void remove();
    ~BaseBag();
};
class BagLancelotKnight : public BaseBag{
    public:
    BagLancelotKnight(BaseKnight * knight);
};
class BagDragonKnight : public BaseBag{
    public:
    BagDragonKnight(BaseKnight * knight);
    bool insertFirst(BaseItem * item);
};
class BagPaladinKnight : public BaseBag{
    public:
    BagPaladinKnight(BaseKnight * knight);
};
class BagNormalKnight : public BaseBag{
    public:
    BagNormalKnight(BaseKnight * knight);
};
enum OpponentType{MadBear = 1, Bandit, LordLupin, Elf, Troll, Tornbery, QueenOfCard, NinaDerings, DurianGarden, OmegaWeapons, Hades};
class BaseOpponent
{
    protected:
        BaseKnight * knight;
        int lvlO;
        int baseDmg;
        int gil;
        OpponentType Opponent;
    public:
        BaseOpponent(BaseKnight * knight);
        int getlvlO();
        int getbaseDmg();
        int getOpponent();
};
class MadBearOpponent : public BaseOpponent{
    public:
        MadBearOpponent(int event_nums):BaseOpponent(knight){
            baseDmg = 10;
            lvlO = (event_nums + 1)%10 + 1;
            gil = 100;
            Opponent = MadBear;
        };
};
class BanditOpponent : public BaseOpponent{
    public:
        BanditOpponent(int event_nums):BaseOpponent(knight){
            baseDmg = 15;
            lvlO = (event_nums + 2)%10 + 1;
            gil = 150;
            Opponent = Bandit;
        };
};
class LordLupinOpponent : public BaseOpponent{
    public:
        LordLupinOpponent(int event_nums):BaseOpponent(knight){
            baseDmg = 45;
            lvlO = (event_nums + 3)%10 + 1;
            gil = 450;
            Opponent = LordLupin;
        };
};
class ElfOpponent : public BaseOpponent{
    public:
        ElfOpponent(int event_nums):BaseOpponent(knight){
            baseDmg = 75;
            lvlO = (event_nums + 4)%10 + 1;
            gil = 750;
            Opponent = Elf;
        };
};
class TrollOpponent : public BaseOpponent{
    public:
        TrollOpponent(int event_nums):BaseOpponent(knight){
            baseDmg = 95;
            lvlO = (event_nums + 5)%10 + 1;
            gil = 800;
            Opponent = Troll;
        };
};
class TornberyOpponent : public BaseOpponent{
    public:
        TornberyOpponent(int event_nums):BaseOpponent(knight){
            lvlO = (event_nums + 6)%10 + 1;
            Opponent = Tornbery;
        }
};
class QueenOfCardOpponent : public BaseOpponent{
    public:
        QueenOfCardOpponent(int event_nums):BaseOpponent(knight){
            lvlO = (event_nums + 7)%10 + 1;
            Opponent = QueenOfCard;
        }
};
class NinaDeringsOpponent : public BaseOpponent{
    public:
        NinaDeringsOpponent():BaseOpponent(knight){
            Opponent = NinaDerings;
        }
};
class DurianGardenOpponent : public BaseOpponent{
    public:
        DurianGardenOpponent():BaseOpponent(knight){
            Opponent = DurianGarden;
        }
};
class OmegaWeaponsOpponent : public BaseOpponent{
    public:
        OmegaWeaponsOpponent():BaseOpponent(knight){
            Opponent = OmegaWeapons;
        }
};
class HadesOpponent : public BaseOpponent{
    public:
        HadesOpponent():BaseOpponent(knight){
            Opponent = Hades;
        }
};
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;
    bool isPoisoned;

public:
    int getHp();
    void setHp(int hp);
    int getMaxHp();
    int getLevel();
    void setLevel(int level);
    int getGil();
    void setGil(int gil);
    bool getPosioned();
    void setPosioned(bool isPosioned);
    bool setBag(BaseItem * item);
    KnightType getKnighttype();

    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    virtual int knightDamage() = 0;
    ~BaseKnight();
};
class LancelotKnight : public BaseKnight{
    public:
        LancelotKnight();
        int knightDamage();
};
class PaladinKnight : public BaseKnight{
    public:
        PaladinKnight();
        int knightDamage();
};
class DragonKnight : public BaseKnight{
    public:
        DragonKnight();
        int knightDamage();
};
class NormalKnight : public BaseKnight{
    public:
        NormalKnight();
        int knightDamage();
};

class ArmyKnights {
protected:
    BaseKnight** arKnights;
    int nKnights;
    bool isPaladinShield = false;
    bool isLancelotSpear = false;
    bool isGuinevereHair = false;
    bool isExcaliburSword = false;
    bool winOmegaWeapon = false;
    bool winHades = false;
public:
    ArmyKnights(const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    virtual ItemType Type() = 0;
};
class AntidoteItem : public BaseItem{
    bool canUse(BaseKnight * knight);
    void use (BaseKnight * knight);
    ItemType Type();
};
class PhoenixDown1Item : public BaseItem{
    bool canUse(BaseKnight * knight);
    void use (BaseKnight * knight);
    ItemType Type();
};
class PhoenixDown2Item : public BaseItem{
    bool canUse(BaseKnight * knight);
    void use (BaseKnight * knight);
    ItemType Type();
};
class PhoenixDown3Item : public BaseItem{
    bool canUse(BaseKnight * knight);
    void use (BaseKnight * knight);
    ItemType Type();
};
class PhoenixDown4Item : public BaseItem{
    bool canUse(BaseKnight * knight);
    void use (BaseKnight * knight);
    ItemType Type();
};
class Events {
private:
    int nEvents;
    int *events;
public:
    Events(const string & file_events);
    int count() const;
    int get(int i) const;
    ~Events();
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__