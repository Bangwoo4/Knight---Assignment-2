#include "knight2.h"

bool isPrime(int n)
{
    if (n <= 1)
        return false;
    for (int i = 2; i < n; i++)
        if (n % i == 0)
            return false;

    return true;
}

bool isPythagoras(int n)
{
    if (n < 100 || n > 999)
    {
        return false;
    }
    int a = n / 100;
    int b = (n / 10) % 10;
    int c = n % 10;
    if (a == 0 || b == 0 || c == 0)
    {
        return false;
    }
    if (a < 1 || a > 9 || b < 0 || b > 9 || c < 0 || c > 9)
    {
        return false;
    }
    if (a > b)
    {
        swap(a, b);
    }
    if (b > c)
    {
        swap(b, c);
    }
    if (a > b)
    {
        swap(a, b);
    }
    if (pow(a, 2) + pow(b, 2) == pow(c, 2))
    {
        return true;
    }
    return false;
}

/* * * BEGIN implementation of class BaseOpponent * * */
OpponentType MadBearOpponent::Type() { return MadBear; }
OpponentType BanditOpponent::Type() { return Bandit; }
OpponentType LordLupinOpponent::Type() { return LordLupin; }
OpponentType ElfOpponent::Type() { return Elf; }
OpponentType TrollOpponent::Type() { return Troll; }
OpponentType TornberyOpponent::Type() { return Tornbery; }
OpponentType QueenOfCardsOpponent::Type() { return QueenOfCards; }
OpponentType NinaDeRingsOpponent::Type() { return NinaDeRings; }
OpponentType DurianGardenOpponent::Type() { return DurianGarden; }
OpponentType OmegaWeaponOpponent::Type() { return OmegaWeapon; }
OpponentType HadesOpponent::Type() { return Hades; }
/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class BaseBag * * */
BaseBag::Node::Node(BaseItem *data, Node *next)
    : data(data), next(next)
{
}

BaseBag::Node::~Node() { delete data; }

BaseBag::BaseBag(BaseKnight *knight, int antidote, int phoenixDownI)
    : knight(knight), capacity(0), head(nullptr), size(0)
{
}

bool BaseBag::insertFirst(BaseItem *item)
{
    if (size == capacity)
    {
        return false;
    }
    else
    {
        size++;
        Node *new_node = new Node(item, nullptr);
        new_node->next = head;
        head = new_node;
        return true;
    }
}

BaseItem *BaseBag::get(ItemType itemType)
{
    if (size == 0)
    {
        return nullptr;
    }

    Node *temp = head;
    Node *found_node = nullptr;
    while (temp && !found_node)
    {
        if (temp->data->Type() == itemType)
        {
            found_node = temp;
        }
        temp = temp->next;
    }

    if (found_node)
    {
        std::swap(head->data, found_node->data);
        return head->data;
    }
    return nullptr;
}

BaseItem *BaseBag::checkHp()
{
    if (size == 0)
    {
        return nullptr;
    }
    Node *temp = head;
    while (temp && !temp->data->canUse(knight))
    {
        temp = temp->next;
    }
    if (temp)
    {
        swap(head->data, temp->data);
        return head->data;
    }
    return nullptr;
}

bool BaseBag::useItem(ItemType itemType)
{
    BaseItem *temp = nullptr;
    if (itemType == Antidote)
    {
        temp = get(itemType);
    }
    else
    {
        temp = checkHp();
    }
    if (temp == nullptr)
    {
        return false;
    }
    this->head->data->use(knight);
    deleteSlot();
    return true;
}

string BaseBag::toString() const
{
    if (size == 0)
    {
        return "Bag[count=0;]";
    }
    string result = "Bag[count=" + to_string(size) + ";";
    string typeArray[] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};
    Node *current = head;
    if (current)
    {
        result += typeArray[current->data->Type()] + ",";
        current = current->next;
        while (current)
        {
            result += typeArray[current->data->Type()] + ",";
            current = current->next;
        }
        result[result.length() - 1] = ']';
    }
    return result;
}

void BaseBag::deleteSlot()
{
    if (size == 0)
    {
        return;
    }
    else
    {
        size--;
        Node *current = head;
        head = head->next;
        delete current;
    }
}

BaseBag::~BaseBag()
{
    while (size)
        deleteSlot();
}

