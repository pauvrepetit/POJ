// 这河过的真好

#include <algorithm>
#include <cstdio>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::sort;

int main() {
    int t, n;
    cin >> t;
    int sum;
    for (int i = 0; i < t; i++) {
        cin >> n;
        int *num = new int[n];
        for (int j = 0; j < n; j++) {
            scanf("%d", num + j);
        }
        sort(num, num + n);
        sum = 0;
        int j = n;
        for (j = n; j >= 4; j -= 2) {
            sum += std::min(num[0] + num[1] + num[1] + num[j - 1], num[0] + num[0] + num[j - 2] + num[j - 1]);
        }
        if (j == 2) {
            sum += num[1];
        } else if (j == 3) {
            sum += (num[0] + num[1] + num[2]);
        } else {
            sum += num[0];
        }
        cout << sum << endl;
        delete[] num;
    }

    return 0;
}