#include <iomanip>
#include <iostream>

using std::cin;
using std::cout;
using std::ios;
using std::setiosflags;
using std::setprecision;

int main() {
    double average = 0;
    double a;
    for (int i = 0; i < 12; i++) {
        cin >> a;
        average += a / 12.0;
    }
    cout << "$" << setiosflags(ios::fixed) << setprecision(2) << average;
    // POJ 有毒
    // printf("$%.2lf", average);
    // 报答案错误...
    return 0;
}
