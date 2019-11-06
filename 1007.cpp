#include <algorithm>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::sort;
using std::string;

struct dna {
    string dnaStr;
    int sorted;

    bool operator<(const dna &d) const { return this->sorted < d.sorted; }
};

int getSorted(string);

int main() {
    int len, num;
    cin >> len >> num;
    dna *dnaList = new dna[num];
    for (int i = 0; i < num; i++) {
        cin >> dnaList[i].dnaStr;
        dnaList[i].sorted = getSorted(dnaList[i].dnaStr);
    }
    sort(dnaList, dnaList + num);

    for (int i = 0; i < num; i++)
        cout << dnaList[i].dnaStr << endl;

    return 0;
}

int getSorted(string dnaStr) {
    int len = dnaStr.length();
    int count = 0;
    for (int i = 0; i < len; i++) {
        for (int j = i; j < len; j++) {
            if (dnaStr[j] < dnaStr[i])
                count++;
        }
    }
    return count;
}
