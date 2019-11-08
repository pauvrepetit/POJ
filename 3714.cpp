#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>

#define INF 1e308
#define INT32_MAX (2147483647)

using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::setiosflags;
using std::setprecision;
using std::sort;

struct Point {
    int x;
    int y;
    int type;
};

bool Xsort(Point a, Point b) { return (a.x < b.x); }
bool Ysort(Point a, Point b) { return (a.y < b.y); }

double getMinDistance(Point *pointListX, Point *pointListY, int n);
double getCrossDistance(Point *crossPointList, int crossPointCount, double leftRightMinDistance);
double getDistance(Point p1, Point p2);
double getLineDistance(Point *linePointList, int n);

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        int x;
        int y;
        Point *pointListX = new Point[n * 2];
        Point *pointListY = new Point[n * 2];
        Point temp;
        for (int j = 0; j < n; j++) {
            scanf("%d%d", &x, &y);
            temp.x = x;
            temp.y = y;
            temp.type = 0;
            pointListX[j] = temp;
        }
        for (int j = 0; j < n; j++) {
            scanf("%d%d", &x, &y);
            temp.x = x;
            temp.y = y;
            temp.type = 1;
            pointListX[j + n] = temp;
        }
        memcpy(pointListY, pointListX, sizeof(Point) * n * 2);
        sort(pointListX, pointListX + n * 2, Xsort);
        sort(pointListY, pointListY + n * 2, Ysort);

        cout << setiosflags(ios::fixed) << setprecision(3) << getMinDistance(pointListX, pointListY, n * 2) << endl;

        delete[] pointListX;
        delete[] pointListY;
    }

    return 0;
}

double getMinDistance(Point *pointListX, Point *pointListY, int n) {
    if (n == 0 || n == 1) {
        return INF;
    }
    if (n == 2) {
        return getDistance(pointListX[0], pointListX[1]);
    }

    Point *leftPointListY = new Point[n];
    Point *rightPointListY = new Point[n];
    Point *midPointListY = new Point[n];

    Point minPoint = pointListX[n / 2];
    int mid = minPoint.x;
    int flag = 0;
    int firstType = pointListY[0].type;
    int leftY = 0;
    int rightY = 0;
    int midY = 0;
    for (int i = 0; i < n; i++) {
        if (firstType != pointListY[i].type) {
            flag = 1;
        }
        if (pointListY[i].x < mid) {
            leftPointListY[leftY++] = pointListY[i];
        } else if (pointListY[i].x > mid) {
            rightPointListY[rightY++] = pointListY[i];
        } else {
            midPointListY[midY++] = pointListY[i];
        }
    }
    if (flag == 0) {
        return INF;
    }
    double leftDistance;
    double rightDistance;
    double midDistance;

    leftDistance = getMinDistance(pointListX, leftPointListY, leftY);
    rightDistance = getMinDistance(pointListX + leftY + midY, rightPointListY, rightY);
    midDistance = getLineDistance(midPointListY, midY);

    double minLeftRightDistance;
    if (leftDistance > rightDistance && midDistance > rightDistance) {
        minLeftRightDistance = rightDistance;
    } else if (rightDistance > leftDistance && midDistance > leftDistance) {
        minLeftRightDistance = leftDistance;
    } else {
        minLeftRightDistance = midDistance;
    }

    double leftMax = mid - minLeftRightDistance;
    double rightMax = mid + minLeftRightDistance;

    Point *crossPointList = new Point[n];
    int crossPointCount = 0;

    leftPointListY[leftY].y = INT32_MAX;
    rightPointListY[rightY].y = INT32_MAX;
    midPointListY[midY].y = INT32_MAX;

    int leftCross = 0;
    int rightCross = 0;
    int midCross = 0;

    while (1) {
        if (leftPointListY[leftCross].y <= rightPointListY[rightCross].y && leftPointListY[leftCross].y <= midPointListY[midCross].y && leftCross < leftY) {
            if (leftPointListY[leftCross].x >= leftMax) {
                crossPointList[crossPointCount++] = leftPointListY[leftCross];
            }
            leftCross++;
        } else if (rightPointListY[rightCross].y <= leftPointListY[leftCross].y && rightPointListY[rightCross].y <= midPointListY[midCross].y &&
                   rightCross < rightY) {
            if (rightPointListY[rightCross].x <= rightMax) {
                crossPointList[crossPointCount++] = rightPointListY[rightCross];
            }
            rightCross++;
        } else if (midPointListY[midCross].y <= leftPointListY[leftCross].y && midPointListY[midCross].y <= rightPointListY[rightCross].y && midCross < midY) {
            crossPointList[crossPointCount++] = midPointListY[midCross++];
        }

        if (leftCross == leftY && rightCross == rightY && midCross == midY) {
            break;
        }
    }

    double crossDistance = getCrossDistance(crossPointList, crossPointCount, minLeftRightDistance);

    delete[] leftPointListY;
    delete[] rightPointListY;
    delete[] crossPointList;

    if (crossDistance > minLeftRightDistance) {
        return minLeftRightDistance;
    } else {
        return crossDistance;
    }
}

double getCrossDistance(Point *crossPointList, int crossPointCount, double leftRightMinDistance) {
    double minDistance = INF;
    double temp;
    for (int i = 0; i < crossPointCount; i++) {
        for (int j = i + 1; (j < i + 10) && (j < crossPointCount); j++) {
            temp = getDistance(crossPointList[i], crossPointList[j]);
            if (temp < minDistance) {
                minDistance = temp;
            }
        }
    }
    return minDistance;
}


double getDistance(Point p1, Point p2) {
    if (p1.type == p2.type) {
        return INF;
    }
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    return sqrt(x * x + y * y);
}

double getLineDistance(Point *linePointList, int n) {
    double minDistance = INF;
    double temp;
    for (int i = 0; i < n - 1; i++) {
        if (linePointList[i + 1].type == linePointList[i].type) {
            temp = INF;
        } else {
            temp = linePointList[i + 1].y - linePointList[i].y;
        }
        if (temp < minDistance) {
            minDistance = temp;
        }
    }
    return minDistance;
}
