#include <cstdio>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int min(int a, int b);

int main() {
    bool flip[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (getchar() == 'b') {
                flip[i][j] = false;
            } else {
                flip[i][j] = true;
            }
        }
        getchar();
    }

    int count[4][4];
    memset(count, 0, sizeof(int) * 16);
    int minChange = 10000;
    int flag = 0;
    int changeNum = 0;
    for (int i = 0; i < 65536; i++) {
        flag = 0;
        changeNum = 0;
        bool tempFlip[4][4];
        memcpy(tempFlip, flip, sizeof(bool) * 16);
        memset(count, 0, sizeof(int) * 16);
        if (i & 1) {
            count[0][0]++;
            count[0][1]++;
            count[1][0]++;
            changeNum++;
        }
        if (i & 2) {
            count[0][1]++;
            count[0][0]++;
            count[0][2]++;
            count[1][1]++;
            changeNum++;
        }
        if (i & 4) {
            count[0][2]++;
            count[0][1]++;
            count[0][3]++;
            count[1][2]++;
            changeNum++;
        }
        if (i & 8) {
            count[0][3]++;
            count[0][2]++;
            count[1][3]++;
            changeNum++;
        }
        if (i & 16) {
            count[1][0]++;
            count[0][0]++;
            count[1][1]++;
            count[2][0]++;
            changeNum++;
        }
        if (i & 32) {
            count[1][1]++;
            count[0][1]++;
            count[2][1]++;
            count[1][0]++;
            count[1][2]++;
            changeNum++;
        }
        if (i & 64) {
            count[1][2]++;
            count[0][2]++;
            count[2][2]++;
            count[1][1]++;
            count[1][3]++;
            changeNum++;
        }
        if (i & 128) {
            count[1][3]++;
            count[0][3]++;
            count[2][3]++;
            count[1][2]++;
            changeNum++;
        }
        if (i & 256) {
            count[2][0]++;
            count[1][0]++;
            count[3][0]++;
            count[2][1]++;
            changeNum++;
        }
        if (i & 512) {
            count[2][1]++;
            count[1][1]++;
            count[3][1]++;
            count[2][0]++;
            count[2][2]++;
            changeNum++;
        }
        if (i & 1024) {
            count[2][2]++;
            count[1][2]++;
            count[3][2]++;
            count[2][1]++;
            count[2][3]++;
            changeNum++;
        }
        if (i & 2048) {
            count[2][3]++;
            count[1][3]++;
            count[3][3]++;
            count[2][2]++;
            changeNum++;
        }
        if (i & 4096) {
            count[3][0]++;
            count[2][0]++;
            count[3][1]++;
            changeNum++;
        }
        if (i & 8192) {
            count[3][1]++;
            count[2][1]++;
            count[3][0]++;
            count[3][2]++;
            changeNum++;
        }
        if (i & 16384) {
            count[3][2]++;
            count[2][2]++;
            count[3][1]++;
            count[3][3]++;
            changeNum++;
        }
        if (i & 32768) {
            count[3][3]++;
            count[2][3]++;
            count[3][2]++;
            changeNum++;
        }
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (count[j][k] % 2) {
                    tempFlip[j][k] = !tempFlip[j][k];
                }
            }
        }
        bool color = tempFlip[0][0];
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                if (color != tempFlip[j][k]) {
                    flag = 1;
                }
            }
        }
        if (flag == 0) {
            minChange = min(minChange, changeNum);
        }
    }
    if (minChange == 10000) {
        cout << "Impossible" << endl;
    } else {
        cout << minChange << endl;
    }

    return 0;
}

int min(int a, int b) {
    if (a > b) {
        return b;
    }
    return a;
}