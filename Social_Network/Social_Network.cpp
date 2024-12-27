#include<bits/stdc++.h>
using namespace std;

typedef struct _User{
    long long userID;
    string userName;
    int userAge;
    string userEmail;
    string password;

}User;

//====================================================================//

int getID(string yourEmail);
string getTime();

void sendNotification(string receiverEmail, string content){
    ofstream ofs_N;
    ofs_N.open("Notification\\" + to_string(getID(receiverEmail)) + ".txt", ios::out | ios::app);
    ofs_N << getTime();
    ofs_N << content << endl;
    ofs_N << "---" << endl;
    ofs_N.close();
}

bool isFileExist(string filename){
    ifstream ifs;
    ifs.open(filename, ios::in);
    return ifs.is_open();
}

bool isFileEmpty(string filename){
    ifstream ifs;
    ifs.open(filename, ios::in | ios::ate); //Doc file va di chuyen con tro den cuoi file

    if(!ifs.is_open()){
        cout << "File khong ton tai!";
        exit(0);
    }

    if(ifs.tellg() == 0){ //Neu vi tri con tro doc nam tai dau file
        ifs.close();
        return true;
    }
    else{
        ifs.close();
        return false;
    }
}

int getNum(string filename){
    int num; //So luong

    ifstream ifs_N;
    ifs_N.open(filename, ios::in);

    if(!ifs_N.is_open()){
        cout << "File khong ton tai!";
        exit(0);
    }

    if(isFileEmpty(filename))
        num = 0;
    else
        ifs_N >> num; //Lay so luong tu file va luu vao bien num

    ifs_N.close();
    return num;
}

bool isEmailExist(string email){
    if(getID(email) == -1)
        return false;
    else return true;
}

bool isCorrectLoginInfo(string email, string pass){
    int ID = getID(email);
    if(ID == -1) //Email khong ton tai
        return false;
    else{
        ifstream ifs;
        ifs.open("Users\\" + to_string(ID) + ".txt", ios::in);

        int userID, userAge;
        string userName, userEmail, password;

        ifs >> userID;
        ifs.ignore();
        getline(ifs, userName);
        ifs >> userAge;
        ifs.ignore();
        getline(ifs, userEmail);
        getline(ifs, password);

        ifs.close();

        if(password == pass) //Mat khau dung
            return true;
        else return false;
    }
}

void handling_invalid_input_exceptions(int &input_int){
    while (!(cin >> input_int)){
        cin.clear(); // Xóa cờ lỗi của cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Bỏ qua các ký tự còn lại trong dòng
        cout << "ERROR! Vui long nhap lai: ";
    }
}

void choice(int &option, int number_of_option){
    while(true){
        handling_invalid_input_exceptions(option); //Xu ly ngoai le khi nhap option
        cin.ignore();
        if(option >= 1 && option <= number_of_option)
            break;
        else
            cout << "ERROR--Vui long nhap lai: ";
    }
}

//====================================================================//

vector<User> getUserList(){
    vector<User> userList;

    int numAcc = getNum("Number_of_Accounts.txt"); //So luong tai khoan

    for(int i = 1; i <= numAcc; i++){
        ifstream ifs;
        ifs.open("Users\\" + to_string(i) + ".txt", ios::in);

        User user;
        ifs >> user.userID;
        ifs.ignore();
        getline(ifs, user.userName);
        ifs >> user.userAge;
        ifs.ignore();

        getline(ifs, user.userEmail);
        getline(ifs, user.password);

        userList.push_back(user);

        ifs.close();
    }

    return userList;
}

User getUser(string yourEmail){
    User user;
    ifstream ifs;
    ifs.open("Users\\" + to_string(getID(yourEmail)) + ".txt", ios::in);

    ifs >> user.userID;
    ifs.ignore();
    getline(ifs, user.userName);
    ifs >> user.userAge;
    ifs.ignore();
    getline(ifs, user.userEmail);
    getline(ifs, user.password);

    ifs.close();
    return user;
}

void saveUserChanges(User user){
    ofstream ofs;
    ofs.open("Users\\" + to_string(user.userID) + ".txt", ios::out);
    ofs << user.userID << endl;
    ofs << user.userName << endl;
    ofs << user.userAge << endl;
    ofs << user.userEmail << endl;
    ofs << user.password << endl;
    ofs.close();
}

map<string, vector<string>> getList(string filename){
    map<string, vector<string>> List; //<yourEmal, yourList>

    int numAcc = getNum("Number_of_Accounts.txt");
    for(int i = 0; i <= numAcc; i++){
        string yourEmail, line; //line luu tung du lieu trong yourList
        vector<string> yourList;

        ifstream ifs;
        ifs.open(filename + "\\" + to_string(i) + ".txt", ios::in);

        getline(ifs, yourEmail);

        while(getline(ifs, line))
            yourList.push_back(line);

        List.insert({yourEmail, yourList});
    }
    return List;
}

vector<string> getYourList(string yourEmail, string filename){
    string email, line;
    vector<string> yourList;

    ifstream ifs;
    ifs.open(filename + "\\" + to_string(getID(yourEmail)) + ".txt", ios::in);

    getline(ifs, email);
    while(getline(ifs, line))
        yourList.push_back(line);

    ifs.close();
    return yourList;
}

void saveYourListChanges(string yourEmail, vector<string> yourList, string filename){
    ofstream ofs;
    ofs.open(filename + "\\" + to_string(getID(yourEmail)) + ".txt", ios::out);

    ofs << yourEmail << endl;
    for(string str : yourList)
        ofs << str << endl;

    ofs.close();
}

//====================================================================//

int getID(string yourEmail){
    string name, email;
    int ID, age;

    int numAcc = getNum("Number_of_Accounts.txt"); //So luong tai khoan

    for(int i = 1; i <= numAcc; i++){
        ifstream ifs;
        ifs.open("Users\\" + to_string(i) + ".txt", ios::in);

        ifs >> ID;
        ifs.ignore();
        getline(ifs, name);
        ifs >> age;
        ifs.ignore();

        getline(ifs, email);
        if(email == yourEmail)
            return ID;

        ifs.close();
    }

    return -1; //Neu email khong ton tai
}

