#include <cstdio>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int getCount[1024];
int trans[1024];

int check(int j);
int calc(int A[100][70][70], int n, int m, int num[100]);

int main() {
    int n, m;
    cin >> n >> m;
    int num[100];
    int A[100][70][70];

    getchar();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (getchar() == 'P') {
                num[i] += 1;
            }
            num[i] <<= 1;
        }
        num[i] >>= 1;
        getchar();
    }

    memset(getCount, 0, sizeof(int) * 1024);
    for (int i = 0; i < (1 << m); i++) {
        int j = i;
        while (j != 0) {
            if (j % 2 != 0) {
                getCount[i]++;
            }
            j >>= 1;
        }
    }

    int count = 0;
    for (int i = 0; i < (1 << m); i++) {
        if (check(i) == 0) {
            trans[i] = count++;
        } else {
            trans[i] = -1;
        }
    }

    memset(A, -1, sizeof(int) * 100 * 70 * 70);

    cout << calc(A, n, m, num) << endl;

    return 0;
}

int check(int j) {
    int count = 0;
    int begin = 0;
    while (j != 0) {
        count++;
        if (j % 2 == 1) {
            if (begin == 0 || (count - begin > 2)) {
                begin = count;
            } else {
                return 1;
            }
        }
        j >>= 1;
    }
    return 0;
}

int calc(int A[100][70][70], int n, int m, int num[100]) {
    for (int i = 0; i < (1 << m); i++) {
        if (trans[i] == -1) {
            continue;
        }
        if (~(num[0] | (~i))) {
            continue;
        }
        A[0][0][trans[i]] = getCount[i];
    }

    for (int i = 0; i < (1 << m); i++) {
        if (trans[i] == -1) {
            continue;
        }
        if (~(num[0] | (~i))) {
            continue;
        }
        for (int j = 0; j < (1 << m); j++) {
            if (trans[j] == -1) {
                continue;
            }
            if (~(num[1] | (~j))) {
                continue;
            }
            if ((i & j) != 0) {
                continue;
            }
            A[1][trans[i]][trans[j]] = std::max(A[1][trans[i]][trans[j]], A[0][0][trans[i]] + getCount[j]);
        }
    }

    for (int i = 2; i < n; i++) {
        for (int ll = 0; ll < (1 << m); ll++) {
            if (trans[ll] == -1) {
                // 状态不可行
                continue;
            }
            if (~(num[i - 2] | (~ll))) {
                continue;
            }
            int l = trans[ll];
            for (int kk = 0; kk < (1 << m); kk++) {
                if (trans[kk] == -1 || (ll & kk) != 0) {
                    continue;
                }
                if (~(num[i - 1] | (~kk))) {
                    continue;
                }
                int k = trans[kk];
                for (int jj = 0; jj < (1 << m); jj++) {
                    if (~(num[i] | (~jj))) {
                        continue;
                    }
                    if (trans[jj] == -1) {
                        continue;
                    }
                    if ((jj & kk) != 0 || (jj & ll) != 0) {
                        continue;
                    }
                    if(A[i - 1][l][k] == -1) {
                        continue;
                    }
                    int j = trans[jj];
                    A[i][k][j] = std::max(A[i][k][j], A[i - 1][l][k] + getCount[jj]);
                }
            }
        }
    }

    int max = 0;
    for (int i = 0; i < 70; i++) {
        for (int j = 0; j < 70; j++) {
            max = std::max(max, A[n - 1][i][j]);
        }
    }

    return max;
}