// PaladinKnight
BagPaladinKnight::BagPaladinKnight(BaseKnight *knight, int antidote, int phoenixDownI)
    : BaseBag(knight, antidote, phoenixDownI)
{
    this->capacity = -1;

    for (int i = 0; i < phoenixDownI && this->size != this->capacity; i++)
    {
        this->insertFirst(new PhoenixDownIItem());
    }
    for (int i = 0; i < antidote && this->size != this->capacity; i++)
    {
        this->insertFirst(new AntidoteItem());
    }
}

BagLancelotKnight::BagLancelotKnight(BaseKnight *knight, int antidote, int phoenixDownI)
    : BaseBag(knight, antidote, phoenixDownI)
{
    this->capacity = 16;
    for (int i = 0; i < phoenixDownI && this->size != this->capacity; i++)
    {
        this->insertFirst(new PhoenixDownIItem());
    }
    for (int i = 0; i < antidote && this->size != this->capacity; i++)
    {
        this->insertFirst(new AntidoteItem());
    }
}

BagDragonKnight::BagDragonKnight(BaseKnight *knight, int antidote, int phoenixDownI)
    : BaseBag(knight, antidote, phoenixDownI)
{
    this->capacity = 14;
    for (int i = 0; i < phoenixDownI && this->size < this->capacity; i++)
    {
        this->insertFirst(new PhoenixDownIItem());
    }
}

BagNormalKnight::BagNormalKnight(BaseKnight *knight, int antidote, int phoenixDownI)
    : BaseBag(knight, antidote, phoenixDownI)
{
    this->capacity = 19;
    for (int i = 0; i < phoenixDownI && this->size < this->capacity; i++)
    {
        this->insertFirst(new PhoenixDownIItem());
    }
    for (int i = 0; i < antidote && this->size < this->capacity; i++)
    {
        this->insertFirst(new AntidoteItem());
    }
}

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseItem * * */
// Antidote
bool AntidoteItem::canUse(BaseKnight *knight) { return knight->getPoisoned(); }
void AntidoteItem::use(BaseKnight *knight) { knight->setPoisoned(false); }
AntidoteItem::AntidoteItem() { itemType = Antidote; }
// PhoenixDownI
bool PhoenixDownIItem::canUse(BaseKnight *knight)
{
    return knight->getHp() <= 0;
}
void PhoenixDownIItem::use(BaseKnight *knight)
{
    knight->setHp(knight->getMaxHp());
}
PhoenixDownIItem::PhoenixDownIItem() { itemType = PhoenixDownI; }
// PhoenixDownII
bool PhoenixDownIIItem::canUse(BaseKnight *knight)
{
    return knight->getHp() < knight->getMaxHp() / 4;
}
void PhoenixDownIIItem::use(BaseKnight *knight)
{
    knight->setHp(knight->getMaxHp());
}
PhoenixDownIIItem::PhoenixDownIIItem() { itemType = PhoenixDownII; }
// PhoenixDownIII
bool PhoenixDownIIIItem::canUse(BaseKnight *knight)
{
    return knight->getHp() < knight->getMaxHp() / 3;
}

void PhoenixDownIIIItem::use(BaseKnight *knight)
{
    if (knight->getHp() <= 0)
    {
        knight->setHp(knight->getMaxHp() / 3);
    }
    else
    {
        knight->setHp(knight->getMaxHp() / 4 + knight->getHp());
    }
}