string getName(string yourEmail){
    ifstream ifs;
    ifs.open("Users\\" + to_string(getID(yourEmail)) + ".txt", ios::in); //Mở file ở chế độ đọc

    int userID;
    string userName;

    ifs >> userID;
    ifs.ignore();
    getline(ifs, userName);

    ifs.close();
    return userName;
}

string getTime(){
    time_t timestamp = time(nullptr);
    return ctime(&timestamp);
}

//====================================================================//

void addHobbie(string yourEmail);
void searchHobbie(string yourEmail);
void deleteHobbie(string yourEmail);
void displayMenu(string yourEmail);

vector<string> getListOfAvailablePreferences(){
    vector<string> List_of_available_preferences;
    ifstream ifs;
    ifs.open("List_of_available_preferences.txt", ios::in);

    string line; //Doc tung line
    while(getline(ifs, line)){
        List_of_available_preferences.push_back(line);
    }

    ifs.close();
    return List_of_available_preferences;
}

void updateListOfAvailablePreferences(vector<string> newHobbieList){
    ofstream ofs;
    ofs.open("List_of_available_preferences.txt", ios::out | ios::app);
    for(string hobbie : newHobbieList)
        ofs << hobbie << endl;

    ofs.close();
}

bool isHobbieExist(string yourEmail, string hobbie){
    vector<string> yourHobbieList = getYourList(yourEmail, "Hobbies");

    if(find(yourHobbieList.begin(), yourHobbieList.end(), hobbie) != yourHobbieList.end())
        return true;
    else return false;
}

void displayHobbieList(string yourEmail){
    vector<string> yourHobbieList = getYourList(yourEmail, "Hobbies");

    if(yourHobbieList.size() == 0)
        cout << "Danh sach so thich cua ban rong!" << endl;
    else{
        cout << "Danh sach so thich cua ban la:" << endl;
        int i = 1;
        for(string hobbie : yourHobbieList){
            cout << i << "." << hobbie << endl;
            i++;
        }
    }
    cout << endl;

    cout << "Tiep theo ban muon lam gi?" << endl;
    cout << "1.Tim ban theo so thich." << endl;
    cout << "2.Them so thich." << endl;
    cout << "3.Xoa so thich." << endl;
    cout << "4.Di den menu." << endl;
    cout << "5.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int option;
    choice(option, 5);

    switch(option){
    case 1:
        searchHobbie(yourEmail);
        break;
    case 2:
        addHobbie(yourEmail);
        break;
    case 3:
        deleteHobbie(yourEmail);
        break;
    case 4:
        displayMenu(yourEmail);
        break;
    case 5:
        exit(0);
        break;
    default:
        break;
    }
}

void addHobbie(string yourEmail){
    vector<string> yourHobbieList = getYourList(yourEmail, "Hobbies");
    vector<string> List_of_available_preferences = getListOfAvailablePreferences();
    int So_luong_so_thich_ban_dau = yourHobbieList.size();

    cout << "Hay chon so thich cua ban trong cac so thich sau:" << endl;
    int i = 1;
    for(string available_preferences : List_of_available_preferences){
        cout << i << "." << available_preferences << endl;
        i++;
    }
    cout << i << ".Ban co so thich khac" << endl << endl;

    bool isNewHobbie = false; //Danh dau ban co so thich moi hay khong

    cout << "Dien STT cac so thich cua ban (Ket thuc boi 0): ";

    int _choice;
    while(true){
        cin >> _choice;
        cin.ignore();
        if(_choice == 0)
            break;
        else if(_choice > 0 && _choice <= List_of_available_preferences.size()){
            if(!isHobbieExist(yourEmail, List_of_available_preferences[_choice - 1])) //Neu so thich chua co trong danh sach so thich cua ban
                yourHobbieList.push_back(List_of_available_preferences[_choice - 1]);
        }
        else if(_choice == i) //So thich khong co trong danh sach
            isNewHobbie = true;
    }

    if(isNewHobbie == true){ //Xu ly neu ban co so thich khong co trong danh sach
        cout << "Nhap cac so thich cua ban (ket thuc boi 'end'):" << endl;

        while(true){
            string hobbie;
            getline(cin, hobbie);
            if(hobbie == "end")
                break;
            else{
                yourHobbieList.push_back(hobbie);
                updateListOfAvailablePreferences({hobbie});
            }
        }
    }

    saveYourListChanges(yourEmail, yourHobbieList, "Hobbies");

    if(yourHobbieList.size() == So_luong_so_thich_ban_dau)
        cout << "Ban chua them so thich nao!" << endl;
    else
        cout << "Ban da them so thich thanh cong!" << endl;
    cout << endl;

    cout << "Tiep theo ban muon lam gi?" << endl;
    cout << "1.Xem danh sach so thich." << endl;
    cout << "2.Di den menu." << endl;
    cout << "3.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int option;
    choice(option, 3);

    switch(option){
    case 1:
        displayHobbieList(yourEmail);
        break;
    case 2:
        displayMenu(yourEmail);
        break;
    case 3:
        exit(0);
        break;
    default:
        break;
    }
}

void deleteHobbie(string yourEmail){
    vector<string> yourHobbieList = getYourList(yourEmail, "Hobbies");

    vector<string> list_of_hobbies_you_want_to_delete;

    cout << "\nChon STT so thich ban muon xoa (ket thuc bang 0): ";
    int _choice;
    while(true){
        cin >> _choice;
        cin.ignore();
        if(_choice == 0)
            break;
        else if(_choice > 0 && _choice <= yourHobbieList.size())
            list_of_hobbies_you_want_to_delete.push_back(yourHobbieList[_choice - 1]);

    }

    for(string hobbie_you_want_to_delete : list_of_hobbies_you_want_to_delete){
        yourHobbieList.erase(remove(yourHobbieList.begin(), yourHobbieList.end(), hobbie_you_want_to_delete), yourHobbieList.end());
    }

    if(list_of_hobbies_you_want_to_delete.size() == 0)
        cout << "Ban chua xoa so thich nao!" << endl;
    else
        cout << "Ban da xoa so thich thanh cong!" << endl;
    cout << endl;

    saveYourListChanges(yourEmail, yourHobbieList, "Hobbies");

    cout << "Tiep theo ban muon lam gi?" << endl;
    cout << "1.Xem danh sach so thich." << endl;
    cout << "2.Di den menu." << endl;
    cout << "3.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int option;
    choice(option, 3);

    switch(option){
    case 1:
        displayHobbieList(yourEmail);
        break;
    case 2:
        displayMenu(yourEmail);
        break;
    case 3:
        exit(0);
        break;
    default:
        break;
    }
}

