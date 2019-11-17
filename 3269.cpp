#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using std::binary_search;
using std::cin;
using std::cout;
using std::endl;
using std::sort;
struct dot {
    int x;
    int y;
};

bool x_(const dot &a, const dot &b) {
    if (a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}

bool y_(const dot &a, const dot &b) {
    if (a.y != b.y)
        return a.y < b.y;
    return a.x < b.x;
}

int getCount(dot *array, int x, int y, int n);

int main() {
    int n;
    cin >> n;
    dot *arrayX = new dot[n];
    dot *arrayY = new dot[n];
    for (int i = 0; i < n; i++) {
        scanf("%d%d", &(arrayX[i].x), &(arrayX[i].y));
    }
    memcpy(arrayY, arrayX, sizeof(dot) * n);
    sort(arrayX, arrayX + n, x_);
    sort(arrayY, arrayY + n, y_);

    int x = arrayX[n / 2].x;
    int y = arrayY[n / 2].y;

    dot newDot;
    newDot.x = x;
    newDot.y = y;

    if (n % 2 == 1) {
        // 奇数个
        if (binary_search(arrayX, arrayX + n, newDot, x_)) {
            int tempLengthx = getCount(arrayX, x - 1, y, n);
            int tempLengthy = getCount(arrayX, x, y - 1, n);
            if (tempLengthx == tempLengthy) {
                printf("%d %d\n", tempLengthx, 4);
            } else if (tempLengthx > tempLengthy) {
                printf("%d %d\n", tempLengthy, 2);
            } else {
                printf("%d %d\n", tempLengthx, 2);
            }
        } else {
            int tempLength = getCount(arrayX, x, y, n);
            printf("%d %d\n", tempLength, 1);
        }
    } else {
        x = arrayX[n / 2 - 1].x;
        y = arrayY[n / 2 - 1].y;
        int walkx = arrayX[n / 2].x - x + 1;
        int walky = arrayY[n / 2].y - y + 1;
        int count = walkx * walky;
        int i, j;
        for (i = n / 2; i >= 0; i--) {
            if (arrayX[i].x < x) {
                break;
            }
        }
        for (j = 0; j < n; j++) {
            if (arrayX[j].x > x + walkx) {
                break;
            }
        }
        for (int k = i + 1; k < j; k++) {
            if (arrayX[k].y >= y && arrayX[k].y <= (y + walky)) {
                count--;
            }
        }

        int tempLength = getCount(arrayX, x, y, n);
        printf("%d %d\n", tempLength, count);
    }
    return 0;
}

int getCount(dot *array, int x, int y, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += abs(array[i].x - x);
        count += abs(array[i].y - y);
    }
    return count;
}