PhoenixDownIIIItem::PhoenixDownIIIItem() { itemType = PhoenixDownIII; }
// PhoenixDownIV
bool PhoenixDownIVItem::canUse(BaseKnight *knight)
{
    return knight->getHp() < knight->getMaxHp() / 2;
}
void PhoenixDownIVItem::use(BaseKnight *knight)
{
    if (knight->getHp() <= 0)
    {
        knight->setHp(knight->getMaxHp() / 2);
    }
    else
    {
        knight->setHp(knight->getMaxHp() / 5 + knight->getHp());
    }
}
PhoenixDownIVItem::PhoenixDownIVItem() { itemType = PhoenixDownIV; }
/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class BaseKnight * * */
BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
{
    BaseKnight *knight;
    if (maxhp == 888)
    {
        knight = new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    else if (isPythagoras(maxhp))
    {
        knight = new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    else if (isPrime(maxhp))
    {
        knight = new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }
    else
    {
        knight = new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
    }

    return knight;
}

BaseKnight::BaseKnight(int id, int maxhp, int level, int gil)
{
    this->id = id;
    this->maxhp = this->hp = maxhp;
    this->level = level;
    this->gil = gil;
}
string BaseKnight::toString() const
{
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) + ",hp:" + to_string(hp) + ",maxhp:" + to_string(maxhp) + ",level:" + to_string(level) + ",gil:" + to_string(gil) + "," + bag->toString() + ",knight_type:" + typeString[knightType] + "]";
    return s;
}

bool BaseKnight::fight(BaseOpponent *opponent, int i)
{
    int event_id = int(opponent->Type()); // event_id là mã sự kiện (không phải thứ tự sự kiện (i))

    int levelO = (i + event_id) % 10 + 1;

    if (event_id >= 1 && event_id <= 5)
    {
        if (knightType == PALADIN || knightType == LANCELOT || level >= levelO)
        {
            if (event_id == 1)
                gil = gil + 100;
            else if (event_id == 2)
                gil = gil + 150;
            else if (event_id == 3)
                gil = gil + 450;
            else if (event_id == 4)
                gil = gil + 750;
            else if (event_id == 5)
                gil = gil + 800;
        }

        else
        {
            if (event_id == 1)
                hp = hp - 10 * (levelO - level);
            else if (event_id == 2)
                hp = hp - 15 * (levelO - level);
            else if (event_id == 3)
                hp = hp - 45 * (levelO - level);
            else if (event_id == 4)
                hp = hp - 75 * (levelO - level);
            else if (event_id == 5)
                hp = hp - 95 * (levelO - level);

            this->bag->useItem(PhoenixDownIII);
        }
    }
    // gặp ma Tornbery
    else if (event_id == 6)
    {
        // thắng
        if (level >= levelO)
        {
            level = level + 1;
            if (level > 10)
            {
                level = 10;
            }
        }
        // thua
        else
        {
            if (knightType != DRAGON)
            { // không phải Dragon thì trúng độc
                this->poisoned = true;
                this->bag->useItem(Antidote);

                if (this->poisoned)
                {

                    for (int i = 0; i < 3; i++)
                    {
                        this->bag->deleteSlot();
                    }

                    this->poisoned = false;
                    hp = hp - 10;
                    this->bag->useItem(PhoenixDownIII);
                }
            }
        }
    }

    // gặp nữ hoàng cờ bạc Queen of Cards
    else if (event_id == 7)
    {
        // thắng
        if (level >= levelO)
        {
            gil = gil * 2;
        }
        // thua
        else
        {
            if (knightType != PALADIN)
            {
                gil = (gil / 2);
            }
        }
    }
    // gặp lái buôn vui tính Nina de Rings
    else if (event_id == 8)
    {
        if (hp < maxhp / 3)
        {
            if (knightType == PALADIN)
            {
                hp = hp + maxhp / 5;
            }
            else
            {
                if (gil >= 50)
                {
                    hp = hp + maxhp / 5;
                    gil = gil - 50;
                }
            }
        }
    }
    // gặp Vườn sầu riêng
    else if (event_id == 9)
    {
        hp = maxhp;
    }
    // gặp quái vật Omega Weapon
    else if (event_id == 10 && ArmyKnights::bool_winOmegaWeapon == false)
    {
        // thắng
        if (((level == 10 && hp == maxhp) && (knightType != DRAGON)) || knightType == DRAGON)
        {
            level = 10;
            gil = 999;
            ArmyKnights::bool_winOmegaWeapon = true;
        }
        // thua
        else
        {
            hp = 0;
            this->bag->useItem(PhoenixDownIII);
        }
    }
    // gặp Hades
    else if (event_id == 11 && ArmyKnights::bool_winHades == false)
    {
        if (level == 10 || knightType == PALADIN && level >= 8)
        { // thắng
            ArmyKnights::bool_winHades = true;
        }

        else
        { // thua
            hp = 0;
            this->bag->useItem(PhoenixDownIII);
            ArmyKnights::bool_winHades = false;
        }
    }

    if (this->hp <= 0 && this->gil >= 100)
    {
        this->hp = this->maxhp / 2;
        this->gil = this->gil - 100;
    }

    if (hp > 0)
    {
        return true;
    }
    return false;
}

BaseKnight::~BaseKnight()
{
    delete bag;
}

int BaseKnight::getHp() { return hp; }
int BaseKnight::getMaxHp() { return maxhp; }
int BaseKnight::getGil() { return gil; }
bool BaseKnight::getPoisoned() { return poisoned; }

void BaseKnight::setHp(int hp)
{
    if (hp > maxhp)
        this->hp = maxhp;
    else
    {
        if (this->hp > hp)
        {
            this->hp = hp;
            this->bag->useItem(ItemType::PhoenixDownI);
            if (this->hp <= 0 && this->gil >= 100)
            {
                this->hp = this->maxhp / 2;
                this->gil -= 100;
            }
        }
        else
        {
            this->hp = hp;
        }
    }
}

void BaseKnight::setLevel(int level)
{
    this->level = level;
    if (this->level > 10)
    {
        this->level = 10;
    }
}
void BaseKnight::setPoisoned(bool poisoned)
{
    this->poisoned = poisoned;
}
void BaseKnight::setGil(int gil)
{
    this->gil = gil;
}
bool BaseKnight::setBag(BaseItem *item)
{
    return bag->insertFirst(item);
}

// Paladin Knight
PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) : BaseKnight(id, maxhp, level, gil)
{
    // khởi tạo tên và túi của hiệp sĩ
    this->knightType = PALADIN;
    this->bag = new BagPaladinKnight(this, antidote, phoenixdownI);
}

LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    : BaseKnight(id, maxhp, level, gil)
{
    this->knightType = LANCELOT;
    this->bag = new BagLancelotKnight(this, antidote, phoenixdownI);
}

DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    : BaseKnight(id, maxhp, level, gil)
{
    this->knightType = DRAGON;
    this->bag = new BagDragonKnight(this, antidote, phoenixdownI);
}

NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI)
    : BaseKnight(id, maxhp, level, gil)
{
    this->knightType = NORMAL;
    this->bag = new BagNormalKnight(this, antidote, phoenixdownI);
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
bool ArmyKnights::bool_winHades = false;
bool ArmyKnights::bool_winOmegaWeapon = false;

void ArmyKnights::printInfo() const
{
    cout << "No. knights: " << this->count();
    if (this->count() > 0)
    {
        BaseKnight *last_knight = lastKnight();
        cout << ";" << last_knight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
         << ";LancelotSpear:" << this->hasLancelotSpear()
         << ";GuinevereHair:" << this->hasGuinevereHair()
         << ";ExcaliburSword:" << this->hasExcaliburSword()
         << endl
         << string(50, '-') << endl;
}
void ArmyKnights::printResult(bool win) const
{
    if (win)
    {
        cout << "WIN" << endl;
    }
    else
    {
        cout << "LOSE" << endl;
    }
}

bool ArmyKnights::fight(BaseOpponent *opponent)
{
    // gọi hiệp sĩ cuối cùng ra chiến đấu
    while (size)
    {
        BaseKnight *last_knight = lastKnight();
        // thắng
        if (last_knight->fight(opponent, i))
        {

            if (ArmyKnights::bool_winHades)
            {
                this->bool_hasPaladinShield = true;
            }
            // truyền vàng cho hiệp sĩ tiếp theo
            for (int i = size - 1; i >= 0; i--)
            { // truyền từ cuối mảng về đầu mảng
                int leftovers = BaseKnight_array[i]->getGil() - 999;

                if (leftovers <= 0)
                {
                    break;
                }
                else
                {
                    BaseKnight_array[i]->setGil(999);
                    if (i > 0)
                    {
                        BaseKnight_array[i - 1]->setGil(BaseKnight_array[i - 1]->getGil() + leftovers);
                    }
                }
            }
            break;
        }

        else
        { // thua và chết
            size--;
            delete last_knight;
            break;
        }
    }
    delete opponent;
    return size;
}

bool ArmyKnights::adventure(Events *events)
{

    ArmyKnights::bool_winHades = ArmyKnights::bool_winOmegaWeapon = false;
    this->i = 0;
    for (; i < events->count(); i++)
    {

        if (events->get(i) == 1)
            this->fight(new MadBearOpponent());

        else if (events->get(i) == 2)
            this->fight(new BanditOpponent());

        else if (events->get(i) == 3)
            this->fight(new LordLupinOpponent());

        else if (events->get(i) == 4)
            this->fight(new ElfOpponent());

        else if (events->get(i) == 5)
            this->fight(new TrollOpponent());

        else if (events->get(i) == 6)
            this->fight(new TornberyOpponent());

        else if (events->get(i) == 7)
            this->fight(new QueenOfCardsOpponent());

        else if (events->get(i) == 8)
            this->fight(new NinaDeRingsOpponent());

        else if (events->get(i) == 9)
            this->fight(new DurianGardenOpponent());

        else if (events->get(i) == 10)
            this->fight(new OmegaWeaponOpponent());

        else if (events->get(i) == 11)
            this->fight(new HadesOpponent());

        else if (events->get(i) == 112)
        {
            BaseItem *item = nullptr;
            item = new PhoenixDownIIItem();
            bool insert = false;
            for (int p = size - 1; p >= 0; p--)
            {
                if (insert = BaseKnight_array[p]->setBag(item))
                {
                    break;
                }
            }
            if (insert == false)
            {
                delete item;
            }
        }

        else if (events->get(i) == 113)
        {
            BaseItem *item = nullptr;
            item = new PhoenixDownIIIItem();
            bool insert = false;
            for (int p = size - 1; p >= 0; p--)
            {
                if (insert = BaseKnight_array[p]->setBag(item))
                {
                    break;
                }
            }
            if (insert == false)
            {
                delete item;
            }
        }
        else if (events->get(i) == 114)
        {
            BaseItem *item = nullptr;
            item = new PhoenixDownIVItem();
            bool insert = false;
            for (int p = size - 1; p >= 0; p--)
            {
                if (insert = BaseKnight_array[p]->setBag(item))
                {
                    break;
                }
            }
            if (insert == false)
            {
                delete item;
            }
        }

        else if (events->get(i) == 95)
        {
            this->bool_hasPaladinShield = true;
        }
        else if (events->get(i) == 96)
        {
            this->bool_hasLancelotSpear = true;
        }
        else if (events->get(i) == 97)
        {
            this->bool_hasGuinevereHair = true;
        }
        else if (events->get(i) == 98)
        {
            if (bool_hasPaladinShield && bool_hasLancelotSpear && bool_hasGuinevereHair)
            {
                this->bool_hasExcaliburSword = true;
            }
        }

        // gặp Unltimecia
        else if (events->get(i) == 99)
        {
            if (bool_hasExcaliburSword == 1)
            {
                this->printInfo();
                return true;
            }

            else if ((bool_hasGuinevereHair == 1) && (bool_hasLancelotSpear == 1) && (bool_hasPaladinShield == 1))
            {
                int UltimeciaHp = 5000;
                BaseKnight *lastNormalKnight = nullptr;
                int normalKnightCount = 0;

                while (size > 0)
                {
                    BaseKnight *knight = lastKnight();

                    if (knight->knightBaseDamage() < 0)
                    {
                        delete knight;
                        continue;
                    }

                    UltimeciaHp = UltimeciaHp - knight->knightBaseDamage();

                    if (knight->knightBaseDamage() == 0)
                    {
                        ++normalKnightCount;
                        if (!lastNormalKnight)
                        {
                            lastNormalKnight = knight;
                        }
                        else
                        {
                            delete knight;
                        }
                    }
                    else
                    {
                        delete knight;
                    }

                    if (UltimeciaHp <= 0)
                    {
                        for (int i = 0; i < normalKnightCount; ++i)
                        {
                            BaseKnight_array[size++] = lastNormalKnight;
                        }

                        this->printInfo();
                        return true;
                    }
                    size = size - 1;
                    if (size == 0)
                    {
                        delete lastNormalKnight;
                        this->printInfo();
                        return false;
                    }
                }
            }
            else
            {
                for (int i = 0; i < size; ++i)
                {
                    delete BaseKnight_array[i];
                }
                size = 0;
            }

            this->printInfo();
            return size;
        }

        this->printInfo();
        if (size == 0)
            return false;
    }
    return true;
}

/* * * END implementation of class ArmyKnights * * */
//  g++ -o main main.cpp knight2.cpp -I . -std=c++11
//  ./main file_armyknights file_events