//====================================================================//

void displayMenu(string yourEmail);
void displayFriendList(string yourEmail);
void readNotification(string yourEmail);
void searchHobbie(string yourEmail);

int So_phtu_chung_cua_2_danh_sach(string email1, string email2, string filename){
    vector<string> list1 = getYourList(email1, filename);
    vector<string> list2 = getYourList(email2, filename);

    //Dem so ban chung
    int cnt = 0;
    for(string str : list1){
        if(find(list2.begin(), list2.end(), str) != list2.end()) //Tim thay trong list2 co phtu trung voi phtu str cua list1
            cnt++;
    }

    return cnt;
}

int So_ky_tu_giong_nhau_lien_tiep_lon_nhat(string str1, string str2){
    string temp1 = str1;
    string temp2 = str2;

    //Khong quan tam chu hoa chu thuong => Chuyen tat ca ve chu thuong
    transform(temp1.begin(), temp1.end(), temp1.begin(), ::tolower);
    transform(temp2.begin(), temp2.end(), temp2.begin(), ::tolower);

    int maxx = 0; //So_ky_tu_giong_nhau_lien_tiep_lon_nhat

    for(int i = 0; i < temp1.size(); i++){ //Duyet qua tung phtu cua xau 1
        for(int j = 0; j < temp2.size(); j++){ //Duyet qua tung phtu cua xau 2
            int maxTemp = 0; //bien max tam thoi
            int index1 = i, index2 = j; //Kiem tra xau con bat dau tu cap vi tri (i, j)
            while(index1 < temp1.size() && index2 < temp2.size() && temp1[index1] == temp2[index2]){
                index1++;
                index2++;
                maxTemp++;
            }
            maxx = max(maxx, maxTemp); //Cap nhat gia tri maxx
        }
    }

    return maxx;
}

bool isFriendExist(string yourEmail, string friendEmail){
    vector<string> yourFriendList = getYourList(yourEmail, "Friends");

    if(find(yourFriendList.begin(), yourFriendList.end(), friendEmail) != yourFriendList.end())
        return true;
    else return false;
}

void enterEmail(string yourEmail){
    cout << "\nNhap email de ket ban: ";
    string friendEmail;
    getline(cin, friendEmail);

    if(!isEmailExist(friendEmail)){
        cout << "\nEmail khong ton tai!\n" << endl;
        cout << "Tiep theo ban muon lam gi?" << endl;
        cout << "1.Nhap lai email." << endl;
        cout << "2.Di den menu." << endl;
        cout << "3.Thoat khoi Social Network.\n" << endl;
        cout << "Nhap STT ban muon thuc hien: ";

        int option;
        choice(option, 3);

        switch(option){
        case 1:
            enterEmail(yourEmail);
            break;
        case 2:
            displayMenu(yourEmail);
            break;
        case 3:
            exit(0);
            break;
        default:
            break;
        }
    }
    else{
        if(isFriendExist(yourEmail, friendEmail)){
            cout << "\nCac ban da la ban be!\n" << endl;
        }
        else{
            vector<string> FriendList1 = getYourList(yourEmail, "Friends");
            FriendList1.push_back(friendEmail); //Them friendEmail vao danh sach ban be cua ban
            saveYourListChanges(yourEmail, FriendList1, "Friends");

            vector<string> FriendList2 = getYourList(friendEmail, "Friends");
            FriendList2.push_back(yourEmail); //Them ban vao danh sach ban be cua friendEmail
            saveYourListChanges(friendEmail, FriendList2, "Friends");

            cout << "\nDa ket ban thanh cong!\n" << endl;

            //Thong bao den cho friendEmail
            string content = yourEmail + " da ket ban voi ban!";
            sendNotification(friendEmail, content);
        }
    }

    cout << "Tiep theo ban muon lam gi?" << endl;
    cout << "1.Xem danh sach ban be." << endl;
    cout << "2.Di den menu." << endl;
    cout << "3.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int _option;
    choice(_option, 3);

    switch(_option){
    case 1:
        displayFriendList(yourEmail);
        break;
    case 2:
        displayMenu(yourEmail);
        break;
    case 3:
        exit(0);
        break;
    default:
        break;
    }
}

