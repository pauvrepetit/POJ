#include <iostream>
#define M_PI 3.14159265358979323846

using std::cin;
using std::cout;
using std::endl;

int main() {
    int num;
    double a, b;
    int n;
    cin >> num;
    for (int i = 0; i < num; i++) {
        cin >> a >> b;
        n = M_PI * (a * a + b * b) / 100;
        cout << "Property " << i + 1
             << ": This property will begin eroding in year " << n + 1 << "."
             << endl;
    }
    cout << "END OF OUTPUT.";

    return 0;
}