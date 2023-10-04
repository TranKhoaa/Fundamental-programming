    #include "knight.h"

struct Player //khai báo dữ liệu
{
    int HP;
    int maxHP;
    int level;
    int remedy;
    int maidenkiss;
    int phoenixdown;
    int lvlO;
    int templvl;
    int tini = 0;
    int frog = 0;
    bool Arthur = false;
    bool Lancelot = false;
    bool meetAsclepius = false;
    bool meetMerlin = false;
};
void cutString(string s, int *arr){ // hàm lấy giá trị sau những dấu cách
    int index = 0;
    int temp;
    stringstream ss(s);
    while(ss >> temp){
        arr[index] = temp;
        index++;
    };
}
bool isPrime(int n){ // kiểm tra số nguyên tố
    if(n > 2){
        for(int i = 2; i <= sqrt(n); i++){
            if(n % i == 0) return false;
        }
        return true;
    }
    else if(n == 2) return true;
    else return false;
}
struct Player getValue(string s){ //Hàm lưu dữ liệu của player
    struct Player p;
    int arr[5];
    cutString(s, arr);
    p.HP = arr[0];
    p.maxHP = arr[0];
    p.level = arr[1];
    p.remedy = arr[2];
    p.maidenkiss = arr[3];
    p.phoenixdown = arr[4];
    if(p.HP == 999) p.Arthur = true;
    else if(isPrime(p.HP)) p.Lancelot = true;
    return p;
}

