#include <cstdio>
#include <iostream>
#include <cstring>

#define MIN (-100000000)

using std::cin;
using std::cout;
using std::endl;

int calc(int num[100][100], int n, int result[100][100], int i, int j, int temp[100][100]);

int main() {
    int n;
    int num[100][100];
    int result[100][100];
    int temp[100][100];
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &num[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = MIN;
        }
    }

    cout << calc(num, n, result, 0, 0, temp) << endl;

    return 0;
}

int calc(int num[100][100], int n, int result[100][100], int i, int j, int temp[100][100]) {
    if (result[i][j] != MIN) {
        return result[i][j];
    }

    int max = MIN;

    int right, down;
    if (i == (n - 1)) {
        right = MIN;
    } else {
        right = result[i + 1][j];
        if (right == MIN) {
            right = calc(num, n, result, i + 1, j, temp);
        }
    }
    if (j == (n - 1)) {
        down = MIN;
    } else {
        down = result[i][j + 1];
        if (down == MIN) {
            down = calc(num, n, result, i, j + 1, temp);
        }
    }

    if (right > down) {
        max = right;
    } else {
        max = down;
    }

    memset(temp, 0, sizeof(char) * 10000);

    temp[i][j] = num[i][j];
    if(temp[i][j] > max) {
        max = temp[i][j];
    }

    for (int jj = j + 1; jj < n; jj++) {
        temp[i][jj] = num[i][jj] + temp[i][jj - 1];
        if(temp[i][jj] > max) {
            max = temp[i][jj];
        }
    }
    for (int ii = i + 1; ii < n; ii++) {
        temp[ii][j] = num[ii][j] + temp[ii - 1][j];
        if(temp[ii][j] > max) {
            max = temp[ii][j];
        }
    }

    for (int ii = i + 1; ii < n; ii++) {
        for (int jj = j + 1; jj < n; jj++) {
            temp[ii][jj] = num[ii][jj] + temp[ii - 1][jj] + temp[ii][jj - 1] - temp[ii - 1][jj - 1];
            if(temp[ii][jj] > max) {
                max = temp[ii][jj];
            }
        }
    }

    result[i][j] = max;
    return max;
}