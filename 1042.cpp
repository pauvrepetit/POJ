#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>

using std::endl;
using std::sort;

class island {
  public:
    int x;
    int y;

    bool operator<(const island &i) const {
        if (this->x == i.x) {
            return this->y > i.y;
        }
        return this->x < i.x;
    }
};

double getx(island isl, int d);
int check(island isl, double radar_x, int d);

int main() {
    int n, d;
    int caseNum = 0;
    while (1) {
        scanf("%d%d", &n, &d);
        if (n == 0) {
            return 0;
        }
        caseNum++;

        island *isl = new island[n];
        for (int k = 0; k < n; k++) {
            scanf("%d%d", &(isl[k].x), &(isl[k].y));
        }

        sort(isl, isl + n);

        int i = 0;
        int j = 0;
        double radar_x = 0;
        int count = 0;
        for (i = 0; i < n; i++) {
            if (isl[i].y > d) {
                count = -1;
                break;
            }
            radar_x = getx(isl[i], d);
            for (j = i; j < n && isl[j].x < radar_x; j++) {
                if (check(isl[j], radar_x, d) == 0) {
                    // out
                    radar_x = getx(isl[j], d);
                    j = i;
                }
            }
            for (; j < n; j++) {
                if (check(isl[j], radar_x, d) == 0) {
                    break;
                }
            }
            i = j - 1;
            count++;
        }

        printf("Case %d: %d\n", caseNum, count);
    }
    return 0;
}

int check(island isl, double radar_x, int d) {
    double xlength = isl.x - radar_x;
    double dis = xlength * xlength + isl.y * isl.y;
    if (dis - d * d > 1e-5) {
        // 点在圆外
        return 0;
    } else {
        return 1;
    }
}

double getx(island isl, int d) {
    double t = d * d - isl.y * isl.y;
    return sqrt(t) + isl.x;
}