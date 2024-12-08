#include <iostream>
#include <string> 
#include <vector>
#include <iomanip>
#include <random>
#include <fstream>
#include <sstream>
using namespace std;

struct account {
    int id;
    string platform;
    string username;
    string password;
};

// function prototypes 
void AddAcc(vector<account>& accounts, int& nextId);
void ViewAcc(const vector<account>& accounts);
void SearchAcc(const vector<account>& accounts);
void UpdAcc(vector<account>& accounts);
void DelAcc(vector<account>& accounts);
string GeneratePass(int passLength);
void saveFile(const vector<account>& accounts, const string& filename);
void loadFile(vector<account>& accounts, const string& filename, int& nextId);
void ClearInput();



int main()
{
    vector<account> accounts;
    int nextId = 1;
    int choice;
    const string filename = "accounts.txt";
    loadFile(accounts, filename, nextId);

    do {
        cout << "\n\t\t\t\t\t==== Password Manager ===\n";
        cout << "\t\t\t\t\t1. Add Account\n";
        cout << "\t\t\t\t\t2. View All Your Accounts\n";
        cout << "\t\t\t\t\t3. Search Account\n";
        cout << "\t\t\t\t\t4. Update Account\n";
        cout << "\t\t\t\t\t5. Delete Account\n";
        cout << "\t\t\t\t\t6. Exit\n";
        cout << "\t\t\t\t\tEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            AddAcc(accounts, nextId);
            break;
        case 2:
            ViewAcc(accounts);
            break;
        case 3:
            SearchAcc(accounts);
            break;
        case 4:
            UpdAcc(accounts);
            break;
        case 5:
            DelAcc(accounts);
            break;
        case 6:
            saveFile(accounts, filename);
            cout << "\t\t\t\t\tThank you!\n";
            break;
        default:
            cout << "\t\t\t\t\tInvalid choice! Try again\n";
            ClearInput();
        }
    } while (choice != 6);

    return 0;
}
void AddAcc(vector<account>& accounts, int& nextId) {
    account NewAcc;
    char opt;
    NewAcc.id = nextId++;
    cout << "\t\t\t\t\tEnter platform: ";
    cin >> NewAcc.platform;
    cout << "\t\t\t\t\tEnter username: ";
    cin >> NewAcc.username;
    do {
        cout << "\t\t\Would you like us to generate a password for you? (y/n): ";
        cin >> opt;
        opt = tolower(opt);
        if (opt == 'y') {
            int passLength;
            //avoid input error 
            do {
                cout << "\t\t\t\t\tEnter desired Length: ";
                cin >> passLength;
                if (cin.fail() || passLength <= 0) {
                    cout << "\t\t\t\t\tInvalid input! Please enter a number.\n";
                    ClearInput();
                    continue;
                }
            } while (passLength <= 0 || cin.fail());
            NewAcc.password = GeneratePass(passLength);
            cout << "\t\t\t\t\tGenerated Password: " << NewAcc.password << endl;
            accounts.push_back(NewAcc);
            cout << "\t\t\t\t\tAccount Added!\n";
        }
        else if (opt == 'n') {
            cout << "\t\t\t\t\tEnter password: ";
            cin >> NewAcc.password;
            accounts.push_back(NewAcc);
            cout << "\t\t\t\t\tAccount Added!\n";
        }
        else {
            cout << "\t\t\t\t\tInvalid Input! Please type y for yes and n for no.\n";
            ClearInput();
            continue;
        }
    } while (opt != 'y' && opt != 'n');
    return;

}

void ViewAcc(const vector<account>& accounts) {
    if (accounts.empty()) {
        cout << "\t\t\t\t\tEmpty Accounts!\n";
        return;
    }

    for (const auto& acc : accounts) {
        cout << setw(20) << "ID: " << acc.id
            << setw(15) << "Platform: " << acc.platform
            << setw(20) << "Username: " << acc.username
            << setw(15) << "Password: " << acc.password << "\n";
    }
}

