#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
using namespace std;

// Lớp người dùng (User)
class User {
public:
    string username;
    string password;
    set<string> friends;

    User(string uname, string pword) : username(uname), password(pword) {}

    void addFriend(const string& friendName) {
        if (friends.count(friendName) == 0) {
            friends.insert(friendName);
            cout << "Ban va " << friendName << " da thanh ban be.\n";
        } else {
            cout << friendName << " ket ban roi, forgot it?.\n";
        }
    }

    void showFriends() const {
        if (friends.empty()) {
            cout << "Chua co ban dau, tim mau len!!!\n";
        } else {
            cout << "Danh sach ban be:\n";
            for (const string& friendName : friends) {
                cout << "- " << friendName << endl;
            }
        }
    }
};

// Lớp MXH (SocialNetwork)
class SocialNetwork {
private:
    map<string, User> users;  // Lưu trữ người dùng theo username
    User* currentUser = nullptr; // Người dùng đang đăng nhập

public:
    void registerUser(const string& username, const string& password) {
        if (users.find(username) == users.end()) {
            users[username] = User(username, password);
            cout << "Dang ky thanh cong. Dang nhap ngay di nao!!!!.\n";
        } else {
            cout << "Ten da ton tai. Hay chon ten khac.\n";
        }
    }

    bool loginUser(const string& username, const string& password) {
        auto it = users.find(username);
        if (it != users.end() && it->second.password == password) {
            currentUser = &it->second;
            cout << "Chao " << username << " da quay tro lai.\n";
            return true;
        } else {
            cout << "Sai roi ni' oiiiii.\n";
            return false;
        }
    }

    void logoutUser() {
        if (currentUser) {
            cout << "Cut ra ngoai!\n";
            currentUser = nullptr;
        } else {
            cout << "La dang nhap chua vay??\n";
        }
    }

    void addFriend(const string& friendName) {
        if (!currentUser) {
            cout << "Dang nhap roi moi add chu, vo gia cu a??.\n";
            return;
        }
        if (users.find(friendName) != users.end()) {
            if (friendName != currentUser->username) {
                currentUser->addFriend(friendName);
                users[friendName].addFriend(currentUser->username);
            } else {
                cout << "Tu ki a??.\n";
            }
        } else {
            cout << "Sai roi em oi, khong co dauuu.\n";
        }
    }

    void showFriends() const {
        if (currentUser) {
            currentUser->showFriends();
        } else {
            cout << "Dang nhap di roi cho xem ?.\n";
        }
    }
};

// Lớp quản lý gì đấy mà Quỳnh Anh nói quên rồi sẽ ở đây

// Hàm chính (main)
int main() {
    SocialNetwork sn;
    int choice;

    do {
        cout << "\n=== MXH ===\n";
        cout << "1. Dang ky\n";
        cout << "2. Dang nhap\n";
        cout << "3. Log out\n";
        cout << "4. Them ban!\n";
        cout << "5. Danh sach ban be\n";
        cout << "0. Thoat\n";
        cout << "Chon di ban oi: ";
        cin >> choice;
        cin.ignore();

        string username, password, friendName;
        switch (choice) {
            case 1:
                cout << "Nhap ten dang nhap: ";
                getline(cin, username);
                cout << "Nhap mat khau: ";
                getline(cin, password);
                sn.registerUser(username, password);
                break;

            case 2:
                cout << "Ten gi, nha o dau? : ";
                getline(cin, username);
                cout << "Mat khau dau nhi? : ";
                getline(cin, password);
                sn.loginUser(username, password);
                break;

            case 3:
                sn.logoutUser();
                break;

            case 4:
                cout << "Minh dinh tim ai? : ";
                getline(cin, friendName);
                sn.addFriend(friendName);
                break;

            case 5:
                sn.showFriends();
                break;

            case 0:
                cout << "Bai bai =))))!\n";
                break;

            default:
                cout << "Muon an dam ko? Chon lai!\n";
        }
    } while (choice != 0);

    return 0;
}
