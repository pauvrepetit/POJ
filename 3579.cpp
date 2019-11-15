#include <algorithm>
#include <iostream>
#include <cstdio>

using std::cin;
using std::cout;
using std::endl;
using std::lower_bound;
using std::sort;

int getMinLength(int *num, int n, int LNum, int RNum);

int main() {
    int n;
    int *num;
    while (cin >> n) {
        num = new int[n];
        for (int i = 0; i < n; i++) {
            scanf("%d", num + i);       // use cin to input will Time Limit Exceeded...
        }
        sort(num, num + n);
        cout << getMinLength(num, n, 0, num[n - 1] - num[0]) << endl;

        delete[] num;
    }
    return 0;
}

int getMinLength(int *num, int n, int LNum, int RNum) {
    int midNum = (LNum + RNum) / 2;
    int countLarge = 0;
    int countEqual = 0;
    int countLess = 0;
    int countAll = n * (n - 1) / 2;

    for (int i = 0; i < n; i++) {
        int *less_bound = lower_bound(num, num + n, num[i] + midNum);
        int less = less_bound - num - i - 1;
        int equal = 0;
        while (*less_bound == (num[i] + midNum)) {
            equal++;
            less_bound++;
        }

        countLess += less;
        countEqual += equal;
        countLarge += (n - less - equal - i - 1);

        if(countLess > countAll / 2 || countLarge > countAll / 2) {
            break;
        }
    }

    if (countEqual != 0) {
        if (countLarge <= (countEqual + countLess) && countLess < (countEqual + countLarge)) {
            return midNum;
        } else if (countLarge > (countEqual + countLess)) {
            return getMinLength(num, n, midNum + 1, RNum);
        } else {
            return getMinLength(num, n, LNum, midNum);
        }
    } else {
        if (countLess < countLarge) {
            return getMinLength(num, n, midNum + 1, RNum);
        } else {
            return getMinLength(num, n, LNum, midNum);
        }
    }
}