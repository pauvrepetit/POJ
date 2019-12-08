// 添加节点0
// 每个物品都是一个节点
// 节点0到该物品的距离为该物品的价格
// 节点i 到 节点j 的距离为 用j 替换 i 需要得到的优惠价格
// 找节点0 到 节点1 的最短路径
// 限制：等级

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

#define INF (0x7FFFFFF)

using std::cin;
using std::cout;
using std::endl;
using std::sort;
using std::vector;

int main() {
    int M, N;
    int num[110][110];
    int dij[110][110];
    int save[110];
    int length[110];
    vector<int> levelList;
    levelList.push_back(0);

    cin >> M >> N;

    for (int i = 0; i <= N; i++) {
        length[i] = INF;
        save[i] = 0;
    }
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            num[i][j] = INF;
        }
    }
    for (int i = 0; i <= N; i++) {
        num[i][i] = 0;
    }

    int value, level, number;
    int T, V;

    for (int i = 1; i <= N; i++) {
        scanf("%d%d%d", &value, &level, &number);
        num[0][i] = value;
        length[i] = value;
        levelList.push_back(level);
        for (int j = 0; j < number; j++) {
            scanf("%d%d", &T, &V);
            num[T][i] = V;
        }
    }
    save[0] = 1;

    int minLevel = -1;
    int result = INF;
    for (int k = 1; k < levelList.size(); k++) {
        if (levelList[k] == minLevel) {
            continue;
        }
        minLevel = levelList[k];

        memcpy(dij, num, sizeof(int) * 110 * 110);
        for (int i = 1; i <= N; i++) {
            if (levelList[i] > minLevel + M || levelList[i] < minLevel) {
                for (int j = 0; j <= N; j++) {
                    dij[j][i] = INF;
                }
            }
        }

        for (int i = 0; i <= N; i++) {
            length[i] = dij[0][i];
            save[i] = 0;
        }
        save[0] = 1;

        for (int i = 1; i <= N; i++) {
            int min = INF;
            int minPoint;
            for (int j = 0; j <= N; j++) {
                if (save[j] == 0) {
                    if (length[j] < min) {
                        minPoint = j;
                        min = length[j];
                    }
                }
            }
            save[minPoint] = 1;
            for (int j = 0; j <= N; j++) {
                if (save[j] == 0 && (min + dij[minPoint][j] < length[j])) {
                    length[j] = min + dij[minPoint][j];
                }
            }
        }
        result = std::min(result, length[1]);
    }

    cout << result << endl;

    return 0;
}