int getlvlO(int i){
    int b = (i+1) % 10;
    int lvlO = i > 6?(b > 5?b : 5) : b;
    return lvlO;
}
int getOpponentdmg(int id, int lvlO){
    double basedmg;
    switch(id)
    {
        case 1:
        basedmg = 1;
        break;
        case 2:
        basedmg = 1.5;
        break;
        case 3:
        basedmg = 4.5;
        break;
        case 4:
        basedmg = 7.5;
        break;
        case 5:
        basedmg = 9.5;
        break;
    }
    int dmg;
    dmg = basedmg*lvlO*10;
    return dmg;
}
bool isWin(struct Player p, int lvl){
    return (p.level > lvl || p.Arthur == true || p.Lancelot == true) ;
}
int lvlup(struct Player p, int n){
    p.level += n;
    if(p.level > 10) p.level = 10;
    return p.level;
}
void usePhoenixdown(struct Player &p){
    p.phoenixdown--;
    p.HP = p.maxHP;
}
void getdmg(struct Player &p, int dmg, int &rescue ){
    p.HP -= dmg;
    if(p.HP > p.maxHP) p.HP = p.maxHP;
    if(p.HP <= 0){
        if(p.phoenixdown > 0){
            usePhoenixdown(p); 
        }
        else rescue = 0;
    }
}
void fight(struct Player &p, int id, int i, int &rescue){
    //if(p.Arthur == true || p.Lancelot == true) p.level = lvlup(p,1); 
    //if(p.level == getlvlO(i)) p.level = lvlup(p, 0); 
    if(isWin(p, getlvlO(i)) == true) p.level = lvlup(p,1);
    else if(p.level < getlvlO(i)) getdmg(p, getOpponentdmg(id, getlvlO(i)), rescue);
    else p.level = lvlup(p, 0);
    
}
void shaMan(struct Player &p, int id, int &rescue){
    if(p.tini == 0 && p.frog == 0){
        int lvl = getlvlO(id);

        if(isWin(p, lvl) == true) p.level = lvlup(p, 2);
        else if(p.level < lvl){
            if(p.remedy <= 0){
                p.tini = 4;
                if(p.HP < 5) p.HP = 1;
                else p.HP = p.HP/5;
            }
            else{
                p.remedy--;
            }

        }
    }
}
void SirenVajsh(struct Player &p, int id, int &rescue){
    p.templvl = p.level;
    if(p.tini == 0 && p.frog == 0){
        int lvl = getlvlO(id);

        if(isWin(p, lvl) == true) p.level = lvlup(p, 2);
        else if(p.level < lvl){
            if(p.maidenkiss <= 0){
                p.frog = 4;
                p.level = 1;
            }
            else {
                p.maidenkiss--;
            }
        }
    }
}
void MushMario(struct Player &p){
    int n1 = ((p.level+p.phoenixdown)%5+1)*3;
    int s1;
    s1 = 99*n1 - n1*(n1-1);
    p.HP += (s1%100);
    if(isPrime(p.HP)) p.HP++;
    while(!isPrime(p.HP)){
        p.HP += 1;
        if(p.HP >= p.maxHP) break;
    };
    if(p.HP > p.maxHP) p.HP = p.maxHP;
}
void MushFibo(struct Player &p){
    int a = 0, b =1, c;
    if(p.HP > 1){
    while(a + b < p.HP){
        c = a + b;
        a = b;
        b = c;
    }
    p.HP = c;
    }
}
int maxi(int *arr, int n, int m){
    int max = arr[0];
    int a = 0;
    for(int i = 0; i < n;i++){
        if(m == 0){
        if(max < arr[i]){
            max = arr[i];
            a = i;
        }
        }
        else if(m == 1){
            if(max <= arr[i]){
                max = arr[i];
                a = i;
            }
        }
    }
    return a;
}
int mini(int *arr, int n, int m){
    int min = arr[0];
    int a = 0;
    for(int i = 0; i < n;i++){
        if(m == 0){
        if(min > arr[i]){
            min = arr[i];
            a = i;
        }}
        else if(m == 1){
            if(min >= arr[i]){
                min = arr[i];
                a = i;
            }
        }
    }
    return a;
}
void Mountain(int *arr, int n, int &mtx, int &mti){
    bool isUp = true;
    bool isDown = true;
    int max;
    max = arr[0];
    int pos = 0;
    for(int i = 0; i < n; i++){
        if(max < arr[i]) {
            max = arr[i];
            pos = i;
        }
    }
    if(pos!= 0){
    for(int i = 1; i < pos; i++){
        if(arr[i-1] >= arr[i]) {
        isUp = false;
        break;
        }
    }
    }
    if(pos!= n -1){
    for(int i = pos + 1; i < n;i++){
        if(arr[i-1] <= arr[i]){ 
         isDown = false;
        break;
        }
    }
    }
    if(pos == 0 && isDown == true){
        mtx = max;
        mti = 0;
    }   
    else if(pos == n-1 && isUp == true){
        mtx = max;
        mti = n-1;
    }
    else if(isUp == true && isDown == true){
        mtx = max;
        mti = pos;
    }
    else{
        mtx = -2;
        mti = -3;
    }
}
void changeArr(int *arr, int n, int &maxi2, int &mini2){
    int arr2[n+1];
    int temp;
    for(int i = 0; i  < n; i++){
        temp = arr[i];
        if(temp < 0) temp = -temp;
        arr2[i] = (17 * temp + 9) % 257;
    }
    arr2[n] = '\0';
    maxi2 = maxi(arr2, n, 0);
    mini2 = mini(arr2, n, 0);
}
void findMax2(int *arr, int n, int &max2_3x, int &max2_3i){
    int a = n;
    if(n > 3) a = 3;
    int arr2[a+1];
    int temp;
    for(int i = 0; i < a;i++)
    {
        temp = arr[i];
        if(temp < 0) temp = -temp;
        arr2[i] = ( 17 *  temp + 9 ) % 257;
    }
    int maxi1 = maxi(arr2, a, 0);
    int max1 = arr2[0];
    for(int i = 0; i < n && i < 3; i++){
        if(max1 < arr2[i]) max1 = arr2[i];
    }
    max2_3x = 0;
    max2_3i = maxi1;
    for (int i = 0; i < n && i < 3; i++){
        if(max2_3x < arr2[i] && i != maxi1 && arr2[i] != max1){
            max2_3x = arr2[i];
            max2_3i = i;
        }
    }
    if(n <= 1 || (max2_3i == maxi1) || (max1 == max2_3x)){
        max2_3x = -5;
        max2_3i = -7;
    } 
}
void MushGhost(struct Player &p, string file_mush_ghost, int event, int &rescue){
    // Đọc thông tin của chuỗi 13 <ms>
    string nEvents = to_string(event);
    int size = nEvents.length() - 2;
    char mushGhost[size + 1];
    for(int i = 0; i < size;i++){
        mushGhost[i] = nEvents[i+2];
    }
    
    // Đọc file
    int n;
    string line1, line2;
    ifstream file(file_mush_ghost);
    getline(file, line1, '\n');
    getline(file, line2, '\n');

    // Lấy sự kiện line1, sau đó tạo mảng chứa thông tin của chuỗi mushghost
    stringstream ss(line1);
    ss >> n;
    int arr[n+1];
    int index = 0;
    string mush;
    stringstream ss1(line2);
    while(getline(ss1, mush, ',')){
        stringstream ss2(mush);
        ss2 >> arr[index];
        index++;
    }
    // Thao tác với từng sự kiện
    for(int i = 0; i < size; i++){
        if(mushGhost[i] == '1'){
            getdmg(p, maxi(arr, index, 1) + mini(arr, index, 1), rescue);
        }
        else if(mushGhost[i] == '2'){
            int mtx, mti;
            Mountain(arr, n, mtx, mti);
            getdmg(p, mtx + mti, rescue);
        }
        else if(mushGhost[i] == '3'){
            int maxi2, mini2;
            changeArr(arr, n, maxi2, mini2);
            getdmg(p, maxi2 + mini2, rescue);
        }
        else if(mushGhost[i] == '4'){
            int max2_3x, max2_3i;
            findMax2(arr, n, max2_3x, max2_3i);
            getdmg(p, max2_3x + max2_3i, rescue);
        }
        if(rescue == 0) break;
    }

}
void pickupphoenixdown(struct Player &p){
    if(p.phoenixdown < 99) p.phoenixdown += 1;
}
void pickupRemedy(struct Player &p){
    if(p.tini  > 0){
        p.tini = 0;
        p.HP *= 5;
        if(p.HP > p.maxHP) p.HP = p.maxHP;
    }
    else {
        if(p.remedy < 99) p.remedy += 1;
    }
}
void pickupMaidenkiss(struct Player &p){
    if(p.frog  > 0){
        p.frog = 0;
        p.level = p.templvl;
    }
    else {
        if(p.maidenkiss < 99) p.maidenkiss += 1;
    }
}
bool is3HP(string temp){
    if(temp.length() < 6) return false;
    int n = temp.length();
    for(int i = 0; i < n; i++){
        if((temp[i] == 'M' || temp[i] == 'm') && temp[i+1] == 'e' && temp[i+2] == 'r' && temp[i+3] == 'l' && temp[i+4] == 'i' && temp[i+5] == 'n')
        return true;
    }
    return false;
}
bool is2HP(string temp){
        int len = temp.length();
        int m = 0, e = 0, r = 0, l = 0, i = 0, n = 0;
        for(int j =0; j < len;j++){
            if(temp[j] == 'm' || temp[j] =='M') m++;
            if(temp[j] == 'e' || temp[j] =='E') e++;
            if(temp[j] == 'r' || temp[j] =='R') r++;
            if(temp[j] == 'l' || temp[j] =='L') l++;
            if(temp[j] == 'i' || temp[j] =='I') i++;
            if(temp[j] == 'n' || temp[j] =='N') n++;
        }
        return (m>0 && e>0 && r>0 && l>0 && i>0 && n>0) ;
}
void merlin(struct Player &p, string file_merlin_pack){
    if(p.meetMerlin == false){
        p.meetMerlin = true;

    int n;
    string temp;
    int index = 0;
    ifstream file;
    file.open(file_merlin_pack);
    file >> n;
    string s[n+1];
    getline(file, temp);
    while(getline(file, temp,'\n')){
        s[index] = temp;
        index++;
    }
    file.close();
    for(int i = 0; i < n;i++){
        if(is3HP(s[i])) p.HP += 3;
        else{
            if(is2HP(s[i])) p.HP += 2;
        }
        if(p.HP > p.maxHP) p.HP = p.maxHP;
    }
    }
}
void asclepius(struct Player &p, string fileName){
    int a, b;
    ifstream file(fileName);
    file >> a >> b;
    int arr[a][b];
    for(int i = 0; i < a; i++){
        for(int j = 0; j < b; j++){
            file >> arr[i][j];
        }
    }
    for(int i = 0; i < a; i++){
        int pick = 0;
        for(int j = 0; j < b; j++){
            if(arr[i][j] == 16){
                pickupRemedy(p);
                pick++;
            }
            else if(arr[i][j] == 17){
                pickupMaidenkiss(p);
                pick++;
            }
            else if(arr[i][j] == 18){
                pickupphoenixdown(p);
                pick++;
            }
            if(pick >= 3) break;
        }
    }
}
void Bowser(struct Player &p, int event, int &rescue){
    if(p.Arthur || p.Lancelot && p.level > 8 || p.level > 10) p.level = 10;
    else rescue = 0;
}
void display(struct Player p, int rescue) {
    cout << "HP=" << p.HP
        << ", level=" << p.level
        << ", remedy=" << p.remedy
        << ", maidenkiss=" << p.maidenkiss
        << ", phoenixdown=" << p.phoenixdown
        << ", rescue=" << rescue << endl;
}
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    rescue = -1;
    string line1, line2, line3;
    ifstream myfile(file_input);
    getline(myfile, line1, '\n');
    getline(myfile, line2, '\n');
    getline(myfile, line3, '\n');
    string mush_ghost_pack ="";
    string asclepius_pack_path = "";
    string merlin_pack = "";

    // Lấy dữ liệu của knight
    struct Player player = getValue(line1); 

    // Lấy dữ liệu của từng sự kiện
    int a;
    int events[100], nEvents = 0, index = 0;
    stringstream ss(line2);
    while(ss >> a){
        events[index] = a;
        index++;
        nEvents++;
    };
    
    // Lấy dữ liệu các sự kiện đặc biệt
    int n = 0, b = 0;
    while(line3[n] != '\0'){
        if(line3[n] == ',') b++;
        else{
            if(b == 0) mush_ghost_pack += line3[n];
            else if(b == 1) asclepius_pack_path += line3[n];
            else merlin_pack += line3[n];
        }
        n++;
    }

    int i = 0;
    while(true)
    {
        if(events[i] == 0)
        {
            rescue = 1;
            display(player, rescue);
            break;
        }
        else
        {
            if(events[i] > 0 && events[i] <= 5) {fight(player, events[i], i, rescue);}
            else if(events[i] == 6) shaMan(player, i, rescue);
            else if(events[i] == 7) SirenVajsh(player, i, rescue);
            else if(events[i] == 11) MushMario(player);
            else if(events[i] == 12) MushFibo(player);
            else if(events[i] == 13 || events[i] >= 131) MushGhost(player, mush_ghost_pack, events[i], rescue);
            else if(events[i] == 15) pickupRemedy(player);
            else if(events[i] == 16) pickupMaidenkiss(player);
            else if(events[i] == 17) pickupphoenixdown(player);
            else if(events[i] == 18) merlin(player, merlin_pack);
            
            else if(events[i] == 19){
            if(player.meetAsclepius == false){
                player.meetAsclepius = true;
                asclepius(player, asclepius_pack_path);
                }
            }
            else if(events[i] == 99) Bowser(player,events[i], rescue);

            if(player.tini > 0){
                player.tini -= 1;
                if(player.tini == 0 && rescue != 0){
                    player.HP*=5;
                    if(player.HP > player.maxHP) player.HP = player.maxHP;
                }
            }
            if(player.frog > 0){
                player.frog -= 1;
                if(player.frog == 0 && rescue != 0){
                    player.level = player.templvl;
                }
            }
            
            if(rescue == 0){
                display(player, rescue);
                break;
            }
            if(i == nEvents -1 ){
                rescue = 1; 
                display(player, rescue);
                break;
            } 
            display(player, rescue);
        }
        i++;
    }
}