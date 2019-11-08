#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>

#define INF 1e308

using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::setiosflags;
using std::setprecision;
using std::sort;
using std::vector;

class Point {
  public:
    int x;
    int y;
    int type;

    Point() {}

    Point(int x_, int y_, int type_) {
        this->x = x_;
        this->y = y_;
        this->type = type_;
    }
};

bool Xsort(Point a, Point b) { return (a.x < b.x); }
bool Ysort(Point a, Point b) { return (a.y < b.y); }

double getMinDistance(vector<Point> pointListX, vector<Point> pointListY, int n);
double getCrossDistance(vector<Point> leftList, vector<Point> rightList, double leftRightMinDistance, int leftSize, int rightSize);
double getDistance(Point p1, Point p2);
double getLineDistance(vector<Point> linePointList, int n);

int main() {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        int x;
        int y;
        vector<Point> pointListX;
        vector<Point> pointListY;
        Point temp;
        for (int j = 0; j < n; j++) {
            cin >> x >> y;
            temp.x = x;
            temp.y = y;
            temp.type = 0;
            pointListX.push_back(temp);
        }
        for (int j = 0; j < n; j++) {
            cin >> x >> y;
            temp.x = x;
            temp.y = y;
            temp.type = 1;
            pointListX.push_back(temp);
        }
        pointListY = pointListX;
        sort(pointListX.begin(), pointListX.end(), Xsort);
        sort(pointListY.begin(), pointListY.end(), Ysort);

        cout << setiosflags(ios::fixed) << setprecision(3) << getMinDistance(pointListX, pointListY, n * 2) << endl;
    }

    return 0;
}

double getMinDistance(vector<Point> pointListX, vector<Point> pointListY, int n) {
    if (n == 0 || n == 1) {
        return INF;
    }
    if (n == 2) {
        return getDistance(pointListX[0], pointListX[1]);
    }

    vector<Point> leftPointListY(n);
    vector<Point> rightPointListY(n);
    vector<Point> leftPointListX(n);
    vector<Point> rightPointListX(n);

    Point minPoint = pointListX[n / 2];
    int flag = 0;
    int firstType = pointListY[0].type;
    int leftY = 0;
    int rightY = 0;
    int leftX = 0;
    int rightX = 0;
    for (int i = 0; i < n; i++) {
        if (firstType != pointListY[i].type) {
            flag = 1;
        }
        if (pointListY[i].x < minPoint.x) {
            leftPointListY[leftY++] = pointListY[i];
        } else {
            rightPointListY[rightY++] = pointListY[i];
        }
        if (pointListX[i].x < minPoint.x) {
            leftPointListX[leftX++] = pointListX[i];
        } else {
            rightPointListX[rightX++] = pointListX[i];
        }
    }
    if (flag == 0) {
        return INF;
    }

    double leftDistance;
    double rightDistance;

    if (leftY == 0 && rightY >= 2) {
        leftDistance = INF;
        rightDistance = getLineDistance(rightPointListY, rightY);
    } else {
        leftDistance = getMinDistance(leftPointListX, leftPointListY, leftY);
        rightDistance = getMinDistance(rightPointListX, rightPointListY, rightY);
    }

    double minLeftRightDistance;
    if (leftDistance > rightDistance) {
        minLeftRightDistance = rightDistance;
    } else {
        minLeftRightDistance = leftDistance;
    }

    double mid = minPoint.x;
    double left = mid - minLeftRightDistance;
    double right = mid + minLeftRightDistance;

    vector<Point> leftLessPoint(leftY);
    vector<Point> rightLessPoint(rightY);

    leftY = 0;
    rightY = 0;

    for (int i = 0; i < leftX; i++) {
        if (leftPointListY[i].x > left) {
            leftLessPoint[leftY++] = leftPointListY[i];
        }
    }
    for (int i = 0; i < rightX; i++) {
        if (rightPointListY[i].x <= right) {
            rightLessPoint[rightY++] = rightPointListY[i];
        }
    }

    double crossDistance = getCrossDistance(leftLessPoint, rightLessPoint, minLeftRightDistance, leftY, rightY);
    if (crossDistance > minLeftRightDistance) {
        return minLeftRightDistance;
    } else {
        return crossDistance;
    }
}

double getCrossDistance(vector<Point> left, vector<Point> right, double leftRightMinDistance, int leftSize, int rightSize) {
    int leftCount = 0;
    int rightCount = 0;
    double minDistance = INF;
    double tempDistance;
    int length = leftSize;
    int rightMax = rightSize;
    if (length == 0 || rightMax == 0) {
        return minDistance;
    }

    for (leftCount = 0; leftCount < length; leftCount++) {
        while (right[rightCount].y < left[leftCount].y - leftRightMinDistance) {
            rightCount++;
            if (rightCount >= rightMax) {
                return minDistance;
            }
        }
        for (int i = 0; (i < 16) && (rightCount + i < rightMax); i++) {
            if ((tempDistance = getDistance(left[leftCount], right[rightCount + i])) < minDistance) {
                minDistance = tempDistance;
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

double getLineDistance(vector<Point> linePointList, int n) {
    double minDistance = INF;
    double tempDistance;
    for (int i = 0; i < n - 1; i++) {
        if ((tempDistance = getDistance(linePointList[i], linePointList[i + 1])) < minDistance) {
            minDistance = tempDistance;
        }
    }
    return minDistance;
}