void searchName(string yourEmail){
    cout << "Nhap ten nguoi ban tim kiem: ";
    string friendName;
    getline(cin, friendName);

    vector<User> userList = getUserList();

    //Sap xep tu dong theo thu tu khoa tang dan
    multimap<int, User> mm; //<So_ky_tu_trung, user>

    //Day cac ung cu vien vao multimap
    for(User user : userList){
        int maxx = So_ky_tu_giong_nhau_lien_tiep_lon_nhat(user.userName, friendName);
        if(maxx > 1 && user.userEmail != yourEmail){
            mm.insert({maxx, user});
        }
    }

    if(mm.empty()){ //multimap rong
        cout << "\nKhong tim thay ten phu hop!\n" << endl;
        cout << "Tiep theo ban muon lam gi?" << endl;
        cout << "1.Nhap lai ten can tim kiem." << endl;
        cout << "2.Tim kiem theo so thich." << endl;
        cout << "3.Khong ket ban nua." << endl;
        cout << "4.Thoat khoi Social Network.\n" << endl;
        cout << "Nhap STT ban muon thuc hien: ";

        int option;
        choice(option, 4);

        switch(option){
        case 1:
            searchName(yourEmail);
            break;
        case 2:
            searchHobbie(yourEmail);
            break;
        case 4:
            displayMenu(yourEmail);
            break;
        case 3:
            exit(0);
            break;
        default:
            break;
        }
    }
    else{
        cout << "\nKet qua tim kiem:\n" << endl;
        //Dao nguoc multimap => Dua userName co nhieu ky tu trung voi friendName len tren
        int cnt = 1;
        auto it = mm.rbegin();
        while(it != mm.rend() && cnt <= 10){ //Gioi han in ra nhieu nhat 10 nguoi
            cout << "Name: " << (it->second).userName << endl;
            cout << "Age: " << (it->second).userAge << endl;
            cout << "Email: " << (it->second).userEmail << endl;

            cout << "So thich: ";
            vector<string> yourHobbieList = getYourList((it->second).userEmail, "Hobbies");
            for(string hobbie : yourHobbieList)
                cout << hobbie << ", ";
            cout << endl << endl;

            it++;
            cnt++;
        }

        cout << "Tiep theo ban muon lam gi?" << endl;
        cout << "1.Tim kiem theo so thich." << endl;
        cout << "2.Nhap email de ket ban." << endl;
        cout << "3.Khong ket ban nua." << endl;
        cout << "4.Thoat khoi Social Network.\n" << endl;
        cout << "Nhap STT ban muon thuc hien: ";

        int option;
        choice(option, 4);

        switch(option){
        case 1:
            searchHobbie(yourEmail);
            break;
        case 2:
            enterEmail(yourEmail);
            break;
        case 3:
            displayMenu(yourEmail);
            break;
        case 4:
            exit(0);
            break;
        default:
            break;
        }
    }
}

void searchHobbie(string yourEmail){
    vector<User> userList = getUserList();

    //Sap xep tu dong theo thu tu khoa tang dan
    multimap<int, User> mm; //<So_ky_tu_trung, user>

    for(User user : userList){
        int number_of_common_hobbie = So_phtu_chung_cua_2_danh_sach(yourEmail, user.userEmail, "Hobbies");
        if(number_of_common_hobbie > 0){
            if(user.userEmail != yourEmail)
                mm.insert({number_of_common_hobbie, user});
        }
    }

    if(mm.empty()){ //multimap rong
        cout << "Khong ai co so thich giong ban!" << endl;
        cout << "Tiep theo ban muon lam gi?" << endl;
        cout << "1.Them so thich de de dang tim kiem." << endl;
        cout << "2.Tim kiem theo ten." << endl;
        cout << "3.Khong ket ban nua." << endl;
        cout << "4.Thoat khoi Social Network.\n" << endl;
        cout << "Nhap STT ban muon thuc hien: ";

        int option;
        choice(option, 4);

        switch(option){
        case 1:
            addHobbie(yourEmail);
            break;
        case 2:
            searchName(yourEmail);
            break;
        case 3:
            displayMenu(yourEmail);
            break;
        case 4:
            exit(0);
            break;
        default:
            break;
        }
    }
    else{
        cout << "\nKet qua tim kiem:\n" << endl;
        //Dao nguoc multimap => Dua userName co nhieu so thich chung len tren
        int cnt = 1;
        auto it = mm.rbegin();
        while(it != mm.rend() && cnt <= 10){ //Gioi han in ra nhieu nhat 10 nguoi
            cout << "Name: " << (it->second).userName << endl;
            cout << "Age: " << (it->second).userAge << endl;
            cout << "Email: " << (it->second).userEmail << endl;

            cout << "So thich: ";
            vector<string> yourHobbieList = getYourList((it->second).userEmail, "Hobbies");
            for(string hobbie : yourHobbieList)
                cout << hobbie << ", ";
            cout << endl << endl;

            it++;
            cnt++;
        }

        cout << "Tiep theo ban muon lam gi?" << endl;
        cout << "1.Tim kiem theo ten." << endl;
        cout << "2.Nhap email de ket ban." << endl;
        cout << "3.Khong ket ban nua." << endl;
        cout << "4.Thoat khoi Social Network.\n" << endl;
        cout << "Nhap STT ban muon thuc hien: ";

        int option;
        choice(option, 4);

        switch(option){
        case 1:
            searchName(yourEmail);
            break;
        case 2:
            enterEmail(yourEmail);
            break;
        case 3:
            displayMenu(yourEmail);
            break;
        case 4:
            exit(0);
            break;
        default:
            break;
        }
    }
}

int numberOfFriends(string yourEmail){
    vector<string> yourFriendList = getYourList(yourEmail, "Friends");
    return yourFriendList.size();
}

multimap<int, string> Danh_sach_Users_sap_xep_theo_So_ban(){
    multimap<int, string> Danh_sach_Users_sap_xep_theo_So_ban;
    int numAcc = getNum("Number_of_Accounts.txt");

    for(int i = 1; i <= numAcc; i++){
        ifstream ifs;
        ifs.open("Friends\\" + to_string(i) + ".txt", ios::in);
        string email;
        getline(ifs, email);
        ifs.close();

        Danh_sach_Users_sap_xep_theo_So_ban.insert({numberOfFriends(email), email});
    }

    return Danh_sach_Users_sap_xep_theo_So_ban;
}

void display_Danh_sach_Users_sap_xep_theo_So_ban(string yourEmail){
    multimap<int, string> Danh_sach = Danh_sach_Users_sap_xep_theo_So_ban();

    int cnt = 1;
    auto it = Danh_sach.rbegin();
    while(it != Danh_sach.rend() && cnt <= 10){ //Gioi han in ra nhieu nhat 10 nguoi
        cout << (*it).second << endl;
        cout << "So ban: " << (*it).first << endl << endl;
        cnt++;
        it++;
    }

    cout << "Tiep theo ban muon lam gi?" << endl;
    cout << "1.Nhap email de ket ban." << endl;
    cout << "2.Tim kiem theo ten." << endl;
    cout << "3.Tim kiem theo so thich." << endl;
    cout << "4.Khong ket ban nua." << endl;
    cout << "5.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int option;
    choice(option, 5);

    switch(option){
    case 1:
        enterEmail(yourEmail);
        break;
    case 2:
        searchName(yourEmail);
        break;
    case 3:
        searchHobbie(yourEmail);
        break;
    case 4:
        displayMenu(yourEmail);
    case 5:
        exit(0);
        break;
    default:
        break;
    }
}

