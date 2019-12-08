// 这是个纯Dijkstra算法

#include <cstdio>
#include <cstring>
#include <iostream>

#define INF (0x7FFFFFF)

using std::cin;
using std::cout;
using std::endl;

int main() {
    int T, N;
    int src, dst, len;
    int num[1000][1000];
    int length[1000];
    int save[1000];

    cin >> T >> N;
    for (int i = 0; i < N; i++) {
        length[i] = INF;
    }
    for (int i = 0; i < N; i++) {
        save[i] = 0;
    }
    save[0] = 1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            num[i][j] = INF;
        }
    }
    for (int i = 0; i < T; i++) {
        scanf("%d%d%d", &src, &dst, &len);
        src--;
        dst--;
        len = std::min(len, num[src][dst]);
        num[src][dst] = len;
        num[dst][src] = len;
        if (src == 0) {
            length[dst] = len;
        }
        if (dst == 0) {
            length[src] = len;
        }
    }
    for (int i = 0; i < N; i++) {
        num[i][i] = 0;
    }

    for (int i = 1; i < N; i++) {
        int min = INF;
        int minPoint;
        for (int j = 0; j < N; j++) {
            if (save[j] == 0) {
                if (length[j] < min) {
                    minPoint = j;
                    min = length[j];
                }
            }
        }
        save[minPoint] = 1;
        for (int j = 0; j < N; j++) {
            if (save[j] == 0 && (min + num[minPoint][j] < length[j])) {
                length[j] = min + num[minPoint][j];
            }
        }
    }

    cout << length[N - 1] << endl;

    return 0;
}