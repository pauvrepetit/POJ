#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

#define INF (0x7FFFFFF)

using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::vector;

#define MAX 50010

int relex(int begin, int end, int weight, int *length);

struct node {
    int end;
    int value;
};

int main() {
    vector<node> num[MAX];
    node no;
    int n;
    cin >> n;
    int a, b, c;
    int maxNum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &a, &b, &c);
        no.end = b;
        no.value = -c;
        num[a - 1].push_back(no);
        maxNum = std::max(maxNum, b);
    }
    no.end = 1;
    no.value = 0;
    num[0].push_back(no);
    for (int i = 1; i <= maxNum; i++) {
        no.end = i + 1;
        no.value = 0;
        num[i].push_back(no);
        no.end = i - 1;
        no.value = 1;
        num[i].push_back(no);
    }

    int length[MAX];
    for (int i = 0; i <= maxNum; i++) {
        length[i] = INF;
    }

    length[0] = 0;

    // timeout
    // for (int i = 0; i <= maxNum; i++) {
    //     for (int j = 0; j <= maxNum; j++) {
    //         for (int k = 0; k < num[j].size(); k++) {
    //             relex(j, num[j][k].end, num[j][k].value, length);
    //         }
    //     }
    // }

    // use SPFA

    queue<int> q;
    q.push(0);

    int pop;
    while (!q.empty()) {
        pop = q.front();
        q.pop();
        for (int i = 0; i < num[pop].size(); i++) {
            if (relex(pop, num[pop][i].end, num[pop][i].value, length)) {
                q.push(num[pop][i].end);
            }
        }
    }

    cout << -length[maxNum] << endl;

    return 0;
}

int relex(int begin, int end, int weight, int *length) {
    if (length[end] > length[begin] + weight) {
        length[end] = length[begin] + weight;
        return 1;
    }
    return 0;
}