void addFriend(string yourEmail){
    cout << "1.Nhap email de ket ban." << endl;
    cout << "2.Tim kiem theo ten." << endl;
    cout << "3.Tim kiem theo so thich." << endl;
    cout << "4.Tim kiem nhung nguoi co nhieu ban nhat." << endl;
    cout << "5.Khong ket ban nua.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int option;
    choice(option, 5);

    switch(option){
    case 1:
        enterEmail(yourEmail);
        break;
    case 2:
        searchName(yourEmail);
        break;
    case 3:
        searchHobbie(yourEmail);
        break;
    case 4:
        display_Danh_sach_Users_sap_xep_theo_So_ban(yourEmail);
        break;
    case 5:
        displayMenu(yourEmail);
        break;
    default:
        break;
    }
}

void delete_a_friend(string yourEmail){
    cout << "Nhap email nguoi ban muon xoa ket ban: ";
    string friendEmail;
    getline(cin, friendEmail);

    vector<string> FriendList1 = getYourList(yourEmail, "Friends"); //Lay danh sach ban be cua ban
    vector<string> FriendList2 = getYourList(friendEmail, "Friends");//Lay danh sach ban be cua friendEmail

    if(find(FriendList1.begin(), FriendList1.end(), friendEmail) == FriendList1.end())
                cout << "Cac ban chua ket ban!" << endl;
    else{
        //Xoa friendEmail ra khoi danh sach ban be cua yourEmail
        FriendList1.erase(remove(FriendList1.begin(), FriendList1.end(), friendEmail), FriendList1.end());
        cout << "Da xoa thanh cong!\n" << endl;

        //Xoa yourEmail ra khoi danh sach ban be cua friendEmail
        FriendList2.erase(remove(FriendList2.begin(), FriendList2.end(), yourEmail), FriendList2.end());
        string content = yourEmail + " da xoa ket ban voi ban!";
        sendNotification(friendEmail, content);

        saveYourListChanges(yourEmail, FriendList1, "Friends");
        saveYourListChanges(friendEmail, FriendList2, "Friends");
    }
}

void delete_all_friend(string yourEmail){
    map<string, vector<string>> FriendList = getList("Friends");

    //Gui thong bao den tung nguoi
    for(string friendEmail : FriendList[yourEmail]){
        string content = yourEmail + " da xoa ket ban voi ban!";
        sendNotification(friendEmail, content);

        //Xoa yourEmail ra khoi danh sach ban be cua friendEmail
        FriendList[friendEmail].erase(remove(FriendList[friendEmail].begin(), FriendList[friendEmail].end(), yourEmail), FriendList[friendEmail].end());
        saveYourListChanges(friendEmail, FriendList[friendEmail], "Friends");
    }

    saveYourListChanges(yourEmail, {}, "Friends"); //Danh sach ban be cua ban trong rong

    cout << "Da xoa toan bo ban be!\n" << endl;
}

void deleteFriend(string yourEmail){
    cout << "1.Khong xoa ban." << endl;
    cout << "2.Xoa 1 ban." << endl;
    cout << "3.Xoa tat ca ban be.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int _option;
    choice(_option, 3);

    switch(_option){
    case 2:
        delete_a_friend(yourEmail);
        break;
    case 3:
        delete_all_friend(yourEmail);
        break;
    default:
        break;
    }

    cout << "Tiep theo ban muon lam gi?" << endl;
    cout << "1.Xem danh sach ban be." << endl;
    cout << "2.Di den menu." << endl;
    cout << "3.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int option;
    choice(option, 3);

    switch(option){
    case 1:
        displayFriendList(yourEmail);
        break;
    case 2:
        displayMenu(yourEmail);
        break;
    case 3:
        exit(0);
        break;
    default:
        break;
    }
}

void displayFriendList(string yourEmail){
    vector<User> userList = getUserList();
    vector<string> FriendList = getYourList(yourEmail, "Friends"); //<yourEmail, friendList>

    int numberOfYourFriend = numberOfFriends(yourEmail);
    if(numberOfYourFriend == 0)
        cout << "\nBan khong co ban!\n" << endl;
    else{
        cout << "\nSo ban be cua ban la: " << numberOfYourFriend << endl << endl;
        cout << "Danh sach ban be cua ban la: " << endl;

        for(string friendEmail : FriendList){ //Duyet qua tat ca ban be cua ban
            cout << "Name: " << getName(friendEmail) << endl;
            cout << "Email: " << friendEmail << endl;
            cout << "So ban chung: " << So_phtu_chung_cua_2_danh_sach(yourEmail, friendEmail, "Friends") << endl << endl;
        }
    }

    cout << "Tiep theo ban muon lam gi?" << endl;
    cout << "1.Di den menu." << endl;
    cout << "2.Them ban." << endl;
    cout << "3.Xoa ban." << endl;
    cout << "4.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int _option;
    choice(_option, 4);

    switch(_option){
    case 1:
        displayMenu(yourEmail);
        break;
    case 2:
        addFriend(yourEmail);
    case 3:
        deleteFriend(yourEmail);
        break;
    case 4:
        exit(0);
        break;
    default:
        break;
    }
}

//====================================================================//

void readNotification(string yourEmail);

string getEmail(){
    string email;
    getline(cin, email);
    if(isEmailExist(email))
        return email;
    else{
        cout << "\nEMAIL KHONG TON TAI!" << endl;
        cout << "Vui long nhap lai email: ";
        getEmail();
    }
}

