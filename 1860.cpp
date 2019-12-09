// 判正环

#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

#define DOUBLE_INF -1e30

using std::cin;
using std::cout;
using std::endl;
using std::queue;
using std::vector;

struct node {
    int end;
    double r;
    double c;
};

int relex(int begin, node end, double *money);

int main() {
    int N, M, S;
    double V;
    vector<node> num[105];
    double money[105];
    node n;
    cin >> N >> M >> S >> V;

    int n1, n2;
    double rab, cab, rba, cba;
    for (int i = 0; i < M; i++) {
        scanf("%d%d%lf%lf%lf%lf", &n1, &n2, &rab, &cab, &rba, &cba);
        n1--;
        n2--;
        n.end = n2;
        n.r = rab;
        n.c = cab;
        num[n1].push_back(n);
        n.end = n1;
        n.r = rba;
        n.c = cba;
        num[n2].push_back(n);
    }

    int pop;
    for (int i = 0; i <= N; i++) {
        money[i] = DOUBLE_INF;
    }
    S--;
    money[S] = V;
    int count[105];
    int visit[105];
    for (int i = 0; i < 105; i++) {
        count[i] = 0;
        visit[i] = 0;
    }

    queue<int> q;
    q.push(S);
    visit[S] = 1;
    count[S]++;
    while (!q.empty()) {
        pop = q.front();
        q.pop();
        visit[pop] = 0;
        for (int i = 0; i < num[pop].size(); i++) {
            if (relex(pop, num[pop][i], money) && visit[num[pop][i].end] == 0) {
                q.push(num[pop][i].end);
                count[num[pop][i].end]++;
                visit[num[pop][i].end] = 1;
                if (count[num[pop][i].end] > N) {
                    cout << "YES" << endl;
                    return 0;
                }
            }
        }
    }
    if(money[S] > V) {
        cout << "YES" << endl;
        return 0;
    }

    cout << "NO" << endl;
    return 0;
}

int relex(int begin, node end, double *money) {
    if (money[end.end] < (money[begin] - end.c) * end.r) {
        money[end.end] = (money[begin] - end.c) * end.r;
        return 1;
    }
    return 0;
}