#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::upper_bound;

double *getArray();

int main() {
    double *sum = getArray();
    double num;
    cin >> num;
    while (num - 0.0 > 1e-5) {
        cout << upper_bound(sum, sum + 276, num) - sum + 1 << " card(s)"
             << endl;
        cin >> num;
    }
    return 0;
}

double *getArray() {
    double *sum = new double[276];
    double d = 0.0;
    for (int i = 0; i < 276; i++) {
        d += 1.0 / (i + 2);
        sum[i] = d;
    }
    return sum;
}