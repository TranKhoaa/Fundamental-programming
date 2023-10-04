#include "knight2.h"
    bool isPrime(int n){
        if(n == 2) return true;
        else{
            for(int i{2}; i <= sqrt(n); i++){
                if(n % i == 0) return false;
            }
        }
        return true;
    }
    bool isPythagoras(int n){
        int a, b, c;
        a = n/100;
        b = (n-a*100)/10;
        c = (n - a*100 - b*10);
        if(a == 0 || b == 0 || c == 0) return false;
        if(c*c == a*a + b*b) return true;
        if(b*b == a*a + c*c) return true;
        if(a*a == b*b + c*c) return true;
        return false;
    }
/* * * BEGIN implementation of class BaseBag * * */
BaseBag::BaseBag(BaseKnight * knight){
    this -> knight = knight;
    this -> nItems = 0;
    this -> capacity = 0;
    this -> head = nullptr;
}
bool BaseBag::insertFirst(BaseItem * item){
    if(nItems == capacity) return false;
    else{
        Node * p = new Node;
        p -> data = item;
        p -> next = head;
        head = p;   
        nItems++;
    }
    return true;    
}
BaseItem * BaseBag::get(ItemType itemType){
    if(nItems == 0) return nullptr;
    if(itemType == Antidote){
        Node* temp = head;
        Node * prev = nullptr;
        while(temp != nullptr && temp->data->Type() != itemType){
            prev = temp;
            temp = temp->next;
        } 
        if(temp == nullptr) return nullptr;
        else{
            swap(head->data, temp->data);
            nItems --;
            temp = head;
            head = head->next;
            temp->data->use(knight);
            delete temp->data;
            delete temp;
            return nullptr;
        }
    }
    else{
        Node* temp = head;
        while(temp != nullptr && !temp->data->canUse(knight)) temp = temp->next;
        if(temp == nullptr) return nullptr;
        else{
            swap(head->data, temp->data);
            nItems --;
            temp = head;
            head = head->next;

            temp->data->use(knight);
            delete temp->data;
            delete temp;
            return nullptr;
        }
    }
    return nullptr;
}
void BaseBag::remove(){
    if(nItems == 0) return;
    else{
        nItems--;
        Node * temp = head;
        head = head -> next;
        delete temp -> data;
        delete temp;
    }
    
}
BaseBag::~BaseBag(){
    Node * temp = head;
    while(temp != nullptr){
        Node * next = temp -> next;
        delete temp -> data;
        delete temp;
        temp = next;
    }
}
string BaseBag::toString() const{
    if(nItems == 0) return "Bag[count=0;]";
    string result = "Bag[count=" + to_string(nItems) + ";";
    string infoItem[] = {"Antidote", "PhoenixI", "PhoenixII", "PhoenixIII", "PhoenixIV"};
    Node * temp = head;
    while(temp!=nullptr){
        result += infoItem[temp->data->Type()] + ",";
        temp = temp -> next;
    }
    result[result.length() - 1] = ']';
    return result;
}
BagDragonKnight::BagDragonKnight(BaseKnight * knight):BaseBag(knight){
    this -> capacity = 14;
}
BagLancelotKnight::BagLancelotKnight(BaseKnight * knight):BaseBag(knight){
    this -> capacity = 16;
}
BagPaladinKnight::BagPaladinKnight(BaseKnight * knight):BaseBag(knight){
    this -> capacity = -1;
}
BagNormalKnight::BagNormalKnight(BaseKnight * knight):BaseBag(knight){
    this -> capacity = 19;
}
bool BagDragonKnight::insertFirst(BaseItem * item){
    if(nItems == 0 || item->Type() == Antidote) return false;
    else{
    Node * p = new Node;
    p -> data = item;
    p -> next = head;
    head = p;   
    nItems++;
    }
    return true;
}
/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
BaseKnight * BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    BaseKnight * knight;
    if(maxhp == 888){
        knight = new LancelotKnight();
        knight -> bag = new BagLancelotKnight(knight);
    }
    else if(isPythagoras(maxhp)){
        knight = new DragonKnight();
        knight -> bag = new BagDragonKnight(knight);
    }
    else if(isPrime(maxhp)){
        knight = new PaladinKnight();
        knight -> bag = new BagPaladinKnight(knight);
    }
    else{
        knight = new NormalKnight();
        knight -> bag = new BagNormalKnight(knight);
    }
    knight -> id = id;
    knight -> hp = maxhp;
    knight -> maxhp = maxhp;
    knight -> level = level;
    knight -> gil = gil;
    for(int i{0}; i < phoenixdownI; i++){
        BaseItem * item = new PhoenixDown1Item();
        if(!(knight -> bag -> insertFirst(item))) delete item;
    }
    for(int i{0}; i < antidote; i++){
        BaseItem * item = new AntidoteItem();
        if(!(knight -> bag -> insertFirst(item))) delete item;
    }
    return knight;
}
BaseKnight::~BaseKnight(){
    delete bag;
}
void BaseKnight::setGil(int gil){
    this -> gil = gil;
}
void BaseKnight::setHp(int hp){
    if(this -> hp > hp){
        this -> hp = hp;
        this -> bag -> get(PhoenixDownI);
    }
    else if(this -> hp > maxhp){
        this -> hp = maxhp;
    }
    else this -> hp = hp;   
}
bool BaseKnight::setBag(BaseItem * item){
    return bag->insertFirst(item);
}
void BaseKnight::setLevel(int level){
    if(level > 10){
        this -> level = 10;
    }
    else{
        this -> level = level;
    }
}
void BaseKnight::setPosioned(bool isPoisoned){
    this -> isPoisoned = isPoisoned;
    if(isPoisoned == true){
        this -> bag -> get(Antidote);
        if(this -> isPoisoned == true){
            isPoisoned = false;
            this -> bag -> remove();
            this -> bag -> remove();
            this -> bag -> remove();
            this -> setHp(this -> hp - 10);
        }
    }
}
int BaseKnight::getHp(){
    return hp;
}
int BaseKnight::getGil(){
    return gil;
}
int BaseKnight::getMaxHp(){
    return maxhp;
}
int BaseKnight::getLevel(){
    return level;
}
bool BaseKnight::getPosioned(){
    return isPoisoned;
}
KnightType BaseKnight::getKnighttype(){
    return knightType;
}
PaladinKnight::PaladinKnight(){
    this -> knightType = PALADIN;
}
int PaladinKnight::knightDamage(){
    return 0.06 * this->hp * this->level;
}
LancelotKnight::LancelotKnight(){
    this -> knightType = LANCELOT;
}
int LancelotKnight::knightDamage(){
    return 0.05 * this->hp * this->level;
}
DragonKnight::DragonKnight(){
    this -> knightType = DRAGON;
}
int DragonKnight::knightDamage(){
    return 0.075 * this -> hp * this -> level;
}
NormalKnight::NormalKnight(){
    this -> knightType = NORMAL;
}
int NormalKnight::knightDamage(){
    return 0;
}
string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class BaseOpponent * * */
int BaseOpponent::getlvlO(){
    return lvlO;
}

