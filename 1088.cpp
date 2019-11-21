#include <cstdio>
#include <cstring>
#include <iostream>

#define MAX (100000000)

using std::cin;
using std::cout;
using std::endl;

int calc(int num[100][100], int r, int c, int result[100][100], int i, int j);

int main() {
    int r, c;
    cin >> r >> c;
    int num[100][100];
    int result[100][100];
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            scanf("%d", &num[i][j]);
        }
    }
    memset(result, 0, sizeof(char) * 10000);

    int max = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            calc(num, r, c, result, i, j);
            if (result[i][j] > max) {
                max = result[i][j];
            }
        }
    }
    cout << max << endl;

    return 0;
}

int calc(int num[100][100], int r, int c, int result[100][100], int i, int j) {
    if (result[i][j] != 0) {
        return result[i][j];
    }

    int up, down, left, right;

    if (i == 0) {
        left = MAX;
    } else {
        left = num[i - 1][j];
    }
    if (j == 0) {
        up = MAX;
    } else {
        up = num[i][j - 1];
    }
    if (i == (r - 1)) {
        right = MAX;
    } else {
        right = num[i + 1][j];
    }
    if (j == (c - 1)) {
        down = MAX;
    } else {
        down = num[i][j + 1];
    }

    int self = num[i][j];

    if (self <= up && self <= down && self <= left && self <= right) {
        // num[i][j] = 1;
        result[i][j] = 1;
        return 1;
    }

    if (self > left) {
        if (i == 0) {
            left = 0;
        } else if (result[i - 1][j] == 0) {
            left = calc(num, r, c, result, i - 1, j);
        } else {
            left = result[i - 1][j];
        }
        if (left + 1 > result[i][j]) {
            result[i][j] = left + 1;
        }
    }

    if (self > up) {
        if (j == 0) {
            up = 0;
        } else if (result[i][j - 1] == 0) {
            up = calc(num, r, c, result, i, j - 1);
        } else {
            up = result[i][j - 1];
        }
        if (up + 1 > result[i][j]) {
            result[i][j] = up + 1;
        }
    }

    if (self > right) {
        if (i == (r - 1)) {
            right = 0;
        } else if (result[i + 1][j] == 0) {
            right = calc(num, r, c, result, i + 1, j);
        } else {
            right = result[i + 1][j];
        }
        if (right + 1 > result[i][j]) {
            result[i][j] = right + 1;
        }
    }

    if (self > down) {
        if (j == (c - 1)) {
            down = 0;
        } else if (result[i][j + 1] == 0) {
            down = calc(num, r, c, result, i, j + 1);
        } else {
            down = result[i][j + 1];
        }
        if (down + 1 > result[i][j]) {
            result[i][j] = down + 1;
        }
    }
    return result[i][j];
}