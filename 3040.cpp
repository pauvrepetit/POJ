// problem：poj的long是64位的吗？
// 数字过大导致乘法溢出了

#include <algorithm>
#include <cstdio>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::sort;

class money {
  public:
    int m;
    int num;

    bool operator<(const money &a) const { return this->m > a.m; }
};

int getMoney(money *mon, int n, int c);

int main() {
    int n, c;
    cin >> n >> c;
    money *mon = new money[n];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &(mon[i].m), &(mon[i].num));
    }
    sort(mon, mon + n); // 按面值从大到小排序

    int count = 0;
    while (1) {
        if (getMoney(mon, n, c) == 1) {
            count++;
        } else {
            break;
        }
    }
    cout << count << endl;

    return 0;
}

int getMoney(money *mon, int n, int c) {
    for (int i = 0; i < n; i++) {
        if (mon[i].m <= c) {
            // 面值小于等于c
            while (c >= mon[i].m && mon[i].num > 0) {
                c -= mon[i].m;
                mon[i].num--;
            }
            // if (c > mon[i].m * mon[i].num) {
            //     // 取完
            //     c -= (mon[i].m * mon[i].num);
            //     mon[i].num = 0;
            // } else {
            //     mon[i].num -= (c / mon[i].m);
            //     c %= mon[i].m;
            // }
        }
        if (c == 0) {
            return 1;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        while (c >= mon[i].m && mon[i].num > 0) {
            c -= mon[i].m;
            mon[i].num--;
        }
        if (c > 0 && mon[i].num > 0) {
            c = 0;
            mon[i].num--;
            return 1;
        }
        // if (c > mon[i].m * mon[i].num) {
        //     c -= (mon[i].m * mon[i].num);
        //     mon[i].num = 0;
        // } else {
        //     mon[i].num -= (c / mon[i].m);
        //     if (c % mon[i].m) {
        //         mon[i].num--;
        //     }
        //     return 1;
        // }
        // if (c == 0) {
        //     return 1;
        // }
    }
    return 0;
}

/*
int getMoney(money *mon, int n, int c) {
    if (n == 0) {
        return 0;
    }
    if(c == 0) {
        return 1;
    }
    if (mon->num == 0) {
        return getMoney(mon + 1, n - 1, c);
    }
    if(mon->m == c && mon->num > 0) {
        mon->num--;
        return 1;
    }
    if (mon->m > c && mon->num > 0) {
        // 面值大了
        if (getMoney(mon + 1, n - 1, c) == 1) {
            return 1;
        } else {
            mon->num--;
            return 1;
        }
    }
    if (mon->m < c && c / mon->m <= mon->num) {
        // 面值小 且够用
        mon->num -= (c / mon->m);
        c %= mon->m; // 剩下的部分
        if (getMoney(mon + 1, n - 1, c) == 1) {
            return 1;
        } else {
            if (mon->num > 0) {
                mon->num--;
                return 1;
            } else {
                return 0;
            }
        }
    }
    if (mon->m < c && c / mon->m > mon->num) {
        // 面值小 不怎么够 全部取完
        c -= (mon->m * mon->num);
        mon->num = 0;
        return getMoney(mon + 1, n - 1, c);
    }
}
*/