// 一头牛的排名确定 当且仅当
// 对于其他的任何一头牛，要么 他能到这头牛，要么 这头牛能到他

#include <cstdio>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void mul(int num[100][100], int N);

int main() {
    int N, M;
    cin >> N >> M;
    int num[100][100];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            num[i][j] = 0;
        }
    }
    int A, B;
    for (int i = 0; i < M; i++) {
        scanf("%d%d", &A, &B);
        A--;
        B--;
        num[A][B] = 1;
    }
    for (int i = 0; i < N; i++) {
        num[i][i] = 1;
    }

    mul(num, N);

    int count = N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (num[i][j] == 0 && num[j][i] == 0) {
                count--;
                break;
            }
        }
    }

    cout << count << endl;

    return 0;
}

void mul(int num[100][100], int N) {
    int t[100][100];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                t[j][k] = 0;
                for (int l = 0; l < N; l++) {
                    t[j][k] = t[j][k] || (num[j][l] && num[l][k]);
                    if (t[j][k]) {
                        break;
                    }
                }
            }
        }
        memcpy(num, t, sizeof(int) * 10000);
    }
    return;
}