void sendMessage(string senderEmail, string receiverEmail){
    if(receiverEmail == ""){ //Neu chua xac dinh duoc nguoi nhan
        cout << "Nhap email nguoi nhan: ";
        string rEmail = getEmail();
        receiverEmail = rEmail;
    }

    vector<string> massages;
    cout << "\nNhap noi dung tin nhan (Ket thuc bang 'send'):" << endl;
    string line;
    do{
        getline(cin, line);
        massages.push_back(line);
    }while(line != "send");

    string filename_s_r = "Messages\\" + to_string(getID(senderEmail)) + "_" + to_string(getID(receiverEmail)) + ".txt";
    string filename_r_s = "Messages\\" + to_string(getID(receiverEmail)) + "_" + to_string(getID(senderEmail)) + ".txt";
    string filename;

    if(!isFileExist(filename_s_r) && isFileExist(filename_r_s))
        filename = filename_r_s;
    else
        filename = filename_s_r;

    ofstream ofs;
    ofs.open(filename, ios::out | ios::app);

    //Tin nhan moi
    vector<string> _message; //Doc tin nhan cu de tim "<new message>"
    ifstream ifs;
    string _line;
    ifs.open(filename, ios::in);
    while(getline(ifs, _line))
        _message.push_back(_line);
    if(count(_message.begin(), _message.end(), "<new message>") == 0) //Neu chua co tin nhan moi
        ofs << "<new message>\n" << endl;
    ifs.close();

    ofs << getTime();
    ofs << "Message sent by " << getName(senderEmail) << ":" << endl;
    for(string x : massages){
        if(x != "send")
            ofs << x << endl;
    }
    ofs << "---" << endl;

    cout << "Gui tin nhan thanh cong!" << endl;

    ofs.close();

    //Thong bao den cho nguoi nhan
    string content = "Ban nhan duoc tin nhan tu Email: " + senderEmail;
    sendNotification(receiverEmail, content);

    cout << "Tiep theo ban muon lam gi?" << endl;
    cout << "1.Xem thong bao." << endl;
    cout << "2.Gui tiep tin nhan cho " + getName(receiverEmail) + "." << endl;
    cout << "3.Gui tin nhan cho nguoi khac." << endl;
    cout << "4.Di den menu." << endl;
    cout << "5.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int _option;
    choice(_option, 5);

    switch(_option){
    case 1:
        readNotification(senderEmail);
        break;
    case 2:
        sendMessage(senderEmail, receiverEmail);
        break;
    case 3:
        sendMessage(senderEmail, "");
        break;
    case 4:
        displayMenu(senderEmail);
        break;
    case 5:
        exit(0);
        break;
    default:
        break;
    }
}

void readMessage(string readerEmail, string senderEmail){
    if(senderEmail == ""){
        do{
            cout << "Nhap email nguoi gui tin nhan: ";
            getline(cin, senderEmail);
            if(!isEmailExist(senderEmail)){
                cout << "Email khong ton tai!" << endl;
                cout << "Vui long nhap lai email!" << endl;
            }
        }while(!isEmailExist(senderEmail));
    }

    string filename_s_r = "Messages\\" + to_string(getID(senderEmail)) + "_" + to_string(getID(readerEmail)) + ".txt";
    string filename_r_s = "Messages\\" + to_string(getID(readerEmail)) + "_" + to_string(getID(senderEmail)) + ".txt";
    string filename;

    if(!isFileExist(filename_s_r) && isFileExist(filename_r_s))
        filename = filename_r_s;
    else
        filename = filename_s_r;

    vector<string> _message; //Luu tin nhan khong chua "<new message>"

    cout << endl;

    if(isFileEmpty(filename) || !isFileExist(filename))
        cout << "Tin nhan da bi xoa hoac cac ban chua tung nhan cho nhau!\n" << endl;
    else{
        ifstream ifs;
        ifs.open(filename, ios::in);
        string line;
        while(getline(ifs, line)){ //Doc tung dong trong file
            if(line != "<new message>")
                _message.push_back(line);

            if(line == "---")
                cout << endl;
            else
                cout << line << endl;
        }
        ifs.close();

        string content = "Tin nhan cua ban da duoc doc boi Email: " + readerEmail;
        sendNotification(senderEmail, content);
    }

    ofstream ofs;
    ofs.open(filename, ios::out);
    for(string line : _message)
        ofs << line << endl;
    ofs.close();

    cout << "Tiep theo ban muon lam gi?" << endl;
    cout << "1.Gui tin nhan cho " << getName(senderEmail) << "." << endl;
    cout << "2.Xoa toan bo tin nhan." << endl;
    cout << "3.Di den menu." << endl;
    cout << "4.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int option;
    choice(option, 4);

    switch(option){
    case 1:
        sendMessage(readerEmail, senderEmail);
        break;
    case 2:
        {
        ofstream ofs;
        ofs.open(filename, ios::out);
        ofs.close();
        cout << "Da xoa toan bo tin nhan!" << endl;

        string content = "Toan bo tin nhan giua ban va " + getName(readerEmail) + " da bi xoa!";
        sendNotification(senderEmail, content);

        displayMenu(readerEmail);
        }
        break;
    case 3:
        displayMenu(readerEmail);
        break;
    case 4:
        exit(0);
        break;
    default:
        break;
    }
}

void readNotification(string yourEmail){
    int yourID = getID(yourEmail);

    string filename_N = "Notification\\" + to_string(yourID) + ".txt";
    if(isFileEmpty(filename_N))
        cout << "Ban khong co thong bao nao!\n" << endl;
    else{
        ifstream ifs_N;
        ifs_N.open(filename_N, ios::in);

        string line;
        while(getline(ifs_N, line)){
            cout << line << endl;
        }
        cout << endl;
        ifs_N.close();
    }

    cout << "Tiep theo ban muon lam gi?" << endl;
    cout << "1.Doc tin nhan." << endl;
    cout << "2.Xoa toan bo thong bao." << endl;
    cout << "3.Di den menu." << endl;
    cout << "4.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int option;
    choice(option, 4);

    switch(option){
    case 1:
        readMessage(yourEmail, "");
        break;
    case 2:
        {
            ofstream ofs;
            ofs.open(filename_N, ios::out);
            ofs.close();
            cout << "Da xoa toan bo thong bao!" << endl;

            displayMenu(yourEmail);
        }
        break;
    case 3:
        displayMenu(yourEmail);
        break;
    case 4:
        exit(0);
        break;
    default:
        break;
    }
}

