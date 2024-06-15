#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__
#include "main.h"
// #define DEBUG

class BaseKnight;
class BaseItem;
class Events;
class BaseOpponent;
class BaseBag;

enum ItemType
{
    Antidote = 0,
    PhoenixDownI,
    PhoenixDownII,
    PhoenixDownIII,
    PhoenixDownIV
};

class BaseBag
{
protected:
    class Node
    {
    public:
        BaseItem *data;
        Node *next;

    public:
        Node(BaseItem *data, Node *next);
        ~Node();
    };

protected:
    BaseKnight *knight;
    Node *head = nullptr;
    int size = 0;
    int capacity = 0;

public:
    BaseBag(BaseKnight *knight, int antidote, int phoenixDownI);
    virtual bool insertFirst(BaseItem *item);
    virtual bool useItem(ItemType itemType);
    virtual BaseItem *get(ItemType itemType);
    virtual BaseItem *checkHp();
    virtual void deleteSlot();
    virtual string toString() const;
    ~BaseBag();
};
class BagPaladinKnight : public BaseBag
{
public:
    BagPaladinKnight(BaseKnight *knight, int antidote, int phoenixDownI);
};
class BagLancelotKnight : public BaseBag
{
public:
    BagLancelotKnight(BaseKnight *knight, int antidote, int phoenixDownI);
};
class BagNormalKnight : public BaseBag
{
public:
    BagNormalKnight(BaseKnight *knight, int antidote, int phoenixDownI);
};
class BagDragonKnight : public BaseBag
{
public:
    BagDragonKnight(BaseKnight *knight, int antidote, int phoenixDownI);
};

enum OpponentType
{
    MadBear = 1,
    Bandit,
    LordLupin,
    Elf,
    Troll,
    Tornbery,
    QueenOfCards,
    NinaDeRings,
    DurianGarden,
    OmegaWeapon,
    Hades
};

class BaseOpponent
{
public:
    virtual OpponentType Type() = 0;
};
class MadBearOpponent : public BaseOpponent
{
public:
    OpponentType Type();
};
class BanditOpponent : public BaseOpponent
{
public:
    OpponentType Type();
};
class LordLupinOpponent : public BaseOpponent
{
public:
    OpponentType Type();
};
class ElfOpponent : public BaseOpponent
{
public:
    OpponentType Type();
};
class TrollOpponent : public BaseOpponent
{
public:
    OpponentType Type();
};
class TornberyOpponent : public BaseOpponent
{
public:
    OpponentType Type();
};
class QueenOfCardsOpponent : public BaseOpponent
{
public:
    OpponentType Type();
};
class NinaDeRingsOpponent : public BaseOpponent
{
public:
    OpponentType Type();
};
class DurianGardenOpponent : public BaseOpponent
{
public:
    OpponentType Type();
};
class OmegaWeaponOpponent : public BaseOpponent
{
public:
    OpponentType Type();
};
class HadesOpponent : public BaseOpponent
{
public:
    OpponentType Type();
};
enum KnightType
{
    PALADIN = 0,
    LANCELOT,
    DRAGON,
    NORMAL
};
class BaseKnight
{
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    bool poisoned = 0;
    BaseBag *bag;
    KnightType knightType;

public:
    int getHp();
    int getMaxHp();
    int getGil();
    void setHp(int hp);
    void setLevel(int level);
    void setPoisoned(bool poisoned);
    void setGil(int gil);
    bool getPoisoned();
    bool setBag(BaseItem *item);

public:
    BaseKnight(int id, int maxhp, int level, int gil);
    static BaseKnight *create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;

    virtual bool fight(BaseOpponent *opponent, int);
    virtual int knightBaseDamage() = 0;
    ~BaseKnight();
};
class PaladinKnight : public BaseKnight
{
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    int knightBaseDamage() { return 0.06 * level * hp; }
};
class LancelotKnight : public BaseKnight
{
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    int knightBaseDamage() { return 0.05 * level * hp; }
};
class DragonKnight : public BaseKnight
{
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    int knightBaseDamage() { return 0.075 * level * hp; }
};
class NormalKnight : public BaseKnight
{
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    int knightBaseDamage() { return 0; }
};
class ArmyKnights
{
public:
    static bool bool_winOmegaWeapon;
    static bool bool_winHades;

private:
    BaseKnight **BaseKnight_array;
    int size;
    int i = 0;
    bool bool_hasPaladinShield = false;
    bool bool_hasLancelotSpear = false;
    bool bool_hasGuinevereHair = false;
    bool bool_hasExcaliburSword = false;

public:
    ArmyKnights(const string &file_armyknights)
    {
        ifstream read_armyKnights_files;
        read_armyKnights_files.open(file_armyknights);
        read_armyKnights_files >> size;
        BaseKnight_array = new BaseKnight *[size];

        for (int i = 0; i < size; i++)
        {
            int maxhp, level, phoenixdownI, gil, antidote;
            read_armyKnights_files >> maxhp >> level >> phoenixdownI >> gil >> antidote;

            BaseKnight_array[i] = BaseKnight::create(i + 1, maxhp, level, gil, antidote, phoenixdownI);
        }
    }
    ~ArmyKnights()
    {
        for (int i = 0; i < size; i++)
            delete BaseKnight_array[i];
        delete[] BaseKnight_array;
    }

    bool fight(BaseOpponent *opponent);
    bool adventure(Events *events);
    int count() const { return this->size; }
    BaseKnight *lastKnight() const { return this->BaseKnight_array[size - 1]; }

    bool hasPaladinShield() const { return bool_hasPaladinShield; }
    bool hasLancelotSpear() const { return bool_hasLancelotSpear; }
    bool hasGuinevereHair() const { return bool_hasGuinevereHair; }
    bool hasExcaliburSword() const { return bool_hasExcaliburSword; }

    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem
{
protected:
    ItemType itemType;

public:
    virtual bool canUse(BaseKnight *knight) = 0;
    virtual void use(BaseKnight *knight) = 0;
    virtual ItemType Type() { return itemType; }
};

class AntidoteItem : public BaseItem
{
public:
    AntidoteItem();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};

class PhoenixDownIItem : public BaseItem
{
public:
    PhoenixDownIItem();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownIIItem : public BaseItem
{
public:
    PhoenixDownIIItem();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownIIIItem : public BaseItem
{
public:
    PhoenixDownIIIItem();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};
class PhoenixDownIVItem : public BaseItem
{
public:
    PhoenixDownIVItem();
    bool canUse(BaseKnight *knight);
    void use(BaseKnight *knight);
};

class Events
{
private:
    int *events_list;
    int size;

public:
    Events(string file_input)
    {
        ifstream read_event_files(file_input);
        read_event_files >> size;
        events_list = new int[size];
        for (int i = 0; i < size; i++)
        {
            read_event_files >> events_list[i];
        }
    }
    int count() const
    {
        return size;
    }
    int get(int i) const
    {
        return events_list[i];
    }
    ~Events()
    {
        delete[] events_list;
    }
};

class KnightAdventure
{
private:
    ArmyKnights *armyKnights;
    Events *events;

public:
    KnightAdventure() {}
    void loadArmyKnights(const string &file) { armyKnights = new ArmyKnights(file); }
    void loadEvents(const string &file) { events = new Events(file); }
    void run() { armyKnights->printResult(armyKnights->adventure(events)); }
    ~KnightAdventure()
    {
        delete armyKnights;
        delete events;
    }
};

#endif // __KNIGHT2_H__