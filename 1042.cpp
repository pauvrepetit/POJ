#include <cstdio>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int getmax(int *begin, int *down, int *countList, int n);

int main() {
    int n, h;
    int ttttt = 0;
    while (1) {
        ttttt++;
        cin >> n;
        if (n == 0) {
            break;
        }
        cin >> h;
        h *= 12; // 时间转化为以5分钟为单位

        int *begin = new int[n];
        int *down = new int[n];
        int *length = new int[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", begin + i);
        }
        for (int i = 0; i < n; i++) {
            scanf("%d", down + i);
        }
        length[0] = 0;
        for (int i = 1; i < n; i++) {
            scanf("%d", length + i);
        }

        int temph = h;
        int *tempbegin = new int[n];
        int *tempdown = new int[n];
        int *countList = new int[n];
        int *countListTemp = new int[n];
        memset(countList, 0, sizeof(int) * n);
        memset(countListTemp, 0, sizeof(int) * n);
        memcpy(tempbegin, begin, sizeof(int) * n);
        memcpy(tempdown, down, sizeof(int) * n);
        int max = -1;       // 初值赋成0就会WA...
        int count = 0;
        for (int i = 1; i <= n; i++) {
            count = 0;
            memset(countListTemp, 0, sizeof(int) * n);
            // 算到第i个湖终止的最大值
            for (int j = 0; j < i; j++) {
                h -= length[j];
            }
            // 减去路上的时间
            for (int j = 0; j < h; j++) {
                count += getmax(begin, down, countListTemp, i);
            }
            if (count > max) {
                max = count;
                memcpy(countList, countListTemp, sizeof(int) * n);
            }
            memcpy(begin, tempbegin, sizeof(int) * n);
            memcpy(down, tempdown, sizeof(int) * n);
            h = temph;
        }
        if (ttttt != 1) {
            putchar('\n');
        }
        for (int i = 0; i < n - 1; i++) {
            printf("%d, ", countList[i]);
        }
        printf("%d\n", countList[n - 1]);
        printf("Number of fish expected: %d\n", max);
        delete[] begin;
        delete[] down;
        delete[] length;
        delete[] tempdown;
        delete[] tempbegin;
        delete[] countListTemp;
        delete[] countList;
    }
    return 0;
}

int getmax(int *begin, int *down, int *countList, int n) {
    int maxloc = -1;
    int max = -1;
    for (int i = 0; i < n; i++) {
        if (begin[i] <= 0) {
            continue;
        }
        if (begin[i] > max) {
            max = begin[i];
            maxloc = i;
        }
    }
    if (maxloc == -1) {
        countList[0] += 5;
        return 0;
    }
    begin[maxloc] -= down[maxloc];
    countList[maxloc] += 5;

    return max;
}
