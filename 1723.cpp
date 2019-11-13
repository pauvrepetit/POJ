#include <algorithm>
#include <cstring>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::sort;

int getCountX(int *xArray, int i, int n);

int main() {
    int n;
    cin >> n;
    int *xArray = new int[n];
    int *yArray = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> xArray[i] >> yArray[i];
    }
    sort(xArray, xArray + n);
    sort(yArray, yArray + n);

    int y = yArray[n / 2];
    int count = 0;
    for (int i = 0; i < n / 2; i++) {
        count += (y - yArray[i]);
    }
    for (int i = n / 2; i < n; i++) {
        count += (yArray[i] - y);
    }
    int xCount = 2147483647;
    int temp;
    for (int i = 0; i < n; i++) {
        temp = getCountX(xArray, i, n);
        if(temp < xCount)
            xCount = temp;
    }

    cout << count + xCount << endl;

    return 0;
}

int getCountX(int *xArray, int i, int n) {
    int x = xArray[i];
    int xx;
    int count = 0;
    int temp;
    for (int j = 0; j < n; j++)
    {
        xx = x - (i - j);
        temp = xx - xArray[j];
        if(temp < 0)
            temp = -temp;
        count += temp;
    }
    return count;
}