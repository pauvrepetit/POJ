/*
用C++字典 超时了

#include <iostream>
#include <map>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::map;
using std::string;

int main() {
    map<string, string> translate;
    string keyStr;
    string valueStr;
    string line;
    while (1) {
        getline(cin, line);
        if (line.length() == 0) {
            break;
        }
        int spaceLoc = line.find(' ');
        valueStr = line.substr(0, spaceLoc);
        keyStr = line.substr(spaceLoc + 1);
        translate[keyStr] = valueStr;
    }
    while (cin >> keyStr) {
        if(translate[keyStr] == "") {
            translate[keyStr] = "eh";
        }
        cout << translate[keyStr] << endl;
    }

    return 0;
}

*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::sort;
using std::string;
using std::vector;

struct elem {
    string key;
    string value;

    bool operator<(const elem &e) const { return this->key < e.key; }
};

string binary_find(vector<elem>::iterator begin, vector<elem>::iterator end, string find);

int main() {
    string line;
    elem newElem;
    vector<elem> strList;
    while (1) {
        getline(cin, line);
        if (line == "") {
            break;
        }
        int spaceLoc = line.find(' ');
        newElem.value = line.substr(0, spaceLoc);
        newElem.key = line.substr(spaceLoc + 1);
        strList.push_back(newElem);
    }
    sort(strList.begin(), strList.end());
    while (cin >> line) {
        cout << binary_find(strList.begin(), strList.end(), line) << endl;
    }
    return 0;
}

string binary_find(vector<elem>::iterator begin, vector<elem>::iterator end, string find) {
    vector<elem>::iterator mid = begin + (end - begin) / 2;
    if(mid->key == find) {
        return mid->value;
    }
    if(begin == end) {
        return "eh";
    }
    if((end - begin) == 1 && end->key != find) {
        return "eh";
    }
    if(mid->key > find) {
        return binary_find(begin, mid, find);
    }
    return binary_find(mid, end, find);
}