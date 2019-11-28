// 穷举大法好

#include <cstdio>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

long int getMax(int i, int s, int d);

int main() {
    int s, d;
    long int max;
    while (cin >> s >> d) {
        max = -1;
        for (int i = 0; i < 0x1000; i++) {
            max = std::max(max, getMax(i, s, d));
        }
        if (max <= 0) {
            cout << "Deficit" << endl;
        } else {
            cout << max << endl;
        }
    }
    return 0;
}

long int getMax(int i, int s, int d) {
    unsigned int key = 2048;
    long int month[12];
    int j = 0;
    while (key != 0) {
        if ((key & i) != 0) {
            // 该月亏损
            month[j] = -d;
        } else {
            month[j] = s;
        }
        j++;
        key >>= 1;
    }
    if (month[0] + month[1] + month[2] + month[3] + month[4] >= 0) {
        return -1;
    }
    if (month[1] + month[2] + month[3] + month[4] + month[5] >= 0) {
        return -1;
    }
    if (month[2] + month[3] + month[4] + month[5] + month[6] >= 0) {
        return -1;
    }
    if (month[3] + month[4] + month[5] + month[6] + month[7] >= 0) {
        return -1;
    }
    if (month[4] + month[5] + month[6] + month[7] + month[8] >= 0) {
        return -1;
    }
    if (month[5] + month[6] + month[7] + month[8] + month[9] >= 0) {
        return -1;
    }
    if (month[6] + month[7] + month[8] + month[9] + month[10] >= 0) {
        return -1;
    }
    if (month[7] + month[8] + month[9] + month[10] + month[11] >= 0) {
        return -1;
    }
    long int sum = 0;
    for (j = 0; j < 12; j++) {
        sum += month[j];
    }
    return sum;
}