void SearchAcc(const vector<account>& accounts) {
    string search;
    cout << "\t\t\t\t\tEnter username/platform to search: ";
    cin >> search;

    bool found = false;
    for (const auto& acc : accounts) {
        if (acc.platform == search || acc.username == search) {
            cout << "\t\t\t" << "ID: " << acc.id << ", Platform: " << acc.platform
                << ", Username: " << acc.username << ", Password: " << acc.password << "\n";
            found = true;
        }
    }
    if (!found) {
        cout << "\t\t\t\t\tAccount not found!\n";
    }

}

void UpdAcc(vector<account>& accounts) {
    int id;
    cout << "\t\t\t\t\tEnter account ID: ";
    cin >> id;

    for (auto& acc : accounts) {
        if (acc.id == id) {
            char opt;
            cout << "\t\t\t\t\tEnter new platform: ";
            cin >> acc.platform;
            cout << "\t\t\t\t\tEnter new username: ";
            cin >> acc.username;
            //avoid input error
            do {
                cout << "\t\t\tWould you like us to generate a password for you? (y/n): ";
                cin >> opt;
                if (opt == 'y') {
                    int passLength;
                    do {
                        cout << "\t\t\t\t\tEnter desired Length: ";
                        cin >> passLength;
                        if (cin.fail() || passLength <= 0) {
                            cout << "\t\t\t\t\tInvalid input! Please enter a number.\n";
                            ClearInput();
                            continue;
                        }
                    } while (passLength <= 0 || cin.fail());
                    acc.password = GeneratePass(passLength);
                    cout << "\t\t\t\t\tGenerated Password: " << acc.password << endl;
                    cout << "\t\t\t\t\tAccount Updated! \n";
                }
                else if (opt == 'n') {
                    cout << "\t\t\t\t\tEnter new password: ";
                    cin >> acc.password;
                    cout << "\t\t\t\t\tAccount Updated! \n";
                }
                else {
                    cout << "\t\t\t\t\tInvalid Input! Please type y for yes and n for no.\n";
                    ClearInput();
                }
            } while (opt != 'y' && opt != 'n');
            return;
        }
    }
    cout << "\t\t\t\t\tAccount not found\n";
}

void DelAcc(vector<account>& accounts) {
    int id;
    cout << "\t\t\t\t\tEnter ID to delete: ";
    cin >> id;

    for (auto it = accounts.begin(); it != accounts.end(); ++it) {
        if (it->id == id) {
            accounts.erase(it);
            cout << "\t\t\t\t\tAccount deleted!\n";
            return;
        }
    }
    cout << "\t\t\t\t\tAccount not found!\n";
}

string GeneratePass(int passLength) {
    string pass;
    const string allowedChar = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&";

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(0, allowedChar.size() - 1);

    for (int i = 0; i < passLength; i++) {
        pass += allowedChar[distr(gen)];
    }
    return pass;
}


void saveFile(const vector<account>& accounts, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cout << "Error opening file for saving.\n";
        return;
    }

    // Write each account to the file in CSV format
    for (const auto& acc : accounts) {
        file << acc.id << "," << acc.platform << "," << acc.username << "," << acc.password << "\n";
    }

    file.close();
    cout << "\t\t\t\t\tAccounts saved to file successfully.\n";
}

void loadFile(vector<account>& accounts, const string& filename, int& nextId) {
    ifstream file(filename);
    if (!file) {
        cout << "\t\t\t\t\tNo data file found. Starting fresh.\n";
        return;
    }

    string line;
    int maxId = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        account acc;

        // Parse platform, username, and password from the line
        ss >> acc.id;
        ss.ignore(1);
        getline(ss, acc.platform, ',');
        getline(ss, acc.username, ',');
        getline(ss, acc.password, ',');

        accounts.push_back(acc);
        if (acc.id > maxId) {
            maxId = acc.id;
        }
    }

    file.close();
    cout << "\t\t\t\t\tAccounts loaded from file successfully.\n";
    nextId = maxId + 1;
}

void ClearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}