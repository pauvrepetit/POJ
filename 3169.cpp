// 构造图
// 找最短路
// 若有负环 则无解
// 若大于INF 则为无穷大

#include <cstdio>
#include <iostream>
#include <queue>

#define INF (0x7FFFFFF)

using std::cin;
using std::cout;
using std::endl;
using std::queue;

int main() {
    int N, ML, MD;
    cin >> N >> ML >> MD;
    int num[1010][1010];
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            num[i][j] = INF;
        }
    }

    for (int i = 0; i <= N; i++) {
        num[i][i] = 0;
        num[i + 1][i] = 0;
    }

    int A, B, D;
    for (int i = 0; i < ML; i++) {
        scanf("%d%d%d", &A, &B, &D);
        A--;
        B--;
        num[A][B] = D;
    }
    for (int i = 0; i < MD; i++) {
        scanf("%d%d%d", &A, &B, &D);
        A--;
        B--;
        num[B][A] = -D;
    }

    int length[1010];
    int count[1010];
    int visit[1010];
    for (int i = 0; i <= N; i++) {
        length[i] = INF;
        count[i] = 0;
        visit[i] = 0;
    }

    queue<int> q;
    int pop;
    q.push(0);
    visit[0] = 1;
    count[0]++;
    length[0] = 0;
    while (!q.empty()) {
        pop = q.front();
        q.pop();
        visit[pop] = 0;
        for (int i = 0; i < N; i++) {
            if (length[i] > length[pop] + num[pop][i]) {
                length[i] = length[pop] + num[pop][i];
                if (visit[i] == 0) {
                    q.push(i);
                    count[i]++;
                    visit[i] = 1;
                    if(count[i] > N) {
                        cout << "-1" << endl;
                        return 0;
                    }
                }
            }
        }
    }

    if (length[N - 1] >= INF) {
        cout << "-2" << endl;
    } else if (length[N - 1] < 0) {
        cout << "-1" << endl;
    } else {
        cout << length[N - 1] << endl;
    }

    return 0;
}