//====================================================================//

void logInAccount();
void personalInformation(string yourEmail);

void displayMenu(string yourEmail){
    cout << "\n==== MENU ====" << endl;
    cout << "1.Xem thong tin ca nhan." << endl;
    cout << "2.Xem danh sach ban be." << endl;
    cout << "3.Gui tin nhan." << endl;
    cout << "4.Xem thong bao." << endl;
    cout << "5.Danh sach so thich." << endl;
    cout << "6.Dang xuat khoi tai khoan." << endl;
    cout << "7.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int option;
    choice(option, 7);

    switch(option){
    case 1:
        personalInformation(yourEmail);
        break;
    case 2:
        displayFriendList(yourEmail);
        break;
    case 3:
        sendMessage(yourEmail, "");
        break;
    case 4:
        readNotification(yourEmail);
        break;
    case 5:
        displayHobbieList(yourEmail);
        break;
    case 6:
        logInAccount();
        break;
    case 7:
        exit(0);
        break;
    default:
        break;
    }
}

//====================================================================//

typedef struct _Group{
    int ID;
    string groupName;
    string admin;
    vector<string> members;
}Group;

vector<Group> getGroupList(){
    vector<Group> groupList;

    int numGroup = getNum("Number_of_Groups.txt");
    for(int i = 1; i <= numGroup; i++){
        Group group;

        ifstream ifs;
        ifs.open("Groups\\" + to_string(i) + ".txt", ios::in);

        ifs >> group.ID;
        ifs.ignore();
        getline(ifs, group.groupName);
        getline(ifs, group.admin);

        string member;
        while(getline(ifs, member))
            (group.members).push_back(member);

        groupList.push_back(group);

        ifs.close();
    }

    return groupList;
}

void saveGroupChanges(Group group){
    ofstream ofs;
    ofs.open("Groups\\" + to_string(group.ID) + ".txt", ios::out);

    ofs << group.ID << endl;
    ofs << group.groupName << endl;
    ofs << group.admin << endl;

    for(string member : group.members)
        ofs << member << endl;

    ofs.close();
}

void createGroup(string adminEmail){
    cout << "Nhap email nhung nguoi ban muon them vao nhom (Ket thuc bang 'end'):" << endl;
    string memberEmail;
    vector<string> memberList;
    while(true){
        getline(cin, memberEmail);
        if(memberEmail == "end")
            break;
        else{
            if(isEmailExist(memberEmail))
                memberList.push_back(memberEmail);
        }
    }

    if(memberList.size() == 0){
        cout <<  "Khong du thanh vien de tao thanh nhom!\n" << endl;
        displayMenu(adminEmail);
    }
    else{
        Group group;

        group.ID = getNum("Number_of_Groups.txt") + 1;
        ofstream ofs_NoG;
        ofs_NoG.open("Number_of_Groups.txt", ios::out);
        ofs_NoG << group.ID;
        ofs_NoG.close();

        cout << "Nhap ten nhom: ";
        getline(cin, group.groupName);

        group.admin = adminEmail;
        group.members = memberList;

        cout << "Ban da tao thanh cong nhom " << group.groupName << " voi " << memberList.size() << " thanh vien khac!" << endl;

        saveGroupChanges(group);

        displayMenu(adminEmail);
    }
}

//====================================================================//

void logInAccount();
string setName();
int setAge();
string setPassword();

string getPass(string yourEmail){
    ifstream ifs;
    ifs.open("Users\\" + to_string(getID(yourEmail)) + ".txt", ios::in);
    string name, email, pass;
    int ID, age;

    ifs >> ID;
    ifs.ignore();
    getline(ifs, name);
    ifs >> age;
    ifs.ignore();
    getline(ifs, email);
    getline(ifs, pass);

    ifs.close();
    return pass;
}

void editUserName(string yourEmail){
    cout << "Nhap ten tai khoan moi: ";
    string newName = setName();

    User user = getUser(yourEmail);
    user.userName = newName;

    saveUserChanges(user);

    cout << "\nCap nhat ten tai khoan thanh cong!\n" << endl;

    string content = "Ban da cap nhat ten tao khoan thanh cong!";
    sendNotification(yourEmail, content);

    personalInformation(yourEmail);
}

void editUserAge(string yourEmail){
    cout << "Nhap tuoi moi: ";
    int newAge = setAge();

    User user = getUser(yourEmail);
    user.userAge = newAge;

    saveUserChanges(user);

    cout << "\nCap nhat tuoi thanh cong!\n" << endl;

    string content = "Ban da cap nhat tuoi thanh cong!";
    sendNotification(yourEmail, content);

    personalInformation(yourEmail);
}

void editPassword(string yourEmail){
    cout << "Nhap mat khau hien tai: ";
    string curPass;
    while(true){
        getline(cin, curPass);
        if(curPass == getPass(yourEmail))
            break;
        else
            cout << "Mat khau sai. Vui long nhap lai: ";
    }

    cout << "Nhap mat khau moi (Toi thieu 6 ky tu): ";
    string newPass = setPassword();

    User user = getUser(yourEmail);
    user.password = newPass;

    saveUserChanges(user);

    cout << "\nCap nhat mat khau dang nhap thanh cong!\n" << endl;

    string content = "Ban da cap nhat mat khau thanh cong!";
    sendNotification(yourEmail, content);

    logInAccount();
}

void editPersonalInformation(string yourEmail){
    cout << "Ban muon chinh sua thong tin nao?" << endl;
    cout << "1.Ten tai khoan." << endl;
    cout << "2.Tuoi." << endl;
    cout << "3.Thay doi mat khau dang nhap." << endl;
    cout << "4.Khong thay doi thong tin.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int option;
    choice(option, 4);

    switch(option){
    case 1:
        editUserName(yourEmail);
        break;
    case 2:
        editUserAge(yourEmail);
        break;
    case 3:
        editPassword(yourEmail);
        break;
    case 4:
        displayMenu(yourEmail);
        break;
    default:
        break;
    }
}