int BaseOpponent::getbaseDmg(){
    return baseDmg;
}
int BaseOpponent::getOpponent(){
    return Opponent;
}
BaseOpponent::BaseOpponent(BaseKnight*){}

/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class ArmyKnights * * */

ArmyKnights::ArmyKnights(const string & file_armyknights){
    ifstream input(file_armyknights);
    input >> nKnights;
    arKnights = new BaseKnight * [nKnights];
    int maxhp, level, phoenixdownI, gil, antidote;
    for(int i{0}; i < nKnights; i++){
        input >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        arKnights[i] = BaseKnight::create(i + 1, maxhp, level, gil,antidote, phoenixdownI);
    }
}
bool ArmyKnights::fight(BaseOpponent * opponent){
    while(nKnights > 0){
    BaseKnight * lknight = lastKnight();
    if(opponent -> getOpponent() == MadBear){
        if(lknight -> getKnighttype() == LANCELOT || lknight ->getKnighttype() == PALADIN){
                lknight -> setGil(lknight -> getGil() + 100);
            }
            else if(lknight -> getLevel() >= opponent -> getlvlO()){
                lknight -> setGil(lknight -> getGil() + 100);
            }
            else{
                lknight -> setHp(lknight -> getHp() - opponent -> getbaseDmg() * (opponent -> getlvlO() - lknight -> getLevel()));
            }
        }
    else if(opponent->getOpponent() == Bandit){
            if(lknight -> getKnighttype() == LANCELOT || lknight ->getKnighttype() == PALADIN){
                lknight -> setGil(lknight -> getGil() + 150);
            }
            else if(lknight -> getLevel() >= opponent -> getlvlO()){
                lknight -> setGil(lknight -> getGil() + 150);
            }
            else{
                lknight -> setHp(lknight -> getHp() - opponent -> getbaseDmg() * (opponent -> getlvlO() - lknight -> getLevel()));
            }
    }
    else if(opponent->getOpponent() == LordLupin){
            if(lknight -> getKnighttype() == LANCELOT || lknight ->getKnighttype() == PALADIN){
                lknight -> setGil(lknight -> getGil() + 450);
            }
            else if(lknight -> getLevel() >= opponent -> getlvlO()){
                lknight -> setGil(lknight -> getGil() + 450);
            }
            else{
                lknight -> setHp(lknight -> getHp() - opponent -> getbaseDmg() * (opponent -> getlvlO() - lknight -> getLevel()));
            }
    }
    else if(opponent->getOpponent() == Elf){
            if(lknight -> getKnighttype() == LANCELOT || lknight ->getKnighttype() == PALADIN){
                lknight -> setGil(lknight -> getGil() + 750);
            }
            else if(lknight -> getLevel() >= opponent -> getlvlO()){
                lknight -> setGil(lknight -> getGil() + 750);
            }
            else{
                lknight -> setHp(lknight -> getHp() - opponent -> getbaseDmg() * (opponent -> getlvlO() - lknight -> getLevel()));
            }
    }
    else if(opponent->getOpponent() == Troll){
            if(lknight -> getKnighttype() == LANCELOT || lknight ->getKnighttype() == PALADIN){
                lknight -> setGil(lknight -> getGil() + 800);
            }
            else if(lknight -> getLevel() >= opponent -> getlvlO()){
                lknight -> setGil(lknight -> getGil() + 800);
            }
            else{
                lknight -> setHp(lknight -> getHp() - opponent -> getbaseDmg() * (opponent -> getlvlO() - lknight -> getLevel()));
            }
    }
    else if(opponent -> getOpponent() == Tornbery){
            if(lknight -> getLevel() >= opponent -> getlvlO()){
                lknight -> setLevel(lknight -> getLevel() + 1);
            }
            else{
                if(lknight -> getKnighttype() == DRAGON) break;
                else{
                    lknight -> setPosioned(true);
                }
            }
    }
    else if(opponent -> getOpponent() == QueenOfCard){
            if(lknight -> getLevel() >= opponent -> getlvlO()){
                lknight -> setGil(lknight -> getGil() * 2);
                for(int i{nKnights - 1}; i >= 0; i--){
                int tempGil = arKnights[i]->getGil() - 999;
                if(tempGil < 0) break;
                arKnights[i] -> setGil(999);
                if(i > 0) arKnights[i - 1] -> setGil(arKnights[i - 1] -> getGil() + tempGil);
                }
            }
            else{
                if(lknight -> getKnighttype() == PALADIN) break;
                else{
                    lknight -> setGil(lknight -> getGil()/2);
                }
            }
        }
    else if(opponent -> getOpponent() == NinaDerings){
            if(lknight -> getKnighttype() == PALADIN){
                if(lknight -> getHp() < lknight -> getMaxHp()/3) lknight -> setHp(lknight->getHp() + 1/5 * lknight -> getMaxHp());
            }
            else if(lknight -> getGil() < 50) break;
            else if(lknight -> getHp() < lknight -> getMaxHp()/3){
                lknight -> setHp(lknight->getHp() + lknight -> getMaxHp()/5);
                lknight -> setGil(lknight -> getGil() - 50);
            }
        }
    else if(opponent -> getOpponent() == DurianGarden){
            lknight -> setHp(lknight -> getMaxHp());
            break;
        }
    else if(opponent -> getOpponent() == OmegaWeapons && winOmegaWeapon == false){
        if((lknight -> getLevel() == 10 && lknight -> getHp() == lknight -> getMaxHp()) || lknight -> getKnighttype() == DRAGON){
            winOmegaWeapon = true;
        }
        else{
            lknight -> setHp(0);
        }
    }
    else if(opponent -> getOpponent() == Hades || winHades == false){
        if(lknight -> getLevel() == 10 || lknight -> getKnighttype() == PALADIN && lknight -> getLevel()  >= 8){
            winHades = true;
            isPaladinShield = true;
        }
        else{
            lknight -> setHp(0);
        }
    }
    for(int i{nKnights - 1}; i >= 0; i--){
        int tempGil = arKnights[i]->getGil() - 999;
        if(tempGil < 0) break;
        arKnights[i] -> setGil(999);
        if(i > 0) arKnights[i - 1] -> setGil(arKnights[i - 1] -> getGil() + tempGil);
    }
    if(lknight -> getHp() <= 0){
        if(lknight -> getGil() >= 100){
            lknight -> setGil(lknight -> getGil() - 100);
            lknight -> setHp(lknight -> getMaxHp()*1/2);
        }
        else{
        nKnights--;
        break;
        } 
    }
    break;
    }
    delete opponent;
    return nKnights;
}

