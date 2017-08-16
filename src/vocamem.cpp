#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <tuple>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

void readDirectory(map<string, string>& dict, const string& filename) {
    ifstream fin;
    fin.open(filename);
    string word, translation;
    while (fin >> word) {
        fin >> translation;
        dict[word] = translation;    
    }
}

void readTask(const map<string, string>& dict, vector<pair<string, int> >& task) {
    for (auto iter = dict.begin(); iter != dict.end(); iter++)
        task.push_back(pair<string, int>(iter->first, 3));
}

void readTask(vector<pair<string, int> >& task, const string& filename) {
    ifstream fin;
    fin.open(filename);
    string word;
    int status;
    while (fin >> word) {
        fin >> status;
        if (status <= 0)
            continue;
        else if (status > 3)
            status = 3;
        task.push_back(pair<string, int>(word, status));
    }

}

void updateFile(const map<string, string>& dict, const vector<pair<string, int> >& task, const string& filename) {
    ofstream fout;
    fout.open(filename);
    if (!fout.is_open()) {        
        cout << "Error" << endl;
        exit(1);
    }
    for (auto iter = task.begin(); iter != task.end(); iter++) {
        if (!iter->second)
            continue;
        fout << iter->first << ' ' << iter->second << endl;
    }
}

int main() {
    map<string, string> dict;
    vector<pair<string, int> > task;
    
    cout << "Dictionary: ";
    string filename;
    cin >> filename;
    readDirectory(dict, filename);
    
    cout << "Mode (new or existing): ";
    string mode;
    cin >> mode;
    if (mode != "new" && mode != "existing") {
        cout << "Error" << endl;
        exit(1);
    } else if (mode == "new")
        readTask(dict, task); 
    else {
        cout << "Task file: ";
        cin >> filename;
        readTask(task, filename);
    }
    
    cout << endl << "Let's begin. 1 for \"I know\", 2 for \"I don't know\", 9 for \"Too simple\", -1 for \"save and quit\"." << endl << endl;
    while (!task.empty()) {    
        random_shuffle(task.begin(), task.end());
        updateFile(dict, task, "temp");
        for (auto iter = task.begin(); iter != task.end();) {
            cout << iter->first << ' ';
            int choice;
            cin >> choice;
            cout << dict[iter->first] << endl << endl;
            if (choice == -1) {
                cout << "Save as: ";
                cin >> filename;
                updateFile(dict, task, filename);
                remove("temp");
                cout << "Task saved." << endl;
                system("pause>nul");
                return 0;
            } else if (choice == 1) {
                iter->second--;
            } else if (choice == 2) {
                if (iter->second < 3)
                    iter->second++;
                else
                    iter->second = 3;
            } else if (choice == 9) {
                iter->second = 0;
            } else {
                continue;
            }
            if (iter->second > 0)
                iter++;
            else 
                iter = task.erase(iter);
            updateFile(dict, task, "temp");
        }

    }

    cout << "Task completed." << endl;
    system("pause>nul");
    remove("temp");
    return 0;

}