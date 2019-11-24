#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class pair {
  public:
    int x;
    int y;
};

int calc(vector<pair> dangerous, int n, int p);

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, p; // n个犯人 p对危险
        cin >> n >> p;

        vector<pair> dangerous(p);

        int x, y;
        for (int j = 0; j < p; j++) {
            scanf("%d%d", &x, &y);
            dangerous[j].x = x;
            dangerous[j].y = y;
        }

        cout << calc(dangerous, n, p) << endl;

        dangerous.clear();
    }

    return 0;
}

int calc(vector<pair> dangerous, int n, int p) {
    vector<int> prison1;
    vector<int> prison2;
    int length = p;
    int *p1 = new int[n + 1];
    int *p2 = new int[n + 1];
    int *p3 = new int[p];

    memset(p1, 0, sizeof(int) * (n + 1));
    memset(p2, 0, sizeof(int) * (n + 1));
    memset(p3, 0, sizeof(int) * p);

    int countAll0 = 0;
    int countAll1 = 0;

    prison1.clear();
    prison2.clear();

    while (length > 0) {
        for (int i = 0; i < p; i++) {
            if (p3[i] == 1) {
                continue;
            }
            p1[dangerous[i].x] = 1;
            p2[dangerous[i].y] = 1;
            p3[i] = 1;
            length--;
            break;
        }

        int flag = 0;
        while (1) {
            flag = 0;
            for (int i = 0; i < p; i++) {
                if (p3[i] == 1) {
                    continue;
                }
                if (p1[dangerous[i].x] == 1) {
                    p2[dangerous[i].y] = 1;
                } else if (p2[dangerous[i].y] == 1) {
                    p1[dangerous[i].x] = 1;
                } else {
                    continue;
                }
                p3[i] = 1;
                length--;
                flag = 1;
            }
            if(flag == 0) {
                break;
            }
        }

        int count0 = 0;
        int count1 = 0;
        for (int i = 1; i <= n; i++) {
            count0 += p1[i];
            count1 += p2[i];
        }
        prison1.push_back(count0);
        prison2.push_back(count1);
        countAll0 += count0;
        countAll1 += count1;

        memset(p1, 0, sizeof(int) * (n + 1));
        memset(p2, 0, sizeof(int) * (n + 1));
    }

    for (int i = countAll0; i < n; i++) {
        prison1.push_back(1);
        prison2.push_back(0);
    }

    for (int i = countAll1; i < n; i++) {
        prison1.push_back(0);
        prison2.push_back(1);
    }

    length = prison1.size();

    int dp[300][300];
    memset(dp, 0, sizeof(int) * 300 * 300);
    dp[0][0] = 1;

    for (int i = 0; i < length; i++) {
        for (int j = n; j >= prison1[i]; j--) {
            for (int k = n; k >= prison2[i]; k--) {
                dp[j][k] = dp[j][k] || (dp[j - prison1[i]][k - prison2[i]]);
            }
        }
    }

    for (int j = n / 2; j >= 0; j--) {
        if (dp[j][j]) {
            delete[] p1;
            delete[] p2;
            delete[] p3;
            return j;
        }
    }
    return 0;
}