bool ArmyKnights::adventure(Events * events){
    for(int i{0}; i < events->count(); i++){
        int events_nums = events->get(i);
        if(events_nums == 1){
            this -> fight(new MadBearOpponent(i));
        }
        else if(events_nums == 2){
            this -> fight(new BanditOpponent(i));
        }
        else if(events_nums == 3){
            this -> fight(new LordLupinOpponent(i));
        }
        else if(events_nums == 4){
            this -> fight(new ElfOpponent(i));
        }
        else if(events_nums == 5){
            this -> fight(new TrollOpponent(i));
        }
        else if(events_nums == 6){
            this -> fight(new TornberyOpponent(i));
        }
        else if(events_nums == 7){
            this -> fight(new QueenOfCardOpponent(i));
        }
        else if(events_nums == 8){
            this -> fight(new NinaDeringsOpponent());
        }
        else if(events_nums == 9){
            this -> fight(new DurianGardenOpponent());
        }
        else if(events_nums == 10){
            this -> fight(new OmegaWeaponsOpponent());
        }
        else if(events_nums == 11){
            this -> fight(new HadesOpponent());
        }
        else if(events_nums == 112){
            BaseItem * item;
            item = new PhoenixDown2Item();
            for(int j{nKnights - 1}; j >= 0; j--){
                if(arKnights[j] -> setBag(item)) break;
                else if(j == 0) delete item;
            }
        }
        else if(events_nums == 113){
            BaseItem * item;
            item = new PhoenixDown3Item();
            for(int j{nKnights - 1}; j >= 0; j--){
                if(arKnights[j] -> setBag(item)) break;
                else if(j == 0) delete item;
            }
        }
        else if(events_nums == 114){
            BaseItem * item;
            item = new PhoenixDown4Item();
            for(int j{nKnights - 1}; j >= 0; j--){
                if(arKnights[j] -> setBag(item)) break;
                else if(j == 0) delete item;
            }
        }
        else if(events_nums == 95){
            this -> isPaladinShield = true;
        }
        else if(events_nums == 96){
            this -> isLancelotSpear = true;
        }
        else if(events_nums == 97){
            this -> isGuinevereHair = true;
        }
        else if(events_nums == 98){
            if(isPaladinShield == true && isLancelotSpear == true && isGuinevereHair == true) this -> isExcaliburSword = true;
        }
        else if(events_nums == 99){
            if(isExcaliburSword == true){
                this->printInfo();
                return true;
            }
            if(isGuinevereHair == false || isLancelotSpear == false || isPaladinShield == false){
                for(int i{0}; i < nKnights; i++){
                    delete arKnights[i];
                }
                nKnights = 0;
            }
            else{
                int hpUlti = 5000;
                while(nKnights > 0){
                    BaseKnight * knight = lastKnight();
                    hpUlti -= knight -> knightDamage();
                    if(hpUlti > 0){
                        delete knight;
                        nKnights--;
                    }
                    else{
                        this -> printInfo();
                        return true;
                    }
                    if(nKnights == 0){
                        this -> printInfo();
                        return false;
                    }
                }
            }
        }
        if(winOmegaWeapon == true){
            BaseKnight * lknight = lastKnight();
            lknight -> setLevel(10);
            lknight -> setGil(999);
        }
        this->printInfo();
        if(nKnights == 0) return false;
    }

    return true;
}
int ArmyKnights::count() const{
    return this -> nKnights;  
}
BaseKnight * ArmyKnights::lastKnight() const{
    if(nKnights == 0) return nullptr;
    else return this -> arKnights[nKnights - 1];
}
bool ArmyKnights:: hasPaladinShield() const{
    return isPaladinShield;
};
bool ArmyKnights:: hasLancelotSpear() const{
    return isLancelotSpear;
};
bool ArmyKnights::hasGuinevereHair() const{
    return isGuinevereHair;
};
bool ArmyKnights::hasExcaliburSword() const{
    return isExcaliburSword;
};
ArmyKnights::~ArmyKnights(){
    for(int i{0}; i < nKnights; i++){
        delete arKnights[i];
    }
    delete[] arKnights;
}
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}
/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class BaseItem * * */
// Implementation of Antidote
bool AntidoteItem::canUse(BaseKnight * knight){
    return knight -> getPosioned();
}
void AntidoteItem::use(BaseKnight * knight){
    return knight -> setPosioned(false); 
}
ItemType AntidoteItem::Type(){
    return Antidote;
}
// Implementation of Phoenixdown1
bool PhoenixDown1Item::canUse(BaseKnight * knight){
    return knight -> getHp() <= 0;
}
void PhoenixDown1Item::use(BaseKnight * knight){
    return knight -> setHp(knight -> getMaxHp());
}
ItemType PhoenixDown1Item::Type(){
    return PhoenixDownI;
}
// Implementation of Phoenixdown2
bool PhoenixDown2Item::canUse(BaseKnight * knight){
    return knight -> getHp() < knight -> getMaxHp()/4;
}
void PhoenixDown2Item::use(BaseKnight * knight){
    return knight -> setHp(knight -> getMaxHp());
}
ItemType PhoenixDown2Item::Type(){
    return PhoenixDownII;
}
// Implementation of Phoenixdown3
bool PhoenixDown3Item::canUse(BaseKnight * knight){
    return knight -> getHp() < knight -> getMaxHp()/3;
}
void PhoenixDown3Item::use(BaseKnight * knight){
    if(knight -> getHp() <= 0){
        knight -> setHp(knight -> getMaxHp()/3);
    }
    else{
        knight -> setHp(knight -> getHp() + knight -> getMaxHp()/4);
    }
}
ItemType PhoenixDown3Item::Type(){
    return PhoenixDownIII;
}
// Implementation of Phoenixdown4
bool PhoenixDown4Item::canUse(BaseKnight * knight){
    return knight -> getHp() < knight -> getMaxHp()/2;
}
void PhoenixDown4Item::use(BaseKnight * knight){
    if(knight -> getHp() < 0){
        knight -> setHp(knight -> getMaxHp()/2);
    }
    else{
        knight -> setHp(knight -> getHp() + knight -> getMaxHp()/5);
    }
}
ItemType PhoenixDown4Item::Type(){
    return PhoenixDownIV;
}
/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class Events * * */
Events::Events(const string & file_events){
    ifstream fileEvents(file_events);
    fileEvents >> nEvents;
    events = new int [nEvents];
    for(int i{0}; i < nEvents; i++){
        fileEvents >> events[i];
    }
}
int Events::count() const{
    return nEvents;
}
int Events:: get(int i) const{
    return events[i];
}
Events:: ~Events(){
    delete[]events;
}
/* * * END implementation of class Events * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}
void KnightAdventure::loadArmyKnights(const string & file_armyknights){
    armyKnights = new ArmyKnights(file_armyknights);
}
void KnightAdventure::loadEvents(const string & file_events){
    events = new Events(file_events);
}
void KnightAdventure::run(){
    armyKnights -> printResult(armyKnights -> adventure(events));
}
KnightAdventure::~KnightAdventure(){
    delete armyKnights;
    delete events;
}
/* * * END implementation of class KnightAdventure * * */