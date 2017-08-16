#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <cstdlib>

using namespace std;

void updateFile(const map<string, pair<string, int> >& list, string filename) {
    ofstream fout;
    fout.open(filename);
    for (auto iter = list.begin(); iter != list.end(); iter++) {
        if (!iter->second.second)
            continue;
        fout << iter->first << ' ' << iter->second.first << ' ' << iter->second.second << endl;
    }
}

int main() {
    map<string, pair<string, int> > list;

    cout << "Mode (new or existing): ";
    string mode;
    cin >> mode;
    
    cout << "File: ";
    string filename;
    cin >> filename;
    ifstream fin;
    fin.open(filename);
    string word, translation;
    if (mode != "new" && mode != "existing")
        return 1;
    else if (mode == "new")
        while (fin >> word) {
            fin >> translation;
            list[word] = pair<string, int>(translation, 3);
        }
    else if (mode == "existing") {
        int status;
        while (fin >> word) {
            fin >> translation >> status;
            list[word] = pair<string, int>(translation, status);    
        }
    }
    updateFile(list, "temp");

    cout << endl << "Let's begin. 1 for \"I know\", 2 for \"I don't know\", 9 for \"Too simple\", -1 for \"save and quit\"." << endl << endl;
    while (!list.empty()) {
        for (auto iter = list.begin(); iter != list.end(); iter++) {
            if (!iter->second.second)
                continue;

            cout << iter->first << ' ';
            int choice;
            cin >> choice;
            cout << iter->second.first << endl << endl;
            if (choice == -1) {
                cout << "Save to: ";
                cin >> filename;
                updateFile(list, filename);
                cout << "File saved." << endl;
                system("pause>nul");
                return 0;
            } else if (choice == 1) {
                iter->second.second--;
            } else if (choice == 2) {
                if (iter->second.second < 3)
                    iter->second.second++;
                else
                    iter->second.second = 3;
            } else if (choice == 9) {
                iter->second.second = 0;
            } else {
                iter--;
                continue;
            }
            updateFile(list, "temp");
        }
    }
    cout << "Task completed." << endl;
    system("pause>nul");
    remove("temp");
    return 0;

}