void personalInformation(string yourEmail){
    User user = getUser(yourEmail);

    cout << "Name: " << user.userName << endl;
    cout << "Age: " << user.userAge << endl;
    cout << "Email: " << user.userEmail << endl;

    cout << "So thich: ";
    vector<string> yourHobbieList = getYourList(yourEmail, "Hobbies");
    for(string hobbie : yourHobbieList)
        cout << hobbie << ", ";
    cout << endl << endl;

    cout << "Tiep theo ban muon lam gi?" << endl;
    cout << "1.Chinh sua thong tin ca nhan." << endl;
    cout << "2.Di den menu." << endl;
    cout << "3.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int option;
    choice(option, 3);

    switch(option){
    case 1:
        editPersonalInformation(yourEmail);
        break;
    case 2:
        displayMenu(yourEmail);
        break;
    case 3:
        exit(0);
        break;
    default:
        break;
    }
}

//====================================================================//

void logInAccount();

string setName(){
    string name;
    while(true){
        getline(cin, name);

        string checkName = name;
        checkName.erase(remove(checkName.begin(), checkName.end(), ' '), checkName.end()); //Xoa dau cach trong name => Kiem tra xem ten co chua toan dau cach khong

        if(checkName.size() > 0)
            break;
        else{
            cout << "\nTen nguoi dung khong duoc chua toan dau space!" << endl;
            cout << "Vui long nhap lai ten nguoi dung: ";
        }
    }
    return name;
}

int setAge(){
    int age;
    while(true){
        handling_invalid_input_exceptions(age);
        cin.ignore();
        if(age > 0)
            break;
        else{
            cout << "\nTUOI KHONG HOP LE!" << endl;
            cout << "Vui long nhap lai tuoi cua ban: ";
        }
    }
    return age;
}

string setEmail(){
    string email;
    while(true){
        getline(cin, email);
        if(!isEmailExist(email))
            break;
        else{
            cout << "\nEMAIL DA TON TAI!" << endl;
            cout << "Vui long nhap lai email: ";
        }
    }
    return email;
}

string setPassword(){
    string password;
    while(true){
        getline(cin, password);
        if(password.size() >= 6)
            break;
        else{
            cout << "\nMat khau qua ngan!" << endl;
            cout << "Vui long nhap lai mat khau: ";
        }
    }
    return password;
}

void registerAccount(){
    cout << "== Dang ky tai khoan moi ==" << endl;

    User user;
    cout << "Nhap ten cua ban: ";
    user.userName = setName();

    cout << "Nhap tuoi cua ban: ";
    user.userAge = setAge();

    cout << "Nhap email dang nhap: ";
    user.userEmail = setEmail();

    cout << "Nhap mat khau dang nhap (Toi thieu 6 ky tu): ";
    user.password = setPassword();

    user.userID = getNum("Number_of_Accounts.txt") + 1;
    ofstream ofs_NoA;
    ofs_NoA.open("Number_of_Accounts.txt", ios::out);
    ofs_NoA << user.userID;
    ofs_NoA.close();

    ofstream ofs;
    ofs.open("Users\\" + to_string(user.userID) + ".txt", ios::out); // Mở file ở chế độ ghi
    ofs << user.userID << endl;
    ofs << user.userName << endl;
    ofs << user.userAge << endl;
    ofs << user.userEmail << endl;
    ofs << user.password << endl;
    ofs.close();

    ofstream ofs_FL;
    ofs_FL.open("Friends\\" + to_string(user.userID) + ".txt", ios::out);
    ofs_FL << user.userEmail << endl;
    ofs_FL.close();

    ofstream ofs_HL;
    ofs_HL.open("Hobbies\\" + to_string(user.userID) + ".txt", ios::out);
    ofs_HL << user.userEmail << endl;
    ofs_HL.close();

    cout << "\nChuc mung ban da dang ky tai khoan thanh cong\n" << endl;

    string content = "Chao mung den voi Social Network!";
    sendNotification(user.userEmail, content);

    cout << "Tiep theo ban muon lam gi?" << endl;
    cout << "1.Di den trang dang nhap." << endl;
    cout << "2.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int option;
    choice(option, 2);

    switch(option){
    case 1:
        logInAccount();
        break;
    case 2:
        exit(0);
        break;
    default:
        break;
    }

}

void logInAccount(){
    cout << "\n== Dang nhap tai khoan ==" << endl;
    string email, pass;

    cout << "Email dang nhap: ";
    getline(cin, email);
    cout << "Mat khau: ";
    getline(cin, pass);

    if(!isCorrectLoginInfo(email, pass)){
        cout << "\nEmail hoac mat khau chua dung!\n" << endl;
        cout << "Tiep theo ban muon lam gi?" << endl;
        cout << "1.Dang nhap lai." << endl;
        cout << "2.Dang ky tai khoan moi." << endl;
        cout << "3.Thoat khoi Social Network.\n" << endl;
        cout << "Nhap STT ban muon thuc hien: ";

        int option;
        choice(option, 3);

        switch(option){
        case 1:
            logInAccount();
            break;
        case 2:
            registerAccount();
            break;
        case 3:
            exit(0);
            break;
        default:
            break;
        }
    }
    else{
        cout << endl << "--Dang nhap thanh cong--" << endl << endl;
        displayMenu(email);
    }
}

void RegisterAcc_or_LoginAcc(){
    cout << "1.Dang nhap tai khoan cua ban." << endl;
    cout << "2.Dang ky tai khoan moi." << endl;
    cout << "3.Thoat khoi Social Network.\n" << endl;
    cout << "Nhap STT ban muon thuc hien: ";

    int option;
    choice(option, 3);

    switch(option){
    case 1:
        logInAccount();
        break;
    case 2:
        registerAccount();
        break;
    case 3:
        exit(0);
        break;
    default:
        break;
    }
}

//====================================================================//

int main(){
    RegisterAcc_or_LoginAcc();
}
